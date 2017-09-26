#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE application : 
      virtual public ::console::application
   {
   public:
      
      


      application();
      application(const char * pszId);
      virtual ~application();



      
      virtual bool initialize_application() override;
      virtual int32_t  exit_application() override;

      virtual void _001OnFileNew();
      virtual bool bergedge_start() override;


      virtual bool is_serviceable() override;
      virtual service_base * allocate_new_service() override;


      virtual bool on_install() override;
      virtual bool on_uninstall() override;

      virtual int32_t run() override;

      virtual void on_request(::create * pcreate) override;

      ::user::document * _001OpenDocumentFile(var varFile) override;

      sp(::aura::application) get_system();

   };

   
} // namespace sphere



