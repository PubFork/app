#pragma once


class android_data_exchange
{
   public:

      int            m_iScreenWidth;
      int            m_iScreenHeight;
      const char *   m_pszCommandLine;
      const char *   m_pszCacheDir;
      bool           m_bShowKeyboard;
      bool           m_bHideKeyboard;
      const char *   m_pszOpenUrl;
      const char *   m_pszUserWallpaper;
      const char *   m_pszGetUserWallpaper;
      bool           m_bGetUserWallpaper;
      bool           m_bGettingUserWallpaper;

};




typedef void FN_native_activity_android_start(android_data_exchange * pinitdata);
typedef FN_native_activity_android_start * PFN_native_activity_android_start;
