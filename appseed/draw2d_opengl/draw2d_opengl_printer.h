#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL printer :
      virtual public ::aura::printer
   {
   public:


      class CLASS_DECL_DRAW2D_OPENGL document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::aura::application * papp);
         virtual ~document_properties();


         virtual bool initialize(::draw2d_opengl::printer * pprinter, DEVMODE * pdevmode = NULL);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::aura::application * papp);
      virtual ~printer();


      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace draw2d_opengl


