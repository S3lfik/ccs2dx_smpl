/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
#include "s3e.h"
#include "Iw2D.h"
#include "IwDebug.h"

#include "cocos2d.h"
#include "AppDelegate.h"




// Main entry point for the application
int main()
{

    AppDelegate* app = new AppDelegate;
    cocos2d::CCApplication::sharedApplication()->Run();
	Iw2DInit();

	while (!s3eDeviceCheckQuitRequest())
	{
		Iw2DSurfaceClear(0xff000000);

		// Show the drawing surface
		Iw2DSurfaceShow();

		// Yield to the OS
		s3eDeviceYield(0);
	}	
		
	Iw2DTerminate();
	delete app;
	return 0;
}
