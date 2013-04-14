#include "framework.h"


namespace userex // ca8 + cube
{


   keyboard_layout::keyboard_layout(sp(::ca::application) papp) :
      ca(papp),
      ::user::list_data(papp),
      ::user::split_layout(papp),
      
      ::user::split_view(papp),
      place_holder_container(papp)
   {
      m_pdoc   = ::null();
      m_pview  = ::null();
   }

   keyboard_layout::~keyboard_layout()
   {
   }

   bool keyboard_layout::CreateViews()
   {

      m_pdoc = System.userex().create_form(this, this);

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.30);


      m_plistview = create_view < simple_list_view > ();

      m_plistview->m_bHoverSelect = false;
      m_plistview->m_bMultiSelect = false;

      ::user::list_column column;
      column.m_iWidth = 584;
      m_plistview->_001InsertColumn(column);
      if(m_plistview == ::null())
      {
         System.simple_message_box(::null(), "Could not create list view");
      }


      stringa straPath;
      Application.dir().ls(System.dir().ca2("app/appmatter/main/_std/_std/keyboard layout"), &straPath);
      for(int32_t i = 0; i < straPath.get_count(); i++)
      {
         ::user::keyboard_layout_id layoutid;
         if(System.user()->keyboard().initialize(&layoutid, straPath[i]))
         {
            m_layoutida.add(layoutid);
         }
      }

      m_layoutida.quick_sort(true);
      if(&System.user()->keyboard().layout() != ::null())
      {
         int32_t iFind = -1;
         for(int32_t i = 0; i < m_layoutida.get_count(); i++)
         {
            if(m_layoutida[i].m_strPath.CompareNoCase(System.user()->keyboard().layout().m_strPath) == 0)
            {
               iFind = i;
               break;
            }
         }
         if(iFind >= 0)
         {
            ::user::list::range range;
            ::user::list::item_range itemrange;
            itemrange.set_lower_bound(iFind);
            itemrange.set_upper_bound(iFind);
            range.add_item(itemrange);
            m_plistview->_001SetSelection(range);
         }
      }

      m_plistview->m_pdata = this;
      m_plistview->m_pformcallback = this;
      m_plistview->_001OnUpdateItemCount();
      SetPane(0, m_plistview, false);

      if(m_pdoc != ::null())
      {
         m_pview = m_pdoc->get_typed_view < form_view > ();
         m_pview->m_pcallback = this;
      }


      SetPane(1, m_pview, false);

      layout();


      return true;
   }

   void keyboard_layout::on_show()
   {
      if(!m_pdoc->on_open_document(Application.dir().matter("keyboard layout configuration/form.html")))
      {
         return;
      }
      /*xml::node node(get_app());
      if(node.load(System.file_as_string(System.dir().appdata("proxy.xml"))))
      {
         string strProxy = node.get_attr("server");
         int32_t iProxyPort = node.get_attr("port");
         sp(::user::interaction) pguie = m_pview->get_child_by_name("server");
         sp(text_interface) ptext =  (pguie);
         ptext->_001SetText(strProxy);
         pguie = m_pview->get_child_by_name("port");
         ptext =  (pguie);
         ptext->_001SetText(::ca::str::from(iProxyPort));
      }*/
   }

   bool keyboard_layout::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_list_clicked)
      {
         if(pevent->m_puie == m_plistview)
         {
            ::user::list::range range;
            m_plistview->_001GetSelection(range);
            if(range.get_item_count() > 0)
            {
               index iItem = range.ItemAt(0).get_lower_bound();
               if(iItem >= 0 && iItem < m_layoutida.get_count())
               {
                  System.user()->set_keyboard_layout(m_layoutida[iItem].m_strPath, true);
               }
            }
         }
      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            sp(::user::interaction) pguie = m_pview->get_child_by_name("server");
            sp(text_interface) ptext =  (pguie.m_p);
            //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
            string strServer;
            ptext->_001GetText(strServer);
            if(strServer.get_length() == 0)
            {
               System.file().del(System.dir().appdata("proxy.xml"));
            }
            else
            {
               xml::document doc(get_app());
               doc.get_root()->set_name("proxy");
               doc.get_root()->add_attr("server", strServer);
               pguie = m_pview->get_child_by_name("port");
               ptext =  (pguie.m_p);
               string strPort;
               ptext->_001GetText(strPort);
               doc.add_attr("port", strPort);
               Application.file().put_contents(System.dir().appdata("proxy.xml"), doc.get_xml());
            }
         }
      }
      return false;
   }


   void keyboard_layout::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iItem <  0 || pitem->m_iItem >= m_layoutida.get_size())
         return_(pitem->m_bOk, false);
      pitem->m_strText = m_layoutida[pitem->m_iItem].m_strName;
      pitem->m_bOk = true;
   }

   ::count keyboard_layout::_001GetItemCount()
   {

      return m_layoutida.get_size();

   }


} // namespace userex // ca8 + cube



