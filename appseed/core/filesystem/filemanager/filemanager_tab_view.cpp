#include "framework.h"


namespace filemanager
{


   tab_view::tab_view(::aura::application * papp) :
      object(papp),
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
   }

   tab_view::~tab_view()
   {
   }


   void tab_view::assert_valid() const
   {
      ::user::tab_view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      ::user::tab_view::dump(dumpcontext);
   }



   void tab_view::install_message_routing(::message::sender * pinterface)
   {

      ::user::tab_view::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);
      IGUI_MSG_LINK(WM_SETFOCUS, pinterface, this, &tab_view::_001OnCreate);

   }


   void tab_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      impact::on_update(pSender, lHint, phint);

      ::user::tab_view::on_update(pSender, lHint, phint);

      if (phint != NULL)
      {

         if (base_class < ::user::view_update_hint > ::bases(phint))
         {

            sp(::user::view_update_hint) puh = phint;

            if (puh->is_type_of(::user::view_update_hint::hint_open_document))
            {

               //if (m_viewmap.get_count() == 0)
               //{

               //   set_cur_tab_by_id(0);

               //}

            }

         }
         else if (base_class < update_hint > ::bases(phint))
         {

            update_hint * puh = (update_hint *) phint;

            if (puh->is_type_of(update_hint::TypeInitialize))
            {

               string str;

               str.Format("(%d,%d)",filemanager_manager().get_filemanager_data()->m_iTemplate,filemanager_manager().get_filemanager_data()->m_iDocument);

               sp(::database::client) pclient = GetParentFrame();

               if (pclient.is_set())
               {

                  pclient->set_data_key_modifier(str);

               }

            }
            else if (puh->is_type_of(update_hint::TypePop))
            {

               sp(::user::frame_window) pframe = GetParentFrame();

               if (pframe.is_set())
               {

                  pframe->InitialUpdateFrame(NULL, TRUE);

                  pframe->ShowWindow(SW_SHOW);

                  pframe->ActivateFrame(SW_SHOW);

               }

            }

         }

      }

      if (lHint == manager::hint_add_location)
      {

         set_cur_tab_by_id("add_location");

      }
      else if (lHint == manager::hint_replace_name)
      {
         set_cur_tab_by_id("replace_name");
      }
      else if (lHint == manager::hint_new_folder)
      {
         set_cur_tab_by_id("new_folder");
      }


   }

   void tab_view::on_create_view(::user::view_creator_data * pcreatordata)
   {


      if(pcreatordata->m_id.is_null())
      {
         return;
      }
      else if (pcreatordata->m_id == "add_location"
               || pcreatordata->m_id == "replace_name"
               || pcreatordata->m_id == "new_folder")
      {
         sp(::create) createcontext(allocer());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = pcreatordata->m_pholder;

         Session.filemanager().m_ptemplateForm->request_create(createcontext);

         sp(::user::document) pdoc = ::user::get_document(createcontext);

         if (pdoc == NULL)
            return;
         form * pformview = pdoc->get_typed_view < form >();
         ::user::form_update_hint uh;
         uh.m_etype = ::user::form_update_hint::type_browse;
         if (pcreatordata->m_id == "new_folder")
         {
            uh.m_strForm = "matter://filemanager/new_folder.html";
         }
         if (pcreatordata->m_id == "replace_name")
         {
            uh.m_strForm = "matter://filemanager/replace_name_in_file_system.html";
         }
         else if (pcreatordata->m_id == "add_location")
         {
            uh.m_strForm = "matter://filemanager/add_location_1.html";
         }

         pformview->m_idCreator = pcreatordata->m_id;

         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = ::user::form_update_hint::type_after_browse;

         pdoc->update_all_views(NULL, 0, &uh);

         pformview->m_pmanager = dynamic_cast < ::filemanager::manager * > ( m_pviewdata->m_pdoc);

         pcreatordata->m_pdoc = pdoc;

      }
      else if(pcreatordata->m_id == "filemanager::operation")
      {

         sp(::create) createcontext(allocer());

         createcontext->m_bMakeVisible = false;

         createcontext->m_puiParent = this;

         Session.filemanager().m_ptemplateOperation->request_create(createcontext);

         sp(operation_document) pdoc = ::user::get_document(createcontext);


         if (pdoc == NULL)
         {

            return;

         }

         sp(::user::impact) pview = pdoc->get_view(0);

         pcreatordata->m_pwnd = (pview->GetParentFrame());

         pcreatordata->m_pdoc = pdoc;

      }
      else
      {

         ::filemanager::data * pfilemanagerdata = canew(::filemanager::data(get_app()));

         pfilemanagerdata->m_pcallback = &Session.filemanager();

         pfilemanagerdata->m_pmanagertemplate = Session.filemanager();

         pfilemanagerdata->m_bFileSize = true;

         pfilemanagerdata->m_bTransparentBackground = true;

         sp(::create) createcontext(allocer());

         createcontext->m_bMakeVisible = true;

         createcontext->m_puiParent = pcreatordata->m_pholder;

         createcontext->oprop("filemanager::data") = pfilemanagerdata;

         string str = pcreatordata->m_id;

         ::str::begins_eat_ci(str, "verifile://");

         ::file::path pathFolder = str;

         string strVarFile;

         if (get_document()->m_strManagerId.has_char())
         {

            strVarFile = get_document()->m_strManagerId + ":" + pathFolder;

         }

         createcontext->m_spCommandLine->m_varFile = strVarFile;

         Session.filemanager()->m_pdoctemplateChild->m_bQueueDocumentOpening = false;

         Session.filemanager()->m_pdoctemplateChild->request_create(createcontext);

         sp(manager) pmanager = ::user::get_document(createcontext);

         sp(simple_frame_window) pwndTopLevel = NULL;

         if(pmanager != NULL)
         {

            m_pfilemanager = pmanager;

            pmanager->get_filemanager_data()->m_iTemplate = Session.filemanager()->m_iTemplate;

            pmanager->get_filemanager_data()->m_iDocument = Session.filemanager()->m_iNextDocument++;

            sp(::user::impact) pview = pmanager->get_view(0);

            sp(simple_frame_window) pwnd = (pview->GetParentFrame());

            pwndTopLevel = (pview->GetTopLevelFrame());


            if (Application.dir().is(pathFolder))
            {

               pathFolder.m_iDir = 1;

            }

            pmanager->Initialize(true, pathFolder.m_iDir != 1);

            if (pathFolder.m_iDir == 1)
            {

               pmanager->FileManagerBrowse(pathFolder, ::action::source_user);

            }

            pview->set_need_layout(true);

         }

         if (pmanager == NULL)
         {

            return;

         }

         pcreatordata->m_pdoc = pmanager;

         //if (pwndTopLevel != NULL)
         //{

         //   pwndTopLevel->on_layout();

         //}

         set_need_layout();

      }

   }


   void tab_view::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

      m_pfilemanager = get_document();

   }


   sp(manager) tab_view::get_document()
   {

      return m_pdocument;

   }


} // namespace filemanager



