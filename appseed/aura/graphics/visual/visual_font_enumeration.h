#pragma once


namespace visual
{


   class CLASS_DECL_AURA font_enumeration :
      virtual public object
   {
   public:


      int                                       m_iUpdateId;
      sp(::draw2d::font::enum_item_array)       m_pitema;


      font_enumeration(::aura::application * papp);
      virtual ~font_enumeration();


      virtual bool check_need_update();


   };


} // namespace visual



