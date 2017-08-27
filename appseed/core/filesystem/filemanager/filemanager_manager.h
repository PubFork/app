#pragma once


namespace filemanager
{

   

   
   class CLASS_DECL_CORE manager :
      virtual public ::file_watcher::file_watch_listener,
      virtual public ::userfs::document
   {
   public:

      enum e_hint
      {

         hint_none,
         hint_add_location = 1000,
         hint_replace_name,
         hint_new_folder,

      };

      enum e_mode
      {
         mode_normal,
         mode_saving,
         mode_import,
         mode_export,

      };


      sp(::filemanager::data)             m_spfilemanagerdata;
      sp(::fs::item)                      m_item;
      ::critical_section                  m_csItemIdListAbsolute;
      ::file::path                        m_strTopic;
      bool                                m_bFullBrowse;
      string                              m_strManagerId;
      e_mode                              m_emode;
      //bool                                m_bInitialBrowsePath;


      manager(::aura::application * papp);
      virtual ~manager();

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }

      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual ::fs::data *                         get_fs_data();
      virtual ::fs::item *                         get_filemanager_item();
      virtual ::filemanager::data *                get_filemanager_data();
      virtual ::filemanager::manager_template *    get_filemanager_template();

      virtual manager * get_main_manager();

      DECL_GEN_SIGNAL(_001OnLevelUp);
      DECL_GEN_SIGNAL(_001OnUpdateLevelUp);
      DECL_GEN_SIGNAL(_001OnAddLocation);
      DECL_GEN_SIGNAL(_001OnUpdateAddLocation);
      DECL_GEN_SIGNAL(_001OnReplaceText);
      DECL_GEN_SIGNAL(_001OnUpdateReplaceText);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnFileSaveAs);
      DECL_GEN_SIGNAL(_001OnUpdateFileSaveAs);
      DECL_GEN_SIGNAL(_001OnFileImport);
      DECL_GEN_SIGNAL(_001OnUpdateFileImport);
      DECL_GEN_SIGNAL(_001OnFileExport);
      DECL_GEN_SIGNAL(_001OnUpdateFileExport);
      DECL_GEN_SIGNAL(_001OnNewManager);
      DECL_GEN_SIGNAL(_001OnUpdateNewManager);
      DECL_GEN_SIGNAL(_001OnDelManager);
      DECL_GEN_SIGNAL(_001OnUpdateDelManager);
      DECL_GEN_SIGNAL(_001OnNewFolder);
      DECL_GEN_SIGNAL(_001OnUpdateNewFolder);

      virtual void defer_check_manager_id(string strNewManagerId = "");

      ::critical_section * GetItemIdListCriticalSection();

      virtual bool FileManagerBrowse(::fs::item * pitem, ::action::context actioncontext);
      virtual bool FileManagerBrowse(const char * lpcsz, ::action::context actioncontext);

      virtual void FileManagerOneLevelUp(::action::context actioncontext);
      virtual void OnFileManagerBrowse(::action::context actioncontext);
      virtual void OpenSelectionProperties();

      virtual void GetActiveViewSelection(::fs::item_array & itema);


      virtual void FileManagerSaveAs(::user::document * pdocument);
      virtual void FileManagerImport(::user::document * pdocument);
      virtual void FileManagerExport(::user::document * pdocument);
      virtual void FileManagerTopicOK();
      virtual void FileManagerTopicCancel();



      virtual void handle_file_action(::file_watcher::file_watch_id watchid, const char * dir, const char * filename, ::file_watcher::e_action action) override;


      string calc_data_key(::database::id & id);

      virtual void on_create(::create * pcreate);


      operation_document * get_operation_doc(bool bSwitch);


      virtual void on_command(::user::command * pcommand) override;
      virtual void on_command_probe(::user::command * pcommand) override;

      virtual bool on_new_document();
      virtual bool on_open_document(var varFile);

      virtual bool HandleDefaultFileManagerItemCmdMsg(::user::command * pcommand,::fs::item_array & itema);

      void PopViews();
      void CreateViews();
      void OpenFolder(::fs::item * item,::action::context actioncontext);
      void Initialize(bool bMakeVisible, bool bInitialBrowsePath = true);
      void Initialize(bool bMakeVisible, const ::file::path & path);


      bool set_filemanager_data(::filemanager::data * pdata);

      virtual bool on_create_bars(simple_frame_window * pframe);


      virtual void start_full_browse(string strPath, ::action::context actioncontext);
      virtual void full_browse(string strPath, ::action::context actioncontext);

   };

   
   CLASS_DECL_CORE int get_manager_id_byte_len();

   CLASS_DECL_CORE int get_manager_id_len();

   CLASS_DECL_CORE string create_manager_id(::aura::application * papp);

   CLASS_DECL_CORE bool is_valid_manager_id(const char *);

   CLASS_DECL_CORE bool is_valid_filemanager_project_entry(const char *);

   CLASS_DECL_CORE ::file::path get_filemanager_project_entry(string & strManagerId, const char * psz, ::aura::application * papp);


} // namespace filemanager




