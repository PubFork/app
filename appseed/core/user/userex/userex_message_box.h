#pragma once


namespace userex
{


   class CLASS_DECL_CORE message_box :
      virtual public wait_message_dialog
   {
   public:
      
      
      message_box(::aura::application * papp);

      
      virtual void on_show(const char * pszMatter, property_set * propertyset) override;
      virtual bool on_timeout() override;
      virtual void on_timer_soft_reload(uint32_t dwTimeout) override;


   };


} // namespace userex



