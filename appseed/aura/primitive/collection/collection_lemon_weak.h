#pragma once


namespace lemon
{


   namespace weak
   {


      template < typename A, typename B >
      inline bool contains(const A & a, const B & b)
      {

         return a.weakly_contains(b);

      }


      template <  >
      inline bool contains(const string & a, const string & b)
      {

         return a.contains_ci(b);

      }


      template <  >
      inline string default_value < string >()
      {

         return string();

      }

      namespace map
      {


         template < typename MAP >
         typename MAP::assoc * get(MAP & m, typename MAP::BASE_KEY key)
         {

            for (auto & assoc : m)
            {

               if (contains(assoc.m_element1, key))
               {

                  return &assoc;

               }

            }

            return NULL;

         }


         template < typename MAP >
         typename MAP::BASE_VALUE * pvalue(MAP & m, typename MAP::BASE_ARG_KEY key)
         {

            for (auto & assoc : m)
            {

               if (contains(assoc.m_element1, key))
               {

                  return &assoc.m_element2;

               }

            }

            return NULL;

         }

         template < typename MAP >
         typename MAP::BASE_VALUE value(MAP & m, typename MAP::BASE_ARG_KEY key, typename MAP::BASE_VALUE default_value = default_value < MAP::BASE_VALUE >())
         {

            auto pval = pvalue(m, key);

            if (pval == NULL)
            {

               return default_value;

            }

            return *pval;

         }


      } // namespace map


   } // namespace weak


} // namespace lemon
