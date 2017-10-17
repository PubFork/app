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

         virtual bool initialize_application() override;
         virtual int32_t  exit_application() override;

         virtual void on_request(::create * pcreate) override;


   };


} // namespace helloaxis



