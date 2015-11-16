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
#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	pDirector->setProjection(kCCDirectorProjection2D);

    // Set projection
    float w, h;
    float angle = s3eSurfaceGetInt(S3E_SURFACE_DEVICE_BLIT_DIRECTION) * 90.0f;
    UpdateProjection(angle, w, h);

	// Set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	//CCFileUtils::sharedFileUtils()->setSearchPaths(path);
    // Create a scene
    CCScene *pScene = MainMenuLayer::scene();

    // Run
    pDirector->runWithScene(pScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
	std::cout << "paused" << std::endl;

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
	std::cout << "We're back!" << std::endl;

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::UpdateProjection(float angle, float& w, float& h)
{
    if (IwGLGetInt(IW_GL_VIRTUAL_WIDTH) >= 0)
    {
        w = (float)IwGLGetInt(IW_GL_VIRTUAL_WIDTH);
        h = (float)IwGLGetInt(IW_GL_VIRTUAL_HEIGHT);
    }
    else
    {
        w = (float)s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
        h = (float)s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
    }
    if ((angle == 90.0f) || (angle == 270.0f))
    {
        float oh = h;
        h = w;
        w = oh;
    }
    CCEGLView::sharedOpenGLView()->setFrameSize(w, h);
    CCEGLView::sharedOpenGLView()->setViewPortInPoints(0.0f, 0.0f, w, h);

    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadIdentity();

    // Rotate to achieve landscape orientation
    kmGLRotatef(-(float)angle, 0, 0, 1);
    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, 0, w, 0, h, -1024, 1024 );
    kmGLMultMatrix(&orthoMatrix);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLLoadIdentity();
}
