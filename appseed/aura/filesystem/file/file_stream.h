#pragma once


enum e_str_flag
{

   str_flag_ifnumberspace = 1,
   str_flag_ifnumberparenthesize = 2,
   str_flag_ifnumberparenthesizeandspace = 3,

};


namespace file
{


   class set_width
   {
   public:

      set_width(file_size_t n = 0) { m_width = n; }

      file_size_t m_width;

   };


   enum e_iostate
   {
      goodbit        = 0x00,
      eofbit         = 0x01,
      failbit        = 0x02,
      badbit         = 0x04,
      _Hardfail      = 0x10
   };


   enum e_open
   {
      mode_read                        = (i32) 0x000001,
      mode_write                       = (i32) 0x000002,
      mode_read_write                  = (i32) 0x000003,
      share_compat                     = (i32) 0x000000,
      share_exclusive                  = (i32) 0x000010,
      share_deny_write                 = (i32) 0x000020,
      share_deny_read                  = (i32) 0x000030,
      share_deny_none                  = (i32) 0x000040,
      mode_no_inherit                  = (i32) 0x000080,
      mode_create                      = (i32) 0x001000,
      mode_no_truncate                 = (i32) 0x002000,
      type_text                        = (i32) 0x004000, // type_text and type_binary are used in
      type_binary                      = (i32) 0x008000, // derived classes only
      defer_create_directory           = (i32) 0x010000,
      hint_unknown_length_supported    = (i32) 0x020000,
      mode_truncate                    = (i32) 0x040000,
      no_call_stack                    = (i32) 0x080000,
      no_cache                         = (i32) 0x100000,
      binary                           = type_binary,
      out                              = mode_write,
      in                               = mode_read,
      trunc                            = mode_truncate
   };


   enum fmtflags
   {
      nofmtflags     = 0,
      boolalpha      = 0x00000001,
      showbase       = 0x00000002,
      showpoint      = 0x00000004,
      showpos        = 0x00000008,
      skipws         = 0x00000010,
      unitbuf        = 0x00000020,
      uppercase      = 0x00000040,
      dec            = 0x00000080,
      hex            = 0x00000100,
      oct            = 0x00000200,
      fixed          = 0x00000400,
      scientific     = 0x00000800,
      internal       = 0x00001000,
      left           = 0x00002000,
      right          = 0x00004000,
      adjustfield	   = left | right | internal,
      basefield	   = dec | oct | hex,
      floatfield	   = scientific | fixed
   };



   class CLASS_DECL_AURA stream :
      virtual public seekable,
      virtual public reader,
      virtual public writer
   {
   public:

      e_str_flag                 m_estrflag;
      file_sp                    m_spfile;
      e_iostate                  m_iostate;
      fmtflags                   m_fmtflags;
      file_size_t                m_width;
      file_size_t                m_precision;

      stream();
      stream(file * pfile);
      virtual ~stream();



      fmtflags setf(fmtflags flagsAdd);
      fmtflags setf(fmtflags flagsAdd, fmtflags flagsRemove);



      fmtflags flags() const;


      fmtflags flags(fmtflags flags);


      e_iostate rdstate() const
      {
         return m_iostate;
      }

      bool operator ! ()
      {
         return fail();
      }

      bool bad() const
      {
         return (m_iostate & badbit) != 0;
      }

      bool fail() const
      {
         return ((int) m_iostate & ((int) badbit | (int) failbit)) != 0;
      }

      bool eof() const
      {
         return (m_iostate & eofbit) != 0;
      }

      bool good() const
      {
         return m_iostate == goodbit;
      }

      void setstate(int state)
      {
         clear((e_iostate) (rdstate() | state));
      }

      void clear(int state = goodbit)
      {
         m_iostate = (e_iostate) state;
      }

      virtual string GetFilePath() const;

      string fileName() { return GetFilePath(); }

      virtual void close();

      using seekable::seek;
      virtual file_position_t seek(file_offset_t offset, e_seek eseek);


      file_size_t precision() const;

      file_size_t precision(file_size_t prec);

      file_size_t width() const;

      file_size_t width(file_size_t wide);



      virtual bool is_open() const;



   };


} // namespace file





