#pragma once

class CLASS_DECL_ca2 simple_child_frame :
   public simple_frame_window
{
public:
   simple_child_frame(::ca::application * papp);
   virtual ~simple_child_frame();

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

