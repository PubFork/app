#include "framework.h"


file_memory_map::file_memory_map()
{

   construct();

}


file_memory_map::file_memory_map(const char * psz,bool bRead,bool bWrite, bool bCreate,memory_size_t size)
{

   construct();

   if(!open(psz,bRead,bWrite,bCreate,size))
   {

      string strFormat;

      strFormat.Format("failed to open file_memory_map : \"%s\" bRead %d bWrite %d bCreate %d size %lld ",psz,int(bRead),int(bWrite),int(bCreate),size);

      _throw(simple_exception(get_app(),strFormat));

   }

}



file_memory_map::~file_memory_map()
{

   if(is_mapped())
   {

      close();

   }

}


string file_memory_map::get_path()
{

#ifdef LINUX

   ::file::path path("/var/tmp/ca2/");

   string str = m_strName;

   if(::str::begins_eat_ci(str, "Local\\"))
   {

      path /= Sys(::aura::system::g_p).dir().home() / str;

   }
   else
   {

      path /= str;

   }

   return path;

#endif

   return m_strName;

}


bool file_memory_map::open(const char * psz,bool bRead,bool bWrite,bool bCreate,memory_size_t size)
{

   m_strName   = psz;

   m_bRead     = bRead;

   m_bWrite    = bWrite;

   m_bCreate   = bCreate;

   m_size      = size;

   return open();

}




// SALADA AND PASTA and me pig searching for food is good EAT IT!! But mama te

