#include "framework.h"

namespace xml
{

   output_tree::output_tree(::aura::application * papp) :
      object(papp),
      tree_base(papp)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   output_tree::output_tree(::aura::application * papp, tree_schema * pschema) :
      object(papp),
      tree_base(papp, pschema)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   output_tree::~output_tree()
   {
   }

   node * output_tree::export_node(const char * lpcszName, exportable & exportable)
   {
      if(m_pnode == NULL)
      {
         if(m_pdocument == NULL)
         {
            _throw(::simple_exception(get_app(), "Cannot output to a NULL document"));
         }
         m_pnode = m_pdocument->get_root();
         m_pnode->set_name(lpcszName);
         exportable.xml_export(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnodePrev = m_pnode;
         node * pnode = m_pnode->add_child(lpcszName);
         m_pnode = pnode;
         exportable.xml_export(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }

   node * output_tree::export_node(exportable & exportable)
   {
      return export_node("", exportable);
   }


   node * output_tree::export_node(const char * lpcszName, var var)
   {
      m_varexchange.m_pvar = &var;
      return export_node(lpcszName, m_varexchange);
   }

   void output_tree::set_attr(const char * lpcszName, const char * lpcszValue, bool bOptional)
   {
      if ((lpcszValue == NULL || *lpcszValue == '\0') && bOptional)
         return;
      m_pnode->set_attr(lpcszName, lpcszValue);
   }

   void output_tree::set_attr(const char * lpcszName, int64_t iValue, bool bOptional)
   {
      if (iValue == 0 && bOptional)
         return;
      m_pnode->set_attr(lpcszName, iValue);
   }

   void output_tree::set_bool_attr(const char * lpcszName, bool bValue, bool bOptional)
   {
      if (!bValue && bOptional)
      {
         return;
      }
      m_pnode->set_attr(lpcszName, bValue ? 1 : 0);
   }

   void output_tree::set_double_attr(const char * lpcszName, double dValue)
   {
      m_pnode->set_attr(lpcszName, ::str::from(dValue));
   }

   void output_tree::set_value(const char * lpcszValue)
   {
      m_pnode->set_value(lpcszValue);
   }

   void output_tree::SetNodeName(const char * lpcszName)
   {
      m_pnode->set_name(lpcszName);
   }

} // namespace xml
