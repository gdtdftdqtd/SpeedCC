#ifndef __TESTLOADING_SCENE_H__
#define __TESTLOADING_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestLoadingController
class TestLoadingController : public SpeedCC::SCSceneController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void setupUI();
    void onTimer(float);
private:
    SCWatchString::Ptr      _ptrWatchStr;
    int                     _nCounter;
};

///--------- TestLoadingTraget0Controller
class TestLoadingTraget0Controller : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    void setupUI();
private:
};

///--------- TestLoadingTraget1Controller
class TestLoadingTraget1Controller : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters);
};

#endif // __TESTLOADING_SCENE_H__
