#pragma once


namespace user
{


   class combo_list;


   class CLASS_DECL_CORE combo_box :
      virtual public ::user::plain_edit
   {
   public:


      enum e_style
      {

         style_verisimple,
         style_simply,

      };

      enum e_data_mode
      {

         data_mode_opaque,
         data_mode_string

      };




      size                       m_sizeFull;
      index                      m_iSel;
      string                     m_strText;
      bool                       m_bCaseSensitiveMatch;

      sp(combo_list)             m_plist;

      sp(type)                   m_typeComboList;

      e_style                    m_estyle;

      bool                       m_bEdit;
      e_data_mode                m_edatamode;
      stringa                    m_straList;
      stringa                    m_straValue;



      combo_box();
      combo_box(::aura::application * papp);
      virtual ~combo_box();


      virtual void install_message_routing(::message::sender * psender) override;


      virtual void _000OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      //virtual void _001OnDrawVerisimple(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawCombo(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawStaticText(::draw2d::graphics * pgraphics);


      virtual void _001SetCurSel(index iSel, ::action::context actioncontext);
      virtual index _001GetCurSel();

      virtual void _001SetCurSelByData(uint_ptr ui, ::action::context actioncontext);

      virtual void _001GetText(string & str) const override;
      virtual void _001SetText(const string & str, ::action::context actioncontext) override;


      virtual bool _001GetListText(index iSel, string & str) const;
      virtual index _001FindListText(const string & str) const;
      virtual count _001GetListCount() const;

      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual bool get_element_rect(LPRECT lprect, e_element eelement);
      virtual e_element hit_test(point pt);


      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMove);

      virtual void _001ShowDropDown(bool bShow = true);
      virtual void _001ToggleDropDown();


      virtual void defer_create_combo_list();

      virtual bool has_action_hover() override;
      virtual bool has_text_input() override;
      virtual bool is_drop_down();



      virtual void on_layout() override;

      virtual void _001OnAfterChangeText(::action::context actioncontext) override;

      virtual void _001OnInitialUpdate() override;



      virtual bool create_window(const RECT & rect, sp(::user::interaction) puiParent, id id);

      //::count get_count();
      //index get_cur_sel();
      //index set_cur_sel(index nSelect);
      LCID GetLocale();
      LCID SetLocale(LCID nNewLocale);
      index GetTopIndex();
      index SetTopIndex(index nIndex);
      index InitStorage(::count nItems, UINT nBytes);
      void SetHorizontalExtent(UINT nExtent);
      UINT GetHorizontalExtent();
      int32_t SetDroppedWidth(UINT nWidth);
      int32_t GetDroppedWidth();

#if defined(WINDOWSEX) && (WINVER >= 0x0500)
      bool GetComboBoxInfo(PCOMBOBOXINFO pcbi);
#endif   // WINVER >= 0x0500

      // for edit control
      bool GetEditSel(strsize & nStartChar, strsize & nEndChar);
      bool LimitText(strsize nMaxChars);
      bool SetEditSel(strsize nStartChar, strsize nEndChar);

      // for combobox item
      uint_ptr GetItemData(index nIndex);
      index SetItemData(index nIndex, uint_ptr dwItemData);
      void * GetItemDataPtr(index nIndex);
      index SetItemDataPtr(index nIndex, void * pData);
      index GetLBText(index nIndex, char * lpszText);
      void GetLBText(index nIndex, string & rString);
      strsize GetLBTextLen(index nIndex);

      int32_t SetItemHeight(index nIndex, UINT cyItemHeight);
      int32_t GetItemHeight(index nIndex);
      index FindStringExact(index nIndexStart, const char * lpszFind);
      int32_t SetExtendedUI(bool bExtended = TRUE);
      bool GetExtendedUI();
      void GetDroppedControlRect(LPRECT lprect);
      bool GetDroppedState();

      // Operations
      // for drop-down combo boxes
      void ShowDropDown(bool bShowIt = TRUE);

      // manipulating listbox items
      virtual index AddString(const char * lpszString, uint_ptr dwItemData = 0);
      index DeleteString(index nIndex);
      index InsertString(index nIndex, const char * lpszString);
      void ResetContent();
      index Dir(index attr, const char * lpszWildCard);


      void clear();
      void copy();
      void Cut();
      void Paste();


      // Overridables (must override draw, measure and compare for owner draw)
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
      virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
      virtual int32_t CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
#endif

      virtual bool OnChildNotify(::message::base * pbase) override;


      virtual void _001SetCurSelByStringValue(const string & strValue,::action::context eaction_source);
//      virtual void _001SetCurSelByData(uint_ptr ui,::action::context eaction_source);

      virtual string _001GetCurSelStringValue();


      virtual COLORREF get_action_hover_border_color() override;


      //virtual void _001OnDraw(::draw2d::graphics * pgraphics);

//      virtual void _001GetListText(index iSel,string & str) const;
      //    virtual index _001FindListText(const string & str) const;
      //  virtual count _001GetListCount() const;


//      virtual index AddString(const char * lpszString,uint_ptr dwItemData);
      virtual index AddString(const char * lpszString,const string & strValue);


      virtual bool keyboard_focus_is_focusable() override;


      virtual void on_control_event(::user::control_event * pevent) override;


   };


} //  namespace user



