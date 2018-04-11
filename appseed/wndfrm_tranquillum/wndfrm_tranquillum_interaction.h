#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace wndfrm_tranquillum
      {


         class CLASS_DECL_APP_WNDFRM_TRANQUILLUM interaction:
            public ::user::wndfrm::interaction
         {
         public:


            


            interaction(::aura::application * papp);
            virtual ~interaction();

            virtual void update();


            virtual void get_frame_schema_list(stringa & stra);


            virtual sp(::user::wndfrm::frame::frame) get_frame_schema(const char * pszSchema);


         };


      } // namespace wndfrm_tranquillum


   } // namespace wndfrm


} // namespace user





