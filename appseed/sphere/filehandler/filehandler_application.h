#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE application :
      virtual public ::calculator::application
   {
   public:


      sp(pane_view)                                  m_ppaneview;      
      sp(::user::single_document_template)       m_ptemplateMenu;


      application();
      virtual ~application();

      void construct();

      virtual bool initialize_application() override;
      virtual int32_t exit_application() override;


      virtual void on_request(::create * pcreate) override;


   };


} // namespace filehandler


