/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

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
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    void setupUI();
private:
};

///--------- TestLoadingTraget1Controller
class TestLoadingTraget1Controller : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
};

#endif // __TESTLOADING_SCENE_H__
