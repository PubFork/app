#pragma once


class html_document;


namespace html
{


   class data;


   class message :
      public ::message::message
   {
   public:


      ::html::data *                m_pdata;
      ::message::message *          m_psignal;
      sp(::user::interaction)       m_pui;


      message(::aura::application * papp = NULL);


   };


} // namespace html






