#pragma once


namespace message
{


   class CLASS_DECL_AURA base :
      public ::message::message
   {
   public:


      ::user::primitive *        m_pwnd;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;
      LRESULT *                  m_plresult;
      LRESULT                    m_lresult;


      base(::aura::application * papp = NULL);
      base(::aura::application * papp, ::user::primitive * pwnd, UINT_PTR uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      base(const base & base);
      virtual ~base();


      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(::user::primitive * pwnd, UINT_PTR uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      virtual void set(::user::primitive * pwnd, UINT_PTR uiMessage, WPARAM wparam, ::lparam lparam) override;

      base & operator = (const base & base);

   };


} // namespace message


#define new AURA_NEW


