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

#include "TestDockController.h"

USING_NS_CC;

void TestDockController::onCreate(SCDictionary parameters)
{
    parameters.setValue("name", "dock");
    parameters.setValue("title", "Test Dock");
    TestCaseController::onCreate(parameters);
    
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseNoScale, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseWithScale, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseWithScaleAnchor, this)));
    
    _ptrCaseBvr->execute();
}

void TestDockController::testCaseNoScale()
{
    (*_ptrWatchDescription) = "(No Scale, Middle Anchor)";
    _pContainerLayer->removeAllChildren();
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, nullptr, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=center;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|top;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=top|mid-x;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // top-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|top;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
        SC_END_CONTAINER
    
        // bottom-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|bottom;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
        SC_END_CONTAINER
    
        // bottom-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=bottom|mid-x;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|bottom;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|mid-y;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|mid-y;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}



void TestDockController::testCaseWithScale()
{
    (*_ptrWatchDescription) = "(With Scale, Middle Anchor)";
    _pContainerLayer->removeAllChildren();
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, nullptr, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=center; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|top; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=top|mid-x; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // top-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|top; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
        SC_END_CONTAINER
    
        // bottom-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|bottom; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
        SC_END_CONTAINER
    
        // bottom-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=bottom|mid-x; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|bottom; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|mid-y; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|mid-y; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestDockController::testCaseWithScaleAnchor()
{
    (*_ptrWatchDescription) = "(With Scale, Different Anchor)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, nullptr, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=center; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|top; scale=0.5; anchor=(0.5,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=top|mid-x; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // top-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|top; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
        SC_END_CONTAINER
    
        // bottom-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|bottom; scale=0.5; anchor=(0.1,0.2);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
        SC_END_CONTAINER
    
        // bottom-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=bottom|mid-x; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|bottom; scale=0.5; anchor=(0,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=left|mid-y; scale=0.5; anchor=(1,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=right|mid-y; scale=0.5; anchor=(1,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(nullptr, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}

