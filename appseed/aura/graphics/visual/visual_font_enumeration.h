#pragma once


namespace visual
{


   class CLASS_DECL_AURA font_enumeration :
      virtual public object
   {
   public:


      ::draw2d::font::enum_item_array     m_itema;


      font_enumeration(::aura::application * papp);

      virtual ~font_enumeration();

      template < typename PRED >
      void start_update(PRED predRunAfterEnumeration = []() {})
      {

         fork([&]()
         {

            update();

            predRunAfterEnumeration();

         });

      }


      void update();

   };



} // namespace visual



