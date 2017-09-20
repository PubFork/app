#include "framework.h"
#include <stdio.h>


blob::blob()
{
   m_sizet     = 0;
   m_pchData   = NULL;
}

blob::~blob()
{
   if(m_pchData != NULL)
   {
      memory_free_dbg(m_pchData, 0);
      m_pchData = NULL;
   }
}


void blob::read(FILE * file)
{

   if(m_pchData != NULL)
   {

      memory_free_dbg(m_pchData, 0);

   }

   auto iRead = fread(&m_sizet, 1, (int) sizeof(m_sizet), file);

   if(m_sizet == 0)
   {

      m_pchData = NULL;

   }
   else
   {

      m_pchData = (char *) memory_alloc(m_sizet);

      size_t sRead = 0;

      while(true)
      {

         iRead  = (int) fread(&m_pchData[sRead], 1, 1024, file);

         if(iRead == 0)
            break;

         sRead += iRead;

      }

   }

}

void blob::write(FILE * file)
{

   size_t iWritten = fwrite(&m_sizet, 1, sizeof(m_sizet), file);

   if(iWritten == sizeof(m_sizet) && m_sizet > 0)
   {

      iWritten = ::fwrite(m_pchData, 1, m_sizet, file);

      if(iWritten == m_sizet)
      {

      }

   }

}


blob & blob::operator = (const char * psz)
{
   m_sizet = strlen_dup(psz) + 1;
   m_pchData = (char *) strdup_dup(psz);
   return *this;
}


machine_event_data::fixed::fixed()
{
   m_bRequestCloseApplication    = false;
   m_bSpaUpgrade                 = false;
}


void machine_event_data::read(FILE * file)
{

   size_t iRead = fread(&m_fixed, 1, sizeof(m_fixed), file);

   m_blobCommand.read(file);

}


void machine_event_data::write(FILE * file)
{

   size_t iWritten = fwrite(&m_fixed, 1, sizeof(m_fixed), file);

   m_blobCommand.write(file);

}



