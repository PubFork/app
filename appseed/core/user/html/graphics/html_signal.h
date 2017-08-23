#pragma once


class html_document;


namespace html
{


   class data;


   class signal :
      public ::message::message
   {
   public:


      ::html::data *             m_pdata;
      ::message::message *           m_psignal;
      sp(::user::interaction)    m_pui;


      signal(class ::message::sender * psignal);


   };


} // namespace html






