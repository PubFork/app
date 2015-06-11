#pragma once


namespace macos
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::user::copydesk,
      virtual public ::user::interaction
   {
   public:


      copydesk(::aura::application * papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(stringa & stra);

      virtual int32_t get_file_count();
      virtual void get_filea(stringa & stra);

      virtual void set_plain_text(const char * psz);
      virtual string get_plain_text();


      virtual bool desk_to_dib(::draw2d::dib * pdib);
      

   };


} // namespace macos


