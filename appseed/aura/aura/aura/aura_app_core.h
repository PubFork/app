#pragma once


typedef int_bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;
typedef int_bool DEFER_TERM();
typedef DEFER_TERM * PFN_DEFER_TERM;


class STRLANGMAP
{
public:

   int      m_iPo;
   char *   m_pszLanguageCode;

};



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


   int                           m_iPathInstallFolderExeArg;
   STRLANGMAP *                  m_pstrlangmap;
   bool                          m_bFork;
   node_data_exchange *          m_pnodedataexchange;
   ::command::command *          m_pmaininitdata;
   bool                          m_bConsole;
   int                           m_argc;
   char **                       m_argv;
   int                           m_iExitCode;
   string                        m_strCommandLine;
   sp(app_core)                  m_pappcore;
   string                        m_strStandalone;



#ifdef WINDOWS

   HINSTANCE                     m_hinstance;
   HINSTANCE                     m_hPrevInstance;
   int32_t                       m_nCmdShow;

#elif defined(LINUX)

   bool                          m_bGtkApp;

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

   //static app_core *             s_pappcoreMain;
   //static app_core *             s_pappcore;
   string                        m_strCommandLine;
   string                        m_strProgName;
   bool                          m_bAcidApp;
   ::aura::PFN_GET_NEW_LIBRARY   m_pfnNewLibrary;
   ::aura::PFN_GET_NEW_APP       m_pfnNewApp;
   PFN_DEFER_TERM                m_pfnDeferTerm;
   DWORD                         m_dwStartTime;
   DWORD                         m_dwAfterApplicationFirstRequest;
   sp(aura_main_data)            m_pmaindata;
   ::aura::system *              m_psystem;
   string                        m_strAppId;
   int                           m_iMatterFromHttpCache;



   int                           m_iaError[APP_CORE_MAXIMUM_ERROR_COUNT];
   int                           m_iErrorCount;
   int                           m_iTotalErrorCount;



   app_core(aura_main_data * pdata);
   app_core(aura_main_data * pdata, ::aura::PFN_GET_NEW_APP pgetnewapp);
   app_core(aura_main_data * pdata, ::aura::PFN_GET_NEW_LIBRARY pgetnewlibrary);
   app_core(aura_main_data * pdata, ::aura::PFN_GET_NEW_APP pgetnewapp, ::aura::PFN_GET_NEW_LIBRARY pgetnewlibrary);
   ~app_core();


   void app_core_common_construct(aura_main_data * pdata, ::aura::PFN_GET_NEW_APP pgetnewapp, ::aura::PFN_GET_NEW_LIBRARY pgetnewlibrary);


   bool on_result(int iResultCode);

   void main();

   static DWORD WINAPI MAIN(LPVOID pvoid);

   bool beg();

   bool ini();

   virtual void defer_load_backbone_libraries(string strAppId);
   virtual void defer_unload_backbone_libraries();

   void run();

   void set_command_line(const char * psz);

   string get_command_line();

   void end();

};

typedef bool FN_AURA_APP_CORE(app_core * pappcore);

typedef FN_AURA_APP_CORE * PFN_AURA_APP_CORE;

CLASS_DECL_AURA long aura_aura(aura_main_data * pmaindata);

CLASS_DECL_AURA long aura_aura(aura_main_data * pmaindata, ::aura::PFN_GET_NEW_APP pfnNewApp);

CLASS_DECL_AURA long aura_aura(aura_main_data * pmaindata, ::aura::PFN_GET_NEW_LIBRARY pfnNewLibrary);

CLASS_DECL_AURA long _aura_aura(aura_main_data * pmaindata, ::aura::PFN_GET_NEW_APP pfnNewApp, ::aura::PFN_GET_NEW_LIBRARY pfnNewLibrary);

CLASS_DECL_AURA void aura_boot(app_core * pappcore);

CLASS_DECL_AURA void aura_main(app_core * pappcore);

CLASS_DECL_AURA bool node_fill(app_core * pappcore);


//aura_prelude();


//   aura_prelude();
//
//
//   virtual ~aura_prelude();
//
//
//   static bool defer_call_construct(app_core * pappcore);
//
//   virtual bool construct(app_core * pappcore);
//
//
//   static bool defer_call_prelude(app_core * pappcore);
//
//
//   virtual bool prelude(app_core * pappcore);
//
//
//};
//

CLASS_DECL_AURA string transform_to_c_arg(const char * psz);
CLASS_DECL_AURA stringa get_c_args(const char * psz);
CLASS_DECL_AURA stringa get_c_args_for_c(const char * psz);
CLASS_DECL_AURA stringa get_c_args(int argc, char ** argv);
#ifdef WINDOWS
CLASS_DECL_AURA string ca2_command_line(HINSTANCE hinstance);
#else
CLASS_DECL_AURA string ca2_command_line();
#endif




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

