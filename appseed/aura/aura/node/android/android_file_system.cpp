#include "framework.h"
//#include "android.h"
//#include <sys/stat.h>
//#include <ctype.h>


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

	
	bool file_system::update_module_path()
	{

	{

		if (!br_init_lib(NULL))
			return false;

		char * lpszModule = br_find_exe(NULL);

		if (lpszModule == NULL)
			return false;

		m_pathModule = lpszModule;

		free(lpszModule);

	}

	{

		//void * handle = dlopen("libca.so", RTLD_NOW);

		//if(handle == NULL)
		{

			m_pathCa2Module = m_pathModule;

		}
		/*else
		{

		link_map * plm;

		dlinfo(handle, RTLD_DI_LINKMAP, &plm);

		m_strCa2ModuleFolder = ::dir::name(plm->l_name);

		if(m_strCa2ModuleFolder.is_empty() || m_strCa2ModuleFolder[0] != '/')
		{

		m_strCa2ModuleFolder = m_strModuleFolder;

		}

		dlclose(handle);

		}*/

	}

	return true;

}


} // namespace android

























