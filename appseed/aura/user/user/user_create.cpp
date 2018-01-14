#include "framework.h" // previously aura/user/user.h


namespace user
{


   create::create()
   {

      m_pdocumentCurrent = NULL;
      m_ptemplateNewDocument = NULL;
      m_puiLastView = NULL;
      m_puiCurrentFrame = NULL;
      m_puiNew = NULL;

   }

   create::create(const create & createcontext)
   {

      operator =(createcontext);

   }

   create::~create()
   {

   }

   create & create::operator=(const create & createcontext)
   {

      if (this == &createcontext)
         return *this;

      m_typeinfoNewView = createcontext.m_typeinfoNewView;
      m_pdocumentCurrent = createcontext.m_pdocumentCurrent;
      m_ptemplateNewDocument = createcontext.m_ptemplateNewDocument;
      m_puiLastView = createcontext.m_puiLastView;
      m_puiCurrentFrame = createcontext.m_puiCurrentFrame;
      m_puiNew = createcontext.m_puiNew;

      return *this;

   }


} // namespace aura





