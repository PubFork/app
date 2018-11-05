#pragma once


namespace xml
{


   class importable;
   class attribute_array;


   class CLASS_DECL_AURA input_tree :
      public tree_base
   {
   public:


      sp(::xml::document)     m_pdocument;
      sp(::xml::node)         m_pnode;


      input_tree(::aura::application * papp);
      input_tree(::aura::application * papp, tree_schema * pschema);
      virtual ~input_tree();


      virtual node * import_node(const char * lpcszName, importable & importable);
      virtual node * import_node(const char * lpcszName, attr_array & attributea, importable & importable);
      virtual node * import_node(const char * lpcszName, var & var);

      virtual bool load_attr(const char * lpcszName, string & strValue);
      virtual bool load_attr(const char * lpcszName, bool & b);
      virtual bool load_attr(const char * lpcszName, double & d);
      virtual bool load_attr(const char * lpcszName, int32_t & iValue);
      virtual bool get_attr(const char * lpcszName, string & strValue, string strDefault = "");
      virtual bool get_attr(const char * lpcszName, bool & b, bool bDefault = false);
      virtual bool get_attr(const char * lpcszName, double & d, double dDefault = 0.0);
      virtual bool get_attr(const char * lpcszName, int32_t & iValue, int iDefault = 0);
      virtual void get_value(string & strValue);

   };


} // namespace xml





