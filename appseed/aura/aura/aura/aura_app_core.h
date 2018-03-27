#pragma once


typedef int_bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;


class node_data_exchange;


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


   node_data_exchange *          m_pnodedataexchange;
   ::command::command *          m_pmaininitdata;
   bool                          m_bConsole;
   int                           m_argc;
   char **                       m_argv;
   int                           m_iExitCode;
   string                        m_strCommandLine;
   sp(app_core)                  m_pappcore;



#ifdef WINDOWS

   HINSTANCE                     m_hinstance;
   HINSTANCE                     m_hPrevInstance;
   int32_t                       m_nCmdShow;

#endif


   aura_main_data(int argc, char ** argv);
#ifdef WINDOWSEX
   aura_main_data(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);
#elif defined(METROWIN)
   aura_main_data(Array < String ^ > ^ refstra);
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

   static app_core *             s_pappcoreMain;
   static app_core *             s_pappcore;
   string                        m_strCommandLine;
   string                        m_strProgName;
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


#ifdef LINUX

   bool                          m_bGtkApp;

#endif

   app_core(aura_main_data * pdata);
   ~app_core();

   bool on_result(int iResultCode);

   void main();

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
   ::aura::PFN_GET_NEW_LIBRARY   m_pfnNewLibrary;


   aura_prelude();


   aura_prelude(::aura::PFN_GET_NEW_APP pgetnewapp);


   aura_prelude(::aura::PFN_GET_NEW_LIBRARY pgetnewlibrary);


   virtual ~aura_prelude();


   static bool defer_call_construct(app_core * pappcore);

   virtual bool construct(app_core * pappcore);


   static bool defer_call_prelude(app_core * pappcore);


   virtual bool prelude(app_core * pappcore);


};


CLASS_DECL_AURA string transform_to_c_arg(const char * psz);
CLASS_DECL_AURA stringa get_c_args(const char * psz);
CLASS_DECL_AURA stringa get_c_args_for_c(const char * psz);
CLASS_DECL_AURA stringa get_c_args(int argc, char ** argv);
CLASS_DECL_AURA string ca2_command_line();



class CLASS_DECL_AURA aura_level
{
public:


   enum e_level
   {
      level_aura,
      level_axis,
      level_base,
      level_core,
   };


   e_level                    m_elevel;
   PFN_DEFER_INIT             m_pfnDeferInit;
   aura_level *               m_plevelNext;


   static aura_level *        s_plevel;


   aura_level(e_level elevel, PFN_DEFER_INIT pfnDeferInit);

   static aura_level * get_maximum_level();

   static aura_level * find_level(PFN_DEFER_INIT pfnDeferInit);

   static bool defer_init();

   static bool defer_init(PFN_DEFER_INIT pfnDeferInit);



};



class CLASS_DECL_AURA aura_app
{
public:


   enum e_flag
   {
      flag_none,
      flag_do_not_install = 4096,

   };


   const char *                  m_pszName;
   ::aura::PFN_GET_NEW_APP       m_pfnNewApp;
   ::aura::PFN_GET_NEW_LIBRARY   m_pfnNewLibrary;
   e_flag                        m_eflag;


   aura_app *                    m_pappNext;


   static aura_app *             s_papp;


   aura_app(::aura_app::e_flag eflag);
   aura_app(const char * pszName, ::aura::PFN_GET_NEW_APP pfnNewApp);
   aura_app(const char * pszName, ::aura::PFN_GET_NEW_LIBRARY pfnNewLibrary);

   static ::aura_app * get(const char * pszName);

   static bool should_install();

};

