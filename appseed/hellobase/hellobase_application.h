#pragma once



namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE application :
      virtual public ::helloaxis::application,
      virtual public ::base::application
   {
   public:


      ::user::document *                     m_pdocMenu;
      ::user::single_document_template *     m_ptemplateHelloBaseMain;



      application();
      virtual ~application();

      virtual string preferred_userschema() override;
      virtual bool init_instance() override;
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual string get_helloaura() override;

   };


} // namespace hellobase



