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

#include "TestHomeController.h"

USING_NS_CC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    _ptrConsumablePrice = SCWatchFloat::create();
    _ptrConsumableCurrency = SCWatchString::create();
    
    _ptrNonConsumablePrice = SCWatchFloat::create();
    _ptrNonConsumableCurrency = SCWatchString::create();
    
    auto ptrBvrConsumable = SCBehaviorPurchase::create(kFeatureIDOfConsumable,
                                                       SC_MAKE_FUNC(onPurchaseResult, this));
    
    auto ptrBvrNonConsumable = SCBehaviorPurchase::create(kFeatureIDOfNonConsumable,
                                                          SC_MAKE_FUNC(onPurchaseResult, this));
    
    SC_BEGIN_CONTAINER_ROOT(nullptr,nullptr)
//        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,"dock=center;",SCWinSize,Color4B::WHITE)
            SC_BEGIN_CONTAINER_ALIGNMENT(nullptr, "dock=center;", false, 40, nullptr)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                    SC_INSERT_LABEL(nullptr, "", "Consumable Price:  ", "", 20)
                    SC_INSERT_LABEL(nullptr, "", _ptrConsumableCurrency, "", 20)
                    SC_INSERT_LABEL(nullptr, "", _ptrConsumablePrice, "", 20)
                SC_END_CONTAINER
    
                SC_INSERT_BUTTON_LABEL(nullptr, "", "Purchase Consumable", "", 15, ptrBvrConsumable)
    
                SC_INSERT_LAYER(nullptr, "", Size(10,30))
    
                SC_BEGIN_CONTAINER_ALIGNMENT(nullptr, "dock=center;", true, 5, nullptr)
                    SC_INSERT_LABEL(nullptr, "", "Consumable Price:  ", "", 20)
                    SC_INSERT_LABEL(nullptr, "", _ptrNonConsumableCurrency, "", 20)
                    SC_INSERT_LABEL(nullptr, "", _ptrNonConsumablePrice, "", 20)
                SC_END_CONTAINER
    
                SC_INSERT_BUTTON_LABEL(nullptr, "", "Purchase Non-Consumable", "", 15, ptrBvrNonConsumable)
            SC_END_CONTAINER
//        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestHomeController::onPurchaseResult(SCString strProductID,SCStore::EResultType result,void* pInfo)
{
    switch(result)
    {
        case SCStore::EResultType::kSuccess:
        {
            if(strProductID==kProductIDOfNonConsumable)
            {// non-consumable
                
            }
            else if(strProductID==kProductIDOfConsumable)
            {// consumable
                
            }
            
            SCLog("Purchase '%s' success.",strProductID.c_str());
        }
            break;
            
        case SCStore::EResultType::kFailed:
        {
            SCLog("Purchase '%s' failed.",strProductID.c_str());
        }
            break;
            
        case SCStore::EResultType::kUserCancelled:
        {
            SCLog("User cancels purchase.");
        }
            break;
    }
}

void TestHomeController::onRequestIAPInfoResult(SCString strProductID,SCStore::EResultType result,void* pInfo)
{
    if(result==SCStore::EResultType::kSuccess)
    {
        SCLog("Store IAP info request success.");
        SCASSERT(pInfo!=nullptr);
        SCStore::SIAPInfo* pInfo2 = (SCStore::SIAPInfo*)pInfo;
        
        if(strProductID==kProductIDOfNonConsumable)
        {// non-consumable
            (*_ptrNonConsumablePrice) = *(pInfo2->ptrPrice);
            (*_ptrNonConsumableCurrency) = pInfo2->strCurrency;
        }
        else if(strProductID==kProductIDOfConsumable)
        {// consumable
            (*_ptrConsumablePrice) = *(pInfo2->ptrPrice);
            (*_ptrConsumableCurrency) = pInfo2->strCurrency;
        }
        else
        {
            SCASSERT(false);
        }
    }
    else
    {
        SCLog("Store IAP info request failed.");
    }
}

