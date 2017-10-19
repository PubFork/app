#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::fontopus::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace user
{


   impact_system::on_open_document::on_open_document()
   {

   }


   impact_system::on_open_document::~on_open_document()
   {

   }


   impact_system::impact_system(::aura::application * papp, const char * pszMatter, sp(type) pDocClass, sp(type) pFrameClass, sp(type) pViewClass) :
      ::object(papp)
   {

      m_puiOwner = NULL;

      m_bQueueDocumentOpening = true;
      m_strMatter = pszMatter;
      m_typeinfoDocument = pDocClass;
      m_typeinfoFrame = pFrameClass;
      m_typeinfoView = pViewClass;
      m_pAttachedFactory = NULL;
      m_bAutoDelete = TRUE;   // usually allocated on the heap

      load_template();

   }


   void impact_system::load_template()
   {
   }


   impact_system::~impact_system()
   {

   }

   bool impact_system::GetDocString(string & rString, enum DocStringIndex i) const
   {
      //xxx return ::core::extract_sub_string(rString, m_strDocStrings, (int32_t)i);
      return false;
   }


   void impact_system::add_document(::user::document * pdocument)
   {

      ASSERT(pdocument->m_pimpactsystem == NULL);   // no template attached yet

      pdocument->m_pimpactsystem = this;

      pdocument->install_message_routing(pdocument);

   }


   void impact_system::remove_document(::user::document * pdocument)
   {
      ASSERT(pdocument->m_pimpactsystem == this);   // must be attached to us
      pdocument->m_pimpactsystem = NULL;
   }

   impact_system::Confidence impact_system::MatchDocType(const ::file::path & lpszPathName,::user::document *& rpDocMatch)
   {

      ASSERT(lpszPathName.has_char());

      rpDocMatch = NULL;

      // go through all documents
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         if (pdocument->get_file_path() == lpszPathName)
         {
            // already open
            rpDocMatch = pdocument;
            return yesAlreadyOpen;
         }
      }

      // see if it matches our default suffix
      string strFilterExt;
      if (GetDocString(strFilterExt, impact_system::filterExt) &&
            !strFilterExt.is_empty())
      {
         // see if extension matches
         ASSERT(strFilterExt[0] == '.');
         string strExtension = lpszPathName.ext();
         if (strExtension.has_char())
         {
            if (strExtension.compare_ci(strFilterExt) == 0)
            {
               return yesAttemptNative; // extension matches, looks like ours
            }
         }
      }

      // otherwise we will guess it may work
      return yesAttemptForeign;
   }

   ::user::document * impact_system::create_new_document(::create * pcreate)
   {
      // default implementation constructs one from sp(type)
      if (!m_typeinfoDocument)
      {
         TRACE(::aura::trace::category_AppMsg, 0, "Error: you must override impact_system::create_new_document.\n");
         ASSERT(FALSE);
         return NULL;
      }

      ::aura::application * papp = pcreate->get_app() != NULL ? pcreate->get_app() : get_app();

      sp(::user::document) pdocument = App(papp).alloc(m_typeinfoDocument);
      if (pdocument == NULL)
      {
         TRACE(::aura::trace::category_AppMsg, 0, "Warning: Dynamic create of ::user::document type %hs failed.\n",
               m_typeinfoDocument->name());
         return NULL;
      }
      pdocument->on_create(pcreate);
      ASSERT_KINDOF(::user::document, pdocument);
      add_document(pdocument);
      return pdocument;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Default frame creation

   sp(::user::frame_window) impact_system::create_new_frame(::user::document * pdocument, sp(::user::frame_window) pOther, ::create * pcreate)
   {

      // create a frame wired to the specified ::user::document

      ASSERT(m_strMatter.get_length() > 0); // must have a resource ID to load from

      ::user::create usercreate;

      SRESTORE(pcreate->m_pusercreate, &usercreate);

      usercreate.m_puiCurrentFrame = pOther;

      usercreate.m_pdocumentCurrent = pdocument;

      if (pcreate->m_puiAlloc != NULL)
      {

         usercreate.m_puiNew = pcreate->m_puiAlloc;

      }
      else
      {

         usercreate.m_typeinfoNewView = m_typeinfoView;

      }

      usercreate.m_ptemplateNewDocument = this;

      if (!m_typeinfoFrame)
      {

         TRACE(::aura::trace::category_AppMsg, 0, "Error: you must override impact_system::create_new_frame.\n");

         ASSERT(FALSE);

         return NULL;

      }

      ::aura::application * papp = pcreate->get_app() != NULL ? pcreate->get_app() : get_app();

      sp(::user::frame_window) pframe = App(papp).alloc(m_typeinfoFrame);

      if (pframe == NULL)
      {

         TRACE(::aura::trace::category_AppMsg, 0, "Warning: Dynamic create of frame %hs failed.\n", m_typeinfoFrame->name());

         string strMessage;

         strMessage.Format("Warning: Dynamic create of frame %hs failed.\n\n(Does allocation was implemented)?",m_typeinfoFrame->name());

         Application.simple_message_box(NULL, strMessage);

         return NULL;

      }

      ASSERT_KINDOF(frame_window, pframe);

      pframe->m_pdocumenttemplate = this;

      if (!usercreate.m_typeinfoNewView)
      {

         TRACE(::aura::trace::category_AppMsg, 0, "Warning: creating frame with no default ::user::impact.\n");

      }

      if (m_puiOwner != NULL)
      {

         pframe->m_puiOwner = m_puiOwner;

      }

      // create new from resource
      if (!pframe->LoadFrame(m_strMatter,
                             WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
                             dynamic_cast < ::user::interaction * > (pcreate->m_puiParent), pcreate))
      {

         TRACE(::aura::trace::category_AppMsg, 0, "Warning: impact_system couldn't create a frame.\n");

         // frame will be deleted in PostNcDestroy cleanup

         return NULL;

      }

      return pframe;

   }


   void impact_system::InitialUpdateFrame(sp(::user::frame_window) pFrame, ::user::document * pdocument,
                                          bool bMakeVisible)
   {
      // just delagate to implementation in frame_window
      pFrame->InitialUpdateFrame(pdocument, bMakeVisible);
   }

   /////////////////////////////////////////////////////////////////////////////
   // impact_system commands and command helpers

   bool impact_system::save_all_modified()
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         if (!pdocument->save_modified())
            return FALSE;
      }
      return TRUE;
   }


   void impact_system::close_all_documents(bool)
   {

      for (index index = 0; index < get_document_count(); index++)
      {

         try
         {
            sp(::user::document) pdocument = get_document(index);

            pdocument->close_document();

         }
         catch (...)
         {

         }

      }

   }



   void impact_system::on_idle()
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         ASSERT_KINDOF(::user::document, pdocument);
         pdocument->on_idle();
      }
   }


   void impact_system::_001OnCmdMsg(::user::command * pcommand)
   {

      command_target::_001OnCmdMsg(pcommand);

   }


   void impact_system::dump(dump_context & dumpcontext) const
   {
      command_target::dump(dumpcontext);

      dumpcontext << "m_strMatter = " << m_strMatter;
      dumpcontext << "\nm_strDocStrings: " << m_strDocStrings;

      if (m_typeinfoDocument)
         dumpcontext << "\nm_pDocClass = " << m_typeinfoDocument->name();
      else
         dumpcontext << "\nm_pDocClass = NULL";

      if (dumpcontext.GetDepth() > 0)
      {
         dumpcontext << "\ndocument list = {";
         ::count count = get_document_count();
         for (index index = 0; index < count; index++)
         {
            sp(::user::document) pdocument = get_document(index);
            dumpcontext << (int_ptr)pdocument.m_p;
         }
         dumpcontext << "\n}";
      }

      dumpcontext << "\n";
   }

   void impact_system::assert_valid() const
   {
      command_target::assert_valid();

      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdocument = get_document(index);
         pdocument->assert_valid();
      }
   }



   void impact_system::update_all_views(sp(::user::impact) pviewSender, LPARAM lhint, ::object * puh)
   {
      ::count count = get_document_count();
      for (index index = 0; index < count; index++)
      {
         sp(::user::document) pdoc = get_document(index);
         pdoc->update_all_views(pviewSender, lhint, puh);
      }
   }

   bool impact_system::on_open_document(::user::document * pdocument, var varFile)
   {

      if (m_bQueueDocumentOpening)
      {

         class on_open_document * ponopendocument = new class on_open_document();

         ponopendocument->m_pschema = this;
         ponopendocument->m_pdocument = pdocument;
         ponopendocument->m_varFile = varFile;

         __begin_thread(get_app(), &impact_system::s_on_open_document, ponopendocument);

         return true;

      }
      else
      {

         wait_cursor wait(get_app());

         return do_open_document(pdocument, varFile);

      }

   }

   bool impact_system::do_open_document(::user::document * pdocument, var varFile)
   {

      if (!pdocument->on_open_document(varFile))
      {
         return false;
      }

      return true;

   }

   UINT impact_system::s_on_open_document(LPVOID lpvoid)
   {

      class on_open_document * ponopendocument = (class on_open_document *) lpvoid;

      ponopendocument->m_pschema->do_open_document(ponopendocument->m_pdocument, ponopendocument->m_varFile);

      delete ponopendocument;

      return 0;

   }


   void impact_system::reload_template()
   {
   }


} // namespace user







