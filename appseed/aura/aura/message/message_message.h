#pragma once


namespace message
{


   class CLASS_DECL_AURA message :
      public object
   {
   public:


      id                         m_id;
      route_array                m_routea;
      sender *                   m_psender;
      WPARAM                     m_wparam;
      lparam                     m_lparam;
      index                      m_iRouteIndex;
      index                      m_iParam;
      bool                       m_bRet;
      



      message(::aura::application * papp = NULL);
      message(::message::e_type etype);
      //message(dispatch * pdispatch);
      //message(::aura::application * papp, class dispatch * pdispatch);
      virtual ~message();


      void common_construct(::message::e_type etype = ::message::type_null);


      inline bool is_message() { return m_id.m_emessagetype == ::message::type_message; }


      bool route(); // returns m_bRet

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet


   };



} // namespace message
