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

#include "../system/SCFileUtils.h"

#include "../component/SCBehaviorCommon.h"

#include "SCBinder.h"
#include "SCNodeProperty.h"
#include "SCRefHolder.h"

#include "cocos2d.h"

namespace SpeedCC
{
    class SCSceneController;
    class SCUIBuilder;
    
    typedef void (*FUN_SCSetProperty_t)(cocos2d::Node* pNode,const SCString& strProperty,SCNodeProperty::SFilterConfig* pFilterConfig);
    
    struct SCUIArg
    {
        struct StringPurifier
        {
            StringPurifier(void*){}
            StringPurifier(long){}
            StringPurifier(int){}
            StringPurifier(const char* psz):strResult(psz){}
            StringPurifier(const SCString& str):strResult(str){}
            
            SCString strResult;
        };
        
        struct LabelStringPurifier
        {
            LabelStringPurifier(...) {}
            LabelStringPurifier(void*) {}
            LabelStringPurifier(const char* psz):strResult(psz){}
            LabelStringPurifier(const SCString& str):strResult(str) {}
            LabelStringPurifier(long n):strResult(n){}
            LabelStringPurifier(int n):strResult(n) {}
            LabelStringPurifier(float n):strResult(n) {}
            LabelStringPurifier(double n):strResult(n) {}
            
            template<typename T,
            typename = typename std::enable_if<SCIsWatchClass<typename T::type>::value==1,T>::type >
            LabelStringPurifier(T ptrWatch)
            {
                if(ptrWatch!=NULL)
                {
                    ptrLabelBinder = SCBinderUILabel::create();
                    ptrLabelBinder->setWatch(ptrWatch);
                }
            }
            
            LabelStringPurifier(SCBinderUILabel::Ptr ptrBinder): ptrLabelBinder(ptrBinder) {}
            
            SCString strResult;
            SCBinderUILabel::Ptr    ptrLabelBinder;
        };
        
        struct BehaviorPurifier
        {
            BehaviorPurifier(cocos2d::SEL_CallFunc func):
            callFunc(func),
            menuFunc(NULL)
            {
            }
            
            BehaviorPurifier(cocos2d::SEL_MenuHandler func):
            menuFunc(func),
            callFunc(NULL)
            {
            }
            
            template<typename T,
            typename = typename std::enable_if<std::is_convertible<T,SCBehavior::Ptr>::value,T>::type >
            BehaviorPurifier(T bvr):
            callFunc(NULL),
            menuFunc(NULL),
            ptrResultBvr(bvr)
            {
            }
            
            BehaviorPurifier(decltype(NULL)):
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
        
        struct BoolPurifier
        {
            BoolPurifier(const bool bValue):
            bResult(bValue)
            {}
            
            BoolPurifier(SCWatchBool::Ptr ptrBool):
            ptrWatch(ptrBool)
            {
                SCASSERT(ptrBool!=NULL);
                bResult = (ptrBool==NULL ? false : (bool)(*ptrBool));
            }
            
            bool bResult;
            SCWatchBool::Ptr    ptrWatch;
        };
        
        struct NodePurifier
        {
            template<typename T>
            NodePurifier(T* node):
            pfunSetProperty(&SCNodeProperty::setProperty<T>)
            {
                ptrNodeHolder = SCRefHolder::create(node);
            }
            
            SCRefHolder::Ptr        ptrNodeHolder;
            FUN_SCSetProperty_t     pfunSetProperty;
        };
        
        struct MenuItemPurifier
        {
            MenuItemPurifier(const SCString& strImage)
            {
                SCString strFile = SCFileUtils::getFullPathFile(strImage);
                auto pMenuItem = cocos2d::MenuItemImage::create(strFile.c_str(),strFile.c_str(),strFile.c_str());
                ptrHolder = SCRefHolder::create(pMenuItem);
            }
            
            MenuItemPurifier(const SCString& strText,const int size)
            {
                auto pLabel = cocos2d::Label::createWithSystemFont(strText.c_str(),"",size);
                auto pMenuItem = cocos2d::MenuItemLabel::create(pLabel);
                
                ptrHolder = SCRefHolder::create(pMenuItem);
            }
            
            MenuItemPurifier(cocos2d::MenuItem* pMenuItem)
            {
                SCASSERT(pMenuItem!=NULL);
                ptrHolder = SCRefHolder::create(pMenuItem);
            }
            
        public:
            SCRefHolder::Ptr    ptrHolder;
        };
        
        struct NumberPurifier
        {
            template<typename T,
            typename = typename std::enable_if<SCIsWatchNumberable<typename T::type>::value==1,T>::type >
            NumberPurifier(T ptrWatch)
            {
                if(ptrWatch!=NULL)
                {
                    ptrBinderProgress = SCBinderUIProgress::create();
                    ptrBinderProgress->setWatch(ptrWatch);
                }
            }
            
            NumberPurifier(const int nValue):
            nPercentage(nValue)
            {
                
            }
            
            SCBinderUIProgress::Ptr     ptrBinderProgress;
            int                         nPercentage;
        };
 
    };
    
    class SCUITypeDef
    {
        friend class SCUIBuilder;
        
        typedef void (*FUN_SCSetProperty_t)(cocos2d::Node* pNode,const SCString& strProperty);
        
        struct ContainerEndFunctor
        {
            cocos2d::Node*              pNode;
            SCString                    strProperty;
            FUN_SCSetProperty_t         pfunSetProperty;
            
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
            kLayoutPadding,
            kMultiplexLayer
        };
        
        struct SUIContext
        {
            cocos2d::Node*                      pContainerNode;
            std::list<cocos2d::Node*>           childNodeList;
            std::function<void(SUIContext&)>    endFunc;
            EContainerType                      containerType;
            
            SUIContext():
            pContainerNode(NULL),
            containerType(EContainerType::kNormal)
            {}
        };
    };
}

#endif // __SPEEDCC__SCUIARG_H__
