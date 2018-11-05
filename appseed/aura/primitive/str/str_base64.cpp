#include "framework.h"

#define N1_A 0
#define N1_B 1
#define N1_C 2
#define N1_D 3
#define N1_E 4
#define N1_F 5
#define N1_G 6
#define N1_H 7
#define N1_I 8
#define N1_J 9
#define N1_K 10
#define N1_L 11
#define N1_M 12
#define N1_N 13
#define N1_O 14
#define N1_P 15
#define N1_Q 16
#define N1_R 17
#define N1_S 18
#define N1_T 19
#define N1_U 20
#define N1_V 21
#define N1_W 22
#define N1_X 23
#define N1_Y 24
#define N1_Z 25
#define N1_a 26
#define N1_b 27
#define N1_c 28
#define N1_d 29
#define N1_e 30
#define N1_f 31
#define N1_g 32
#define N1_h 33
#define N1_i 34
#define N1_j 35
#define N1_k 36
#define N1_l 37
#define N1_m 38
#define N1_n 39
#define N1_o 40
#define N1_p 41
#define N1_q 42
#define N1_r 43
#define N1_s 44
#define N1_t 45
#define N1_u 46
#define N1_v 47
#define N1_w 48
#define N1_x 49
#define N1_y 50
#define N1_z 51
#define N1_0 52
#define N1_1 53
#define N1_2 54
#define N1_3 55
#define N1_4 56
#define N1_5 57
#define N1_6 58
#define N1_7 59
#define N1_8 60
#define N1_9 61
#define N1_plus 62
#define N1_slash 63


namespace str
{


   base64::base64(::aura::application * papp) :
      ::object(papp)
   {
      int32_t i, j;

      // etable
      for (j = 0; j < 3; j++)
      {
         for (i = 0; i < 9; i++)
         {
            etable[j][i + N1_A] = (uchar)('A' + i);
            etable[j][i + N1_J] = (uchar)('J' + i);
            etable[j][i + N1_a] = (uchar)('a' + i);
            etable[j][i + N1_j] = (uchar)('j' + i);
         }
         for (i = 0; i < 8; i++)
         {
            etable[j][i + N1_S] = (uchar)('S' + i);
            etable[j][i + N1_s] = (uchar)('s' + i);
         }
         for(i= 0; i<10; i++)
         {
            etable[j][i+N1_0]    = (uchar) ('0'+i);
         }
      }
      etable[mode_normal][N1_plus]      = (uchar) ('+');
      etable[mode_normal][N1_slash]     = (uchar) ('/');
      etable[mode_url_safe][N1_plus] = (uchar)('-');
      etable[mode_url_safe][N1_slash] = (uchar)('_');
      etable[mode_ex][N1_plus] = (uchar)('.');
      etable[mode_ex][N1_slash] = (uchar)('_');


      // dtable
      for(i= 0; i<255; i++)
      {
         dtable[i]= 0x80;
      }
      for(i= 'A'; i<='I'; i++)
      {
         dtable[i]= (uchar) (N1_A+(i-'A'));
      }
      for(i= 'J'; i<='R'; i++)
      {
         dtable[i]= (uchar) (N1_J+(i-'J'));
      }
      for(i= 'S'; i<='Z'; i++)
      {
         dtable[i]= (uchar) (N1_S+(i-'S'));
      }
      for(i= 'a'; i<='i'; i++)
      {
         dtable[i]= (uchar) (N1_a+(i-'a'));
      }
      for(i= 'j'; i<='r'; i++)
      {
         dtable[i]= (uchar) (N1_j+(i-'j'));
      }
      for(i= 's'; i<='z'; i++)
      {
         dtable[i]= (uchar) (N1_s+(i-'s'));
      }
      for(i= '0'; i<='9'; i++)
      {
         dtable[i]= (uchar) (N1_0+(i-'0'));
      }
      dtable['+']= (uchar) (N1_plus);
      dtable['/']= (uchar) (N1_slash);
      dtable['-'] = (uchar)(N1_plus);
      dtable['_'] = (uchar)(N1_slash);
      dtable['.'] = (uchar)(N1_plus);
      dtable['=']= (uchar) (0);
   }


   base64::~base64()
   {

   }


   void base64::encode(::stream & ostream, ::stream & istream, e_mode emode)
   {

      int32_t i,hiteof= FALSE;
      byte igroup[3],ogroup[4];
      int32_t n;
      char ch;

      uchar * enc_table = this->etable[emode];

      while(!hiteof)
      {
         igroup[0]= igroup[1]= igroup[2]= 0;
         for(n= 0; n<3; n++)
         {
            if(istream.read(&ch, 1) == 0)
            {
               hiteof= TRUE;
               break;
            }
            igroup[n]= (uchar)ch;
         }
         if(n> 0)
         {
            ogroup[0]= enc_table[igroup[0]>>2];
            ogroup[1]= enc_table[((igroup[0]&3)<<4)|(igroup[1]>>4)];
            ogroup[2]= enc_table[((igroup[1]&0xF)<<2)|(igroup[2]>>6)];
            ogroup[3]= enc_table[igroup[2]&0x3F];
            if(n<3)
            {
               ogroup[3]= '=';
               if(n<2)
               {
                  ogroup[2]= '=';
               }
            }
            for(i= 0; i<4; i++)
            {
               ostream.write(&ogroup[i], 1);
            }
         }
      }
   }


   bool base64::decode(::stream & ostream, ::stream & istream)
   {
      int32_t i;
      byte a[4],b[4],o[3];
      uchar uch;

      while(true)
      {
         for(i= 0; i<4; i++)
         {
            if(istream.read(&uch, 1) == 0)
            {
               if( i > 0)
               {
                  //_throw(io_exception(get_app(), "Input file incomplete.\n"));
                  //ASSERT(FALSE);
                  return false;
               }
               return true;
            }
            if(dtable[uch]&0x80)
            {

               string str;

               str.Format("Illegal character '%ca' in input spfile->\n", uch);

               //_throw(io_exception(get_app(), str));
               return false;

//               i--;
//
//               continue;

            }
            a[i]= (uchar) uch;
            b[i]= (uchar) dtable[uch];
         }
         o[0]= (b[0]<<2)|(b[1]>>4);
         o[1]= (b[1]<<4)|(b[2]>>2);
         o[2]= (b[2]<<6)|b[3];
         i= a[2]=='='?1:(a[3]=='='?2:3);
         ostream.write(o, i);

         if (i < 3)
         {

            break;

         }

      }

      return true;

   }


   string base64::encode(const char * psz, e_mode emode)
   {

      memory storage;

      strsize iLen = strlen(psz);

      storage.allocate(iLen);

      memcpy(storage.get_data(), psz, iLen);

      return encode(storage, emode);

   }

   string base64::encode(byte * p, ::count ca, e_mode emode)
   {

      memory storage;

      storage.allocate(ca);

      memcpy(storage.get_data(), p, ca);

      return encode(storage, emode);

   }

   string base64::encode(primitive::memory_base & storageBinary, e_mode emode)
   {

      ::memory_file buf(get_app(), &storageBinary);

      serialize istream(&buf);

      ::file::string_file file;

      ::file::plain_text_stream ostream(&file);

      encode(ostream, istream, emode);

      return file.m_str;

   }

   string base64::decode(const char * pszBase64)
   {

      memory storage;

      decode(storage, pszBase64);

      string str;

      memcpy(
      str.GetBufferSetLength(storage.get_size()),
      storage.get_data(),
      storage.get_size());

      str.ReleaseBuffer();

      return str;

   }

   bool base64::decode(::primitive::memory_base & storageBinary, const char * pszBase64, strsize s)
   {

      string str(pszBase64, s);

      ::file::string_file buf(str);

      ::file::plain_text_stream istream(&buf);

      ::memory_file bufOut(get_app(), &storageBinary);

      serialize ostream(&bufOut);

      return decode(ostream, istream);

   }

   string base64::encode(::object & object, e_mode emode)
   {

      memory storageBinary;

      ::memory_file buf(get_app(), &storageBinary);

      writer writer(&buf);

      writer(object);

      buf.seek_to_begin();

      ::file::string_file file;

      reader reader(&buf);

      ::file::plain_text_stream ostream(&file);

      encode(ostream, reader, emode);

      return file.m_str;

   }


   bool base64::decode(::object & object, const char * pszBase64)
   {

      string str(pszBase64);

      ::file::string_file bufIn(str);

      ::file::plain_text_stream istream(&bufIn);

      memory storageBinary;

      ::memory_file buf(get_app(), &storageBinary);

      serialize stream(&buf);

      if (!decode(stream, istream))
      {
         return false;
      }

      buf.seek_to_begin();

      reader reader(&buf);

      reader(object);

      return true;

   }

   // https://stackoverflow.com/questions/13195143/range-of-valid-character-for-a-base-64-encoding

   bool base64::is(int iChar)
   {

      if (iChar >= 'A' && iChar <= 'Z')
      {

         return true;

      }
      else if (iChar >= 'a' && iChar <= 'z')
      {

         return true;

      }
      else if (iChar >= '0' && iChar <= '9')
      {

         return true;

      }
      else if (iChar == '+')
      {

         return true;

      }
      else if (iChar == '/')
      {

         return true;

      }
      else if (iChar == '-')  // RFC 4648 (+)
      {

         return true;

      }
      else if (iChar == '_')// RFC 4648 (/)
      {

         return true;

      }
      else if (iChar == '=')
      {

         return true;

      }
      else
      {

         return false;

      }

   }

} // namespace str


