//
//  SCArgTraits.hpp
//  libspeedcc
//
//  Created by Kevin on 21/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCUIARG_H__
#define __SPEEDCC__SCUIARG_H__

#include "../base/SCString.h"
#include "../base/SCObject.h"
#include "../base/SCWatchNumberT.h"

#include "../component/SCBehaviorCommon.h"

#include "SCBinder.h"
#include "SCNodeProperty.h"

#include "cocos2d.h"

namespace SpeedCC
{
    class SCSceneController;
    class SCUIBuilder;
    
    typedef void (*FUN_SCSetProperty2_t)(cocos2d::Node* pNode,const SCString& strProperty,SCNodeProperty::SFilterConfig* pFilterConfig);
    
    struct SCUIArg
    {
        struct PurifyString
        {
            PurifyString(void*){}
            PurifyString(long){}
            PurifyString(int){}
            PurifyString(const char* psz):strResult(psz){}
            PurifyString(const SCString& str):strResult(str){}
            
            SCString strResult;
        };
        
        struct PurifyLabelString
        {
            PurifyLabelString(...) {}
            PurifyLabelString(void*) {}
            PurifyLabelString(const char* psz):strResult(psz){}
            PurifyLabelString(const SCString& str):strResult(str) {}
            PurifyLabelString(long n):strResult(n){}
            PurifyLabelString(int n):strResult(n) {}
            PurifyLabelString(float n):strResult(n) {}
            PurifyLabelString(double n):strResult(n) {}
            
            template<typename T,
            typename = typename std::enable_if<SCIsWatchClass<typename T::type>::value==1,T>::type >
            PurifyLabelString(T ptrWatch)
            {
                if(ptrWatch!=NULL)
                {
                    ptrLabelBinder = SCBinderUILabel::create();
                    ptrLabelBinder->setWatch(ptrWatch);
                }
            }
            
            PurifyLabelString(SCBinderUILabel::Ptr binderPtr): ptrLabelBinder(binderPtr) {}
            
            SCString strResult;
            SCBinderUILabel::Ptr    ptrLabelBinder;
        };
        
        struct PurifyBehavior
        {
            PurifyBehavior(cocos2d::SEL_CallFunc func):
            callFunc(func),
            menuFunc(NULL)
            {
            }
            
            PurifyBehavior(cocos2d::SEL_MenuHandler func):
            menuFunc(func),
            callFunc(NULL)
            {
            }
            
            PurifyBehavior(SCBehavior::Ptr bvr):
            callFunc(NULL),
            menuFunc(NULL)
            { ptrResultBvr = bvr; }
            
            PurifyBehavior(decltype(NULL)):
            callFunc(NULL),
            menuFunc(NULL)
            {}
            
            PurifyBehavior(...):
            callFunc(NULL),
            menuFunc(NULL)
            {}
            
            void setupBehavior(cocos2d::Ref* pCall,cocos2d::Ref* pSender)
            {
                if(ptrResultBvr==NULL)
                {
                    if(menuFunc!=NULL)
                    {
                        auto func = menuFunc;
                        ptrResultBvr = SCBehaviorCallFunc::create([pCall,func,pSender]()
                                                                  {
                                                                      (pCall->*func)(pSender);
                                                                  });

                    }
                    else if(callFunc!=NULL)
                    {
                        auto func = callFunc;
                        ptrResultBvr = SCBehaviorCallFunc::create([pCall,func]()
                                                                  {
                                                                      (pCall->*func)();
                                                                  });
                    }
                }
            }
            
            SCBehavior::Ptr     ptrResultBvr;
            
        private:
            cocos2d::SEL_CallFunc callFunc;
            cocos2d::SEL_MenuHandler menuFunc;
        };
        
        struct PurifyBool
        {
            PurifyBool(const bool bValue):bResult(bValue) {}
            PurifyBool(SCWatchBool::Ptr ptrBool) { bResult = (ptrBool==NULL ? false : (bool)(*ptrBool)); }
            
            bool bResult;
        };
        
        struct PurifyNode
        {
            template<typename T>
            PurifyNode(T* node):
            pNode(node),
            pfunSetProperty(&SCNodeProperty::setProperty<T>)
            {
            }
            
            cocos2d::Node*          pNode;
            FUN_SCSetProperty2_t     pfunSetProperty;
        };
 
    };
    
    class SCUIMethod
    {
        friend class SCUIBuilder;
        
        static inline void assignNode(...){}
        
        template<typename T1,typename T2>
        static inline void assignNode(T1* pNodeFrom,T2 *&pNodeTo) {pNodeTo = pNodeFrom;}
        
        // label binder
//        static inline void bindLabel(...) {}
//        static inline void bindLabel(cocos2d::Label* pLabel,...) {}
//        static void bindLabel(cocos2d::Label* pLabel,SCBinderUILabel::Ptr ptrBinder,SCSceneController* pController);
        
        /*
        template<typename T,
        typename = typename std::enable_if<SCIsWatchClass<typename T::type>::value==1,T>::type >
        static inline SCBinderUILabel::Ptr createLabelBinder(T ptrWatch)
        {
            if(ptrWatch!=NULL)
            {
                auto ptrLabelBinder = SCBinderUILabel::create();
                
                ptrLabelBinder->setWatch(ptrWatch);
                return ptrLabelBinder;
            }
            
            return NULL;
        }
        
        static inline SCBinderUILabel::Ptr createLabelBinder(SCBinderUILabel::Ptr ptrBinder) { return ptrBinder; }
        
        static inline SCBinderUILabel::Ptr createLabelBinder(...) { return NULL; }
        */
        // toggle binder
        static inline SCBinderUISwitch::Ptr createToggleBinder(SCBinderUISwitch::Ptr ptrBinder) { return ptrBinder; }
        
        static inline SCBinderUISwitch::Ptr createToggleBinder(SCWatchBool::Ptr ptrWatch)
        {
            return (ptrWatch==NULL) ? NULL : SCBinderUISwitch::create(ptrWatch);
        }
        
        static inline SCBinderUISwitch::Ptr createToggleBinder(...) { return NULL;}
        
        static void bindToggle(cocos2d::MenuItemToggle* pToggle,
                                      SCBinderUISwitch::Ptr ptrBinder,
                                      SCSceneController* pController,
                                      const std::function<void(cocos2d::Ref*)>& func);
    };
    
    class SCUITypeDef
    {
        friend class SCUIBuilder;
        
        typedef void (*FUN_SCSetProperty2_t)(cocos2d::Node* pNode,const SCString& strProperty);
        
        struct ContainerEndFunctor
        {
            cocos2d::Node*              pNode;
            SCString                    strProperty;
            FUN_SCSetProperty2_t         pfunSetProperty;
            
            ContainerEndFunctor():
            pfunSetProperty(NULL),
            pNode(NULL)
            {}
            
            virtual void operator()()
            {
                if(pNode!=NULL && pfunSetProperty!=NULL && !strProperty.isEmpty())
                {
                    (*pfunSetProperty)(pNode,strProperty);
                }
            }
        };
        
        enum class EContainerType
        {
            kNormal,
            kButtonList,
            kMultiplexLayer
        };
        
        enum class ELabelType
        {
            kSystem,
            kTTF,
            kBMFont,
        };
        
        struct SUIContext
        {
            cocos2d::Node*                      pContainerNode;
            ContainerEndFunctor*                pfunEndFunctor;
            std::vector<cocos2d::MenuItem*>     menuItemVtr;
            EContainerType                      containerType;
            
            SUIContext():
            pContainerNode(NULL),
            pfunEndFunctor(NULL),
            containerType(EContainerType::kNormal)
            {}
        };
    };
}

#endif // __SPEEDCC__SCUIARG_H__
