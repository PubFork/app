#pragma once


namespace user
{


   class CLASS_DECL_BASE control_descriptor :
      virtual public object
   {
   public:


      union
      {

         void *                           m_pvoid;
         class control_ddx_dbflags *      m_pdbflags;

      } m_ddx;


      index                         m_iItem;
      ::user::interaction *         m_pui;
      ::user::interaction *         m_puiParent;
      index_map < sp(interaction) > m_controlmap;
      id                            m_id;
      id                            m_uiText;
      sp(type)                      m_typeinfo;
      index                         m_iSubItem;
      index                         m_iColumn;
      id                            m_idPrivateDataSection;
      bool                          m_bTransparent;
      e_control_type                m_econtroltype;
      bool                          m_bCreated;
      bool                          m_bSubclassed;
      e_control_ddx                 m_eddx;
      ::database::id                m_dataid;
      flags < e_control_function >  m_flagsfunction;
      e_control_data_type           m_edatatype;
      rect                          m_rect;
      property_set                  m_setValue;
      int                           m_iSubItemDisableCheckBox;
      int                           m_iSubItemDuplicateCheckBox;
      int_array                     m_iaSubItemDuplicate;
      int_array                     m_iaSubItemDisable;

      control_descriptor();
      control_descriptor(const control_descriptor & control_descriptor);
      virtual ~control_descriptor();


      void clear();
      bool operator == (const control_descriptor & control_descriptor) const;
      control_descriptor & operator = (const control_descriptor & control_descriptor);
      e_control_type get_control_type();
      void set_control_type(e_control_type e_control);
      void add_function(e_control_function e_control_function);
      void remove_function(e_control_function e_control_function);
      bool has_function(e_control_function e_control_function);
      e_control_data_type get_data_type();
      void set_data_type(e_control_data_type e_control_data_type);
      void set_ddx_dbflags(::database::id id, int_ptr value);
      control * get_control(::user::form * pform, index iItem = 0);

      index find_control(::user::interaction * pui);

   };



} // namespace user



