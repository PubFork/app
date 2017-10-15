#pragma once


class CLASS_DECL_AURA string_list :
   virtual public list < string >
{
   public:


      string_list();
      virtual ~string_list();


#ifdef DEBUG
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
#endif


      POSITION find(string searchValue, POSITION startAfter = NULL) const;



};


