#include "framework.h"

#include <stdio.h>




namespace exception
{


   exception::exception()
   {

      debug_print("log:exception");
      //::MessageBox(NULL,"abc123","abc123",MB_OK);


      m_bHandled = false;

      m_bContinue = true;

      m_pszMessage = NULL;

      m_pszException = NULL;

      m_pszFile = NULL;

      m_iLine = -1;

   }

   exception::exception(e_context_switcher_failed efail)
   {
      //debug_print("log:exception");
      //::MessageBox(NULL,"abc123","abc123",MB_OK);
      //m_bLog = efail != failure_no_log;

      //if(m_bLog)
      //{
      //   debug_print("log:exception");
      //}

      m_bHandled = false;

      m_bContinue = true;

      m_pszMessage = NULL;

      m_pszException = NULL;


   }


   exception::~exception()
   {
      //if(m_bLog)
      //{

      //if(m_bContinue)
      //{
      //   cat_exception("-continue");
      //}
      //else
      //{
      //   cat_exception("-should_not_continue(fatal_exception_instance_candidate)");
      //}

      //if(m_bHandled)
      //{
      //   cat_exception("-explicitly_handled");
      //}
      //else
      //{
      //   cat_exception("-not_handled_explicitly");
      //}

      //debug_print(m_pszException);

      //debug_print("\n");

      ///}


      if (m_pszException != NULL)
      {

         free((void *)m_pszException);

      }

      if (m_pszMessage != NULL)
      {

         free((void *)m_pszMessage);

      }

      if (m_pszFile != NULL)
      {

         free((void *)m_pszFile);

      }

   }


   const char * exception::cat_message(const char * pszMessage)
   {

      m_pszMessage = strcat_and_dup(m_pszMessage, pszMessage);

      return m_pszMessage;

   }

   const char * exception::set_file(const char * pszFile)
   {

      if (m_pszFile != NULL)
      {

         free((void *) m_pszFile);

      }

      m_pszFile = strdup(pszFile);

      return m_pszFile;

   }

   const char * exception::cat_exception(const char * pszException)
   {

      m_pszException = strcat_and_dup(m_pszException, pszException);

      return m_pszException;

   }


   void exception::Delete()
   {

      delete this;

   }

   void rethrow(exception * pe)
   {

      _throw(pe);

   }

   const char * exception::what() const NOTHROW
   {

      return m_pszMessage;

   }


   result::result(std::initializer_list < exception * > list)
   {

      forallref(list)
      {

         add(item);

      }

   }

} // namespace exception


#ifdef APPLE_IOS



#else

thread_object < string > t_strNote;


string __get_thread_note()
{
   return t_strNote->c_str();
}
void __set_thread_note(const char * pszNote)
{
   t_strNote->operator=(pszNote);
}

#endif






errno_t c_runtime_error_check(errno_t error)
{
   switch(error)
   {
   case ENOMEM:
      _throw(memory_exception(get_app()));
      break;
   case EINVAL:
   case ERANGE:
      _throw(invalid_argument_exception(get_app()));
      break;
#if defined(WINDOWS)
   case STRUNCATE:
#endif
   case 0:
      break;
   default:
      _throw(invalid_argument_exception(get_app()));
      break;
   }
   return error;
}

void __cdecl __clearerr_s(FILE *stream)
{
#ifdef WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   clearerr(stream);
   C_RUNTIME_ERROR_CHECK(errno);
#endif
}



namespace exception
{

   CLASS_DECL_AURA void throw_interface_only(::aura::application * papp)
   {
      _throw(interface_only_exception(papp));
   }

   CLASS_DECL_AURA void throw_not_implemented(::aura::application * papp)
   {
      _throw(not_implemented(papp));
   }


   string result::get_all_messages()
   {

      ::count c = this->get_count();

      if (c <= 0)
      {

         return "";

      }
      else if (c == 1)
      {

         return element_at(0)->m_pszMessage;

      }
      else
      {

         string str;

         index i = 0;

         this->pred_each(

         [&](auto & pe)
         {

            str += ::str::from(++i);

            str += ". ";

            str += pe->m_pszMessage;

            str += ";";

            if (i < c)
            {

               str += " ";

            }

         }

         );

         return str;

      }

   }


} // namespace exception















