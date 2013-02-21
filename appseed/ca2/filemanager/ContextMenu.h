#pragma once


namespace filemanager
{


   class ContextMenu  :
      virtual public ::gen::object
   {
   public:


#ifdef WINDOWSEX
      IContextMenu *    m_pcontextmenu;
      IContextMenu2 *   m_pcontextmenu2;
#endif
      UINT              m_uiMinId;


      ContextMenu();
      virtual ~ContextMenu();


      void OnCommand(UINT uiId);
      void GetMessageString(UINT nID, string & rstrMessage);
      void GetVerb(UINT nID, string & rwstrMessage);


   };


} // namespace filemanager


