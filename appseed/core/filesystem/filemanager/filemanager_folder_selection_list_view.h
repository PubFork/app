#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_selection_list_view:
      virtual public ::user::split_view,
      virtual public ::filemanager::impact
   {
   public:


      ::user::tree *             m_pusertree;
      tree *                     m_ptree;
      folder_list_view *         m_plistview;
      data *                     m_pdata;


      folder_selection_list_view(::aura::application * papp);
      virtual ~folder_selection_list_view();


      virtual data * get_filemanager_data() override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual void on_update(user::impact *p, LPARAM l, object * o) override;

      DECL_GEN_SIGNAL(_001OnAdd);
      DECL_GEN_SIGNAL(_001OnRemove);

      virtual void on_create_views() override;


      virtual void browse_sync(::action::context actioncontext) override;


      virtual void FolderAdd();
      virtual void FolderRemove();

   };


} // namespace filemanager





