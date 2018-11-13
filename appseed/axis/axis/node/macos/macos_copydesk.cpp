#include "framework.h"
#include "macos.h"


dispatch_source_t CreateDispatchTimer(double interval, dispatch_queue_t queue, dispatch_block_t block)
{
   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
   if (timer)
   {
      dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, interval * NSEC_PER_SEC), interval * NSEC_PER_SEC, (1ull * NSEC_PER_SEC) / 10);
      dispatch_source_set_event_handler(timer, block);
      dispatch_resume(timer);
   }
   return timer;
}


int macos_clipboard_get_file_count();

void macos_clipboard_get_filea(::file::patha & stra);

void macos_clipboard_set_filea(const ::file::patha & stra);

string macos_clipboard_get_plain_text();

void macos_clipboard_set_plain_text(const char * pszPlainText);

void * mm_clipboard_get_dib(int & cx, int & cy, int & iScan);

bool mm_clipboard_has_dib();

bool mm_clipboard_has_plain_text();

namespace macos
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp)
   {
      
      m_bHasFile = false;
      
      m_bHasText = false;
      
      m_bHasDib = false;
      
      dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

      double secondsToFire = 0.33333333333333333;
      
      m_ds = CreateDispatchTimer(secondsToFire, queue, ^{ _os_step(); });

   }

   copydesk::~copydesk()
   {
      
      if (m_ds)
      {
         dispatch_source_cancel(m_ds);
         // Remove this if you are on a Deployment Target of iOS6 or OSX 10.8 and above
         dispatch_release(m_ds);
         m_ds = nil;
      }

      
   }

   
   bool copydesk::_os_has_filea()
   {
      
      return macos_clipboard_get_file_count() > 0;
      
   }

   
   bool copydesk::_has_filea()
   {
      
      return m_bHasFile;
      
   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {
      
      if(!has_filea())
      {
       
         return false;
         
      }

      eop = op_copy;
      
      macos_clipboard_get_filea(patha);
      
      return true;
      
   }

   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {
      
      ns_main_sync(^
                    {
      macos_clipboard_set_filea(patha);
                    });
      
      return true;

   }



   bool copydesk::initialize()
   {

      if(!::user::copydesk::initialize())
      {
         
         return false;
         
      }

  //    if(!m_p->CreateEx(0, System.RegisterWndClass(0), NULL, 0, rect(0, 0, 0, 0), NULL, id()))
    //     return false;

//      if(!m_p->CreateEx(0, NULL, NULL, 0, rect(0, 0, 0, 0), NULL, id()))
  //       return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;

      bOk = ::user::copydesk::finalize();

//      if(window_sp::is_set() && window_sp::m_p->IsWindow())
  //    {
    //     bOk = window_sp::m_p->DestroyWindow() != FALSE;
      //}
//      else
  //    {
    //     bOk = false;
      //}

      return bOk;

   }

   
   bool copydesk::_set_plain_text(const string & str)
   {
      
      macos_clipboard_set_plain_text(str);
      
      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {
      
      str = macos_clipboard_get_plain_text();
      
      return true;
      
   }
   
   
   bool copydesk::_os_has_plain_text()
   {
      
      return mm_clipboard_has_plain_text();

   }

   
   bool copydesk::_has_plain_text()
   {
      
      return m_bHasText;
      
   }
   
   
   bool copydesk::_desk_to_dib(::draw2d::dib * pdib)
   {
      
      int w = 0;
      
      int h = 0;
      
      int iScan = 0;

      ::aura::malloc < COLORREF * > pcolorref = (COLORREF *) mm_clipboard_get_dib(w, h, iScan);
      
      if(pcolorref == NULL)
      {
       
         return false;
         
      }
      
      if(!System.imaging()._load_image(pdib, w, h, iScan, pcolorref))
      {
       
         return false;
         
      }
      
      return true;
      
   }

   
   bool copydesk::_dib_to_desk(::draw2d::dib * pdib)
   {
      
      throw todo(get_app());
//      int w = 0;
//
//      int h = 0;
//
//      int iScan = 0;
//
//      ::aura::malloc < COLORREF * > pcolorref = (COLORREF *) mm_clipboard_get_dib(w, h, iScan);
//
//      if(pcolorref == NULL)
//      {
//
//         return false;
//
//      }
//
//      if(!System.imaging()._load_image(pdib, w, h, iScan, pcolorref))
//      {
//
//         return false;
//
//      }
      
      return true;
      
   }
   
   
   bool copydesk::_os_has_dib()
   {

      return mm_clipboard_has_dib();
      
   }

   
   bool copydesk::_has_dib()
   {
      
      return m_bHasDib;
      
   }


   void copydesk::_os_step()
   {
      
      m_bHasFile = _os_has_filea();
      
      m_bHasText = _os_has_plain_text();
      
      m_bHasDib = _os_has_dib();
      
   }

   
} // namespace macos


