#include "framework.h"



#include <winapifamily.h>
#include <shlwapi.h>
#include <wrl/client.h>
#include <D2d1_1.h>


#include <DXGI1_2.h>
#include <Dwrite.h>
#include <D3D11.h>
#include <D3D11_1.h>
#include <Dxgi1_3.h>
#include <Initguid.h>
#include <DXGIDebug.h>

#include "draw2d_direct2d_global.h"

typedef HRESULT WINAPI FN_DXGIGetDebugInterface(REFIID riid, void **ppDebug);

typedef FN_DXGIGetDebugInterface * PFN_DXGIGetDebugInterface;

class dxgidebug
{
public:

   Microsoft::WRL::ComPtr<IDXGIDebug> d;

   void init()
   {

#ifdef METROWIN
      HRESULT hr = DXGIGetDebugInterface1(0, IID_IDXGIDebug1, &d);
#else

      Microsoft::WRL::ComPtr<IDXGIInfoQueue> dxgiInfoQueue;

      typedef HRESULT(WINAPI * LPDXGIGETDEBUGINTERFACE)(REFIID, void **);

      HMODULE dxgidebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
      if (dxgidebug)
      {
         auto dxgiGetDebugInterface = reinterpret_cast<LPDXGIGETDEBUGINTERFACE>(
                                      reinterpret_cast<void*>(GetProcAddress(dxgidebug, "DXGIGetDebugInterface")));
         if (SUCCEEDED(dxgiGetDebugInterface(IID_IDXGIDebug, &d)))
         {

         }
         //d.Attach(dxgiGetDebugInterface);
         //if (SUCCEEDED(dxgiGetDebugInterface(IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
         //{
         // dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
         //dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
         //}
      }

#endif


   }

   void debug()
   {

      if (d.Get() != NULL)
      {

         ::output_debug_string("MY_DEBUG : IDXGIDebug::ReportLiveObjects");

         d->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);

      }
      else
      {

         init();

      }

   }

} *g_pdxgidebug;


CLASS_DECL_AURA void directx_debug()
{

   g_pdxgidebug->debug();

}


namespace draw2d_direct2d
{


   class plugin
   {
   public:

      Microsoft::WRL::ComPtr<IDWriteFactory> g_pwritefactory;
      Microsoft::WRL::ComPtr<ID2D1Factory1> g_pd2factory;
      Microsoft::WRL::ComPtr<ID2D1Device> g_pd2device;
      Microsoft::WRL::ComPtr<ID2D1DeviceContext> g_pd2devicecontext;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_pd3devicecontext;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext1> g_pd3devicecontext1;
      Microsoft::WRL::ComPtr<ID3D11Device> g_pd3device;
      Microsoft::WRL::ComPtr<ID3D11Device1> g_pd3device1;
      Microsoft::WRL::ComPtr<IDXGIDevice> g_pdxgidevice;

      D3D_FEATURE_LEVEL g_featurelevel;

      void initialize();

   } *g_pplugin;


   CLASS_DECL_AURA void finalize()
   {

      delete g_pplugin;

      delete g_pdxgidebug;

   }

   CLASS_DECL_AURA void initialize()
   {

      g_pdxgidebug = new dxgidebug;

      g_pplugin = new plugin;

      g_pplugin->initialize();

   }


   void plugin::initialize()
   {

      // This flag adds support for surfaces with a different color channel ordering
      // than the API default. It is required for compatibility with Direct2D.
      UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)

      // If the project is in a debug build, enable debugging via SDK Layers with this flag.
      creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

#endif

      // This array defines the set of DirectX hardware feature levels this app will support.
      // Note the ordering should be preserved.
      // Don't forget to declare your application's minimum required feature level in its
      // description.  All applications are assumed to support 9.1 unless otherwise stated.
      D3D_FEATURE_LEVEL featureLevels[] =
      {
         D3D_FEATURE_LEVEL_11_1,
         D3D_FEATURE_LEVEL_11_0,
         D3D_FEATURE_LEVEL_10_1,
         D3D_FEATURE_LEVEL_10_0,
         D3D_FEATURE_LEVEL_9_3,
         D3D_FEATURE_LEVEL_9_2,
         D3D_FEATURE_LEVEL_9_1
      };

      // Create the Direct3D 11 API device object and a corresponding context.
      Microsoft::WRL::ComPtr<ID3D11Device> device;

      Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

      ::dx::throw_if_failed(
      D3D11CreateDevice(
      nullptr,                    // Specify nullptr to use the default adapter.
      D3D_DRIVER_TYPE_HARDWARE,
      0,
      creationFlags,              // Set debug and Direct2D compatibility flags.
      featureLevels,              // List of feature levels this app can support.
      ARRAYSIZE(featureLevels),
      D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Metro style apps.
      &device,                    // Returns the Direct3D device created.
      &g_featurelevel,            // Returns feature level of device created.
      &context                    // Returns the device immediate context.
      )
      );

      // Get the Direct3D 11.1 API device and context interfaces.
      ::dx::throw_if_failed(
      device.As(&g_pd3device)
      );

      ::dx::throw_if_failed(
      device.As(&g_pd3device1)
      );

      ::dx::throw_if_failed(
      context.As(&g_pd3devicecontext)
      );

      ::dx::throw_if_failed(
      context.As(&g_pd3devicecontext1)
      );

      // Get the underlying DXGI device of the Direct3D device.
      ::dx::throw_if_failed(
      device.As(&g_pdxgidevice)
      );

      // Create the Direct2D device object and a corresponding context.
      ::dx::throw_if_failed(
      get_d2d1_factory1()->CreateDevice(g_pdxgidevice.Get(), &g_pd2device)
      );

   }


} // namespace draw2d_direct2d


#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define d2d1_thread_model D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?

CLASS_DECL_AURA IDWriteFactory * global_draw_get_write_factory(bool bCreate)
{

   if (::draw2d_direct2d::g_pplugin->g_pwritefactory != NULL || !bCreate)
      return ::draw2d_direct2d::g_pplugin->g_pwritefactory.Get();

   HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &::draw2d_direct2d::g_pplugin->g_pwritefactory);

   if (FAILED(hr))
      return NULL;

   return ::draw2d_direct2d::g_pplugin->g_pwritefactory.Get();

}


ID2D1Factory1 * get_d2d1_factory1(bool bCreate)
{


   if (::draw2d_direct2d::g_pplugin->g_pd2factory != NULL || !bCreate)
   {

      return ::draw2d_direct2d::g_pplugin->g_pd2factory.Get();

   }

   d2d1_fax_options options;

   memset(&options, 0, sizeof(options));

   HRESULT hr = ::D2D1CreateFactory(d2d1_thread_model, __uuidof(ID2D1Factory1), &options, &::draw2d_direct2d::g_pplugin->g_pd2factory);

   if (FAILED(hr))
   {

      return NULL;

   }

   ::draw2d::device_lock::g_pfactory = ::draw2d_direct2d::g_pplugin->g_pd2factory.Get();

   return ::draw2d_direct2d::g_pplugin->g_pd2factory.Get();

}


ID3D11Device * global_draw_get_d3d11_device()
{

   return ::draw2d_direct2d::g_pplugin->g_pd3device.Get();

}


ID3D11Device1 * global_draw_get_d3d11_device1()
{

   return ::draw2d_direct2d::g_pplugin->g_pd3device1.Get();

}


ID3D11DeviceContext * global_draw_get_d3d11_device_context()
{

   return ::draw2d_direct2d::g_pplugin->g_pd3devicecontext.Get();

}


ID3D11DeviceContext1 * global_draw_get_d3d11_device_context1()
{

   return ::draw2d_direct2d::g_pplugin->g_pd3devicecontext1.Get();

}

IDXGIDevice * global_draw_get_dxgi_device()
{

   return ::draw2d_direct2d::g_pplugin->g_pdxgidevice.Get();

}

ID2D1Device * global_draw_get_d2d1_device()
{

   return ::draw2d_direct2d::g_pplugin->g_pd2device.Get();

}

CLASS_DECL_AURA float point_dpi(float points)
{

   FLOAT dpiX, dpiY;

   get_d2d1_factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return points * dpiY / 72.f;

}

CLASS_DECL_AURA float dpiy(float y)
{

   FLOAT dpiX, dpiY;

   get_d2d1_factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y * dpiY / 96.f;

}

CLASS_DECL_AURA float dpix(float x)
{

   FLOAT dpiX, dpiY;

   get_d2d1_factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x * dpiX / 96.f;

}


CLASS_DECL_AURA float y_dpi(float y)
{

   FLOAT dpiX, dpiY;

   get_d2d1_factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return y / dpiY;

}

CLASS_DECL_AURA float x_dpi(float x)
{

   FLOAT dpiX, dpiY;

   get_d2d1_factory1()->GetDesktopDpi(&dpiX, &dpiY);

   return x / dpiX;

}



