#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::helloaura::application,
      virtual public ::axis::application
   {
   public:


      application();
      virtual ~application();

      virtual bool init_instance() override;
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual string get_helloaura() override;

   };


} // namespace helloaxis



