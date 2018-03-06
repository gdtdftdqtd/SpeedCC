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

#include "SCMessageDefaultProc.h"

#include "../system/SCSetting.h"
#include "../system/SCStore.h"
#include "../system/SCSystem.h"

#include "../platform/SCOSSystem.h"

namespace SpeedCC
{
    void SCMessageDefaultProc::addAlertBoxCallback(const std::function<void(int)>& func,
                                                   const int nAlertBoxID)
    {
        SCASSERT(func!=nullptr);
        SCASSERT(nAlertBoxID>0);
        _alertBoxID2CBMap[nAlertBoxID] = func;
    }
    
    void SCMessageDefaultProc::processMessage(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        
        switch(ptrMsg->nMsgID)
        {
            case SCID::Msg::kMsgAppEnterBackground:
            {
                SCSetting::getInstance()->flush();
            }
                break;
                
            case SCID::Msg::kMsgAlertBoxSelected:
            {
                auto nAlertBoxID = ptrMsg->parameters.getValue(SC_KEY_ID).getInt();
                auto it = _alertBoxID2CBMap.find(nAlertBoxID);
                if(it!=_alertBoxID2CBMap.end())
                {
                    auto nSelected = ptrMsg->parameters.getValue(SC_KEY_RESULT).getInt();
                    (*it).second(nSelected);
                    _alertBoxID2CBMap.erase(it);
                }
            }
                break;
                
            case SCID::Msg::kMsgQuit:
                exit(0);
                break;
        }
    }
}
