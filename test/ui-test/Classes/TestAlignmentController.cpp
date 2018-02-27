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

#include "TestAlignmentController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestAlignmentController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Alignment");
    TestCaseController::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT_EX(nullptr, SCWinSize, _pContainerLayer, this)
        SC_BEGIN_CONTAINER_ALIGNMENT(nullptr,"dock=top|mid-x; y-by=-20;",true,50,SCNodeUtils::EDockType::kDockTop)
            SC_INSERT_LABEL(nullptr, "text-color=black;", "ABC", "", 20)
            SC_INSERT_SPRITE(nullptr, "scale=0.4;", "HelloWorld.png")
            SC_INSERT_LABEL(nullptr, "text-color=black;", "123", "", 20)
        SC_END_CONTAINER
    SC_END_CONTAINER
}




