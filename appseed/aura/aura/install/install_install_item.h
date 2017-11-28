#pragma once


namespace install
{


   struct install_status
   {
      int_ptr     m_lTotal;
      int_ptr     m_lProcessing;
      int_ptr     m_lOk;
      int_ptr     m_lBad;


      install_status() { ZEROP(this); }

   };



   class CLASS_DECL_AURA install_item :
      virtual public object
   {
   public:


      bootstrap *             m_pbootstrap;
      string                  m_strUrlPrefix;
      string                  m_strPath;
      string                  m_strFile;
      install_status *        m_pstatus;
      IDTHREAD                m_dwThreadId;
      string                  m_strMd5;
      string                  m_strPlatform;
      e_item_type             m_eitemtype;


      install_item(bootstrap * pbootstrap, string strFile, string strPlatform, install_status * pstatus);


      static UINT c_cdecl proc(LPVOID lp);

      void run();

      void progress(double dRate = 1.0);

      void op_spa();

      void op_set();

   };


} // namespace install


