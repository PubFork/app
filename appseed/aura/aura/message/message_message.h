#pragma once


namespace message
{


   class CLASS_DECL_AURA message :
      public object
   {
   public:


      id                         m_id;
      dispatch *                 m_pdispatch;
      WPARAM                     m_wparam;
      lparam                     m_lparam;
      index                      m_iIndex;
      index                      m_iParam;
      bool                       m_bRet;
      



      message(::aura::application * papp = NULL);
      message(dispatch * pdispatch);
      message(::aura::application * papp, class dispatch * pdispatch);
      virtual ~message();


      bool route_message(); // returns m_bRet

      bool route_all_previous(); // returns bRet

      bool route_previous(); // returns bRet

   };



} // namespace message
