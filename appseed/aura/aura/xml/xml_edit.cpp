#include "framework.h"


namespace xml
{


   edit_item::edit_item(::aura::application * papp) :
      object(papp)
   {
   }


   void edit_item::set_name(const sp(::xml::node) pnode)
   {

      m_eaction      = ::xml::set_name;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pnode->get_name();

   }

   void edit_item::set_value(const sp(::xml::node) pnode)
   {

      m_eaction      = ::xml::set_value;
      pnode->get_indexed_path(m_iaPath);
      m_strValue     = pnode->get_value();

   }

   void edit_item::set_attr(const sp(::xml::node) pnode, const attr * pattr)
   {

      m_eaction      = ::xml::set_attr;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->get_value();

   }

   void edit_item::add_attr(const sp(::xml::node) pnode, const attr * pattr)
   {

      m_eaction      = ::xml::add_attr;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->get_value();

   }

   void edit_item::stream(serialize & serialize)
   {

      serialize((int32_t &) m_eaction);
      serialize.stream_array(m_iaPath);
      serialize(m_strName);
      serialize(m_strValue);

   }


   edit::edit(::aura::application * papp) :
      object(papp),
      ::edit < ::xml::document > (papp)
   {

      m_iEdit = -1;

   }

   edit::~edit()
   {
   }


   void edit::set_name(const sp(::xml::node) pnode)
   {

      if(pnode->get_document() != m_spdata.m_p)
         _throw(simple_exception(get_app(), "unmatched xml document"));

      edit_item * pitem = add_new();

      pitem->set_name(pnode);

   }

   void edit::set_value(const sp(::xml::node) pnode)
   {

      if(pnode->get_document() != m_spdata.m_p)
         _throw(simple_exception(get_app(), "unmatched xml document"));

      edit_item * pitem = add_new();

      pitem->set_value(pnode);

   }

   void edit::set_attr(const sp(::xml::node) pnode, const ::xml::attr * pattr)
   {

      if(pnode->get_document() != m_spdata.m_p)
         _throw(simple_exception(get_app(), "unmatched xml document"));

      edit_item * pitem = add_new();

      pitem->set_attr(pnode, pattr);

   }


   void edit::add_attr(const sp(::xml::node) pnode, const ::xml::attr * pattr)
   {

      if(pnode->get_document() != m_spdata.m_p)
         _throw(simple_exception(get_app(), "unmatched xml document"));

      edit_item * pitem = add_new();

      pitem->add_attr(pnode, pattr);

   }



} // namespace xml



