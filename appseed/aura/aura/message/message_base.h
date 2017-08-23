#pragma once


namespace message
{



   class CLASS_DECL_AURA base :
      public ::message::message
   {
   public:


      sp(::user::primitive)      m_pwnd;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;
      LRESULT *                  m_plresult;
      LRESULT                    m_lresult;


      //base(class ::message::sender * psignal);
      //base(::aura::application * papp, class ::message::sender * psignal = NULL);
      base(::aura::application * papp);
      base(::aura::application * papp, ::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      base(const base & base);
      virtual ~base();



      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);

      base & operator = (const base & base);

      //void copy_this(const base & base);

   };





} // namespace message


#define new AURA_NEW
