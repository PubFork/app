#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         class list_view;


         class CLASS_DECL_CORE view :
            virtual public ::user::split_view
         {
         public:
            
            
            tree *             m_ptree;
            ::user::tree *     m_pusertree;

            list_view *        m_plist;
            ::object *  m_prequestinterface;

            
            view(::aura::application * papp);
            virtual ~view();


            void install_message_routing(::message::sender * pinterface);

            void open_file(int64_t iFolder, const char * lpszFileName, const char * pszExt);
            void open_folder(int64_t iFolder);
            void start_music();
            void start_root();
            void CreateViews();

            void set_request_interface(::object * prequestinterface);

            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;

            DECL_GEN_SIGNAL(on_request_response);

         };


      } // namespace simple


   } // namespace fs


} // namespace mplite
