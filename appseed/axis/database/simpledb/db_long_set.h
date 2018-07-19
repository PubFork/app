#pragma once

//
//
//class CLASS_DECL_AXIS db_long_set :
//   virtual public ::object
//{
//public:
//
//
//   sp(::db_set)            m_pcore;
//
//
//   db_long_set(db_server * pdatacentral);
//   virtual ~db_long_set();
//
//
//
//   // load Functions
//   template < typename T >
//   inline bool load(const ::database::key & key, T & rvalue)
//   {
//
//      int64_t i;
//
//      if(!load(key, &i))
//         return false;
//
//      rvalue = (T &) i;
//
//      return true;
//
//   }
//
//   bool load(const ::database::key & key, int64_t * lValue);
//   bool load(const ::database::key & key, LPRECT lpRect);
//#ifdef WINDOWSEX
//   bool load(const ::database::key & key, WINDOWPLACEMENT & wp);
//#endif
//   bool load(const ::database::key & key, LPPOINT lpPoint);
//
//   // save Functions
//   template < typename T >
//   inline bool save(const ::database::key & key, T value)
//   {
//
//      return save(key, (int64_t) value);
//
//   }
//
//   bool save(const ::database::key & key, int64_t lValue);
//   bool save(const ::database::key & key, LPCRECT lpRect);
//#ifdef WINDOWSEX
//   bool save(const ::database::key & key, WINDOWPLACEMENT & wp);
//#endif
//   bool save(const ::database::key & key, LPPOINT lpPoint);
//
//   // Search Functions
//   bool find(const ::database::key & key);
//
//
////   bool MoveWindow_(const char * lpKey, ::user::primitive * pwindow);
////   bool SaveWindowRect_(const char * lpKey,::user::primitive * pwindow);
////   bool SetWindowPlacement(const char * lpKey,::user::primitive * pwindow);
////   bool SaveWindowPlacement(const char * lpKey,::user::primitive * pwindow);
//
//};
//
