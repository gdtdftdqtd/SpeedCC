#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "gtest/gtest.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    //AppDelegate app;
    //return Application::getInstance()->run();
	int argc = 1;
	char *argv[] = {"abc"};
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
