#include "framework.h"


namespace user
{


   menu_central::menu_central(::aura::application * papp) :
      object(papp),
      ::aura::department(papp),
      m_fontMenu(allocer())
   {

      m_pil             = canew(image_list(papp));
      m_pilHue          = canew(image_list(papp));
      m_pilBlend        = canew(image_list(papp));
      m_pilHueLight     = canew(image_list(papp));


      VERIFY(m_fontMenu->create_point_font(FONT_SANS, 11));

   #ifdef WINDOWSEX
      if(!MenuV033GetImageList()->create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 10))
      {
         _throw(simple_exception(papp, "resource exception menu_central constructor"));
      }
   #else
      if(!MenuV033GetImageList()->create(16, 16, 0, 0, 10))
      {
         _throw(simple_exception(papp, "resource exception menu_central constructor"));
      }
   #endif

   }


   menu_central::~menu_central()
   {

   }


   bool menu_central::MenuV033AddImageMap(::xml::node * pnode)
   {

      /*   if(!MenuV033GetImageList()->create(
            16, 16,
            ILC_COLOR24 | ILC_MASK,
            0, 10))
         {
            return FALSE;
         }*/

      int32_t iIndex;

      id id;

      for(int32_t i = 0; i < pnode->children().get_count(); i++)
      {

         sp(::xml::node) lpchild = pnode->child_at(i);

         string strId;
         lpchild->get_attr("id", strId);
         string strImage;
         lpchild->get_attr("img", strImage);
         iIndex = MenuV033GetImageList()->add_matter(strImage);
         id = strId;

         m_mapCommandImage.set_at(id, iIndex);

         m_mapImageCommand.set_at(iIndex, id);

      }


      ::draw2d::graphics_sp spgraphics(allocer());
      spgraphics->CreateCompatibleDC(NULL);

      class imaging & imaging = Application.imaging();

      imaging.CreateHueImageList(
      spgraphics,
      m_pilHue,
      MenuV033GetImageList(),
      RGB(192, 192, 180),
      0.50);

      imaging.Createcolor_blend_ImageList(
      m_pilBlend,
      MenuV033GetImageList(),
      RGB(255, 255, 240),
      64);

      imaging.CreateHueImageList(
      spgraphics,
      m_pilHueLight,
      m_pil,
      RGB(220, 220, 215),
      0.5);

      return true;

   }




   ::draw2d::font * menu_central::MenuV033GetFont()
   {
      return GetMenuFont();
   }

   ::draw2d::font * menu_central::GetMenuFont()
   {
      return m_fontMenu;
   }



   /*bool menu_central::MenuV033CreateImageMap()
   {
       UINT uiaMenuV003Map [][2] =
       {
           {ID_FILE_NEW, 0},
           {ID_FILE_OPEN, 1},
           {ID_FILE_SAVE, 2},
           {ID_VIEW_FULL_SCREEN, 7},
           {ID_TOOLS_ALBUM, 8},
           {ID_VIEW_PLAYLIST, 9},
           {ID_VIEW_LYRICS, 10},
           {ID_TOOLS_MIXER, 11},
           {ID_PLAY, 12},
           {ID_STOP, 13},
           {ID_PAUSE, 14},
           {ID_NEXTSONG, 15},
           {ID_ALBUM_NAVIGATOR, 20},
           {ID_ALBUM_FULLLIST, 21},
           {ID_ALBUM_TREELIST, 22},
           {ID_ALBUM_SEARCHLIST, 23},
           {ID_ALBUM_RESERVESONG, 24},
           {ID_CHECK, 25},
           {ID_ALBUM_DUPLICATESLIST, 27},
       };

       UINT uiSize = sizeof(uiaMenuV003Map) / (sizeof(UINT) * 2);
       for(UINT user = 0; user < uiSize; user++)
       {
           theDll.m_relMenuV033ImageMap.add(uiaMenuV003Map[user][0], uiaMenuV003Map[user][1]);
       }
       return ;
   }*/


   int menu_central::command_image(id id)
   {

      int iImage;

      if(!m_mapCommandImage.Lookup(id, iImage))
      {

         return -1;

      }

      return iImage;

   }


   id menu_central::image_command(int iImage)
   {

      id id;

      if(!m_mapImageCommand.Lookup(iImage, id))
      {

         return ::id();

      }

      return id;

   }


   sp(image_list) menu_central::MenuV033GetImageList()
   {

      return m_pil;

   }


   sp(image_list) menu_central::MenuV033GetImageListHue()
   {

      return m_pilHue;

   }


   sp(image_list) menu_central::MenuV033GetImageListBlend()
   {

      return m_pilBlend;

   }


   sp(image_list) menu_central::MenuV033GetImageListHueLight()
   {

      return m_pilHueLight;

   }


} // namespace user



