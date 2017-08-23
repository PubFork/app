#include "framework.h"


simple_tree_view::simple_tree_view(::aura::application * papp) :
   object(papp),
   tree(papp)
{

}

simple_tree_view::~simple_tree_view()
{

}

void simple_tree_view::install_message_routing(::message::sender * pinterface)
{

   ::user::impact::install_message_routing(pinterface);
   ::user::tree::install_message_routing(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_tree_view::_001OnCreate);

}


void simple_tree_view::on_update(::user::impact * pSender,LPARAM lHint,::object* pHint)
{

   ::user::impact::on_update(pSender,lHint,pHint);
   ::user::tree::on_update(pSender,lHint,pHint);

}


#ifdef DEBUG
void simple_tree_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}
#endif //DEBUG


void simple_tree_view::_001OnCreate(::message::message * pobj)
{

   SCAST_PTR(::message::create, pcreate, pobj);

   pcreate->previous();


}



