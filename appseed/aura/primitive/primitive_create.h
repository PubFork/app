#pragma once





class command_line;

class CLASS_DECL_AURA command_line_sp :
   public smart_pointer < command_line >
{
public:


   command_line_sp();
   command_line_sp(const ::aura::allocatorsp & allocer);


   using smart_pointer < command_line >::operator =;
   inline command_line_sp & operator = (command_line * p)
   {
      smart_pointer < command_line >::operator =(p);
      return *this;
   }

};



class CLASS_DECL_AURA create :
   virtual public ::command::command
{
public:


   bool                                                        m_bMakeVisible;
   bool                                                        m_bTransparentBackground;
   bool                                                        m_bClientOnly;
   bool                                                        m_bOuterPopupAlertLike;
   bool                                                        m_bHold;
   ::user::primitive *                                         m_puiParent;
   ::user::primitive *                                         m_puiAlloc;
   sp(application_bias)                                        m_spApplicationBias;
   command_line_sp                                             m_spCommandLine;
   stack < ::aura::create_context >                            m_user; 
   ::handler *                                                 m_phandlerParent;


   create(::aura::application * papp);
   create(::handler * phandlerParent);
   create(::handler * phandlerParent,var varFile,bool bMakeVisible = true,::user::primitive * puiParent = NULL);
   create(const create & createcontext);
   virtual ~create();

   
   void common_construct(bool bMakeVisible = true, ::user::primitive * puiParent = NULL);

   create & operator = (const create & createcontext);

};





