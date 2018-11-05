#include "framework.h"


struct PROCESS_INFO_t
{


   string csProcess;
   uint32_t dwImageListIndex;


};


namespace android
{


   file_system::file_system(::aura::application * papp) :
      ::object(papp),
      ::file::system(papp)
   {

   }


   file_system::~file_system()
   {

   }


   bool file_system::update_module_path()
   {

      m_pathModule = ::file::app_module();

      m_pathCa2Module = m_pathModule;

      return true;

   }


} // namespace android



