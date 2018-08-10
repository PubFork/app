#pragma once


namespace filehandler
{


   enum e_pane_view
   {
      pane_view_none,
      pane_view_new
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

   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      e_pane_view m_eview;
   protected:
      e_type m_etype;

   };


} // namespace filehandler


