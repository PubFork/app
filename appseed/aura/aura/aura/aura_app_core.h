#pragma once


class raw_fail
{
public:

   raw_fail() {}
   ~raw_fail() {}

};

class CLASS_DECL_AURA aura_aura
{
public:

   aura_aura()
   {

      if (!defer_aura_init())
      {

         throw raw_fail();

      }

   }

   ~aura_aura()
   {

      defer_aura_term();

   }

};

class CLASS_DECL_AURA aura_main_data :
   virtual public object
{
public:

   ::command::command *          m_pmaininitdata;
   bool                          m_bConsole;
   int                           m_argc;
   char **                       m_argv;
   int                           m_iExitCode;
   stringa                       m_straCommandLine;

#ifdef WINDOWS

   HINSTANCE                     m_hinstance;
   HINSTANCE                     m_hPrevInstance;
   int32_t                       m_nCmdShow;

#endif

   aura_main_data(int argc, char ** argv);
#ifdef WINDOWSEX
   aura_main_data(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);
#endif
   aura_main_data(LPTSTR lpCmdLine);
   ~aura_main_data();


};


#define APP_CORE_MAXIMUM_ERROR_COUNT 100


// ATTENTION
// This class should (if it uses) member functions with care:
// It is used after all application app_core (library) finalization,
// when even new/delete/strings/ids can be used anymore for example.

class CLASS_DECL_AURA app_core :
   virtual public object
{
public:


   static app_core *             s_pappcore;
   string                        m_strCommandLine;
   bool                          m_bAcidApp = false;
   ::aura::PFN_GET_NEW_LIBRARY   m_pfnNewLibrary = NULL;
   ::aura::PFN_GET_NEW_APP       m_pfnNewApp = NULL;
   DWORD                         m_dwStartTime;
   DWORD                         m_dwAfterApplicationFirstRequest;
   sp(aura_main_data)            m_pmaindata;
   ::aura::system *              m_psystem = NULL;
   string                        m_strAppId;

   int                           m_iaError[APP_CORE_MAXIMUM_ERROR_COUNT];
   int                           m_iErrorCount = 0;
   int                           m_iTotalErrorCount = 0;


   app_core(aura_main_data * pdata);
   ~app_core();

   bool on_result(int iResultCode);

   bool beg();

   bool ini();

   virtual void defer_load_backbone_libraries(string strAppId);

   void run();

   void end();

};

typedef bool FN_AURA_APP_CORE(app_core * pappcore);

typedef FN_AURA_APP_CORE * PFN_AURA_APP_CORE;

CLASS_DECL_AURA long aura_aura(aura_main_data * pmaindata);

CLASS_DECL_AURA void aura_boot(app_core * pappcore);

CLASS_DECL_AURA void aura_main(app_core * pappcore);

CLASS_DECL_AURA bool node_fill(app_core * pappcore);


class CLASS_DECL_AURA aura_prelude
{
public:


   static aura_prelude *         s_pprelude;

   ::aura::PFN_GET_NEW_APP       m_pfnNewApp;


   aura_prelude();


   aura_prelude(::aura::PFN_GET_NEW_APP pgetnewapp);


   virtual ~aura_prelude();


   static bool defer_call_construct(app_core * pappcore);

   virtual bool construct(app_core * pappcore);


   static bool defer_call_prelude(app_core * pappcore);


   virtual bool prelude(app_core * pappcore);


};


CLASS_DECL_AURA string transform_to_c_arg(const char * psz);
CLASS_DECL_AURA stringa get_c_args(const char * psz);
CLASS_DECL_AURA stringa get_c_args(int argc, char ** argv);
CLASS_DECL_AURA string ca2_command_line();
