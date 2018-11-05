#pragma once


namespace user
{


   class CLASS_DECL_CORE menu_central :
      virtual public ::aura::department
   {
   public:


      id_map < int >          m_mapCommandImage;
      ::int_map < id >        m_mapImageCommand;

      sp(image_list)          m_pil;
      sp(image_list)          m_pilHue;
      sp(image_list)          m_pilBlend;
      sp(image_list)          m_pilHueLight;
      ::draw2d::font_sp       m_fontMenu;


      menu_central(::aura::application * papp);
      virtual ~menu_central();


      sp(image_list) MenuV033GetImageList();
      sp(image_list) MenuV033GetImageListHue();
      sp(image_list) MenuV033GetImageListBlend();
      sp(image_list) MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::xml::node * pnode);

      int command_image(id id);
      id image_command(int iImage);


      ::draw2d::font * MenuV033GetFont();
      ::draw2d::font * GetMenuFont();


   };


} // namespace user



