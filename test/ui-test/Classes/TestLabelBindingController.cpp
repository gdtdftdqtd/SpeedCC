/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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

#include "TestLabelBindingController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLabelBindingController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    _ptrWatchInt = SCWatchInt::create();
    _ptrWatchStr = SCWatchString::create();
    *_ptrWatchStr = "test string";
    
    SCBinderUILabel::Ptr binderStrPtr = SCBinderUILabel::create();
    binderStrPtr->setWatch(_ptrWatchStr);

    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,nullptr,SCWinSize)

        // title
        SC_INSERT_LABEL_BMFONT(nullptr,0.5,0.95,"","Label Binding","blue_font.fnt")
    
        // number binding
        SC_INSERT_LABEL(nullptr,0.4,0.75,"",_ptrWatchInt,"",30)
        SC_INSERT_BUTTON_LABEL(nullptr,0.6,0.75,"color-text=red;","+","",33,SCF(onButtonAdd))
        SC_INSERT_BUTTON_LABEL(nullptr,0.7,0.75,"color-text=red;","-","",33,SCF(onButtonSub))
    
        // string binding
        SC_INSERT_LABEL(nullptr,0.4,0.5,"color-text=yellow;",binderStrPtr,"",30)
        SC_INSERT_BUTTON_LABEL(nullptr,0.65,0.5,"color-text=red;","click","",25,SCF(onButtonRandomText))
    
        // back
        SC_INSERT_BUTTON_LABEL(nullptr,0.15,0.95,"color-text=red;","back","",25,SCF(onButtonBack))
    SC_END_CONTAINER
    
}

void TestLabelBindingController::onButtonAdd()
{
    ++(*_ptrWatchInt);
}

void TestLabelBindingController::onButtonSub()
{
    --(*_ptrWatchInt);
}

void TestLabelBindingController::onButtonRandomText()
{
    (*_ptrWatchStr).format("%d",rand());
}

void TestLabelBindingController::onButtonBack()
{
    SCSceneNav()->back();
}
