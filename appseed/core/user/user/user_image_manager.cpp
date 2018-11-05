#include "framework.h"

namespace user
{

   image_manager::image_manager()
   {
      m_pimagelist            = NULL;
      m_pimagelistDisable     = NULL;
   }

   image_manager::~image_manager()
   {
   }


   bool image_manager::Initialize(::aura::application * papp, UINT uiaMenuV003Map [][2])
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(uiaMenuV003Map);
      ::exception::throw_not_implemented(get_app());

      return true;

   }

   image_list & image_manager::GetImageList()
   {
      return *m_pimagelist;
   }

   image_list & image_manager::GetImageListDisable()
   {
      return *m_pimagelistDisable;
   }


   /*void image_manager::LoadToolbar(toolbar & toolbar, UINT * pui)
   {

      toolbar.GetToolBarCtrl().SetImageList(&GetImageList());
      TBBUTTON tbb;

      Carray < UINT, UINT > uia;
      while(*pui != 0xffffffff)
      {
         tbb.idCommand = *pui;
         uia.remove_all();
         m_rel.GetFromA(*pui, uia);
         if(uia.get_size() > 0)
         {
            tbb.iBitmap = uia[0];
         }
         else
         {
            tbb.iBitmap = -1;
         }
         tbb.fsState = 0;
         if(*pui == 0)
         {
            tbb.fsStyle = TBSTYLE_SEP;
         }
         else
         {
            tbb.fsStyle = TBSTYLE_BUTTON;
         }
         tbb.dwData = 0;
         tbb.iString = -1;
         toolbar.GetToolBarCtrl().AddButtons(1, &tbb);
         pui++;
      }

   }*/

   /*
   void image_manager::LoadToolbar(simple_toolbar & toolbar, UINT * pui)
   {

      toolbar._001SetImageList(&GetImageList());
      TBBUTTON tbb;
      memset(&tbb, 0, sizeof(tbb));

      UINT user;
      while(*pui != 0xffffffff)
      {
         tbb.idCommand = *pui;
         if(m_rel.Lookup(*pui, user))
         {
            tbb.iBitmap = user;
         }
         else
         {
            tbb.iBitmap = -1;
         }
         tbb.fsState = 0;
         if(*pui == 0)
         {
            tbb.fsStyle = TBSTYLE_SEP;
         }
         else
         {
            tbb.fsStyle = TBSTYLE_BUTTON;
         }
         tbb.dwData = 0;
         tbb.iString = -1;
         toolbar.AddButton(&tbb);
         pui++;
      }
      toolbar._001Layout();
   }
   */

} // namespace user
