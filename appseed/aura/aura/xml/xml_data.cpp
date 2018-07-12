#include "framework.h"


namespace xml
{


   data::data(::aura::application * papp, ::xml::parse_info * pparseinfo) :
      ::object(papp),
      ::xml::node(papp),
      ::data::data(papp),
      ::xml::document(papp, pparseinfo)
   {



   }


   data::~data()
   {



   }


   void data::io(stream & stream)
   {

      ::xml::document::io(stream);

   }



} // namespace core



