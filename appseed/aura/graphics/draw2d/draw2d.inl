//
//  draw2d.inl
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 11/03/18.
//


#pragma once


namespace draw2d
{

   
   inline COLORREF get_pixel(COLORREF * pdata, int iScan, int iHeight, int x, int y)
   {
      
#ifdef APPLEOS

      return ((COLORREF *)&((byte *)pdata)[iScan * (iHeight - y - 1)])[x];
      
#else
   
      return ((COLORREF *)&((byte *)pdata)[iScan * y])[x];
   
#endif
   
   }


} // namespace draw2d





