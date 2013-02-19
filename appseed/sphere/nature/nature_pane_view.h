#pragma once

namespace nature
{
   
   class CLASS_DECL_ca2 pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

      
      ::userbase::single_document_template * m_pdoctemplateAppearance;
      ::ca8::keyboard_layout *             m_pkeyboardlayout;


      pane_view(::ca::application * papp);

#if !core_level_1
      using ::userbase::tab_view::on_show_view;
#endif

      virtual void on_create_view(::user::view_creator_data * pdata);
      virtual void on_show_view() ;

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      void on_update(::view * pview, LPARAM lHint, ::radix::object* pHint);

      virtual ~pane_view();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   protected:
      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace nature