#pragma once


namespace aura
{


   class CLASS_DECL_AURA application_ptra:
      virtual public spa(application)
   {
   public:


      application_ptra(::aura::application * papp);
      application_ptra(const application_ptra & a);
#if defined(MOVE_SEMANTICS)
      application_ptra(application_ptra && a);
#endif
      virtual ~application_ptra();
      
      
      application_ptra & operator = (const application_ptra & a);
#if defined(MOVE_SEMANTICS)
      application_ptra & operator = (application_ptra && a);
#endif

      application * find_by_app_name(string strAppName);

      application * find_running_defer_try_quit_damaged(string strAppName);

      bool lookup(string strAppName, sp(::aura::application) & papp);


   };


} // namespace aura



