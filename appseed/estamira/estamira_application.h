#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA application :
      virtual public ::multimedia::application
   {
   public:


      sp(::estamira::game)       m_pgame;


      application();
      virtual ~application();


      virtual bool init_instance();
      virtual int32_t  exit_application() override;

   };


} // namespace estamira





