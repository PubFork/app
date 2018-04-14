#pragma once
/*-------------------------------------
|   itemidlist class for operate     |
| ITEMIDLIST data type and more       |
| functions.                          |
|           Version:2.0               |
|                                     |
|     Written by kim-ryo,2002.9(1.0)  |
|        Updated in 2002.11(2.0)	  |
|									  |
|  If you have any suggestion, please |
|mail to kim-ryo@netease.com,greate   |
|Thanks                               |
--------------------------------------*/

#include <Shlobj.h>
#include "aura/aura/os/windows_common/windows_common_comptr.h"

class CLASS_DECL_AURA itemidlist
{
public:


   LPITEMIDLIST m_pidl;


   itemidlist();
   itemidlist(const char * pcszPath);
   itemidlist(LPCITEMIDLIST pidl, bool bAttach = true);
   itemidlist(const itemidlist & iidl);
   ~itemidlist();

   //comptr < IShellFolder> _017GetParentShellFolder(LPITEMIDLIST lpiidlChild);
   //comptr < IShellFolder> _017GetShellFolder(const string & str, LPITEMIDLIST lpiidlChild);
   comptr < IShellFolder> get_shell_folder() const;


   HRESULT GetUIObjectOf(REFIID riid, LPVOID* ppOut, HWND hWnd = NULL);
   //Get relative pidl and the corresponding ShellFolder interface.
   void split(IShellFolder ** lpsf, itemidlist & ciid);
   //get last relative pidl.
   itemidlist last() const;
   string tooltip_info() const;
   void attach(LPITEMIDLIST pidl);
   LPITEMIDLIST detach();
   int icon_index(int uFlags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON) const;
   string display_name(DWORD dwFlags = SHGDN_NORMAL) const;//Retrieve pidl's dislpay name.
   //Copy a pidl due to the count number.
   //nCount=-1 indicate copy all pidl.
   itemidlist left(int nCount = -1) const;
   inline bool is_empty() const { return m_pidl ? false : true; }
   itemidlist at(int nIndex) const;//Return a relative pidl at specified index.
   bool copy(LPCITEMIDLIST pidlf);
   inline int count() const { return _count(m_pidl); }//Get pidl count.
   inline int len() const { return _len(m_pidl); }
   inline void free() { _free(m_pidl); }
   string path() const;//Retrieve full path.(only available for full-quality pidl)
   void parse(const char * pszPath);

   itemidlist operator/(const itemidlist & piidl) const ;//Concat two pidls.
   inline operator LPITEMIDLIST() const { return m_pidl; }
   inline operator LPCITEMIDLIST() const { return (LPCITEMIDLIST)m_pidl; }
   inline operator LPITEMIDLIST*() { return &m_pidl; }
   inline operator LPCITEMIDLIST*() { return (LPCITEMIDLIST*)&m_pidl; }
   itemidlist & operator=(const char * pszPath);
   itemidlist & operator=(const itemidlist & pidl);
   itemidlist & operator=(LPCITEMIDLIST pidl);
   itemidlist & operator/=(const itemidlist & ciidl);//Add a new pidl to tail.
   itemidlist & operator-=(int i);//remove i Count items from tail.
   itemidlist operator -(int i) const;//remove i Count items from tail.
   bool operator==(const itemidlist & ciidl) const;
   itemidlist operator[](int nIndex) const;//Return a relative pidl at specified index.



   static int _icon_index(LPCITEMIDLIST pidlf, int uFlags = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
   static void _split(IShellFolder ** lpsf, LPITEMIDLIST& pidl, LPITEMIDLIST pidlf);
   static string _tooltip_info(IShellFolder * lpsf, LPCITEMIDLIST pidl);
   static LPITEMIDLIST _create(int nSize);
   static LPITEMIDLIST _cat(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);//Concat two pidl.
   //Create a relative pidl through a full-quality pidl at specified index.
   static LPITEMIDLIST _create_one(LPCITEMIDLIST pidlf, int Index);
   static int _count(LPCITEMIDLIST pidl);
   static int _len(LPCITEMIDLIST pidl);
   static int _len(LPCITEMIDLIST pidl, int nCount);//Get pidl size throught the specified count.
   static void _free(LPITEMIDLIST& pidl);
   static LPITEMIDLIST _copy(LPCITEMIDLIST pidl);//Duplicate specified pidl,and you need free it.
   //Get full-quality pidl throught a relative pidl and it's corresponding ShellFolder interface
   static LPITEMIDLIST _full(IShellFolder * lpsf, LPCITEMIDLIST lpi);
   static string _display_name(IShellFolder * lpsf, LPCITEMIDLIST lpi, DWORD dwFlags);
   static HRESULT _GetUIObjectOf(REFIID riid, LPVOID* ppOut, LPITEMIDLIST pidlf, HWND hWnd);
   static LPITEMIDLIST _copy(LPCITEMIDLIST pidlOrg, int nCount);
   static int _compare(LPCITEMIDLIST pidlf1, LPCITEMIDLIST pidlf2, IShellFolder * psfFolder = NULL, LPARAM lParam = 0);//return zero means same,non-zero means different.
   static HRESULT _parse(LPITEMIDLIST &pidl, const char * pcszPath, IShellFolder * psfFolder);
   static HRESULT _parse(LPITEMIDLIST& pidlf, const char * pcszPath);
   static int _overlay_icon_index(IShellFolder * lpsfFolder, LPCITEMIDLIST pidl);
   static string _display_name(STRRET& str, LPCITEMIDLIST pidl);
   static string _path(LPCITEMIDLIST pidl);

   inline static LPCITEMIDLIST _next(LPCITEMIDLIST pidl)
   {

      LPBYTE lpMem = (LPBYTE)pidl;

      lpMem += pidl->mkid.cb;

      return (LPITEMIDLIST)lpMem;

   }

   inline static LPITEMIDLIST _next(LPITEMIDLIST pidl)
   {

      return (LPITEMIDLIST)_next((LPCITEMIDLIST)pidl);

   }

};

