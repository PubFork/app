#include "framework.h"



create::create(::aura::application * papp) :
   object(papp),
   command(papp),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer())
{
   
   common_construct();

   m_phandlerParent = papp->m_phandler;

}


create::create(::handler * phandlerParent) :
   create(phandlerParent->get_app())
{

}


create::create(::handler * pthreadParent, var varFile, bool bMakeVisible, ::user::primitive * puiParent) :
   object(pthreadParent->get_app()),
   command(pthreadParent->get_app()),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer())
{
   
   common_construct(bMakeVisible, puiParent);

   m_spCommandLine->m_varFile          = varFile;
   
   m_phandlerParent                    = pthreadParent;

}


void create::common_construct(bool bMakeVisible, ::user::primitive * puiParent)
{
   
   m_bMakeVisible                      = bMakeVisible;
   m_bTransparentBackground            = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_puiAlloc                          = NULL;
   m_puiParent                         = puiParent;
   m_phandlerParent                    = NULL;

}


create::create(const create & createcontext) :
   object(createcontext.get_app()),
   command(createcontext.get_app()),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer())
{
   
   common_construct();
   
   operator = (createcontext);
   
}


create::~create()
{
   
}


create & create::operator = (const create & create)
{
   
   if(this == &create)
   {
      
      return *this;
      
   }

   m_bMakeVisible             = create.m_bMakeVisible;
   m_bTransparentBackground   = create.m_bTransparentBackground;
   m_bClientOnly              = create.m_bClientOnly;
   m_bOuterPopupAlertLike     = create.m_bOuterPopupAlertLike;
   m_bHold                    = create.m_bHold;
   m_puiParent                = create.m_puiParent;
   m_puiAlloc                 = create.m_puiAlloc;
   m_spApplicationBias        .oattrib(create.m_spApplicationBias);
   m_spCommandLine            .oattrib(create.m_spCommandLine);

   m_phandlerParent->merge(this);

   return *this;

}
























