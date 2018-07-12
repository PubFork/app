#pragma once



namespace xml
{


   class CLASS_DECL_AURA data :
      public ::xml::document
   {
   public:


      data(::aura::application * papp, ::xml::parse_info * pparseinfo = NULL);
      virtual ~data();


      virtual void io(stream & stream);


   };


} // namespace xml





