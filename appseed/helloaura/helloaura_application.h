#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::axis::application
   {
      public:


         enum e_type
         {

            type_normal,
            type_mili,

         };

         e_type                                 m_etype;
         string                                 m_strHelloMultiverse;
         string                                 m_strHelloMultiverseDefault;
         string                                 m_strAlternateHelloMultiverse;
         string                                 m_strAlternateHelloMultiverseDefault;

         bool                                   m_bMultiverseChat;

         ::user::document *                     m_pdocMenu;

         mutex                                  m_mutexAiFont;
         int32_t                                m_iErrorAiFont;
         bool                                   m_bLoadAiFont;
         void *                                 m_faceAi; // FT_Face m_faceAi;

         application();
         virtual ~application();

         virtual bool initialize_application() override;
         virtual int32_t  exit_application() override;

         virtual void on_request(::create * pcreate) override;

         virtual int64_t add_ref() override;
         virtual int64_t dec_ref() override;

         void paint(HWND hwnd, HDC hdc);

         void paint(HWND hwnd, ::draw2d::graphics * pgraphics);

   };


} // namespace helloaxis



