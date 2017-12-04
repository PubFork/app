#pragma once


namespace filemanager
{


   class  CLASS_DECL_CORE folder_list_view:
      virtual public simple_list_view,
      virtual public ::filemanager::impact
   {
      public:


         bool                             m_bRecursive;

         bool                             m_bRecursiveColumn;

         folder_list_view(::aura::application * papp);
         virtual ~folder_list_view();


         virtual void install_message_routing(::message::sender * pinterface);


         void initialize(string strDataKeyModifier,bool bRecursive);


         virtual string calc_data_id();

         void _001InsertColumns();

         bool add_unique(const stringa & stra);
         bool add_unique(const stringa & stra,bool_array & baRecursive);
         bool remove(const stringa & stra);


         void GetSel(stringa & stra);

         void on_update(::user::impact * pSender,LPARAM lHint,object* phint);


   };


} // namespace filemanager













