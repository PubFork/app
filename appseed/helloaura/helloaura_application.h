#pragma once



namespace helloaura
{


   class CLASS_DECL_APP_CORE_HELLOAURA application :
      virtual public ::aura::application
   {
   public:


      enum e_type
      {

         type_normal,
         type_mili,

      };

      double                                 m_dFps;
      e_type                                 m_etype;
      string                                 m_strHelloAura;
      string                                 m_strHelloAuraDefault;
      string                                 m_strAlternateHelloAura;
      string                                 m_strAlternateHelloAuraDefault;

      //bool                                   m_bAuraChat;

      //::user::document *                     m_pdocMenu;

      //mutex                                  m_mutexAiFont;
      //int32_t                                m_iErrorAiFont;
      //bool                                   m_bLoadAiFont;
      //void *                                 m_faceAi; // FT_Face m_faceAi;
      render *                               m_prender;

      application();
      virtual ~application();

      virtual bool init_instance() override;
      virtual int32_t  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual int64_t add_ref() override;
      virtual int64_t dec_ref() override;

      virtual string get_helloaura();

   };


   CLASS_DECL_AURA int main_window(::helloaura::render * prender);


} // namespace helloaura



