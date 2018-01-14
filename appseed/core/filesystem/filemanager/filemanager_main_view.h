#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_view:
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      file_list *         m_pfilelist;
      preview *              m_ppreview;
      file_properties_form *   m_ppropform;
      ::fs::item_array                      m_itema;


      main_view(::aura::application * papp);
      virtual ~main_view();
      
      
      virtual void install_message_routing(::message::sender * pinterface) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      void on_create_views() override;

      void FileManagerBrowse(const char * lpcwstr,::action::context actioncontext);

      virtual void on_command(::user::command * pcommand) override;

      virtual void OpenSelectionProperties();

      virtual void on_update(::user::impact * pSender,LPARAM lHint,object* pHint) override;


   };


} // namespace filemanager




