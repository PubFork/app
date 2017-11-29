#include "framework.h"
#include "framework.h" // from "axis/net/net_sockets.h"
#include "fiasco_finder.h"

//#ifndef WINDOWS
//#include "ft2build.h"
//#include FT_FREETYPE_H
//#endif


namespace axis
{



   system::system(::aura::application * papp, app_core * pappcore):
      aura::system(this, pappcore, NULL)//,
//      m_httpsystem(this),
//      m_visual(this),

      //m_emaildepartment(this)
   {

      m_paxissystem = this;


      g_pszCooperativeLevel = "axis";

      m_pDraw2dFactoryExchange = NULL;

      m_puserstr                 = NULL;


      __node_axis_factory_exchange(this);



      factory().creatable_small < ::file::axis::application >(System.type_info < ::file::application >());
      factory().creatable_small < ::file::dir::axis::application >(System.type_info < ::file::dir::application >());

      //m_psimpleui       = NULL;


      set_app(this);

//      m_pbasesystem     = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(object)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_paxissystem;

      }


      //__node_base_factory_exchange(this);

      m_bSystemSynchronizedCursor = true;

      m_bSystemSynchronizedScreen = true;




   }


   system::~system()
   {

      ::aura::del(m_purldepartment);

      ::aura::del(m_pcompress);

   }





   bool system::process_init()
   {

//#ifndef WINDOWS
//
//      int32_t error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
//      if(error)
//      {
//         TRACE("an error occurred during Free Type library initialization");
//         return false;
//      }
//
//#endif

      //enum_display_monitors();

      //if (m_peengine != NULL)
      //{

      //   m_peengine = new ::exception::engine(this);

      //}


      if(!::axis::application::process_init())
         return false;

      if(!::aura::system::process_init())
         return false;


      m_spos.alloc(allocer());





      return true;

   }


   bool system::init1()
   {

      if(!::aura::system::init1())
         return false;

      if(!::axis::application::init1())
         return false;


      Session.m_puserstrcontext->defer_ok(m_puserstr);




      return true;

   }


   bool system::init2()
   {

      if(!::aura::system::init2())
         return false;

      if(!::axis::application::init2())
         return false;


      return true;

   }

   bool system::verb() // ambigous inheritance from ::aura::system/::axis::application
   {

      return ::aura::system::verb();

   }

   bool system::init_application()
   {

      if (!::aura::system::init_application())
      {

         return false;

      }

      if (!::axis::application::init_application())
      {

         return false;

      }

      return true;

   }


   bool system::finalize()
   {

      __wait_threading_count_except(this,::millis((5000) * 77));

      bool bOk = false;

      try
      {

         if(m_spcrypto.is_set())
         {

            m_spcrypto.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {

         bOk = ::axis::application::finalize();

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {

         if(m_spfile.is_set())
         {

            m_spfile.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      return bOk;

   }


   bool system::initialize()
   {

      if (!::axis::application::initialize())
      {

         return false;

      }

      if (!::aura::system::initialize())
      {

         return false;

      }

      return true;

   }

   int32_t system::exit_application()
   {

      try
      {

         for(auto & pair : System.m_appmap)
         {

            try
            {

               if(pair.m_element2->m_paxissystem == this)
               {

                  pair.m_element2->m_paxissystem = NULL;

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

      __wait_threading_count(::millis((5000) * 8));

      try
      {

         m_pmath.release();

         m_pgeometry.release();

      }
      catch(...)
      {

         m_iErrorCode = -86;

      }

      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {

         try
         {

            m_serviceptra[i]->Stop(0);

         }
         catch(...)
         {

         }

      }

      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {

         try
         {

            m_serviceptra[i]->Stop((5000) * 2);

         }
         catch(...)
         {

         }

      }

      m_serviceptra.remove_all();

      int32_t iRet = m_iErrorCode;

      try
      {

         iRet = ::axis::application::exit_application();

      }
      catch(...)
      {

      }

      try
      {

         if(m_spos.is_set())
         {

            m_spos.release();

         }

      }
      catch(...)
      {

      }

      try
      {

         m_spdir.release();

      }
      catch(...)
      {

      }

      try
      {

         m_spos.release();

      }
      catch(...)
      {

      }

      try
      {

         m_spdir.release();

      }
      catch(...)
      {

      }

      try
      {

         if(m_pmachineeventcentral != NULL)
         {

            m_pmachineeventcentral->post_quit();

         }

      }
      catch(...)
      {

      }

#ifdef DEBUG

      m_plog.release();

#endif

//#ifdef METROWIN
//
//      m_pdevicecontext = nullptr;
//
//#endif

      //::aura::del(m_peengine);

      try
      {

         ::aura::system::exit_application();

      }
      catch(...)
      {

      }

      try
      {

         if(m_mapLibrary["draw2d"]->is_opened())
         {

            if(m_pDraw2dFactoryExchange != NULL)
            {

               delete m_pDraw2dFactoryExchange;

               m_pDraw2dFactoryExchange = NULL;

            }

         }

      }
      catch(...)
      {

      }

      return iRet;

   }


   bool system::is_system()
   {

      return true;

   }


   ::file::path system::dir_appmatter_locator(::aura::application * papp)
   {

      return dir().appmatter_locator(papp);

   }


   string system::crypto_md5_text(const string & str)
   {

      return crypto().md5(str);

   }


   uint32_t _thread_proc_start_system(void * p)
   {

      ::axis::system * psystem = (::axis::system *)p;

      return psystem->main();

   }

   CLASS_DECL_AXIS void __start_system(::axis::system * psystem)
   {

      ::create_thread(NULL,0,&_thread_proc_start_system,(LPVOID)psystem,0,0);

   }


   ::aura::session * system::on_create_session()
   {

      return canew(::axis::session(this));

   }




   void system::on_request(::create * pcreate)
   {

      ::aura::system::on_request(pcreate);

   }


} // namespace axis























#include "framework.h" // from "axis/user/user.h"

//void dappy(const char * psz);



namespace axis
{








   //::user::document * system::place_hold(::user::interaction * pui)
   //{


   //   //if(m_pcubeInterface != NULL)
   //   //{
   //   // return m_pcubeInterface->hold(pui);
   //   //}

   //   return NULL;

   //}


   ::aura::session * system::query_session(index iEdge)
   {

      return NULL;

   }









   void system::hist_hist(const char * psz)
   {
   }

   //void system::on_request(::create * pcreate)
   //{

   //   ::axis::system::on_request(pcreate);

   //}

   //::user::interaction_impl * system::impl_from_handle(void * posdata)
   //{

   //   return NULL;

   //}

   //::user::interaction * system::ui_from_handle(void * posdata)
   //{

   //   return NULL;

   //}


   string system::url_encode(const string & str)
   {

      return m_purldepartment->url_encode(str);

   }



} // namespace axis













