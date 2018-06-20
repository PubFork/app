#include "framework.h"
#include "aura/aura/os/windows_common/windows_common_cotaskptr.h"


itemidlist::itemidlist() :
   m_pidl(NULL)
{

}


itemidlist::itemidlist(const itemidlist & iidl) :
   m_pidl(NULL)
{

   if (!iidl.is_empty())
   {

      m_pidl = _copy(iidl);

   }

}


itemidlist::itemidlist(const char * pszPath) :
   m_pidl(NULL)
{

   parse(pszPath);

}


itemidlist::itemidlist(LPCITEMIDLIST pidl, bool bAttach) :
   m_pidl(NULL)
{

   if (bAttach)
   {

      attach((LPITEMIDLIST) pidl);

   }
   else
   {

      copy(pidl);

   }

}


itemidlist::~itemidlist()
{

   free();

}


void itemidlist::_free(LPITEMIDLIST & pidl)
{

   if (!pidl)
   {

      return;

   }

   LPITEMIDLIST p = pidl;

   pidl = NULL;

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      return;

   }

   pmalloc->Free(p);

}


int itemidlist::count() const
{

   return _count(m_pidl); //Get pidl count.

}


int itemidlist::len() const
{

   return _len(m_pidl);

}


void itemidlist::free()
{

   _free(m_pidl);

}



bool itemidlist::parse(const char * pszPath)
{

   free();

   if(FAILED(_parse(m_pidl, pszPath)))
   {

      return false;

   }

   return true;

}


LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return NULL;

   }

   int nSize = _len(pidl);

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      throw memory_exception(::get_app());

      return NULL;

   }

   LPITEMIDLIST pidlNew = (LPITEMIDLIST)pmalloc->Alloc(nSize);

   if (pidlNew)
   {

      memcpy(pidlNew, pidl, nSize);

   }

   return pidlNew;

}


int itemidlist::_count(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return 0;

   }

   LPCITEMIDLIST pidlr = pidl;

   int nCount = 0;

   while (pidlr->mkid.cb)
   {

      nCount++;

      pidlr = _next(pidlr);

   }

   return nCount;

}


int itemidlist::_len(LPCITEMIDLIST pidl)
{

   if (!pidl)
   {

      return 0;

   }

   int nSize = sizeof(pidl->mkid.cb);

   while (pidl->mkid.cb)
   {

      nSize += pidl->mkid.cb;

      pidl = _next(pidl);

   }

   return nSize;

}


itemidlist itemidlist::operator/(const itemidlist & piidl) const
{

   return _cat(m_pidl, piidl);

}


itemidlist & itemidlist::operator=(const char * pszPath)
{

   if (!parse(pszPath))
   {

      throw resource_exception(::get_app(), "Failed to parse the path " + string (pszPath));

   }

   return *this;

}


itemidlist & itemidlist::operator=(const itemidlist & piidl)
{

   copy(piidl);

   return *this;

}

LPITEMIDLIST itemidlist::_cat(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
   LPITEMIDLIST pidlNew;

   int cb1;

   int cb2;

   if (pidl1)
   {

      cb1 = _len(pidl1) - sizeof(pidl1->mkid.cb);

   }
   else
   {

      cb1 = 0;

   }

   cb2 = _len(pidl2);

   pidlNew = _create(cb1 + cb2);

   if (pidlNew)
   {

      if (pidl1)
      {

         memcpy(pidlNew, pidl1, cb1);

      }

      memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);

   }

   return pidlNew;

}


LPITEMIDLIST itemidlist::_create(int nSize)
{

   comptr < IMalloc > pmalloc;

   LPITEMIDLIST pidl = NULL;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      throw memory_exception(::get_app());

      return NULL;

   }

   pidl = (LPITEMIDLIST)pmalloc->Alloc(nSize);

   if (pidl == NULL)
   {

      throw memory_exception(::get_app());

      return NULL;

   }

   zero(pidl, nSize);

   return pidl;

}


itemidlist & itemidlist::operator=(LPCITEMIDLIST pidl)
{

   copy(pidl);

   return *this;

}

bool itemidlist::copy(LPCITEMIDLIST pidlf)
{

   free();

   m_pidl = _copy(pidlf);

   return true;

}


itemidlist & itemidlist::operator/=(const itemidlist & pidl)
{

   LPITEMIDLIST pidlp = m_pidl;

   m_pidl = _cat(m_pidl, pidl);

   _free(pidlp);

   return *this;

}


itemidlist & itemidlist::operator-=(int i)
{

   left(count() - i);

   return *this;

}

itemidlist itemidlist::operator-(int i) const
{

   return _copy(m_pidl, count() - i);

}


itemidlist itemidlist::at(int nIndex) const
{

   return _create_one(m_pidl, nIndex);

}


itemidlist itemidlist::operator[](int nIndex) const
{

   return at(nIndex);

}


LPITEMIDLIST itemidlist::_create_one(LPCITEMIDLIST pidlf, int iIndex)
{

   if (iIndex < 0)
   {

      return NULL;

   }

   int iCount = _count(pidlf);

   if (iCount <= 0 || iIndex > iCount)
   {

      return NULL;

   }

   while (iIndex)
   {

      iIndex--;

      pidlf = _next(pidlf);

   }

   LPITEMIDLIST pidlRet = NULL;

   int uSize = pidlf->mkid.cb;

   pidlRet = _create(uSize + sizeof(pidlf->mkid.cb));

   zero(pidlRet, uSize + sizeof(pidlf->mkid.cb));

   memcpy(pidlRet, pidlf, uSize);

   return pidlRet;

}


bool itemidlist::operator==(const itemidlist & pidl) const
{

   comptr < IShellFolder > lpsfDesktop;

   if (FAILED(SHGetDesktopFolder(&lpsfDesktop)))
   {

      return false;

   }

   return lpsfDesktop->CompareIDs(0, m_pidl, pidl) == 0;

}


itemidlist itemidlist::left(int nCount) const
{

   itemidlist pidl;

   if (nCount == -1)
   {

      nCount = count();

   }

   if (nCount <= 0)
   {

      return pidl;

   }

   int iCount = count();

   if (nCount > iCount)
   {

      nCount = iCount;

   }

   LPITEMIDLIST pidlRes = NULL;

   size_t nSize = _len(m_pidl, nCount);

   comptr < IMalloc > pmalloc;

   if (FAILED(SHGetMalloc(&pmalloc)))
   {

      return pidl;

   }

   pidlRes = (LPITEMIDLIST)pmalloc->Alloc(sizeof(m_pidl->mkid.cb) + nSize);

   zero(pidlRes, nSize + sizeof(m_pidl->mkid.cb));

   memcpy((LPVOID)pidlRes, (LPVOID)m_pidl, nSize);

   return pidlRes;

}


int itemidlist::_len(LPCITEMIDLIST pidl, int nCount)
{

   int iCount = _count(pidl);

   if (nCount >= iCount)
   {

      return _len(pidl);

   }

   int cbTotal = 0;

   if (pidl)
   {

      while (nCount--)
      {

         cbTotal += pidl->mkid.cb;

         pidl = _next(pidl);

      }

   }

   return cbTotal;

}


string itemidlist::display_name(DWORD dwFlags) const
{

   comptr < IShellFolder > lpsf;

   comptr < IShellFolder > lpsfDesktop;

   HRESULT hr;

   itemidlist pidl;

   if (FAILED(SHGetDesktopFolder(&lpsfDesktop)))
   {

      return "";

   }

   int nCount = count();

   if (nCount > 1)
   {
      pidl = left(nCount - 1);

      hr = lpsfDesktop->BindToObject(pidl, 0, IID_IShellFolder, (LPVOID*)&lpsf);

      if (FAILED(hr))
      {

         return "";

      }

   }
   else
   {

      lpsf = lpsfDesktop;

   }

   pidl = at(nCount - 1);

   return _display_name(lpsf, pidl, dwFlags);

}


string itemidlist::path() const
{

   return _path(m_pidl);

}


int itemidlist::icon_index(int uFlags) const
{

   return _icon_index(m_pidl, uFlags);

}


void itemidlist::attach(LPITEMIDLIST pidl)
{

   free();

   m_pidl = pidl;

}


LPITEMIDLIST itemidlist::detach()
{

   LPITEMIDLIST pidl = m_pidl;

   m_pidl = NULL;

   return pidl;

}


string itemidlist::tooltip_info() const
{

   comptr < IShellFolder > psfDesktop;

   comptr < IShellFolder > psf;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return "";

   }

   int iCount = count();

   itemidlist item = left(iCount - 1);

   HRESULT hr = psfDesktop->BindToObject(item, 0, IID_IShellFolder, (LPVOID*)&psf);

   if (FAILED(hr))
   {

      return "";

   }

   item = at(iCount - 1);

   return _tooltip_info(psf, item);

}


string itemidlist::_tooltip_info(IShellFolder * lpsf, LPCITEMIDLIST pidl)
{

   if (!lpsf)
   {

      return "";

   }

   comptr < IQueryInfo > pinfo;

   lpsf->GetUIObjectOf(NULL, 1, (LPCITEMIDLIST*)&(pidl), IID_IQueryInfo, 0, (LPVOID*)&pinfo);

   if (pinfo.is_null())
   {

      return "";

   }

   cotaskptr < LPWSTR > lpwsz;

   pinfo->GetInfoTip(0, &lpwsz);

   return utf8(lpwsz);

}


LPITEMIDLIST itemidlist::_full(IShellFolder * lpsf, LPCITEMIDLIST lpi)
{

   //   OLECHAR szOleChar[MAX_PATH + 1];

   comptr < IShellFolder > lpsfDeskTop;
   LPITEMIDLIST lpifq;
   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   string str = _display_name(lpsf, lpi, SHGDN_FORPARSING);

   if (str.is_empty())
   {

      return NULL;

   }

   hr = SHGetDesktopFolder(&lpsfDeskTop);

   if (FAILED(hr))
   {

      return NULL;

   }

   wstring wstr(str);

   hr = lpsfDeskTop->ParseDisplayName(NULL, NULL, wstr, &ulEaten, &lpifq, &ulAttribs);

   if (FAILED(hr))
   {

      return NULL;

   }

   return lpifq;

}


HRESULT itemidlist::_GetUIObjectOf(REFIID riid, LPVOID* ppOut, LPITEMIDLIST pidlf, HWND hWnd)
{

   comptr < IShellFolder > lpsf;

   HRESULT hr = S_OK;

   itemidlist ciidf(pidlf), pidl;

   ciidf.split(&lpsf, pidl);

   if (lpsf.is_null())
   {

      return E_FAIL;

   }

   hr = lpsf->GetUIObjectOf(hWnd, 1, pidl, riid, NULL, ppOut);

   return hr;

}


HRESULT itemidlist::GetUIObjectOf(REFIID riid, LPVOID* ppOut, HWND hWnd)
{

   return _GetUIObjectOf(riid, ppOut, m_pidl, hWnd);

}


//Get relative pidl and the corresponding ShellFolder interface.
void itemidlist::split(IShellFolder ** lpsf, itemidlist & pidl)
{

   _split(lpsf, pidl.m_pidl, m_pidl);

}


itemidlist itemidlist::last() const
{

   int nCount = count();

   itemidlist pidl;

   if (nCount > 1)
   {

      pidl = at(nCount - 1);

   }

   return pidl;

}


void itemidlist::_split(IShellFolder ** lpsf, LPITEMIDLIST &pidl, LPITEMIDLIST pidlf)
{

   pidl = NULL;

   *lpsf = NULL;

   if (!pidlf)
   {
      SHGetDesktopFolder(lpsf);
      return;
   }

   comptr < IShellFolder > lpsfDesktop ;

   if (FAILED(SHGetDesktopFolder(&lpsfDesktop)))
   {

      return;

   }

   int nCount = _count(pidlf);

   itemidlist pidlFolder = _copy(pidlf, nCount - 1);

   if (pidlFolder.m_pidl)
   {

      lpsfDesktop->BindToObject(pidlFolder, NULL, IID_IShellFolder, (LPVOID*)lpsf);

      pidl = _create_one(pidlf, nCount - 1);

   }
   else
   {

      *lpsf = lpsfDesktop;

      (*lpsf)->AddRef();

   }

}


LPITEMIDLIST itemidlist::_copy(LPCITEMIDLIST pidlOrg, int nCount)
{

   if (nCount < 1)
   {

      return NULL;

   }

   LPITEMIDLIST pidlRes = NULL;

   comptr < IMalloc > pmalloc;

   size_t nSize = _len(pidlOrg, nCount);

   HRESULT hr;

   int nPidlCount = _count(pidlOrg);

   if (nPidlCount < nCount)
   {

      nCount = nPidlCount;

   }

   hr = SHGetMalloc(&pmalloc);

   if (FAILED(hr))
   {

      return NULL;

   }

   pidlRes = (LPITEMIDLIST)pmalloc->Alloc(sizeof(pidlOrg->mkid.cb) + nSize);

   zero(pidlRes, nSize + sizeof(pidlOrg->mkid.cb));

   memcpy((LPVOID)pidlRes, (LPVOID)pidlOrg, nSize);

   return pidlRes;

}

int itemidlist::_compare(LPCITEMIDLIST pidlf1, LPCITEMIDLIST pidlf2,
                         IShellFolder * psfFolder, LPARAM lParam)
{

   comptr < IShellFolder > psfDesktop = psfFolder;

   if (psfDesktop.is_null())
   {

      SHGetDesktopFolder(&psfDesktop);

      if (psfDesktop.is_null())
      {

         return 0;

      }

   }
   else
   {

      psfDesktop->AddRef();

   }

   HRESULT hr = psfDesktop->CompareIDs(lParam, pidlf1, pidlf2);

   return int(HRESULT_CODE(hr));

}


HRESULT itemidlist::_parse(LPITEMIDLIST & pidl, LPCTSTR pcszPath, IShellFolder * psfFolder)
{

   if (!psfFolder)
   {

      return E_FAIL;

   }

   wstring wstr(pcszPath);

   ULONG chEaten = 0;

   return psfFolder->ParseDisplayName(NULL, NULL, wstr, &chEaten, &pidl, NULL);

}


HRESULT itemidlist::_parse(LPITEMIDLIST &pidlf, LPCTSTR pcszPath)
{

   comptr < IShellFolder > psfDesktop;

   if (FAILED(SHGetDesktopFolder(&psfDesktop)))
   {

      return E_FAIL;

   }

   return _parse(pidlf, pcszPath, psfDesktop);

}


int itemidlist::_icon_index(LPCITEMIDLIST pidlf, int uFlags)
{

   SHFILEINFO sfi;

   SHGetFileInfo((LPCTSTR)pidlf, 0, &sfi, sizeof(SHFILEINFO), uFlags);

   return sfi.iIcon;

}


int itemidlist::_overlay_icon_index(IShellFolder * lpsfFolder, LPCITEMIDLIST pidl)
{

   if (!lpsfFolder || !pidl)
   {

      return -1;

   }

   comptr < IShellIcon > lpsiIcon;

   comptr < IShellIconOverlay >  lpsiIconOl;

   int index = -1;

   lpsfFolder->QueryInterface(IID_IShellIcon, (LPVOID*)&lpsiIcon);

   if (lpsiIcon.is_null())
   {

      return -1;

   }

   lpsiIcon->QueryInterface(IID_IShellIconOverlay, (LPVOID*)&lpsiIconOl);

   if (lpsiIconOl.is_null())
   {

      return -1;

   }

   if (lpsiIconOl->GetOverlayIndex(pidl, &index) != S_OK)
   {

      index = -1;

   }

   return index;

}

string itemidlist::_display_name(STRRET & strret, LPCITEMIDLIST pidl)
{

   string str;

   switch (strret.uType)
   {
   case STRRET_WSTR:
   {
      str = (WCHAR *)strret.pOleStr;
   }
   break;
   case STRRET_OFFSET:
   {
      str = (LPSTR)pidl + strret.uOffset;
   }
   break;
   case STRRET_CSTR:
   {
      str = (LPSTR)strret.cStr;
      break;
   }
   default:
      break;
   }

   return str;

}


string itemidlist::_display_name(IShellFolder * lpsf, LPCITEMIDLIST lpi, DWORD dwFlags)
{

   string str;

   STRRET strret;

   if (NOERROR == lpsf->GetDisplayNameOf(lpi, dwFlags, &strret))
   {

      str = _display_name(strret, lpi);

   }

   return str;

}


string itemidlist::_path(LPCITEMIDLIST pidl)
{

   wstring wstr;

   SHGetPathFromIDListEx(pidl, wstr.alloc(2048), 2048, 0);

   return wstr;

}



// left member (with -2? or "count-1" argument)
//comptr < IShellFolder> itemidlist::_017GetShellParentFolder(LPITEMIDLIST lpiidlChild)
//{
//
//   LPITEMIDLIST lpiidlParent = _017ItemIDListGetFolderParent(lpiidlChild);
//
//   comptr < IShellFolder> pfolderRet = _017GetShellFolder(lpiidlParent);
//
//   _017ItemIDListFree(lpiidlParent);
//
//   return pfolderRet;
//
//}




comptr < IShellFolder > itemidlist::get_shell_folder() const
{

   HRESULT hr = S_OK;

   if (SUCCEEDED(hr))
   {

      comptr < IShellFolder > pfolderDesktop;

      SHGetDesktopFolder(&pfolderDesktop);

      comptr < IShellFolder > pfolder;

      hr = pfolderDesktop->BindToObject(
           m_pidl,
           NULL,
           IID_IShellFolder,
           pfolder);

      if (SUCCEEDED(hr))
      {

         return pfolder;

      }

   }
   else
   {
      ASSERT(FALSE);
   }

   return NULL;

}


