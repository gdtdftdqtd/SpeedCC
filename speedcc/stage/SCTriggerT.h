//
//  SCTrigger.h
//  libspeedcc
//
//  Created by Kevin on 8/2/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

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
            bool                        bActived;
            unsigned char               byPriority; // 0: highest; 255: lowest
            
            inline bool operator<(const SConditionInfo& info) const { return byPriority<info.byPriority; }
            inline bool operator>(const SConditionInfo& info) const { return byPriority>info.byPriority; }
        };
        
    public:
        SC_AVOID_CLASS_COPY(SCTriggerT)
        SC_DEFINE_CLASS_PTR(SCTriggerT)
        
        SC_DEFINE_CREATE_FUNC_0(SCTriggerT)
        
        virtual ~SCTriggerT()
        {
            this->removeUpdateFunc();
        }
        
        void setActive(const bool bActived);
        inline bool getActive() const {return _bActived;}
        
        void addWatch(PtrType_t ptrWatch)
        {
            SCASSERT(ptrWatch!=NULL);
            this->removeUpdateFunc();
            
            _nFuncID = ptrWatch->addUpdateFunc([this](PtrType_t ptrNum, NumberType_t newNum,NumberType_t oldNum)
                                               {
                                                   this->fireBehavior(newNum,oldNum);
                                               });
            
            _ptrWatch = ptrWatch;
        }
        
        int addCondition(const EComparsion comp,
                         const NumberType_t num,
                           SCBehavior::Ptr ptrBvr,
                            const SCDictionary parDic = SCDictionary(),
                           const unsigned char nPriority=kPriorityDefault,
                           const bool bSwallow=false,
                           const bool bActived=true)
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
            
            return this->addCondition(f,ptrBvr,parDic,nPriority,bSwallow,bActived);
        }
        
        int addCondition(const EComparsion comp,
                         const PtrType_t ptrNum,
                         SCBehavior::Ptr ptrBvr,
                         const SCDictionary parDic = SCDictionary(),
                         const unsigned char nPriority=kPriorityDefault,
                         const bool bSwallow=false,
                         const bool bActived=true)
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
            
            return this->addCondition(f,ptrBvr,parDic,nPriority,bSwallow,bActived);
        }
        
        int addCondition(const MatchFunc_t& func,
                         SCBehavior::Ptr ptrBvr,
                         const SCDictionary parDic = SCDictionary(),
                         const unsigned char nPriority=kPriorityDefault,
                         const bool bSwallow=false,
                         const bool bActived=true)
        {
            SConditionInfo ci = {++_nIDCounter,func,ptrBvr,parDic,nPriority,bSwallow,bActived};
            _conditionList.push_back(ci);
            _conditionList.sort(std::greater<SConditionInfo>());
            
            return _nIDCounter;
        }
        
        void setConditionActive(const int nConditionID,const bool bActived)
        {
            for(auto& it : _conditionList)
            {
                if(it.nID == nConditionID)
                {
                    it.bActived = bActived;
                    return;
                }
            }
        }
        
        bool getConditionActive(const int nConditionID) const
        {
            for(const auto& it : _conditionList)
            {
                SC_RETURN_IF(it.nID == nConditionID,it.bActived);
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
        
    protected:
        SCTriggerT():
        _bActived(true),
        _nFuncID(0),
        _nIDCounter(0)
        {}
        
    private:
        void removeUpdateFunc()
        {
            if(_ptrWatch!=NULL && _nFuncID>0)
            {
                _ptrWatch->removeUpdateFunc(_nFuncID);
            }
            _nFuncID = 0;
        }
        
        void fireBehavior(const NumberType_t newNum,const NumberType_t oldNum)
        {
            for(const auto& it : _conditionList)
            {
                SC_CONTINUE_IF(!it.bActived);
                
                if(it.matchFunc(newNum,oldNum))
                {
                    it.ptrBvr->execute(it.parDic);
                    SC_RETURN_V_IF(it.bSwallow);
                }
            }
        }
        
    private:
        int                         _nIDCounter;
        bool                        _bActived;
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
    typedef SCTriggerT<SCWatchString>              SCTriggerString;
}

#endif // __SPEEDCC__SCTRIGGERT_H__
