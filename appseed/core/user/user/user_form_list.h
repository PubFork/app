#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list:
      virtual public ::user::form_mesh,
      virtual public ::user::list
   {
   public:




      form_list();
      virtual ~form_list();


      virtual void _001DrawSubItem(draw_list_item * pdrawitem) override;

      using ::user::list::_001HitTest_;
      virtual bool _001HitTest_(point point,index &iItem,index &iSubItem) override;

      void _000OnMouse(::message::mouse * pmouse) override;

      void control_get_client_rect(sp(control) pcontrol,LPRECT lprect) override;
      void control_get_window_rect(sp(control) pcontrol,LPRECT lprect) override;
      bool control_001DisplayHitTest(POINT pt);

      virtual bool _001IsEditing() override;

      virtual bool _001IsPointInside(sp(control) pcontrol,point64 ptt) override;

      virtual void _001OnAddColumn(list_column * pcolumn);

      virtual void _001HideEditingControls();
      virtual void _001HideControl(sp(control) pcontrol);
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam) override;
      void _001UpdateColumns() override;
      sp(control) _001GetEditControl();
      void _001SetEditControl(sp(control) pcontrol);
      virtual index _001AddControl(class control_descriptor & descriptorParam);
      virtual void _001PlaceControl(sp(control) pcontrol, index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false) override;
      virtual void _001OnShowControl(sp(control) pcontrol);
      sp(control) _001GetControl(index iItem, index iSubItem) override;
      virtual bool _001OnClick(uint_ptr uiFlags,point point) override;
      virtual bool _001OnClick(uint_ptr uiFlags,point point,index iItem,index iSubItem) override;
      virtual bool _001OnRightClick(uint_ptr uiFlags, point point) override;
      virtual bool _001OnRightClick(uint_ptr uiFlags, point point, index iItem, index iSubItem);
      void _001OnTimer(::timer * ptimer) override;

      using list::_001GetSelection;
      virtual void _001GetSelection(::database::id & key,::database::selection & selection) override;

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0) override;

      virtual void _001UpdateComboBox(sp(control) pcontrol) override;

      virtual void _001UpdateEdit(sp(control) pcontrol) override;
      virtual bool _001SaveEdit(sp(control) pcontrol) override;

      virtual bool _001OnMouseActivate(::window_sp pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult) override;


      virtual void install_message_routing(::message::sender *pinterface) override;

      void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnColumnChange() override;


      virtual void _001DrawChildren(::draw2d::graphics * pgraphics) override;


      virtual bool _001UpperEditableControl(index & iItem, index & iSubItem);
      virtual bool _001PreviousEditableControl(index & iItem, index & iSubItem);
      virtual bool _001NextEditableControl(index & iItem, index & iSubItem);
      virtual bool _001LowerEditableControl(index & iItem, index & iSubItem);

      //virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      virtual ::check::e_check _001GetSubItemCheck(index iItem, index iSubItem);
      virtual bool _001SetSubItemCheck(index iItem, index iSubItem, ::check::e_check echeck);
      virtual bool _001IsSubItemEnabled(index iItem, index iSubItem);

   };

} // namespace user





