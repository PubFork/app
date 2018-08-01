#pragma once


namespace html_lite
{


   class CLASS_DECL_AXIS application :
      virtual public ::aura::application
   {
   public:


      application();
      virtual ~application();


      inline ::html::html * html() { return m_papp->m_psystem->m_phtml; }

      virtual ::html::html * create_html();

      //DECL_GEN_SIGNAL(on_application_signal);


   };


} // namespace html_lite





