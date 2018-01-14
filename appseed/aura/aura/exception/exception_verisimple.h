#pragma once


class CLASS_DECL_AURA verisimple_exception:
   public call_stack
{
   public:


      string m_strMessage;


      verisimple_exception(const string& strMessage = "");
      virtual ~verisimple_exception();


};



#ifdef DEBUG

CLASS_DECL_AURA ::file::ostream & operator << (::file::ostream & dumpcontext,const verisimple_exception & e);

#endif

