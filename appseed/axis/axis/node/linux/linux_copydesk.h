
#pragma once


namespace linux
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::user::copydesk
   {
   public:




      copydesk(::aura::application * papp);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual bool set_filea(const ::file::patha & patha, e_op eop) override;
      virtual bool get_filea(::file::patha & patha, e_op & eop) override;
      virtual bool has_filea() override;


      virtual bool set_plain_text(const string & str) override;
      virtual bool get_plain_text(string & str) override;
      virtual bool has_plain_text() override;

      virtual bool desk_to_dib(::draw2d::dib * pdib) override;
      virtual bool dib_to_desk(::draw2d::dib * pdib) override;
      virtual bool has_dib() override;

   };


} // namespace linux



