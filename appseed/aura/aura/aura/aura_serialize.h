#pragma once


class serializable;
struct POINTD;

#define FIRST_VERSION 0


class CLASS_DECL_AURA serialize :
   virtual public ::file::istream,
   virtual public ::file::ostream
{
public:


   index          m_iVersion;
   bool           m_bStoring;


   serialize(::aura::application * papp);
   virtual ~serialize();

   virtual void stream(serializable & serializable);

   virtual void stream_file(::file::path path, ::serializable & serializable);

   virtual void stream_link(serializable & serializable);

   virtual ::file::path get_link_path(string strLink);

   bool is_version(index i);

   template < typename BLOCK_TYPE >
   void blt(BLOCK_TYPE & t) // block transfer // classes/structures with no virtual members
   {
      operator()(&t, sizeof(t));
   }

   template < typename ARRAY >
   void stream_array(ARRAY & a)
   {
      for (auto & element : a)
      {
         operator()(element);
      }
   }

   template < typename STREAMABLE >
   void operator()(STREAMABLE & streamable)
   {

      if (m_bStoring)
      {

         *this << streamable;

      }
      else
      {

         *this >> streamable;

      }

   }

   virtual void stream(void * p, memory_size_t s);
   virtual void write(void * p, memory_size_t s);
   virtual memory_size_t read(void * p, memory_size_t s);

   //virtual void operator()(RECTD & rectd);
   //virtual void operator()(double & d);
   //virtual void operator()(bool & b);
   //virtual void operator()(POINTD & d);

};


class CLASS_DECL_AURA serializable :
   virtual public ::object
{
public:


   virtual void stream(serialize & serialize);


};


