//
//  ios_windowing.hpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


//
//  ios_window.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//








#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA


void DeactivateWindow(oswindow window);


oswindow GetWindow(oswindow window, int iParentHood);



