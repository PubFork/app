#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   user::user(::aura::application * papp):
      ::object(papp),
      ::aura::department(papp)
   {

      //m_pufeschema = NULL;
      //m_pufe = NULL;

   }


   user::~user()
   {

   }


   bool user::init1()
   {

      System.factory().creatable_small < ::user::document >();
      System.factory().creatable_small < ::user::message_queue >();
      System.factory().creatable_small < ::user::simple_view >();

      if(m_pauraapp->is_system())
      {

         System.factory().creatable_small < keyboard_layout >();

      }

      if(!::aura::department::init1())
         return false;

      return true;

   }


   bool user::init()
   {

      if (!::aura::department::init())
      {

         return false;

      }

      TRACE("::user::application::initialize");

      xml::document docUser(get_app());

      string strUser = Application.file().as_string(System.dir().appdata()/"langstyle_settings.xml");

      string strLangUser;

      string strStyleUser;

      if(docUser.load(strUser))
      {

         if(docUser.get_child("lang") != NULL)
         {

            strLangUser = docUser.get_child("lang")->get_value();

         }

         if(docUser.get_child("style") != NULL)
         {

            strStyleUser = docUser.get_child("style")->get_value();

         }

      }

      if(strLangUser.has_char())
         Session.set_locale(strLangUser,::action::source_database);

      if(strStyleUser.has_char())
         Session.set_schema(strStyleUser,::action::source_database);

      string strLicense = Application.get_license_id();


      var & varTopicQuey = System.handler()->m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      if (!::aura::department::init())
      {

         return false;

      }

      return true;

   }


   bool user::init2()
   {

      if(!::aura::department::init2())
         return false;

      return true;

   }


   void user::term()
   {


      //m_puserstyle.release();
//      ::aura::del(m_pufeschema);
//
//      ::aura::del(m_pufe);


      try
      {

         ::aura::department::term();

      }
      catch(...)
      {

      }

   }


   ::user::elemental * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::elemental * pmousefocus)
   {

      m_pmousefocusLButtonDown = pmousefocus;

   }


   ::user::elemental * user::get_mouse_focus_RButtonDown()
   {

      return m_pmousefocusRButtonDown;

   }


   void user::set_mouse_focus_RButtonDown(::user::elemental * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }




   void user::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   {

      synch_lock sl(&Application.m_mutexFrame);

      sp(::user::interaction) pui;

      while(Application.get_frame(pui))
      {

         if(pui != NULL && pui->IsWindow())
         {

            pui->send_message(message,wparam,lparam);

            pui->send_message_to_descendants(message,wparam,lparam);

         }

      }

   }




//   ::user::front_end_schema * GetUfeSchema(::aura::application * papp)
//   {
//
//      if (papp == NULL)
//      {
//
//         return NULL;
//
//      }
//
//      if (papp->m_pbasesession == NULL)
//      {
//
//         return NULL;
//
//      }
//
//      if (papp->m_pbasesession->m_puser == NULL)
//      {
//
//         return NULL;
//
//      }
//
//      return Sess(papp).user()->GetUfeSchema();
//
//   }
//
//
//   ::user::front_end * GetUfe(::aura::application * papp)
//   {
//
//      return Sess(papp).user()->GetUfe();
//
//   }


//   ::user::front_end_schema * user::GetUfeSchema()
//   {
//
//      return m_pufeschema;
//
//   }
//
//
//   ::user::front_end * user::GetUfe()
//   {
//
//      return m_pufe;
//
//   }

   sp(type) user::controltype_to_typeinfo(::user::e_control_type econtroltype)
   {

      return sp(type)();

   }


//   sp(::user::impact) user::get_view()
//   {
//
//      return NULL;
//
//   }


//   ::user::style * user::get_user_style()
//   {
//
//      retu
//
//   }

} //namespace user



