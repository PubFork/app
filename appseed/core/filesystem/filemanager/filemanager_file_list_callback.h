#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object
   {
   public:

      sp(image_list)           m_pimagelistSubItemHover;
      sp(image_list)           m_pimagelistItemHover;
      sp(image_list)           m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize_file_list_callback();

      virtual int32_t GetActionButtonCount();
      virtual sp(image_list) GetActionButtonImageList(id i);
      virtual void InitializeActionButton(id i, sp(::user::button) pbutton);
      virtual void OnButtonAction(id i, sp(::fs::item)  item);

      virtual bool GetMenuItemCallback(id iId);
      virtual void OnMenuItemAction(id iId, const ::fs::item_array & itema);
      virtual void GetMenuItemUpdate(id iId, const ::fs::item_array & itema, ::user::command * pcommand);

   };


} // namespace filemanager
