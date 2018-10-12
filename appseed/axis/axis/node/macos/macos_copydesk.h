#pragma once


namespace macos
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::user::copydesk
   {
   public:

      
      bool        m_bHasFile;
      bool        m_bHasText;
      bool        m_bHasDib;
      
      dispatch_source_t m_ds;

      copydesk(::aura::application * papp);
      virtual ~copydesk();


      virtual bool initialize() override;
      virtual bool finalize() override;

      virtual bool _set_filea(const ::file::patha & stra, e_op eop) override;
      virtual bool _get_filea(::file::patha & stra, e_op & eop) override;
      virtual bool _has_filea() override;
      
      virtual bool _os_has_filea();

      virtual bool _set_plain_text(const string & str) override;
      virtual bool _get_plain_text(string & str) override;
      virtual bool _has_plain_text() override;
      
      virtual bool _os_has_plain_text();


      virtual bool _desk_to_dib(::draw2d::dib * pdib) override;
      virtual bool _dib_to_desk(::draw2d::dib * pdib) override;
      virtual bool _has_dib() override;
      
      virtual bool _os_has_dib();
      
      
      virtual void _os_step();
      

   };


} // namespace macos



