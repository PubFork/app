#pragma once


namespace userpresence
{


   class userpresence;


} // namespace userpresence


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session,
      virtual public ::axis::application
   {
   public:


      ::user::keyboard *                                       m_pkeyboard;

      ::userpresence::userpresence *                           m_puserpresence;
      sp(::ftpfs)                                              m_pftpfs;
      sp(::fs::remote_native)                                  m_prfs;
      sp(::fs::fs)                                             m_spfs;
      sp(class ::fs::data)                                     m_spfsdata;

      bool                                                     m_bIfs;

      bool                                                     m_bMatterFromHttpCache;

      DWORD                                                    m_dwLongPhRESSingTime;


      session(::aura::application * papp);
      virtual ~session();


      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }

      virtual bool is_session() override;

      void construct(::aura::application * papp, int iPhase) override;

      virtual bool process_init() override;

      virtual bool init1() override;

      virtual bool init2() override;

      virtual bool init_application() override;

      virtual bool init() override;

      virtual void term() override;

      virtual void term_application() override;


      inline sp(class ::fs::data)               fs()           { return m_spfsdata; }
      //inline ::sockets::sockets &               sockets()      { return *m_psockets; }


      virtual size get_window_minimum_size() override;


      //virtual void  get_cursor_pos(LPPOINT lppoint);


      virtual void on_request(::create * pcreate) override;


      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      //virtual string dir().matter(const char * pszMatter,const char * pszMatter2);

      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);

      // Long PhRESSing time
      // time in milliseconds that a pressing is considered a double click
      virtual DWORD get_Long_PhRESSing_time();

      virtual void defer_initialize_user_presence() override;


      virtual string fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive = NULL) override;

      virtual bool on_create_frame_window() override;

      virtual void on_user_login(::fontopus::user * puser) override;

      ::user::keyboard & keyboard();



      virtual string fontopus_get_user_sessid(const string & str) override;

      virtual void translate_os_key_message(::user::key * pkey) override;


   };


} // namespace axis




