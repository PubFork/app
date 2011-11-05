#pragma once


#include <X11/Xlib.h>
#include <X11/Xutil.h>


typedef Window HWND;


class CLASS_DECL_____ device_context
{
public:


   Display *   m_display;
   Drawable    m_d;
   GC          m_gc;
   HWND        m_hwnd;


   device_context();


};



struct tagEXTLOGPEN :
   public gdi_object
{
    DWORD       elpPenStyle;
    DWORD       elpWidth;
    UINT        elpBrushStyle;
    COLORREF    elpColor;
    ULONG_PTR   elpHatch;
    DWORD       elpNumEntries;
    DWORD       elpStyleEntry[1];
};


struct tagLOGBRUSH :
   public gdi_object
{
	UINT        lbStyle;
	COLORREF    lbColor;
	ULONG_PTR   lbHatch;
};



struct tagLOGRGN :
   public gdi_object
{
	UINT        m_uiSize;
	byte *      m_puchData;
};




struct  tagFONTA :
   public gdi_object,
   public tagLOGFONTA
{

};




struct tagBITMAPINFO :
   public gdi_object
{
public:

    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];


};


