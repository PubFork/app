#include "framework.h"


namespace xml
{


   input_tree::input_tree(::aura::application * papp) :
      object(papp),
      tree_base(papp)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   input_tree::input_tree(::aura::application * papp, tree_schema * pschema) :
      object(papp),
      tree_base(papp, pschema)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   input_tree::~input_tree()
   {

   }

   node * input_tree::import_node(const char * lpcszName, importable & importable)
   {
      node * pnodePrev = m_pnode;
      if(m_pnode == NULL)
      {
         m_pnode = m_pdocument->get_root();
         string strName;
         strName = m_pnode->get_name();
         if(strName != lpcszName)
         {
            m_pnode = NULL;
            _throw(simple_exception(get_app(), "Node not found"));
         }
         importable.xml_import(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnode = m_pnode->get_child(lpcszName);
         m_pnode = pnode;
         importable.xml_import(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }


   node * input_tree::import_node(const char * lpcszName, attr_array & attributea, importable & importable)
   {
      node * pnodePrev = m_pnode;
      if(m_pnode == NULL)
      {
         m_pnode = m_pdocument->get_root();
         if(m_pnode->get_name() != lpcszName)
         {
            ASSERT(FALSE);
            m_pnode = NULL;
            _throw(simple_exception(get_app(), "Node not found"));
         }
         if(!m_pnode->contains(attributea))
            return ((node *) NULL);
         importable.xml_import(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnode = m_pnode->child_at(m_pnode->find(lpcszName, attributea));
         m_pnode = pnode;
         importable.xml_import(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }



   bool input_tree::load_attr(const char * lpcszName, string & strValue)
   {
      return m_pnode->get_attr(lpcszName, strValue);
   }


   bool input_tree::load_attr(const char * lpcszName, int32_t & iValue)
   {
      return m_pnode->get_attr(lpcszName, iValue);
   }

   bool input_tree::load_attr(const char * lpcszName, bool & b)
   {
      int32_t iValue;
      if (!m_pnode->get_attr(lpcszName, iValue))
      {
         return false;
      }
      b = iValue != 0;
      return true;
   }


   bool input_tree::load_attr(const char * lpcszName, double & d)
   {
      string strValue;
      if (!m_pnode->get_attr(lpcszName, strValue))
      {
         return false;
      }
      d = ::strtod(strValue, NULL);
      return true;
   }


   bool input_tree::get_attr(const char * lpcszName, string & strValue, string strDefault)
   {

      if (!load_attr(lpcszName, strValue))
      {

         strValue = strDefault;

         return false;

      }

      return true;

   }

   bool input_tree::get_attr(const char * lpcszName, bool & b, bool bDefault)
   {

      if (!load_attr(lpcszName, b))
      {

         b = bDefault;

         return false;

      }

      return true;

   }

   bool input_tree::get_attr(const char * lpcszName, double & d, double dDefault)
   {

      if (!load_attr(lpcszName, d))
      {

         d = dDefault;

         return false;

      }

      return true;

   }


   bool input_tree::get_attr(const char * lpcszName, int32_t & iValue, int iDefault)
   {

      if (!load_attr(lpcszName, iValue))
      {

         iValue = iDefault;

         return false;

      }

      return true;

   }


   void input_tree::get_value(string & strValue)
   {
      strValue = m_pnode->get_value();
   }


   node * input_tree::import_node(const char * lpcszName, var & var)
   {
      m_varexchange.m_pvar = &var;
      return import_node(lpcszName, m_varexchange);
   }


} // namespace xml


