#include "framework.h"
#include "macos.h"


int macos_clipboard_get_file_count();

void macos_clipboard_get_filea(::file::patha & stra);

void macos_clipboard_set_filea(const ::file::patha & stra);


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
//      ASSERT(IsWindow());
   //   int32_t iLen = 0;

      string str;
      str = ::str::international::utf8_to_unicode(psz);



//      ASSERT(IsWindow());
//      if(!m_p->OpenClipboard())
  //    {
    ///     return;
      //}

      _throw(todo(get_app()));

/*

      EmptyClipboard();


      count iCount = ::str::international::utf8_to_unicode_count(str) + 1;
      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iCount * sizeof(WCHAR));
      unichar * lpwstrCopy  = (unichar *) ::GlobalLock(hglbCopy);
      ::str::international::utf8_to_unicode(lpwstrCopy, iCount, str);
      ::GlobalUnlock(hglbCopy);

      HGLOBAL hglbCopy2 = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(CHAR) * (strlen(psz) + 1));
      char * lpstrCopy  = (char *) ::GlobalLock(hglbCopy2);
      strcpy(lpstrCopy, psz);
      ::GlobalUnlock(hglbCopy2);


      SetClipboardData(CF_UNICODETEXT, hglbCopy);
      SetClipboardData(CF_TEXT, hglbCopy2);
      VERIFY(::CloseClipboard());

*/

   }


   string copydesk::get_plain_text()
   {
//      _throw(todo(get_app()));
      return "https://www.liveedu.tv/static/img/logos/logo-white.png?h=fc4045ce";
/* xxx
      if (IsClipboardFormatAvailable(CF_UNICODETEXT))
      {
         if(!m_p->OpenClipboard())
            return "";
         HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
         string str(::str::international::unicode_to_utf8((const unichar *) GlobalLock(hglb)));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else if (IsClipboardFormatAvailable(CF_TEXT))
      {
         if(!m_p->OpenClipboard())
            return "";
         HGLOBAL hglb = GetClipboardData(CF_TEXT);
         string str((char *) GlobalLock(hglb));
         GlobalUnlock(hglb);
         VERIFY(::CloseClipboard());
         return str;
      }
      else
      {
         return "";
      }
*/
   }

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {
//      if(!m_p->OpenClipboard())
  //       return false;
      bool bOk = false;
      _throw(todo(get_app()));
/* xxx
      HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
      try
      {
         ::draw2d::bitmap_sp bitmap(get_app());
         bitmap->Attach(hbitmap);
         //HDC hdc = ::CreateCompatibleDC(NULL);
         //::draw2d::graphics_sp g(get_app());
         //g->Attach(hdc);
         //::draw2d::graphics * pgraphics = Application.graphics_from_os_data(hdc);
         //g->SelectObject(hbitmap);
       //  BITMAP bm;
         //::GetObjectA(hbitmap, sizeof(bm), &bm);
         //if(!pdib->create(bm.bmWidth, bm.bmHeight))
           // return false;
         ::draw2d::graphics_sp g(get_app());
         g->SelectObject(bitmap);
         size sz = bitmap->GetBitmapDimension();
         if(pdib->create(sz))
         {
            bOk = pdib->get_graphics()->BitBlt(0, 0, sz.cx, sz.cy, g, 0, 0, SRCCOPY) != FALSE;
         }
      }
      catch(...)
      {
      }
      ::DeleteObject((HGDIOBJ) hbitmap);
      //::DeleteDC(hdc);
      ::CloseClipboard();

*/

      return bOk;
   }


} // namespace macos


