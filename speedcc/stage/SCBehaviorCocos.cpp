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

#include "SCBehaviorCocos.h"
#include "../cocos/SCSceneController.h"

namespace SpeedCC
{
    ///--------------- SCBehaviorSceneGoto
    SCBehaviorSceneGoto::SCBehaviorSceneGoto(const SCSceneNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic):
            _switch(swi),
            _parameterDic(dic),
            _bDirect(false)
    {

    }

    void SCBehaviorSceneGoto::execute(const SCDictionary& par)
    {
        if(_bDirect)
        {
            this->onBvrFunc();
        }
        else if(_ptrDelayBvr==nullptr)
        {
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->addObject(this->makeObjPtr(this));
            _ptrDelayBvr->execute(par);
        }
        
    }
    
    void SCBehaviorSceneGoto::setSceneParameter(const SCDictionary& dic)
    {
        _parameterDic = dic;
    }
    
    void SCBehaviorSceneGoto::onBvrFunc()
    {
        SCSceneNav()->setSceneParameter(_parameterDic);
        SCSceneNav()->gotoScene(_switch);
        _ptrDelayBvr = nullptr;
    }
    
    ///--------------- SCBehaviorSceneBack
    void SCBehaviorSceneBack::execute(const SCDictionary& par)
    {
        if(_bDirect)
        {
            this->onBvrFunc();
        }
        else if(_ptrDelayBvr==nullptr)
        {
            
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->addObject(this->makeObjPtr(this));
            _ptrDelayBvr->execute(par);
        }
    }
    
    void SCBehaviorSceneBack::onBvrFunc()
    {
        SCSceneNavigator::getInstance()->back(_nSceneNum);
        _ptrDelayBvr = nullptr;
    }
    
    ///--------------- SCBehaviorAlertBoxSelected
    SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected():
    _pController(nullptr),
    _nSelected(0)
    {
    }
    
    SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected(SCSceneController* pController,const int nSelected):
    _pController(pController),
    _nSelected(nSelected)
    {
    }
    
    void SCBehaviorAlertBoxSelected::setController(SCSceneController* pController)
    {
        _pController = pController;
    }
    
    void SCBehaviorAlertBoxSelected::setSelectedIndex(const int nSelectedIndex)
    {
        _nSelected = nSelectedIndex;
    }
    
    void SCBehaviorAlertBoxSelected::execute(const SCDictionary& par)
    {
        if(_pController!=nullptr)
        {
            SCBehaviorSceneBack::create()->execute();
            _pController->finish(SC_NUM_2_PVOID(_nSelected));
        }
    }
    
    ///--------- SCBehaviorPurchase
    SCBehaviorPurchase::SCBehaviorPurchase(const int nFeatureID,SCStore::ResultFunc_t resultFunc):
    _nFeatureID(nFeatureID)
    {
        this->setResultFunc(resultFunc);
    }
    
    SCBehaviorPurchase::~SCBehaviorPurchase()
    {
        SCStore::getInstance()->setPurchaseResultFunc(nullptr);
    }
    
    void SCBehaviorPurchase::setResultFunc(const SCStore::ResultFunc_t& func)
    {
        _resultFunc = [func](int nFeatureID,SCStore::EResultType result,void* pInfo)
        {
            auto ptrCtrl = SCSceneNav()->getCurrentController();
            ptrCtrl->showBlackMask(false);
            ptrCtrl->setAllTouchEnabled(true);
            
            if(func!=nullptr)
            {
                func(nFeatureID,result,pInfo);
            }
        };
    }
    
    void SCBehaviorPurchase::execute(const SCDictionary& par)
    {
        auto ptrCtrl = SCSceneNav()->getCurrentController();
        ptrCtrl->showBlackMask(true);
        ptrCtrl->setAllTouchEnabled(false);
        SCStore::getInstance()->purchaseFeature(_nFeatureID,_resultFunc);
    }
    
    ///---------- SCBehaviorRequestProduct
    SCBehaviorRequestProduct::~SCBehaviorRequestProduct()
    {
        SCStore::getInstance()->setRequestProductResultFunc(nullptr);
    }
    
    void SCBehaviorRequestProduct::execute(const SCDictionary& par)
    {
        SCStore::getInstance()->requestProductInfo(_resultFunc);
    }
    
    
    ///----------- SCBehaviorRestorePurchased
    SCBehaviorRestorePurchased::~SCBehaviorRestorePurchased()
    {
        SCStore::getInstance()->setRestoreResultFunc(nullptr);
    }
    
    void SCBehaviorRestorePurchased::execute(const SCDictionary& par)
    {
        SCStore::getInstance()->restorePurchased(_resultFunc);
    }
}
