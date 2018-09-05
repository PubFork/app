#include "framework.h"


extern bool b_prevent_xdisplay_lock_log;


void windowing_output_debug_string(const char * pszDebugString);


oswindow_data::oswindow_data()
{

   //m_plongptrmap           = new int_ptr_to_int_ptr();

   m_hthread               = 0;

   m_window                = None;

   m_pimpl                 = NULL;

   m_bMessageOnlyWindow    = false;

   m_osdisplay             = NULL;

   ZERO(m_visual);

   m_iDepth                = -1;

   m_iScreen               = -1;

   m_colormap              = None;

}

oswindow_data::~oswindow_data()
{

   //::aura::del(m_plongptrmap);

}


int32_t oswindow_data::map_window()
{

   int i = 0;

   {

      windowing_output_debug_string("\noswindow_data::map_window");

      xdisplay d(display());

      i = XMapWindow(display(), window());

   }

   if(g_psncontext != NULL)
   {

      sn_launchee_context_complete(g_psncontext);

      g_psncontext = NULL;

   }

   windowing_output_debug_string("\noswindow_data::map_window END");

   return i;

}



int32_t oswindow_data::unmap_window(bool bWithdraw)
{

   windowing_output_debug_string("\noswindow_data::unmap_window");

   xdisplay d(display());

   int i;

   if(bWithdraw)
   {

      i = XWithdrawWindow(display(), window(), m_iScreen);

   }
   else
   {

      i = XUnmapWindow(display(), window());

   }

   windowing_output_debug_string("\noswindow_data::unmap_window END");

   return i;

}


oswindow_dataptra * oswindow_data::s_pdataptra = NULL;


mutex * oswindow_data::s_pmutex = NULL;


int32_t oswindow_find_message_only_window(::user::interaction_impl * pimpl)
{

   if(pimpl == NULL)
      return -1;

   single_lock slOsWindow(oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {

      if(::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            && ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}

int32_t oswindow_find(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_osdisplay->display() == pdisplay
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

int32_t oswindow_find(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}


oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * pui)
{

   if(pui == NULL)
   {

      return NULL;

   }

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find_message_only_window(pui);

   if(iFind >= 0)
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_bMessageOnlyWindow      = true;
   pdata->m_window                  = None;
   pdata->m_pimpl                   = pui;
   pdata->m_osdisplay               = NULL;
   pdata->m_parent                  = 0;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_defer_get(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind < 0)
   {

      return NULL;

   }

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual, int iDepth, int iScreen, Colormap colormap)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind >= 0)
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;

   if(pvisual != NULL)
   {

      pdata->m_visual               = *pvisual;

   }

   pdata->m_iDepth                  = iDepth;
   pdata->m_iScreen                 = iScreen;
   pdata->m_colormap                = colormap;
   pdata->m_parent                  = 0;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(window);

   if(iFind < 0)
   {

      return NULL;

   }

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}

bool oswindow_data::bamf_set_icon()
{

   ::linux::desktop_file file(m_pimpl->m_pui->get_app());

   file.bamf_set_icon(this);

}


int oswindow_data::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
{

   return XChangeProperty(display(), window(), property, type, format, mode, data, nelements);

}

Atom oswindow_data::intern_atom(const char * pszAtomName, bool bCreate)
{

   return m_osdisplay->intern_atom(pszAtomName, bCreate);

}


bool oswindow_data::set_icon(::draw2d::dib * pdib)
{

   // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
   // http://stackoverflow.com/users/432509/ideasman42

#if 0

   unsigned int buffer[] =
   {
      16, 16,
      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
      32, 32,
      4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
   };

   xdisplay d(display());

   int iScreen = DefaultScreen(d);

   Atom net_wm_icon = d.intern_atom("_NET_WM_ICON", False);

   Atom cardinal = d.intern_atom("CARDINAL", False);

   int length = 2 + 16 * 16 + 2 + 32 * 32;

   int status = XChangeProperty(d, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);

   if(status != 0)
   {

      return false;

   }

#elif 1

   ::draw2d::dib_sp d1(m_pimpl->m_pui->allocer());

   if(!d1->create(32, 32))
   {

      return false;

   }

   d1->get_graphics()->SetStretchBltMode(HALFTONE);

   d1->get_graphics()->StretchBlt(d1->m_size, pdib->get_graphics(), pdib->m_size);

   memory m(m_pimpl->m_pui->get_app());

   int length = 2 + d1->area();

   m.allocate(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1->m_size.cx;

   pcr[1] = d1->m_size.cy;

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->m_pcolorref[i];

   }

   windowing_output_debug_string("\noswindow_data::set_icon");

   xdisplay d(display());

   Atom net_wm_icon = intern_atom("_NET_WM_ICON", False);

   Atom cardinal = intern_atom("CARDINAL", False);

   int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);

   if(status == BadAlloc)
   {


   }
   else if(status != 0)
   {

      return false;

   }

   windowing_output_debug_string("\noswindow_data::set_icon END");

   fflush(stdout);

#else

   ::draw2d::dib_sp d1(w->m_pimpl->m_pui->allocer());

   if(!d1->create(24, 24))
   {

      return false;

   }

   d1->get_graphics()->SetStretchBltMode(HALFTONE);

   d1->get_graphics()->StretchBlt(0, 0, d1->m_size.cx, d1->m_size.cy, p->get_graphics(), 0, 0, p->m_size.cx, p->m_size.cy);

   ::draw2d::dib_sp d2(w->m_pimpl->m_pui->allocer());

   if(!d2->create(54, 54))
   {

      return false;

   }

   d2->get_graphics()->SetStretchBltMode(HALFTONE);

   d2->get_graphics()->StretchBlt(0, 0, d2->m_size.cx, d2->m_size.cy, p->get_graphics(), 0, 0, p->m_size.cx, p->m_size.cy);

   memory m(w->m_pimpl->m_pui->get_app());

   int length = 2 + d1->area() + 2 + d2->area();

   m.allocate(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1->m_size.cx;

   pcr[1] = d1->m_size.cy;

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->m_pcolorref[i];

   }

   memory_offset_t o;

   o = 2 + d1->area();

   pcr[o] = d2->m_size.cx;

   pcr[o+1] = d2->m_size.cy;

   c = d2->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+o+2] = d2->m_pcolorref[i];

   }

   Display *display = w->display();

   Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);

   Atom cardinal = XInternAtom(display, "CARDINAL", False);

   int status = XChangeProperty(display, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);

   if(status != 0)
   {

      //file_put_contents_dup("/home/camilo/window.txt", ::str::from((int)w->window()));
      return false;

   }
#endif
   return true;

}


int32_t oswindow_data::store_name(const char * psz)
{

   windowing_output_debug_string("\noswindow_data::store_name");

   xdisplay d(display());

   int i = XStoreName(display(), window(), psz);

   windowing_output_debug_string("\noswindow_data::store_name END");

   return i;

}


int32_t oswindow_data::select_input(int32_t iInput)
{

   windowing_output_debug_string("\noswindow_data::select_input");

   xdisplay d(display());

   int i = XSelectInput(display(), window(), iInput);

   windowing_output_debug_string("\noswindow_data::select_input END");

   return i;

}


int32_t oswindow_data::select_all_input()
{

   windowing_output_debug_string("\noswindow_data::select_all_input");

   xdisplay d(display());

   int i = select_input(ExposureMask | ButtonPressMask);

   windowing_output_debug_string("\noswindow_data::select_all_input");

   return i;

}


void oswindow_data::post_nc_destroy()
{

   if(!::is_null(this))
   {

      oswindow_remove(display(), window());

   }

}


void oswindow_data::set_user_interaction(::user::interaction_impl * pimpl)
{

   single_lock slOsWindow(s_pmutex, true);

   if(::is_null(this))
   {

      _throw(simple_exception(get_app(), "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction"));

   }

   m_pimpl = pimpl;

   m_hthread = pimpl->m_papp->get_os_handle();

   oswindow_assign(this, pimpl);

}




bool oswindow_data::is_child(::oswindow oswindow)
{

   if (oswindow == NULL || oswindow->m_pimpl == NULL || oswindow->m_pimpl->m_pui == NULL)
   {

      return false;

   }

   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->IsChild(oswindow->m_pimpl->m_pui);

}


Window oswindow_data::get_parent_handle()
{

   single_lock slOsWindow(s_pmutex, true);

   if(::is_null(this))
      return 0;

   return m_parent;

}


oswindow oswindow_data::get_parent()
{

   if(::is_null(this))
   {

      return NULL;

   }

   return NULL;

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   if(::is_null(this))
   {

      return NULL;

   }

   xdisplay d(display());

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow->window(), 0, 0);

   return oswindowOldParent;

}


/// Post an event from the client to the X server
void oswindow_data::send_client_event(Atom atom, unsigned int numArgs, ...)
{

   XEvent xevent;

   unsigned int i;

   va_list argp;

   va_start(argp, numArgs);

   ZERO(xevent);

   xevent.xclient.type = ClientMessage;
   xevent.xclient.serial = 0;
   xevent.xclient.send_event = False;
   xevent.xclient.display = display();
   xevent.xclient.window = window();
   xevent.xclient.message_type = atom;
   xevent.xclient.format = 32;

   for (i = 0; i < numArgs; i++)
   {

      xevent.xclient.data.l[i] = va_arg(argp, int);

   }

   XSendEvent(display(), RootWindow(display(), m_iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask, &xevent);

   va_end(argp);

}


bool oswindow_data::show_window(int32_t nCmdShow)
{

   windowing_output_debug_string("\n::oswindow_data::show_window 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::show_window 1.1");

      fflush(stdout);

      return false;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(d, m_window, &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::show_window 1.2");

      return false;

   }

   if(nCmdShow == SW_HIDE)
   {

      if(attr.map_state == IsViewable)
      {

         XWithdrawWindow(d, m_window, m_iScreen);

      }

   }
   else if(nCmdShow == SW_MAXIMIZE)
   {

      if(attr.map_state != IsViewable)
      {

         XMapWindow(d, m_window);

      }

      mapped_net_state_raw(true, d, m_window, m_iScreen,
                           intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", false),
                           intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", false));

   }
   else if(nCmdShow == SW_MINIMIZE)
   {

      wm_iconify_window(this);

   }
   else
   {

      if(attr.map_state != IsViewable)
      {

         XMapWindow(d, m_window);

      }

   }

   windowing_output_debug_string("\n::oswindow_data::show_window 2");

   return true;

}


void oswindow_data::full_screen(LPCRECT lpcrect)
{

   m_pimpl->m_pui->m_eappearanceRequest = ::user::appearance_full_screen;

   rect rBest;

   int iMonitor = best_xinerama_monitor(m_pimpl->m_pui, lpcrect, rBest);

   windowing_output_debug_string("\n::oswindow_data::full_screen 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::full_screen 1.1");

      return;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::full_screen 1.2");

      fflush(stdout);

      return;

   }

   ::rect rWindow;

   rWindow.left      = attr.x;
   rWindow.top       = attr.y;
   rWindow.right     = attr.x    + attr.width;
   rWindow.bottom    = attr.y    + attr.height;

   if(rBest != rWindow)
   {

      XMoveResizeWindow(d, m_window, rBest.left, rBest.top, rBest.width(), rBest.height());

   }

   if(attr.map_state == IsViewable)
   {

      mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

   }
   else
   {

      unmapped_net_state_raw(d, window(), intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

      XMapWindow(display(), window());

   }

   windowing_output_debug_string("\n::oswindow_data::full_screen 2");

   fflush(stdout);

}


LONG_PTR oswindow_data::get_window_long_ptr(int32_t nIndex)
{

   return m_pimpl->m_longptr.operator[](nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(int32_t nIndex, LONG_PTR l)
{

   LONG_PTR lOld = m_pimpl->m_longptr[nIndex];

   if(nIndex == GWL_EXSTYLE)
   {

      if((l & WS_EX_TOOLWINDOW) ^ (m_pimpl->m_longptr[nIndex] & WS_EX_TOOLWINDOW) != 0)
      {

         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);

      }

   }

   m_pimpl->m_longptr[nIndex] = l;

   return lOld;

}


bool oswindow_data::client_to_screen(POINT * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT * pp)
{

   return true;

}



long oswindow_data::get_state()
{

   windowing_output_debug_string("\n::oswindow_data::get_state 1");

   xdisplay d(display());

   static const long WM_STATE_ELEMENTS = 2L;

   unsigned long nitems = 0;

   unsigned long leftover = 0;

   Atom atomWmState = 0;

   Atom actual_type = 0;

   int32_t actual_format = 0;

   int32_t status = 0;

   unsigned char* p = NULL;

   atomWmState = d.intern_atom("WM_STATE", false);

   status = XGetWindowProperty(d, m_window, atomWmState, 0L, WM_STATE_ELEMENTS, False, AnyPropertyType, &actual_type, &actual_format, &nitems, &leftover, &p);

   if(status == 0)
   {

      long lStatus = -1;

      if(p!= NULL)
      {

         lStatus = (long)*p;

      }

      XFree(p);

      windowing_output_debug_string("\n::oswindow_data::get_state 1.1");

      return lStatus;

   }

   windowing_output_debug_string("\n::oswindow_data::get_state 2");

   return -1;

}


bool oswindow_data::is_iconic()
{

   b_prevent_xdisplay_lock_log = true;

   bool b = get_state() == IconicState;

   b_prevent_xdisplay_lock_log = false;

   return b;

}


bool oswindow_data::is_window_visible()
{

   windowing_output_debug_string("\n::oswindow_data::is_window_visible 1");

   xdisplay d(display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::oswindow_data::is_window_visible 1.1");

      return false;

   }

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
   {

      windowing_output_debug_string("\n::oswindow_data::is_window_visible 1.2");

      return false;

   }

   windowing_output_debug_string("\n::oswindow_data::is_window_visible 2");

   return attr.map_state == IsViewable;

}


bool oswindow_data::is_destroying()
{

   if(::is_null(this))
   {

      return true;

   }

   if(m_pimpl == NULL)
   {

      return true;

   }

   if(!m_pimpl->m_pui->m_bUserElementalOk)
   {

      return true;

   }

   return false;

}


bool oswindow_data::set_window_pos(oswindow hwndInsertAfter, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags)
{

   windowing_output_debug_string("\n::oswindow_data::set_window_pos 1");

   xdisplay d(display());

   XWindowAttributes attrs;

   Window w = window();

   if(!XGetWindowAttributes(display(), window(), &attrs))
   {

      windowing_output_debug_string("\n::oswindow_data::set_window_pos 1.1");

      return false;

   }

   if(nFlags & SWP_SHOWWINDOW)
   {

      if(attrs.map_state != IsViewable)
      {

         XMapWindow(display(), window());

      }

      if(!XGetWindowAttributes(display(), window(), &attrs))
      {

         return false;

      }

   }

   if(!(nFlags & SWP_NOMOVE))
   {

      if(!(nFlags & SWP_NOSIZE))
      {

         XMoveResizeWindow(display(), window(), x, y, cx, cy);

      }
      else
      {

         XMoveWindow(display(), window(), x, y);

      }

   }
   else if(!(nFlags & SWP_NOSIZE))
   {

      XResizeWindow(display(), window(), cx, cy);

   }

   if(nFlags & SWP_HIDEWINDOW)
   {

      if(attrs.map_state == IsViewable)
      {

         XWithdrawWindow(display(), window(), m_iScreen);

      }

   }

   if(!XGetWindowAttributes(display(), window(), &attrs))
   {

      return false;

   }

   if(attrs.map_state == IsViewable)
   {

      if(!(nFlags & SWP_NOZORDER))
      {

         if(((int_ptr) hwndInsertAfter) == ZORDER_TOP || ((int_ptr) hwndInsertAfter) == ZORDER_TOPMOST)
         {

            XRaiseWindow(display(), window());

         }
         else if(((int_ptr) hwndInsertAfter) == ZORDER_BOTTOM)
         {

            XLowerWindow(display(), window());

         }

      }

   }

   windowing_output_debug_string("\n::oswindow_data::set_window_pos 2");

   return 1;

}

