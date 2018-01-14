#include "framework.h"


namespace user
{


   tooltip::tooltip(::aura::application * papp):
      ::object(papp),
      m_font(allocer())
   {

      m_font->create_point_font(FONT_SANS_EX,12.0);

      m_bError = false;

   }

   tooltip::~tooltip()
   {
   }



   void tooltip::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }

   void tooltip::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);
   }


   void tooltip::install_message_routing(::message::sender * pinterface)
   {
      ::user::interaction::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE,pinterface,this,&tooltip::_001OnCreate);
      //

   }


   void tooltip::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

      if(pobj->m_bRet)
         return;

   }



   void tooltip::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   bool tooltip::get_translucency(::user::e_translucency  & etranslucency, ::user::e_element eelement, ::user::interaction * pui)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


   void tooltip::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      

      pgraphics->SelectClipRgn(NULL);

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::path_sp path(allocer());

      path->add_move(rectClient.left, rectClient.bottom);

      ::rect rectBody;

      rectBody = rectClient;

      rectBody.left += 16;
      rectBody.bottom -= 16;

      path->add_line(rectBody.left, rectBody.top + rectBody.height()/2);
      path->add_line(rectBody.left,rectBody.top);
      path->add_line(rectBody.right,rectBody.top);
      path->add_line(rectBody.right,rectBody.bottom);
      path->add_line(rectBody.left + rectBody.height() / 2,rectBody.bottom);
      path->end_figure(true);

      ::draw2d::brush_sp b(allocer());

      b->create_solid(ARGB(184,255,255,123));

      pgraphics->SelectObject(b);

      pgraphics->fill_path(path);

      ::draw2d::pen_sp p(allocer());

      pgraphics->SelectObject(p);

      p->create_solid(1.0, ARGB(184,123,123,255));

      pgraphics->draw_path(path);

      pgraphics->set_text_color(ARGB(255,123,123,255));

      //::rect rect;

      //rectText.left = 0;

      //rectText.top = 0;

      //rectText.right = m_size.cx;

      //rectText.bottom = m_size.cy;

      pgraphics->SelectFont(m_font);

      rectBody.offset(4,0);

      pgraphics->draw_text(m_str,rectBody,DT_VCENTER);

   }

   size tooltip::CalcSize()
   {

      stringa stra;

      stra.add_lines(m_str);

      ::size size(0,0);

      ::size sizeLine;

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->selectFont(m_font);

      for(auto strLine : stra)
      {

         sizeLine = g->GetTextExtent(strLine);

         size.cx = MAX(size.cx,sizeLine.cx);

         size.cy += sizeLine.cy;

      }

      size.cx += 16 + 16;
      size.cy += 16 + 16;


      m_size = size;

      return size;

   }


   ::user::interaction::e_type tooltip::get_window_type()
   {

      return type_frame;

   }


} // namespace veritile



