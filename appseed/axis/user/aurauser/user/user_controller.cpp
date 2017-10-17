#include "framework.h"


namespace user
{

   
   controller::controller(::aura::application * papp) :
      ::object(papp),
      ::command_target(papp),
      ::data::data_container_base(papp)
   {
      
      m_bModified = false;
      m_bNew = true;
      m_bAutoDelete = false;
      m_bEmbedded = false;

   }


   controller::~controller()
   {


   }


} // namespace user


