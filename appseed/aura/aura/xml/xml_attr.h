#pragma once


namespace xml
{


   class node;


   typedef property attr;


   class CLASS_DECL_AURA attr_array :
      public property_set
   {
   protected:



      friend class node;


      node *      m_pnodeParent;


   public:

      attr_array(::std::initializer_list < var > list);
      attr_array(::aura::application * papp);


      ::xml::attr * add_attr(const id & idName);

   };




} // namespace xml

