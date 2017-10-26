#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list :
      virtual public ::userfs::list,
      virtual public ::filemanager::impact
   {
   public:


      enum e_message
      {

         MessageMainPost = WM_USER + 23,

      };


      enum EMessageMainPost
      {

         MessageMainPostCreateImageListItemStepSetRedraw,
         MessageMainPostCreateImageListItemRedraw,

      };


      class file_size
      {
      public:
         
         file_list * m_pview;
         
         string m_str;

      };

      context_menu                     m_contextmenu;
      stringa                          m_straOpenWith;
      bool                             m_bFileSize;
      bool                             m_bShow;
      uint32_t                         m_dwLastFileSize;
      index                            m_iNameSubItem;
      index                            m_iNameSubItemText;
      index                            m_iSelectionSubItem;
      index                            m_iSizeSubItem;
      bool                             m_bPendingSize;
      uint32_t                         m_dwLastFileSizeGet;


      map < icon_key,const icon_key &,icon,icon & > m_iconmap;

#ifdef WINDOWSEX
      IShellFolder *                   m_pshellfolder;
#endif
      bool                             m_bCreateImageList;
      bool                             m_bCreateImageListRedraw;
      index                            m_iAnimate;
      int64_t                          m_iCreateImageListStep;
      uint32_t                         m_dwLastRedraw;
      bool                             m_bRestartCreateImageList;
      bool                             m_bStatic;


      file_list(::aura::application * papp);
      virtual ~file_list();
      
      
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      
      void schedule_file_size(const char * psz);

      virtual void _017OpenContextMenuFolder(sp(::fs::item) item, ::action::context actioncontext) override;
      virtual void _017OpenContextMenuFile(const ::fs::item_array &itema, ::action::context actioncontext) override;
      virtual void _017OpenContextMenu(::action::context actioncontext) override;
      virtual void _017OpenFile(const ::fs::item_array & itema, ::action::context actioncontext) override;
      virtual void _017OpenFolder(sp(::fs::item)  item, ::action::context actioncontext) override;
      void StartAnimation() override;
      void RenameFile(int32_t iLine, string & str, ::action::context actioncontext);
      static UINT c_cdecl ThreadProcFileSize(LPVOID lpparam);

      void FileSize();

      virtual void _001OnCmdMsg(::user::command * pcommand) override;
      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;
      virtual bool pre_create_window(::user::create_struct& cs) override;

      virtual void on_command_probe(::user::command * pcommand) override;
      virtual void on_command(::user::command * pcommand) override;

      DECL_GEN_SIGNAL(_001OnUpdateOpenWith);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);




      virtual id data_get_current_list_layout_id() override;



      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnShellCommand);
      DECL_GEN_SIGNAL(_001OnFileManagerItemCommand);
      DECL_GEN_SIGNAL(_001OnFileManagerItemUpdate);

      DECL_GEN_SIGNAL(_001OnFileRename);
      DECL_GEN_SIGNAL(_001OnUpdateFileRename);

      DECL_GEN_SIGNAL(_001OnTrashThatIsNotTrash);
      DECL_GEN_SIGNAL(_001OnUpdateTrashThatIsNotTrash);

      DECL_GEN_SIGNAL(_001OnSpafy);
      DECL_GEN_SIGNAL(_001OnUpdateSpafy);
      DECL_GEN_SIGNAL(_001OnSpafy2);
      DECL_GEN_SIGNAL(_001OnUpdateSpafy2);

      virtual bool _001OnClick(uint_ptr nFlags, point point) override;
      virtual bool _001OnRightClick(uint_ptr nFlags, point point) override;

      virtual void _001OnAfterSort() override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual void _001InsertColumns() override;

      virtual void file_size_add_request(bool bClear);


      virtual COLORREF get_background_color() override;
      bool add_item(const char * pszPath, const char * pszTitle);
      //virtual void schedule_file_size(const char * psz) = 0;
      // Attributes
      virtual void browse_sync(::action::context actioncontext) override;

      sp(image_list) GetActionButtonImageList(index i);



      void GetSelected(::fs::item_array & itema);

      void _001OnInitializeForm(sp(::user::control) pcontrol) override;
      void _001OnButtonAction(sp(::user::control) pcontrol) override;

      virtual void _017OpenSelected(bool bOpenFile, ::action::context actioncontext) override;
      virtual void _017OpenContextMenuSelected(::action::context actioncontext) override;
      void _017PreSynchronize(::action::context actioncontext);
      void TakeAnimationSnapshot();
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      ::fs::item & GetFileManagerItem();
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void _017UpdateList(::action::context actioncontext);
      void GetSelectedFilePath(stringa & array);
      //virtual bool TwiHasTranslucency();
      //void _001CreateImageList();
      //bool _001CreateImageListStep();
      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;
      void _017Browse(const char * lpcsz, ::action::context actioncontext);
      void _017UpdateList(const char * lpcsz, ::action::context actioncontext);
      void _017UpdateZipList(const char * lpcsz, ::action::context actioncontext);

      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnVScroll);


      virtual void _001InitializeFormPreData() override;



      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag) override;
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag) override;


   };


} // namespace filemanager


