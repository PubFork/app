#pragma once


namespace message
{


   class CLASS_DECL_AURA message :
      public object
   {
   public:


      id                         m_id;
      ref_array < route >        m_routea;
      sender *                   m_psender;
      WPARAM                     m_wparam;
      lparam                     m_lparam;
      index                      m_iRouteIndex;
      index                      m_iParam;
      bool                       m_bRet;
      unsigned int               m_uiMessageFlags;


      message(::aura::application * papp = NULL);
      message(::message::e_type etype);
      //message(dispatch * pdispatch);
      //message(::aura::application * papp, class dispatch * pdispatch);
      virtual ~message();


      void common_construct(::message::e_type etype = ::message::type_null);


      inline bool is_message() { return m_id.m_emessagetype == ::message::type_message; }


      bool route_message(); // returns m_bRet

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set(::user::primitive * pwnd, UINT_PTR uiMessage, WPARAM wparam, ::lparam lparam);


   };



} // namespace message
