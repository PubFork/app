#pragma once


namespace dynamic_source
{

   class script;
   class script_instance;
   class script_manager;

   typedef   script_instance * (*NET_NODE_CREATE_INSTANCE_PROC)(script * pscript);


   class CLASS_DECL_PROGRAMMING script :
      virtual public ::object
   {
   public:


      sp(script_manager)                        m_pmanager;
      string                                    m_strName;
      ::file::plain_text_stream_memory_file     m_memfileError;
      string                                    m_strError;


      script(::aura::application * papp);
      virtual ~script();


      virtual script_instance * create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();


   };


   class CLASS_DECL_PROGRAMMING ds_script :
      virtual public script
   {
   public:


      sp(::aura::library)              m_plibrary;


      file_time                        m_ft;
      file_time                        m_ftDs;

      bool                             m_bLastVersionCheck;
      uint32_t                         m_dwLastVersionCheck;
      ::file::path                     m_strSourcePath;
      ::file::path                     m_strSourceDir;
      ::file::path                     m_strCppPath;
      ::file::path                     m_strScriptPath;
      //::file::path                     m_strBuildBat;
      manual_reset_event               m_evCreationEnabled;
      uint32_t                         m_dwLastBuildTime;
      bool                             m_bShouldBuild;
      bool                             m_bShouldCalcTempError;
      bool                             m_bHasTempError;
      bool                             m_bHasTempOsError;
      bool                             m_bUnloading;
      NET_NODE_CREATE_INSTANCE_PROC    m_lpfnCreateInstance;


      ds_script(::aura::application * papp);
      ~ds_script();


      virtual void defer_build();
      virtual void on_start_build();

      bool DoesMatchVersion();
      bool ShouldBuild();
      bool HasCompileOrLinkError();
      bool HasTempError();
      bool CalcHasTempError();
      bool HasDelayedTempError();
      bool HasTimedOutLastBuild();
      void Load();
      void Unload();

      string get_stage_path();


      sp(::aura::application) get_app() const;

      script_instance * create_instance();


   };

   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script(::aura::application * papp) :
         ::object(papp),
         script(papp)
      {
      };


      virtual script_instance * create_instance()
      {
         return new T(this);
      }

   };


} // namespace dynamic_source


