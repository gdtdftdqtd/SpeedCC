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

#ifndef __SPEEDCC__SCUIARG_H__
#define __SPEEDCC__SCUIARG_H__

#include "../base/SCString.h"
#include "../base/SCObject.h"
#include "../base/SCWatchNumberT.h"

#include "../stage/SCBehaviorCommon.h"

#include "SCBinderCocos.h"
#include "SCNodeStyle.h"
#include "SCRefHolder.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace SpeedCC
{
    class SCSceneController;
    class SCUIBuilder;
    
    typedef void (*FUN_SCSetStyle_t)(cocos2d::Node* pNode,const SCString& strStyle,SCNodeStyle::SFilterConfig* pFilterConfig);
    
    struct SCUIArg
    {
        struct StringPurifier
        {
            StringPurifier(void*){}
            StringPurifier(decltype(nullptr)){}
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
            typename = typename std::enable_if<SCIsWatchClassT<typename T::type>::value==1,T>::type >
            LabelStringPurifier(T ptrWatch)
            {
                if(ptrWatch!=nullptr)
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
            menuFunc(nullptr)
            {
            }
            
            BehaviorPurifier(cocos2d::SEL_MenuHandler func):
            menuFunc(func),
            callFunc(nullptr)
            {
            }
            
            template<typename T,
            typename = typename std::enable_if<std::is_convertible<T,SCBehavior::Ptr>::value,T>::type >
            BehaviorPurifier(T bvr):
            callFunc(nullptr),
            menuFunc(nullptr),
            ptrResultBvr(bvr)
            {
            }
            
            BehaviorPurifier(decltype(nullptr)):
            callFunc(nullptr),
            menuFunc(nullptr)
            {}
            
            void setupBehavior(cocos2d::Ref* pCall,cocos2d::Ref* pSender)
            {
                if(ptrResultBvr==nullptr)
                {
                    if(menuFunc!=nullptr)
                    {
                        auto func = menuFunc;
                        ptrResultBvr = SCBehaviorCallFunc::create([pCall,func,pSender]()
                                                                  {
                                                                      (pCall->*func)(pSender);
                                                                  });

                    }
                    else if(callFunc!=nullptr)
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
                SCASSERT(ptrBool!=nullptr);
                bResult = (ptrBool==nullptr ? false : (bool)(*ptrBool));
            }
            
            bool bResult;
            SCWatchBool::Ptr    ptrWatch;
        };
        
        struct NodePurifier
        {
            template<typename T>
            NodePurifier(T* node):
            pfunSetStyle(&SCNodeStyle::setStyle<T>)
            {
                ptrNodeHolder = SCRef2Ptr::create(node);
            }
            
            SCRef2Ptr::Ptr        ptrNodeHolder;
            FUN_SCSetStyle_t     pfunSetStyle;
        };
        
        struct MenuItemPurifier
        {
            MenuItemPurifier(const char* pszImage)
            {
                SCString strImage = pszImage;
                auto pMenuItem = cocos2d::MenuItemImage::create(strImage.c_str(),strImage.c_str(),strImage.c_str());
                ptrHolder = SCRef2Ptr::create(pMenuItem);
            }
            
            MenuItemPurifier(const SCString& strImage)
            {
                auto pMenuItem = cocos2d::MenuItemImage::create(strImage.c_str(),strImage.c_str(),strImage.c_str());
                ptrHolder = SCRef2Ptr::create(pMenuItem);
            }
            
            MenuItemPurifier(const SCString& strText,const int size)
            {
                auto pLabel = cocos2d::Label::createWithSystemFont(strText.c_str(),"",size);
                auto pMenuItem = cocos2d::MenuItemLabel::create(pLabel);
                
                ptrHolder = SCRef2Ptr::create(pMenuItem);
            }
            
            MenuItemPurifier(cocos2d::MenuItem* pMenuItem)
            {
                SCASSERT(pMenuItem!=nullptr);
                ptrHolder = SCRef2Ptr::create(pMenuItem);
            }
            
        public:
            SCRef2Ptr::Ptr    ptrHolder;
        };
        
        struct NumberPurifier
        {
            template<typename T,
            typename = typename std::enable_if<SCIsWatchNumberableT<typename T::type>::value==1,T>::type >
            NumberPurifier(T ptrWatch)
            {
                if(ptrWatch!=nullptr)
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
        
        struct SizePurifier
        {
            SizePurifier(const cocos2d::Size& size0):
            size(size0)
            {
            }
            
            SizePurifier(decltype(nullptr)):
            size(cocos2d::Size::ZERO)
            {
            }
            
            cocos2d::Size size;
        };
        
        struct ScrollViewDirectionPurifier
        {
            ScrollViewDirectionPurifier(const bool bHor)
            {
                direction = bHor ? cocos2d::ui::ScrollView::Direction::HORIZONTAL : cocos2d::ui::ScrollView::Direction::VERTICAL;
            }
            
            ScrollViewDirectionPurifier(const cocos2d::ui::ScrollView::Direction dir):
            direction(dir)
            {
            }
            
            cocos2d::ui::ScrollView::Direction direction;
        };
 
    };
    
    class SCUITypeDef
    {
        friend class SCUIBuilder;
        
        typedef void (*FUN_SCSetStyle_t)(cocos2d::Node* pNode,const SCString& strStyle);
        
        struct ContainerEndFunctor
        {
            cocos2d::Node*              pNode;
            SCString                    strStyle;
            FUN_SCSetStyle_t         pfunSetStyle;
            
            ContainerEndFunctor():
            pfunSetStyle(nullptr),
            pNode(nullptr)
            {}
            
            virtual void operator()()
            {
                if(pNode!=nullptr && pfunSetStyle!=nullptr && !strStyle.isEmpty())
                {
                    (*pfunSetStyle)(pNode,strStyle);
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
            pContainerNode(nullptr),
            containerType(EContainerType::kNormal)
            {}
        };
    };
}

#endif // __SPEEDCC__SCUIARG_H__
