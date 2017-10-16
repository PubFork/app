#pragma once


namespace user
{


   class CLASS_DECL_AURA frame:
      virtual public interaction
   {
      public:


         frame();
         virtual ~frame();


         virtual bool IsFullScreen() = 0;
         virtual ::user::impact * GetActiveView() const = 0;           // active ::user::impact or NULL
         virtual void SetActiveView(::user::impact * pViewNew, bool bNotify = TRUE) = 0;

         virtual void ActivateFrame(int32_t nCmdShow = -1) = 0;

   };


} // namespace aura



