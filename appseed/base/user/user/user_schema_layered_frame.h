#pragma once


namespace user
{


   class CLASS_DECL_BASE schema_layered_frame:
      virtual public ::user::schema
   {
   public:


      schema_layered_frame(::aura::application * papp);


      virtual bool get_translucency(e_translucency & etranslucency);


   };

   
} // namespace user























