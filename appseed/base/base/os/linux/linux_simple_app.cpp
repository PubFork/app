#include "framework.h"


void dappy(const char * psz);


namespace base
{


   app::app():
      ::aura::system(this, NULL),
      ::axis::system(this),
      ::base::system(this)
   {

   }

   app::~app()
   {

   }


   int32_t app::main()
   {



//      TCHAR *cmd = GetCommandLine();
      TCHAR *cmd = NULL;

      // Skip program name
      if(*cmd == _T('"'))
      {

         while(*cmd && *cmd != _T('"'))
            cmd++;

         if(*cmd == _T('"'))
            cmd++;

      }
      else
      {

         while(*cmd > _T(' '))
            cmd++;

      }

      // Skip any white space
      while(*cmd && *cmd <= _T(' '))
         cmd++;

      body();

//      _term_args();

      //::simple_message_box(NULL,"t3=" + ::str::from(m_iErrorCode),"t3",MB_OK);


      return m_iErrorCode;

   }


   void app::body()
   {

      try
      {
         if((m_iErrorCode = simple_app_pre_run()) != 0)
         {
            return;

         }
      }
      catch(...)
      {

         if(m_iErrorCode == 0)
            m_iErrorCode = -1;

         return;

      }


      try
      {

//         set_main_thread(GetCurrentThread());

  //       set_main_thread_id(GetCurrentThreadId());

         if(!pre_run())
         {

            if(m_iErrorCode == 0)
               m_iErrorCode = -1;

            return;

         }

         dappy(string(typeid(*this).name()) + " : s_app pre_runned : " + ::str::from(m_iErrorCode));

         SetCurrentHandles();

         dappy(string(typeid(*this).name()) + " : handles set s_app : " + ::str::from(m_iErrorCode));

      }
      catch(...)
      {

         if(m_iErrorCode == 0)
            m_iErrorCode = -1;

         return;

      }


      try
      {

         dappy(string(typeid(*this).name()) + " : s_app going to intro : " + ::str::from(m_iErrorCode));

         if(!intro())
         {

            if(m_iErrorCode == 0)
               m_iErrorCode = -1;

            return;

         }

         dappy(string(typeid(*this).name()) + " : s_app introduced : " + ::str::from(m_iErrorCode));

      }
      catch(...)
      {

         if(m_iErrorCode == 0)
            m_iErrorCode = -1;

         return;

      }

      try
      {

         m_iErrorCode = run();

      }
      catch(...)
      {

         if(m_iErrorCode == 0)
            m_iErrorCode = -1;

         return;

      }

      try
      {

         end();

      }
      catch(...)
      {

      }

   }


   bool app::intro()
   {

      return true;

   }


   int32_t app::refrain()
   {

      while(true)
      {

         GetMessage(&m_msg,NULL,0,0xffffffffu);

         TranslateMessage(&m_msg);

         DispatchMessage(&m_msg);

      }

      return 0;
   }


   bool app::end()
   {

      try
      {

         m_iErrorCode = exit_thread();

      }
      catch(...)
      {

         m_iErrorCode = -1;

      }

      return true;

   }


   int32_t app::simple_app_pre_run()
   {

      return 0;

   }


} // namespace aura






