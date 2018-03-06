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

#ifndef __TESTHOME_SCENE_H__
#define __TESTHOME_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"


#define kFeatureIDOfNonConsumable       1
#define kProductIDOfNonConsumable       "non-consumable" // setup in IAP from App Store

#define kFeatureIDOfConsumable          2
#define kProductIDOfConsumable          "consumable" // setup in IAP from App Store
#define kPointIDOfConsumable            1
#define kPointDiffOfConsumable          10

#define kFeatureIDOfConsumePoint        3
#define kPointStepOfConsume             5

using namespace SpeedCC;

class TestHomeController : public SpeedCC::SCSceneController
{
public:
    virtual void onCreate(SCDictionary parameters) override;
    
    void onPurchaseResult(SCString strProductID,SCStore::EResultType result,void* pInfo);
    void onRequestIAPInfoResult(SCString strProductID,SCStore::EResultType result,void* pInfo);
    
private:
    SCWatchString::Ptr      _ptrConsumableCurrency;
    SCWatchFloat::Ptr       _ptrConsumablePrice;
    
    SCWatchString::Ptr      _ptrNonConsumableCurrency;
    SCWatchFloat::Ptr       _ptrNonConsumablePrice;
};

#endif // __TESTHOME_SCENE_H__
