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

#include "TestUIMiscController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestUIMiscController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test UI Misc");
    TestCaseController::onCreate(parameters);
    this->setupUI();
}
    
void TestUIMiscController::setupUI()
{
    SC_BEGIN_CONTAINER_ROOT_EX("dock=center;", SCWinSize, _pContainerLayer, this)
        SC_INSERT_EDITBOX(nullptr,"dock=center;",Size(100,26),"progressbar_bk.png",this)
    SC_END_CONTAINER
}

void TestUIMiscController::editBoxReturn(ui::EditBox* editBox)
{
    SCLog("editbox text: %s",editBox->getText());
}
