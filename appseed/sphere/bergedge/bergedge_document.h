#pragma once


namespace bergedge
{


   class system;
   class view;


   class CLASS_DECL_ca2 document :
      public ::userbase::document
   {
   public:


      platform::document *                m_pplatformdocument;
      nature::document *                  m_pnaturedocument;
      

      document(::ca::application * papp); 
      virtual ~document();


      void set_platform(platform::document * pdoc);
      void set_nature(nature::document * pdoc);

      ::bergedge::bergedge * get_bergedge();

      view * get_bergedge_view();
      
      virtual bool on_new_document();
      
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

#endif

   };


} // namespace bergedge


