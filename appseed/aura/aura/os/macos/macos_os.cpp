//
//  macos_os.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "framework.h"



CLASS_DECL_AURA bool _istlead(int32_t ch)
{
   
   return false;
   
}








WINBOOL GetCursorPos(LPPOINT lpptCursor)
{
   
   HIPoint point;
   
   HICoordinateSpace space = kHICoordSpaceScreenPixel;
   
   HIGetMousePosition(space, NULL, &point);
   
   
   lpptCursor->x = point.x;
   lpptCursor->y = point.y;
   
   
   return TRUE;
   
}






char * mm_browse_folder(const char * pszStartDir);


string apple_browse_folder(const char * pszStartDir)
{
   
   return ::str::from_strdup(mm_browse_folder(pszStartDir));
   
}



char** mm_browse_file_open(const char ** pszStartDir, bool bMulti);



stringa apple_browse_file_open(const char ** pszStartDir, bool bMulti)
{

   
   
   return ::stra::from_strdup(mm_browse_file_open(pszStartDir, bMulti));
   
}
