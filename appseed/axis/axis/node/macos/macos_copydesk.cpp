#include "framework.h"
#include "macos.h"


int macos_clipboard_get_file_count();

void macos_clipboard_get_filea(::file::patha & stra);

void macos_clipboard_set_filea(const ::file::patha & stra);

string macos_clipboard_get_plain_text();

void macos_clipboard_set_plain_text(const char * pszPlainText);

void * mm_clipboard_get_dib(int & cx, int & cy, int & iScan);

namespace macos
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {

      return macos_clipboard_get_file_count();
      
   }


   void copydesk::get_filea(::file::patha & patha)
   {

      macos_clipboard_get_filea(patha);
      
   }

   void copydesk::set_filea(const ::file::patha & patha)
   {
      
      macos_clipboard_set_filea(patha);

   }



   bool copydesk::initialize()
   {

      if(!::user::copydesk::initialize())
         return false;

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

   
   void copydesk::set_plain_text(const char * psz)
   {
      
      macos_clipboard_set_plain_text(psz);

   }


   string copydesk::get_plain_text()
   {
      
      return macos_clipboard_get_plain_text();
      
   }
   

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
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


} // namespace macos


