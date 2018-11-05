#include "framework.h"


db_stra_set::db_stra_set(db_server * pserver, ::database::key & key) :
   m_key(key)
{

   UNREFERENCED_PARAMETER(pserver);

   m_iMaximumCount = 32;

}


void db_stra_set::get_data(stringa & stra)
{

   data_load(m_key, stra);

}


// return the number of set directories
::count db_stra_set::set_data(stringa & stra)
{

   data_save(m_key, stra);

   return stra.get_size();

}






