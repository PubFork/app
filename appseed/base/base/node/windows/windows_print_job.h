#pragma once


namespace windows
{


   class CLASS_DECL_BASE print_job :
      virtual public ::user::print_job
   {
   public:


      print_job(::aura::application * papp);
      virtual ~print_job();


      virtual void run() override;

   };


} // namespace windows




