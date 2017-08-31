#pragma once


namespace user
{


   class CLASS_DECL_AURA create :
      virtual public object
   {
   public:


      sp(type)                         m_typeinfoNewView;
      ::user::controller *             m_pdocumentCurrent;
      ::user::primitive *              m_puiNew;

      // multiple document interface children
      ::user::impact_system *          m_ptemplateNewDocument;

      // original view/frame
      ::user::primitive *              m_puiLastView;
      ::user::primitive *              m_puiCurrentFrame;


      create();
      create(const create & createcontext);
      virtual ~create();


      create & operator = (const create & createcontext);


   };


} // namespace user


