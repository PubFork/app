#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {

         class view;

         enum EItemType
         {
            ItemTypeFolder,
            ItemTypeArtist,
            ItemTypeSong,
         };
         class Item :
            virtual public object
         {
         public:
            int64_t     m_iParent;
            int64_t     m_iFolder;
            string      m_strTitle;
            string      m_strFileName;
            string      m_strExtension;
            int32_t         m_iId;
            EItemType   m_etype;
            int32_t         m_iImage;

            bool IsFolder();
         };

         class ItemArray :
            public spa(Item)
         {
         public:
            //int32_t FindAbsolute(const char * lpszId);
         };


         class CLASS_DECL_CORE list_view :
            public simple_list_view
         {
         public:

            enum EFieldIndex
            {
               FieldIndexNone = -1,
               FieldIndexId = 0,
               FieldIndexTitle,
               FieldIndexArtist,
               FieldIndexFileName,
               FieldIndexFilePath,
            };

            enum ESubItem
            {
               SubItemId,
               SubItemTitle,
               SubItemArtist,
               SubItemFileName,
               SubItemFilePath,
            };


            class FillTask
            {
            public:

                  string             m_strFile;
               UINT              m_uiTimer;

            };

            class BuildHelper
            {
            public:
               BuildHelper();
               ::index      m_iTopIndex;
               ::count m_iDisplayItemCount;
               ::index      m_iStep;
               bool     m_bActive;
            };

            ::user::list_cache         m_cache;
            bool                 m_bKickActive;

            sp(image_list)          m_pil;
            int64_t m_iParentFolder;
            sp(::filemanager::fs::simple::view) m_pserver;
            

            int32_t m_iIconFolder;
            int32_t m_iIconArtist;
            int32_t m_iIconSong;
            ItemArray         m_itema; 
            
            BuildHelper          m_buildhelper;


            list_view(::aura::application * papp);
            virtual ~list_view();


            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;


            void install_message_routing(::message::sender * pinterface);
       

            static UINT c_cdecl ThreadProcFillTask(LPVOID lpParameter);


            void parse(const char * lpszSource);
            void start_build(int32_t iItem = -1);
         
            void PostFillTask(string & strFile, uint_ptr uiTimer);

            virtual void _001OnSort();
            bool GetSongPath(string & str, index iItem);

            virtual void _001GetItemImage(::user::mesh_item * pitem);
            virtual void _001InsertColumns();
            virtual void _001GetItemText(::user::mesh_item * pitem);
            virtual count _001GetItemCount();
            virtual void _001SearchGetItemText(::user::mesh_item * pitem);

            virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

            virtual bool _001OnClick(uint_ptr nFlags, point point);

            DECL_GEN_SIGNAL(_001OnLButtonDblClk);
            void _001OnTimer(::timer * ptimer);
            DECL_GEN_SIGNAL(_001OnSize);
            DECL_GEN_SIGNAL(_001OnContextMenu);
            DECL_GEN_SIGNAL(_001OnEraseBkgnd);
            DECL_GEN_SIGNAL(_001OnFillTaskResponse);

         };


      } // simple


   } // namespace fs


} // namespace filemanager

