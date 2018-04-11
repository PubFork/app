#pragma once


namespace user
{


   namespace wndfrm
   {

      namespace wndfrm_anthill
      {


         class CLASS_DECL_APP_CORE_WNDFRM_ANTHILL library:
            virtual public ::aura::library
         {
         public:


            library(::aura::application * papp);
            virtual ~library();


//            virtual bool is_uinteraction_library() override;
            virtual sp(::object) create_object(::aura::application * papp,const char * pszClass, object * p) override;


         };


      } // namespace wndfrm_anthill


   } // namespace wndfrm


} // namespace user






