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

#ifndef __SPEEDCC__SCTRIGGERT_H__
#define __SPEEDCC__SCTRIGGERT_H__

#include "SCPerformObject.h"
#include "../base/SCWatchNumberT.h"
#include "../base/SCWatchString.h"

namespace SpeedCC
{
    template<typename T>
    class SCTriggerT : public SCObject
    {
    public:
        typedef typename T::type    NumberType_t;
        typedef typename T::Ptr     PtrType_t;
        typedef std::function<bool(const NumberType_t,const NumberType_t)>      MatchFunc_t;
        
        enum EPriority
        {
            kPriorityHighest = 0,
            kPriorityDefault = 128,
            kPriorityLowest = 255,
        };
        
        enum EComparsion
        {
            kEqual,
            kNotEqual,
            kGreaterThan,
            kGreaterEqual,
            kLessThan,
            kLessEqual,
        };
        
    private:
        struct SConditionInfo
        {
            int                         nID;
            MatchFunc_t                 matchFunc;
            SCBehavior::Ptr             ptrBvr;
            SCDictionary                parDic;
            bool                        bSwallow;
            bool                        bActive;
            unsigned char               byPriority; // 0: highest; 255: lowest
            
            inline bool operator<(const SConditionInfo& info) const { return byPriority<info.byPriority; }
            inline bool operator>(const SConditionInfo& info) const { return byPriority>info.byPriority; }
        };
        
    public:
        SC_AVOID_CLASS_COPY(SCTriggerT)
        SC_DEFINE_CLASS_PTR(SCTriggerT)
        
        SC_DEFINE_CREATE_FUNC_0(SCTriggerT)
        SC_DEFINE_CREATE_FUNC_1(SCTriggerT,PtrType_t)
        
        virtual ~SCTriggerT()
        {
            this->removeUpdateFunc();
        }
        
        void setActive(const bool bActive);
        inline bool getActive() const {return _bActive;}
        
        void setWatch(PtrType_t ptrWatch)
        {
            SCASSERT(ptrWatch!=nullptr);
            this->removeUpdateFunc();
            
            _nFuncID = ptrWatch->addUpdateFunc([this](PtrType_t ptrNum, const NumberType_t newNum,const NumberType_t oldNum)
                                               {
                                                   this->fireBehavior(newNum,oldNum);
                                               });
            
            _ptrWatch = ptrWatch;
        }
        
        inline PtrType_t getWatch() const { return _ptrWatch; }
        
        int addCondition(const EComparsion comp,
                         const NumberType_t num,
                           SCBehavior::Ptr ptrBvr,
                            const SCDictionary parDic = SCDictionary(),
                           const unsigned char nPriority=kPriorityDefault,
                           const bool bSwallow=false,
                           const bool bActive=true)
        {
            auto f = [num,comp](const NumberType_t newNum,const NumberType_t oldNum) -> bool
            {
                switch(comp)
                {
                    case EComparsion::kEqual:           return (num == newNum);
                    case EComparsion::kNotEqual:        return (num != newNum);
                    case EComparsion::kGreaterThan:     return (num > newNum);
                    case EComparsion::kGreaterEqual:    return (num >= newNum);
                    case EComparsion::kLessThan:        return (num < newNum);
                    case EComparsion::kLessEqual:       return (num <= newNum);
                }
                
                return false;
            };
            
            return this->addCondition(f,ptrBvr,parDic,nPriority,bSwallow,bActive);
        }
        
        int addCondition(const EComparsion comp,
                         const PtrType_t ptrNum,
                         SCBehavior::Ptr ptrBvr,
                         const SCDictionary parDic = SCDictionary(),
                         const unsigned char nPriority=kPriorityDefault,
                         const bool bSwallow=false,
                         const bool bActive=true)
        {
            auto f = [ptrNum,comp](const NumberType_t newNum,const NumberType_t oldNum) -> bool
            {
                switch(comp)
                {
                    case EComparsion::kEqual:           return ((*ptrNum) == newNum);
                    case EComparsion::kNotEqual:        return ((*ptrNum) != newNum);
                    case EComparsion::kGreaterThan:     return ((*ptrNum) > newNum);
                    case EComparsion::kGreaterEqual:    return ((*ptrNum) >= newNum);
                    case EComparsion::kLessThan:        return ((*ptrNum) < newNum);
                    case EComparsion::kLessEqual:       return ((*ptrNum) <= newNum);
                }
                
                return false;
            };
            
            return this->addCondition(f,ptrBvr,parDic,nPriority,bSwallow,bActive);
        }
        
        int addCondition(const MatchFunc_t& func,
                         SCBehavior::Ptr ptrBvr,
                         const SCDictionary parDic = SCDictionary(),
                         const unsigned char nPriority=kPriorityDefault,
                         const bool bSwallow=false,
                         const bool bActive=true)
        {
            SConditionInfo ci = {++_nIDCounter,func,ptrBvr,parDic,bSwallow,bActive,nPriority};
            _conditionList.push_back(ci);
            _conditionList.sort(std::greater<SConditionInfo>());
            
            return _nIDCounter;
        }
        
        void setConditionActive(const int nConditionID,const bool bActive)
        {
            for(auto& it : _conditionList)
            {
                if(it.nID == nConditionID)
                {
                    it.bActive = bActive;
                    return;
                }
            }
        }
        
        bool getConditionActive(const int nConditionID) const
        {
            for(const auto& it : _conditionList)
            {
                SC_RETURN_IF(it.nID == nConditionID,it.bActive);
            }
            
            return false;
        }
        
        void removeCondition(const int nConditionID)
        {
            _conditionList.remove_if([nConditionID](const SConditionInfo& ci)
                                     {
                                         return (ci.nID==nConditionID);
                                     });
        }
        
        void Activate()
        {
            SC_RETURN_V_IF(_ptrWatch==nullptr);
            this->fireBehavior((*_ptrWatch),(*_ptrWatch));
        }
        
    protected:
        SCTriggerT():
        _bActive(true),
        _nFuncID(0),
        _nIDCounter(0)
        {}
        
        SCTriggerT(PtrType_t ptrWatch):
        _bActive(true),
        _nFuncID(0),
        _nIDCounter(0)
        {
            this->setWatch(ptrWatch);
        }
        
        
    private:
        void removeUpdateFunc()
        {
            if(_ptrWatch!=nullptr && _nFuncID>0)
            {
                _ptrWatch->removeUpdateFunc(_nFuncID);
            }
            _nFuncID = 0;
        }
        
        void fireBehavior(const NumberType_t newNum,const NumberType_t oldNum)
        {
            for(auto& it : _conditionList)
            {
                SC_CONTINUE_IF(!it.bActive);
                
                if(it.matchFunc(newNum,oldNum))
                {
                    it.ptrBvr->execute(it.parDic);
                    SC_RETURN_V_IF(it.bSwallow);
                }
            }
        }
        
    private:
        int                         _nIDCounter;
        bool                        _bActive;
        PtrType_t                   _ptrWatch;
        int                         _nFuncID;
        std::list<SConditionInfo>   _conditionList;
    };
    
    typedef SCTriggerT<SCWatchUInt>                SCTriggerUInt;
    typedef SCTriggerT<SCWatchFloat>               SCTriggerFloat;
    typedef SCTriggerT<SCWatchDouble>              SCTriggerDouble;
    typedef SCTriggerT<SCWatchInt>                 SCTriggerInt;
    typedef SCTriggerT<SCWatchLong>                SCTriggerLong;
    typedef SCTriggerT<SCWatchULong>               SCTriggerULong;
    typedef SCTriggerT<SCWatchByte>                SCTriggerByte;
    typedef SCTriggerT<SCWatchBool>                SCTriggerBool;
    typedef SCTriggerT<SCWatchString>              SCTriggerString;
}

#endif // __SPEEDCC__SCTRIGGERT_H__
