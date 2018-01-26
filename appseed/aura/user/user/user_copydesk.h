#pragma once


namespace user
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::object
   {
      public:


        enum e_op
        {

         op_copy,
         op_cut,

      };


         copydesk(::aura::application * papp);
         virtual ~copydesk();


         virtual bool initialize();
         virtual bool finalize();

         virtual bool set_filea(const ::file::patha & stra, e_op eop);
         virtual bool get_filea(::file::patha & stra, e_op & eop);
         virtual bool has_filea();

         virtual bool set_plain_text(const string & str);
         virtual bool get_plain_text(string & str);
         virtual bool has_plain_text();

         virtual bool desk_to_dib(::draw2d::dib * pdib);
         virtual bool dib_to_desk(::draw2d::dib * pdib);
         virtual bool has_dib();

   };


   typedef smart_pointer < copydesk > copydesk_sp;


} // namespace user



