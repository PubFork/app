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

   bool copydesk::_has_filea()
   {

      return macos_clipboard_get_file_count() > 0;
      
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
      
      macos_clipboard_set_filea(patha);
      
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
   
   
   bool copydesk::_has_plain_text()
   {
      
      return macos_clipboard_get_plain_text().length()>0;

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
   
   
   bool copydesk::_has_dib()
   {
      int w = 0;
      
      int h = 0;
      
      int iScan = 0;
      
      ::aura::malloc < COLORREF * > pcolorref = (COLORREF *) mm_clipboard_get_dib(w, h, iScan);
      
      if(pcolorref == NULL)
      {
         
         return false;
         
      }
      
      return true;

   }


} // namespace macos


