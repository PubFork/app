#include "framework.h"
#include "aura/net/net_sockets.h"
//#include "fiasco_finder.h"
#include "aura/net/ftp/ftp_data_types.h"

namespace axis
{


   session::session(::aura::application * papp) :
      ::object(papp),
      ::thread(papp),
      ::aura::session(papp)
   {

      m_paxissession                = this;

      m_bMatterFromHttpCache        = m_paxissystem->m_bMatterFromHttpCache;


#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance                = m_pauraapp->m_hinstance;

      }

#endif


      m_bIfs                        = true;

      m_psavings                    = canew(class ::aura::savings(this));

      m_bZipIsDir                   = true;

      m_puserstrcontext             = NULL;


//      m_puserstyle                 = &m_schemasimple;

      //    m_schemasimple.m_pfont.alloc(allocer());

      //  m_schemasimple.m_pfont->create_pixel_font(FONT_SANS,16);

      m_puserpresence               = NULL;

      m_bMatterFromHttpCache        = m_paxissystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor   = m_paxissystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen   = m_paxissystem->m_bSystemSynchronizedScreen;

      m_iMainMonitor                = -1;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance                = m_pauraapp->m_hinstance;

      }

#endif



      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;



      m_puiMouseMoveCapture         = NULL;

      m_puiLastLButtonDown          = NULL;

      m_psavings                    = canew(class ::aura::savings(this));

      m_bZipIsDir                   = true;

      m_pmapKeyPressed              = NULL;

      m_puserstrcontext             = NULL;

      m_puserpresence = NULL;

      //      m_paxissystem->m_basesessionptra.add_unique(this);

      m_pcopydesk = NULL;


      m_pkeyboardfocus  = NULL;
      //      m_pshellimageset  = NULL;
      m_pkeyboard       = NULL;
      //    m_pufeschema      = NULL;
      //  m_pufe            = NULL;
   }


   void session::construct(::aura::application * papp, int iPhase)
   {

      if(iPhase == 0)
      {


      }


   }

   session::~session_parent
   {


   }


   bool session::is_session()
   {

      return true;

   }


   void session::on_user_login(::fontopus::user * puser)
   {


      ::aura::session::on_user_login(puser);

   }






   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }




   bool session::process_init()
   {

      thisstart;

      if (!::aura::session::process_init())
      {

         thisfail << 1;

         return false;

      }

      thisok << 1;

      if(m_pfontopus == NULL)
      {

         m_pfontopus = create_fontopus();

         if (m_pfontopus == NULL)
         {

            thisfail << 2 << "Failed to create fontopus";

            return false;

         }

         m_pfontopus->construct(this);

      }

      if (m_pifs == NULL)
      {

         m_pifs = new ifs(this, "");

      }

      if (m_prfs.is_null())
      {

         m_prfs = canew(::fs::remote_native(this, ""));

      }

      if (m_pftpfs.is_null())
      {

         m_pftpfs = canew(ftpfs(this, ""));

      }

      if (m_spfsdata.is_null())
      {

         ::fs::set * pset = canew(class ::fs::set(this));

         ::fs::link * plink = canew(::fs::link(this));

         plink->fill_os_user();

         pset->m_spafsdata.add(plink);

         pset->m_spafsdata.add(canew(::fs::native(this)));

         m_spfsdata = pset;

      }

      thisok << 2;

      if (!::axis::application::process_init())
      {

         thisfail << 3;

         return false;

      }

      fill_locale_schema(*str_context()->m_plocaleschema);

      thisend;

      return true;

   }


   bool session::init1()
   {

      m_spfs = canew(::fs::fs(this));

      if(m_spfs == NULL)
         return false;

      m_spfs->construct(this);

      if(!m_spfs->initialize())
         return false;

      //m_spcopydesk.alloc(allocer());

      //if(!m_spcopydesk->initialize())
      //   return false;

      if(!::aura::session::init1())
         return false;

      if(!::axis::application::init1())
         return false;

      m_puserpresence = new ::userpresence::userpresence(this);

      if(m_puserpresence == NULL)
      {

         TRACE("Failed to create new User Presence");

         return false;

      }

      try
      {

         m_puserpresence->construct(this);

      }
      catch(...)
      {

         TRACE("Failed to construct User Presence");

         return false;

      }


      if(!m_puserpresence->initialize())
      {

         TRACE("Failed to initialize User Presence");

         return false;

      }

      return true;

   }


   bool session::init2()
   {

      if(!::aura::session::init2())
         return false;

      if(!::axis::application::init2())
         return false;

      return true;

   }



   bool session::init_application()
   {

      if (!m_pfontopus->init_instance())
      {

         return false;

      }

      if(Application.handler()->m_varTopicQuery.has_property("uninstall")
            || Application.handler()->m_varTopicQuery.has_property("install"))
      {

         if(is_null_ref(m_pfontopus->create_system_user("system")))
            return false;

      }

      if (!::aura::session::init_application())
      {

         return false;

      }

      if (!::axis::application::init_application())
      {

         return false;

      }

      return true;

   }


   bool session::init()
   {

      if (!::aura::session::init())
      {

         return false;

      }

      if (!::axis::application::init())
      {

         return false;

      }

      if(m_bIfs)
      {

         if (m_spfsdata.is_null())
         {

            m_spfsdata = canew(::fs::set(this));

         }

         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);

         if(pset != NULL)
         {

            pset->m_spafsdata.add_unique(m_pifs);

            pset->m_spafsdata.add_unique(m_prfs);

         }

         ::file::listing patha;

         m_spfsdata->root_ones(patha);

      }

      ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);

      if (pset != NULL)
      {
         pset->m_spafsdata.add_unique(m_pftpfs);

      }

      return true;

   }


   void session::term()
   {

      try
      {

         ::axis::application::term();

      }
      catch(...)
      {

         m_error.set_if_not_set();

      }


      try
      {

         ::aura::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      try
      {

         if (m_puserpresence != NULL)
         {

            if (!m_puserpresence->finalize())
            {

               m_error.set_if_not_set();

            }

            ::aura::del(m_puserpresence);

         }


      }
      catch (...)
      {

         m_error.set_if_not_set();

      }


      try
      {

         m_spfsdata.release();

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }


      try
      {

         ::aura::del(m_pifs);

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      try
      {

         m_prfs.release();

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      try
      {

         m_pftpfs.release();

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      if(::ftp::command::info2::g_pTheOneAndOnly != NULL)
      {

         try
         {

            delete ::ftp::command::info2::g_pTheOneAndOnly;

         }
         catch (...)
         {

            m_error.set_if_not_set();

         }

      }

      try
      {

         m_pfontopus.release();

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      try
      {

         ::aura::del(m_psockets);

      }
      catch (...)
      {

         m_error.set_if_not_set();

      }

      try
      {

         ::aura::session::term();

      }
      catch(...)
      {

         m_error.set_if_not_set();

      }

   }


   void session::term_application()
   {

      try
      {

         for(auto & pair : System.m_appmap)
         {

            try
            {

               if(pair.m_element2->m_paxissession == this)
               {

                  pair.m_element2->m_paxissession = NULL;

               }

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         m_mapApplication.remove_all();

      }
      catch (...)
      {

      }

      try
      {

         if(m_pcopydesk != NULL)
         {

            m_pcopydesk->finalize();

            ::release(m_pcopydesk);

         }

      }
      catch(...)
      {

      }

      ::aura::del(m_pkeyboard);

      ::axis::application::term_application();

      ::aura::session::term_application();

   }


   DWORD session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   void session::defer_initialize_user_presence()
   {

      ::aura::session::defer_initialize_user_presence();

      userpresence().defer_initialize_user_presence();

   }


   void session::on_request(::create * pcreate)
   {

      ::aura::session::on_request(pcreate);

   }






   /*::aura::str_context * session::str_context()
   {

   return m_puserstrcontext;

   }
   */








   //COLORREF session::get_default_color(uint64_t ui)
   //{

   //   switch(ui)
   //   {
   //   case COLOR_3DFACE:
   //      return ARGB(127,192,192,184);
   //   case COLOR_WINDOW:
   //      return ARGB(127,255,255,255);
   //   case COLOR_3DLIGHT:
   //      return ARGB(127,218,218,210);
   //   case COLOR_3DHIGHLIGHT:
   //      return ARGB(127,238,238,230);
   //   case COLOR_3DSHADOW:
   //      return ARGB(127,138,138,130);
   //   case COLOR_3DDKSHADOW:
   //      return ARGB(127,90, 90, 80);
   //   default:
   //      break;
   //   }

   //   return ARGB(127,0,0,0);

   //}


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}

   //void session::on_request(::create * pcreate)
   //{

   //   ::axis::session::on_request(pcreate);

   //}


   string session::fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive)
   {

      string str = ::fontopus::get_cred(papp,strUsername,strPassword,strToken);

      if(str == "ok")
         return "ok";

      return "failed";

   }




   ::user::keyboard & session::keyboard()
   {

      if(m_pkeyboard == NULL)
      {

         //string strRellPath = "rell/path.txt";

         //string str = ::file::path("https://server.ca2.cc") / "matter" / strRellPath;

         m_pkeyboard = new ::user::keyboard(m_pauraapp);

         if(m_pkeyboard == NULL)
            _throw(simple_exception(get_app(),"Could not create keyboard"));

         if(!m_pkeyboard->initialize())
            _throw(simple_exception(get_app(),"Could not initialize keyboard"));

         Application.on_create_keyboard();

      }

      return *m_pkeyboard;

   }



   string session::fontopus_get_user_sessid(const string & str)
   {

      return fontopus()->get_user()->get_sessid(str);

   }


   void session::translate_os_key_message(::user::key * pkey)
   {

      Session.keyboard().translate_os_key_message(pkey);

   }



} // namespace axis
































