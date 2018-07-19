#pragma once


class CLASS_DECL_AXIS db_stra_set :
   public ::database::client
{
public:


   int32_t         m_iMaximumCount;
   ::database::key     m_key;


   db_stra_set(db_server * pdatacentral, ::database::key & key);


   void get_data(stringa & stra);
   ::count set_data(stringa & stra);

};

