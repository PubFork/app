#pragma once


class CLASS_DECL_CORE db_stra_set :
   public ::database::client
{
public:


   int32_t         m_iMaximumCount;
   ::database::key     m_id;


   db_stra_set(db_server * pdatacentral, ::database::key & id);
   
   
   void get_data(stringa & stra);
   ::count set_data(stringa & stra);

};

