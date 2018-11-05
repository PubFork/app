#include "framework.h"
//#include <stdarg.h>

namespace xml
{


   document::document(::aura::application * papp, parse_info * pparseinfo) :
      object(papp != NULL ? papp : get_app()),
      node(papp != NULL ? papp : get_app()),
      data(papp != NULL ? papp : get_app())
   {

      m_pdoc         = this;
      m_pparseinfo   = pparseinfo != NULL ? pparseinfo : System.xml().m_pparseinfoDefault;
      m_pedit        = NULL;

      entitiesHash.set_at("lt", "<");
      entitiesHash.set_at("gt", ">");
      entitiesHash.set_at("quot", "\"");
      entitiesHash.set_at("apos", "'");
      entitiesHash.set_at("amp", "&");


   }

   document::~document()
   {
   }


   document & document::operator = (const document & document)
   {
      if(this == &document)
         return *this;
      *get_root() = *document.get_root();
      return *this;
   }

   bool document::load_location(const char * psz)
   {

      m_pathLocation = psz;
      string str;
      str = Session.file().as_string(psz);
      return load(str);

   }

   bool document::load(serialize & s)
   {

      memory memory;

      s.stream_object(memory);

      return load(memory.to_string());

   }

   // <?xml version='1.0'?>
   // <TAG attr1="value1" attr2='value2' attr3=value3 >
   // </TAG>
   // or
   // <TAG />
   //        ^- return pointer
   //========================================================
   // Name   : Load
   // Desc   : load xml plain text for xml document
   // Param  : pszXml - plain xml text
   //          pparseinfo = parser information
   // Return : advanced string pointer  (error return NULL)
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   bool document::load(const char * psz)
   {

      m_nodea.remove_all();

      m_strData = psz;
      const char * pszXml = m_strData;
      sp(::xml::node) pnodeRoot = canew(class node(this));
      pnodeRoot->m_pnodeParent = (node *)this;
      pnodeRoot->m_etype = node_element;
      pnodeRoot->m_pdoc = this;
      char * end;

      if((end = pnodeRoot->load( pszXml, m_pparseinfo )) == NULL)
      {
         pnodeRoot.release();
         return false;
      }

      m_nodea.add(pnodeRoot);

      // Load Other Node after </Tag>(pparseinfo, comment, CDATA etc)
      char * ret;
      bool bRet = false;
      ret = pnodeRoot->LoadOtherNodes(&bRet, end, m_pparseinfo);
      if( ret != NULL )
         end = ret;

      return end != NULL;

   }

   node * document::get_root() const
   {

      index i = 0;

      for( ; i < m_nodea.get_size(); i++)
      {

         ::xml::node & node = *m_nodea[i].m_p;

         e_node e_type = node.m_etype;

         if(e_type == node_element || e_type == node_text)
            return m_nodea[i];

      }

      // Not found: create one.
      sp(::xml::node) pnodeRoot = canew(class node(get_app()));
      pnodeRoot->m_pnodeParent = (node *)this;
      pnodeRoot->m_etype = node_element;
      pnodeRoot->m_pdoc = ((document *)this);
      ((document *)this)->m_nodea.add(pnodeRoot);

      return pnodeRoot;

   }


   string document::consume_entity_ref(const char * & pszXmlParam, string & strName, bool useExtEnt, bool & bExt)
   {

      const char * pszXml = pszXmlParam;

      if(*pszXml == '\0')
      {

         _throw(simple_exception(get_app(), "No Entity"));

      }

      ::str::consume(pszXml, "&");

      strName.Empty();

      while(*pszXml != ';')
      {

         if(*pszXml == '\0'
         || *pszXml == '<'
         || *pszXml == '>'
         || *pszXml == ' '
         || *pszXml == '\n'
         || *pszXml == '\r'
         || *pszXml == ','
         || *pszXml == '.'
         || *pszXml == '=')
         {

            _throw(simple_exception(get_app(), "Not expected character on Entity Reference"));

         }

         strName += *pszXml;

         pszXml = ::str::utf8_inc(pszXml);

      }

      pszXml++;

      string ent = entitiesHash[strName];

      string extEnt;

      if (useExtEnt)
      {

         extEnt = extEntitiesHash[strName];

      }

      if(ent.is_empty() && extEnt.is_empty() && (strName.is_empty() || strName[0] != '#'))
      {

         _throw(simple_exception(get_app(), "Undefined Entity Reference"));

      }

      if(ent.has_char())
      {

         bExt = false;

         pszXmlParam = pszXml;

         return ent;

      }

      if(extEnt.has_char())
      {

         bExt = true;

         pszXmlParam = pszXml;

         return Session.file().as_string(m_pathLocation.sibling(extEnt));

      }

      string strEntityReference(pszXmlParam, pszXml - pszXmlParam);

      if(::str::begins_eat_ci(strEntityReference, "&#"))
      {

         int i = atoi(strEntityReference);

         wchar_t wsz[2];

         wsz[0] = i;
         wsz[1] = L'\0';

         strEntityReference = wsz;

      }

      pszXmlParam = pszXml;

      return strEntityReference;

   }


   // the additional parameter must end with , NULL
   // the parameters are pointers based on m_strData that should be offset because m_strData will be edited by entity ref patch
   char * document::patch_entity_ref(const char * & pszXml, int bUseExtEnt, ...)
   {

      // pszXml must be a valid portion of and point to an entity ref in:
      // m_strData of this document

      const char * pszOldData = m_strData;

      strsize iPos = pszXml - pszOldData;

      ASSERT(iPos < m_strData.get_length() && iPos >= 0);

      string strName;

      bool bExt = false;

      string strValue = pszXml[0];

      try
      {

         strValue = consume_entity_ref(pszXml, strName, bUseExtEnt, bExt);

      }
      catch(...)
      {

         pszXml++;

      }


      m_strData = m_strData.Left(iPos) + strValue + m_strData.Mid(iPos + strName.get_length() + 2);

      strsize iOffset = ((const char *)m_strData) - pszOldData;

      va_list ptr;

      va_start(ptr, bUseExtEnt);

      int_ptr p;

      while((p = va_arg(ptr, int_ptr)) != 0)
      {

         const char ** ppch = (const char **) p;

         if(*ppch <= (pszOldData + iPos))
         {

            *ppch += iOffset;

         }
         else if(*ppch >= (pszOldData + iPos + strName.get_length() + 2))
         {

            *ppch += iOffset + strValue.get_length() - strName.get_length() - 2;

         }
         else
         {

            _throw(simple_exception(get_app(), "pointer to be offset cannot lie inside the entity ref"));

         }

      }

      va_end(ptr);

      return (char *) &((const char *)m_strData)[iPos + (bExt ? 0 : strValue.get_length())];

   }


   void document::io(stream & stream)
   {

      ::xml::node::io(stream);

   }


   void document::edit(base_edit * pbaseedit)
   {

      sp(::xml::edit) pedit = validate_edit(pbaseedit);


      if(pedit == NULL)
         _throw(simple_exception(get_app(), "edit exception"));


      sp(::xml::node) pnode;
//      ::xml::attr * pattr;


      for(index iEdit = pedit->m_iEdit; iEdit < pedit->get_count(); iEdit++)
      {

         ::xml::edit_item * pitem = pedit->element_at(iEdit);

         try
         {

            switch(pitem->m_eaction)
            {

            case ::xml::set_name:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if(pnode == NULL)
                  return;
               pnode->set_name(pitem->m_strValue);
            }
            break;

            case ::xml::set_value:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if(pnode == NULL)
                  return;
               pnode->set_value(pitem->m_strValue);
            }
            break;

            case ::xml::set_attr:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if(pnode == NULL)
                  return;
               pnode->set_attr(pitem->m_strName,pitem->m_strValue);
            }
            break;

            case ::xml::add_attr:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if(pnode == NULL)
                  return;
               pnode->add_attr(pitem->m_strName, pitem->m_strValue);
            }
            break;

            }

         }
         catch(...)
         {
            break;
         }

         pedit->m_iEdit = iEdit;
      }



   }


} // namespace xml



