//
//  SCClickable.hpp
//  libspeedcc
//
//  Created by Kevin on 8/2/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCNODECLICKABLE_H__
#define __SPEEDCC__SCNODECLICKABLE_H__

#include "cocos2d.h"

#include "SCEventEmitter.h"

#include "../base/SCObject.h"
#include "../stage/SCMessageDispatch.h"
#include "../stage/SCPerformObject.h"

namespace SpeedCC
{
    class SCNodeClickable :
    public SCObject,
    public SCMessageListener
    {
    public:
        SC_AVOID_CLASS_COPY(SCNodeClickable)
        SC_DEFINE_CLASS_PTR(SCNodeClickable)
        
        SC_DEFINE_CREATE_FUNC_0(SCNodeClickable)
        SC_DEFINE_CREATE_FUNC_1(SCNodeClickable,cocos2d::Node*)
        SC_DEFINE_CREATE_FUNC_2(SCNodeClickable,cocos2d::Node*,SCBehavior::Ptr)
        
        virtual ~SCNodeClickable();
        
        void setActived(const bool bActived);
        inline bool getActived() const { return _bActived; }
        
        void setNode(cocos2d::Node* pNode);
        void setBehavior(SCBehavior::Ptr ptrBvr);
        
    private:
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        bool isNodeInTouch(cocos2d::Touch* pTouch, const cocos2d::Camera* pCamera);
        
    protected:
        SCNodeClickable();
        SCNodeClickable(cocos2d::Node* pNode);
        SCNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr);
        
    protected:
        bool                        _bActived;
        bool                        _bTrack;
        bool                        _bSelected;
        cocos2d::Node*              _pNode;
        cocos2d::MenuItem*          _pMenuItem;
        SCEventEmitter::Ptr         _ptrEventEmitter;
        const cocos2d::Camera*       _pSelectedCamera;
        SCBehavior::Ptr             _ptrBvr;
    };
}

#endif // __SPEEDCC__SCNODECLICKABLE_H__