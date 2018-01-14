#include "framework.h"
#include <commctrl.h >
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib,"comctl32.lib")


INT_PTR CALLBACK DialogProc(HWND h, UINT u, WPARAM, LPARAM)
{

   if (u == WM_CLOSE)
   {
      return DestroyWindow(h);
   }
   else if(u == WM_INITDIALOG)
   {
      return 1;
   }
   else if(u==WM_PAINT)
   {
      //return 1;
   }

   return 0;
}


namespace helloaura
{


   application::application() //:
//      m_mutexAiFont(this)
   {

      m_strAppName = "app/helloaura";
      m_strLibraryName = "app/helloaura";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloMultiverseDefault = "Hello Aura!!";
      m_strAlternateHelloMultiverseDefault = "Hello Aura!!";

      m_strHelloMultiverse = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse = m_strAlternateHelloMultiverseDefault;

//      m_iErrorAiFont = -1;

      //    m_bLoadAiFont = false;

      //  m_faceAi = NULL; // FT_Face m_faceAi;

//      m_bMultiverseChat = true;



   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      ::core::session * pcoression = m_pauraapp->m_pcoresession;

      if (!::aura::application::init_instance())
      {

         return false;

      }

      m_dFps = 60;



      string str = handler()->m_varTopicQuery["helloaura"];

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

//      set_local_data_key_modifier();



      return true;

   }


   int32_t application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef DEBUG

      output_debug_string("DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif


//      m_bMultiverseChat = !handler()->m_varTopicQuery["no_hello_edit"].is_set();

      output_debug_string("\nfinished helloaura::on_request");

      //property_set set;

      //set["raw_http"] = true;
      //set["disable_common_name_cert_check"] = true;

      //string str = Application.http().get("https://ca2.cc/", set);

      //Application.file().put_contents("C:/archive/hhh.html", str);

      //fork([&]()
      //{

      //   HWND hDlg;
      //   hDlg = CreateDialogParam(System.m_hinstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
      //   //ShowWindow(hDlg, SW_SHOW);

      //   rect r;
      //   GetWindowRect(GetDesktopWindow(), r);
      //   rect r2;
      //   GetWindowRect(hDlg, r2);

      //   r2.Align(align_horizontal_center, r);

      //   r2.top = (r.height() - r2.height()) / 3;

      //   SetWindowPos(hDlg, HWND_TOP, r2.left, r2.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);

      //   BOOL ret;
      //   MSG msg;
      //   while ((ret = GetMessage(&msg, 0, 0, 0)) != 0)
      //   {
      //      if (ret == -1) /* error found */
      //         return -1;

      //      if (!IsDialogMessage(hDlg, &msg))
      //      {
      //         TranslateMessage(&msg); /* translate virtual-key messages */
      //         DispatchMessage(&msg); /* send it to dialog procedure */
      //      }
      //   }
      //});

      m_prender = new render(this);

      ::helloaura::main_window(m_prender);

      System.post_quit();

   }





   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }



   string application::get_helloaura()
   {

      return "Hello Aura!!";

   }

} // namespace helloaura




extern "C"
::aura::library * app_helloaura_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::helloaura::application >(papp, "app/helloaura");

}




