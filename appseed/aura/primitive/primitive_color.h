#pragma once



//#define  HLSMAX   100.0 /* H,L, and S vary over 0-HLSMAX */
//#define  RGBMAX   100.0   /* R,G, and B vary over 0-RGBMAX */
/* HLSMAX BEST IF DIVISIBLE BY 6 */
/* RGBMAX, HLSMAX must each fit in a byte. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED_HUE (HLSMAX*2.0/3.0)

enum e_color
{

   color_black,
   color_red,
   color_green,
   color_blue,
   color_white,
   color_yellow,
   color_magenta,
   color_cyan,
   color_gray,

};

class CLASS_DECL_AURA color
{
public:
   double            m_dR;
   double            m_dG;
   double            m_dB;
   double            m_dA;
   uchar     m_uchR;
   uchar     m_uchG;
   uchar     m_uchB;
   uchar     m_uchA;

   class CLASS_DECL_AURA hls
   {
   public:
      double m_dH;
      double m_dL;
      double m_dS;
   };

   color();
   color(const color & color);
   color(e_color ecolor, double dAlpha = 1.0);
   color(const hls & hls, double dAlpha = 1.0);
   color(COLORREF cr);
   virtual ~color();

   void hls_mult(double dRateH, double dRateL, double dRateS);
   void hls_rate(double dRateH, double dRateL, double dRateS);
   void set_rgb(COLORREF cr);
   void set_bgr(uint32_t dw);
   void get_hls(
   double & dH,
   double & dL,
   double & dS) const;

   void set_hls(
   double dHue,
   double dLightness,
   double dSaturation);
   void hls_mult(hls & hls);
   void hls_rate(hls & hls);
   void get_hls(
   hls & hls) const;
   void set_hls(
   const hls & hls);

   uint32_t get_rgb() const;
   uint32_t get_bgr() const;
   uint32_t get_rgba() const;
   uint32_t get_bgra() const;
//   RGBQUAD get_rgbquad() const;


   operator COLORREF() const;
//   operator RGBQUAD() const;

   color & operator = (const color & color);
   color & operator = (COLORREF cr);
   color & operator = (const hls & hls);

   bool parse_color(const char * psz);

   void set_COLORREF(COLORREF cr);

   void hue_offset(double dRadians);


};



#define rgba_get_r(rgba)      ((byte)(rgba & 0xff))
#define rgba_get_g(rgba)      ((byte)((rgba >> 8) & 0xff))
#define rgba_get_b(rgba)      ((byte)((rgba >> 16) & 0xff))
#define rgba_get_a(rgba)      ((byte)((rgba >> 24) & 0xff))


namespace visual
{


   namespace rgba
   {


      enum echannel
      {

         channel_red = 0,
         channel_green = 1,
         channel_blue = 2,
         channel_alpha = 3

      };


   } // namespace rgba


} // namespace visual


#define rgb_get_r_value(rgb)      (LOBYTE(rgb))
#define rgb_get_g_value(rgb)      (LOBYTE((rgb)>>8))
#define rgb_get_b_value(rgb)      (LOBYTE((rgb)>>16))
#define rgb_get_a_value(rgb)      (LOBYTE((rgb)>>24))

#define bgr_get_b_value(bgr)      (LOBYTE(bgr))
#define bgr_get_g_value(bgr)      (LOBYTE((bgr)>>8))
#define bgr_get_r_value(bgr)      (LOBYTE((bgr)>>16))
#define bgr_get_a_value(bgr)      (LOBYTE((bgr)>>24))


CLASS_DECL_AURA COLORREF alpha_color(BYTE bAlpha, COLORREF cr);
CLASS_DECL_AURA COLORREF alpha_color(BYTE bAlpha, e_color ecolor);
CLASS_DECL_AURA COLORREF opaque_color(COLORREF cr);
CLASS_DECL_AURA COLORREF pure_color(e_color ecolor);
CLASS_DECL_AURA COLORREF opaque_color(e_color ecolor);
