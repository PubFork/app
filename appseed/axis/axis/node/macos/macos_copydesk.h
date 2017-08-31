#pragma once


namespace macos
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::user::copydesk
   {
   public:


      copydesk(::aura::application * papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void set_filea(const ::file::patha & stra) override;

      virtual int32_t get_file_count() override;
      virtual void get_filea(::file::patha & stra) override;

      virtual void set_plain_text(const char * psz) override;
      virtual string get_plain_text() override;


      virtual bool desk_to_dib(::draw2d::dib * pdib);
      

   };


} // namespace macos



