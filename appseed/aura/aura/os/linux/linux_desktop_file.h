

// Cynokron "influenced" by handjob collaboration to use just C - the best choice, Artful Ubuntu 17.10
// using C++ to proof that C is better
// better
// best
// Everyone wants to rule the world....

namespace linux
{

   class desktop_file :
      virtual public ::object
   {
   public:


      stringa     m_straLine;


      desktop_file(::aura::application * papp);
      virtual ~desktop_file();


      void create_default();
      void create();

      stringa registered_categories();
      string proper_category(string strCategory);
      stringa proper_category(stringa straCategory);


      ::file::path get_file_path();

      void write();

      bool bamf_set_icon(oswindow oswindow);

   };


} // namespace linux



