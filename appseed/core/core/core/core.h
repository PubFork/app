#pragma once


#include "app/appseed/base/base/base/base.h"


#ifdef _CORE_LIBRARY
#define CLASS_DECL_CORE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CORE  CLASS_DECL_IMPORT
#endif


#ifndef __PARTIAL_CPP

class image_list;


#ifdef WINDOWS

interface ID2D1DeviceContext;

#endif



namespace user
{

   class printer;
   class tree;
   class form;
   class single_document_template;
   class main_frame;

   namespace wndfrm
   {

      class wndfrm;

   }
   enum e_mouse
   {

      mouse_left_button,
      mouse_right_button,
      mouse_middle_button

   };

} // namespace user

class service_base;


namespace bergedge
{


   class document;
   class view;


} // namespace bergedge


namespace filehandler
{


   class handler;


} // namespace filehandler


namespace html
{


   class html_ex;


} // namespace html

namespace userfs
{

   class userfs;

} // namespace userfs


namespace userex
{


   class userex;


} // namespace userex


namespace filemanager
{


   class manager;
   class data;
   class filemanager;


} // namespace filemanager


namespace user
{


   class view_creator_data;
   class form_callback;
   class split_view;


   namespace wndfrm
   {


      class interaction;


   } // namespace wndfrm

} // namespace user





namespace dynamic_source
{


   class script;
   class script_manager;


} // namespace dynamic_source

namespace core
{

#ifdef INSTALL_SUBSYSTEM

   class run_start_installer;

#endif

   CLASS_DECL_CORE bool init_core();

   CLASS_DECL_CORE bool term_core();


} // namespace core

extern "C"
bool defer_core_init();

extern "C"
CLASS_DECL_CORE bool defer_core_term();


namespace core
{
   
   
   namespace static_start
   {
      
      
      CLASS_DECL_CORE void init(void);
      
      CLASS_DECL_CORE void term(void);
      
      
   } // namespace static_start
   
   
} // namespace core





#undef App
#define App(pbaseapp) CoreApp(pbaseapp)

#undef Sess
#define Sess(pauraapp) (*pauraapp->m_pcoresession)

#undef CaSys
#define CaSys(pca) (*pca->m_pauraapp->m_pcoresystem)

#undef Sys
#define Sys(pbaseapp) (*pbaseapp->m_pcoresystem)

#define CoreApp(pbaseapp) (*pbaseapp->m_pcoreapp)
#define CoreApplication (CoreApp(m_pauraapp))


class job;




#pragma warning(disable: 4250)














class stdio_file;
struct memory_state;

#include "core_strn.h"


#include "core_less.h"




#include "core_smart_pointer_query.h"



#define ASSERT_KINDOF(class_name, object) ASSERT(base_class < class_name > ::bases(object))
#define DYNAMIC_CAST(class_name, object) (dynamic_cast < class_name * > (object))
#define ZERO_INIT_JUST_THIS(base_class) memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));




#include "core_constraint.h"





class resource_exception;
class user_exception;   
namespace aura
{
   class menu;                 // a menu

}

namespace draw2d
{
   class graphics;                   // a Display Context / HDC wrapper
   class object;            // ::draw2d::graphics_sp drawing tool
   class bitmap;           // a bitmap
   class palette;          // a palette
   class region;
   class font;
   class pen;
   class brush;
   class memory_graphics;         // ::draw2d::graphics_sp for client of window
   class window_graphics;         // ::draw2d::graphics_sp for entire window
   class paint_graphics;          // embeddable BeginPaint struct helper
}

namespace core
{
   class job;
}

class command_target;            // a target for ::fontopus::user commands

namespace user
{
   class plain_edit;            // Edit control
   class document_manager;      // impact_system manager object
   class frame_window;        // standard SDI frame
   class interaction_child;
   class combo_box;        // ComboBox control
} // namespace user


namespace math
{


   class math;


} // namespace math

namespace geometry
{

   class geometry;

} // namespace geometry
class dialog;          // a dialog

                       // standard windows controls
class CStatic;          // Static control
class CListBox;         // ListBox control
class CCheckListBox;// special listbox with checks
class CScrollBar;       // ScrollBar control

                        // frame windows
class CMDIFrameWnd; // standard MDI frame
class CMDIChildWnd; // standard MDI child
class CMiniFrameWnd;// half-height caption frame wnd

                    // views on a document
class CScrollView;  // a scrolling ::user::impact

class single_document_template;
class multiple_document_template;





#include "graphics/visual/visual_const.h"



namespace user
{

   class user;


} // namespace user


#include "core/user/user/user_control_property.h"

#include "core_history.h"

#include "core_os_history.h"


namespace core
{

   CLASS_DECL_CORE void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString);
   CLASS_DECL_CORE bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep = '\n');

}

#include "core_process_data.h"

#include "core_types.h"

#include "core_match.h"

#include "core_progress_interface.h"

#include "app/appseed/core/core/os/os.h"

#include "core_debug.h"

#include "core_iterator.h"
#include "core_insert_iterator.h"
#include "core_back_insert_iterator.h"
#include "core_std_pair.h"


#include "core_muldiv32.h"


#include "core_logic.h"

#include "core_util1.h"

#include "app/appseed/core/math/math_math.h"


#include "app/appseed/core/user/user/user.h"

#include "core_debug.h"

#include "core/filesystem/filehandler/filehandler.h"

#include "core_patch.h"

#include "filesystem/filemanager/filemanager_callback.h"

#include "filesystem/filemanager/filemanager_item_action.h"

#include "core_application.h"

#include "core_simple_app.h"

#include "core/math/math_math.h"

#include "core_library.h"

#include "core_session.h"

#include "core_system.h"

#include "core/core/plugin/plugin.h"






#include "core.inl"



#endif





