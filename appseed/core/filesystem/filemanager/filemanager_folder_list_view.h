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


      virtual void install_message_routing(::message::sender * pinterface) override;


      virtual void initialize(string strDataKeyModifier,bool bRecursive);

      
      virtual void _001InsertColumns() override;


      bool add_unique(const stringa & stra);
      bool add_unique(const stringa & stra, bool_array & baRecursive);
      bool remove(const stringa & stra);


      virtual void GetSel(stringa & stra);

      virtual void on_update(::user::impact * pSender,LPARAM lHint,object* phint) override;


   };


} // namespace filemanager













