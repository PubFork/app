#pragma once


namespace prompt
{

   enum e_pane_view
   {
      pane_view_none,
      pane_view_context_menu,
      PaneViewPrimaryCommand,
      pane_view_three_action_launch,
      pane_view_configuration,
   };


   class CLASS_DECL_SPHERE pane_view_update_hint :
      public ::object
   {
   public:
      enum e_type
      {
         type_get_view,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };
      // DECLARE_DYNAMIC(pane_view_update_hint)
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      e_pane_view m_eview;
   protected:
      e_type m_etype;

   };


} // namespace prompt


