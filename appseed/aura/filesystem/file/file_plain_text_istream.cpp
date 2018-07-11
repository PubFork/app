#include "framework.h"


namespace file
{


//   plain_text_stream::plain_text_stream()
//   {
//   }
//
//   plain_text_stream::plain_text_stream(file * preader) :
//      istream(preader)
//   {
//
//   }
//
//   plain_text_stream::plain_text_stream(const istream & is) :
//      istream(is)
//   {
//
//   }
//
//   plain_text_stream::~plain_text_stream()
//   {
//
//   }

   void plain_text_stream::read (bool & b)
   {
      m_spfile->read(&b, sizeof(b));

   }

   void plain_text_stream::read (char & ch)
   {
      m_spfile->read(&ch, sizeof(ch));

   }

   void plain_text_stream::read (uchar & uch)
   {
      m_spfile->read(&uch, sizeof(uch));

   }
#ifdef WINDOWS
   void plain_text_stream::read (unichar & wch)
   {
      m_spfile->read(&wch, sizeof(wch));

   }
#endif
   void plain_text_stream::read (int16_t & sh)
   {
      m_spfile->read(&sh, sizeof(sh));

   }

   void plain_text_stream::read (uint16_t & ui)
   {
      m_spfile->read(&ui, sizeof(ui));

   }

   void plain_text_stream::read (int32_t & i)
   {
      uint64_t uiRead = m_spfile->read(&i, sizeof(i));
      if(uiRead != sizeof(i))
         _throw(simple_exception(get_app(), "failed to read int32_t"));

   }

   void plain_text_stream::read (uint32_t & ui)
   {
      uint64_t uiRead = m_spfile->read(&ui, sizeof(ui));
      if(uiRead != sizeof(ui))
         _throw(simple_exception(get_app(), "failed to read uint32_t"));

   }

   void plain_text_stream::read (int64_t & i)
   {
      m_spfile->read(&i, sizeof(i));

   }

   void plain_text_stream::read (uint64_t & ui)
   {
      m_spfile->read(&ui, sizeof(ui));

   }

   void plain_text_stream::read (float & f)
   {
      m_spfile->read(&f, sizeof(f));

   }

   void plain_text_stream::read (double & d)
   {
      m_spfile->read(&d, sizeof(d));

   }

   void plain_text_stream::read (LPRECT lprect)
   {
      m_spfile->read(&lprect->left,     sizeof(lprect->left));
      m_spfile->read(&lprect->top,      sizeof(lprect->top));
      m_spfile->read(&lprect->right,    sizeof(lprect->right));
      m_spfile->read(&lprect->bottom,   sizeof(lprect->bottom));

   }

   void plain_text_stream::read (SIZE & size)
   {
      m_spfile->read(&size.cx,     sizeof(size.cx));
      m_spfile->read(&size.cy,      sizeof(size.cy));

   }

   void plain_text_stream::read (sp(type) info)
   {
      {
         int32_t iLen;
         m_spfile->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spfile->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_id = psz;
         free((void *) psz);
      }
      {
         int32_t iLen;
         m_spfile->read(&iLen, sizeof(iLen));
         char * psz = (char *) malloc(iLen + 1);
         m_spfile->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_idFriendly = psz;
         free((void *) psz);
      }

   }


   string plain_text_stream::get_location() const
   {

      return "<unknown plain_text_stream location>";

   }


//   istream & plain_text_stream::operator = (const istream & istream)
//   {
//
//      return istream::operator = (istream);
//
//   }








} // namespace core

