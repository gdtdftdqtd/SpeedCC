

#include "SCNodeUtils.h"
#include "SCMacroDef.h"
#include "SCCocosDef.h"
#include "SCNodeClickable.h"
#include "SCRefHolder.h"

using namespace cocos2d;

namespace SpeedCC
{
    Vec2 SCNodeUtils::posA2P(const Vec2& ptAbs,const Size& frameSize=SCWinSize)
    {
        return Vec2(ptAbs.x/frameSize.width,ptAbs.y/frameSize.height);
    }
    
    Vec2 SCNodeUtils::posP2A(const Vec2& ptPer,const Size& frameSize=SCWinSize)
    {
        return Vec2(ptPer.x*frameSize.width,ptPer.y*frameSize.height);
    }
    
    bool SCNodeUtils::setPerPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer)
    {
        SC_RETURN_IF(pNode==NULL || pNode->getParent()==NULL,false);
        
        const auto frameSize = pNode->getParent()->getContentSize();
        const auto pos = SCNodeUtils::posP2A(ptPer,frameSize);
        
        if(ptPer.x!=kSCPositionIgnore && ptPer.y!=kSCPositionIgnore)
        {
            pNode->setPosition(pos);
        }
        else if(ptPer.x!=kSCPositionIgnore)
        {
            pNode->setPositionX(pos.x);
        }
        else if(ptPer.y!=kSCPositionIgnore)
        {
            pNode->setPositionY(pos.y);
        }
        
        return true;
    }
    
    void SCNodeUtils::setPositionBy(cocos2d::Node* pNode,float fXBy,float fYBy)
    {
        SC_RETURN_V_IF(pNode==NULL);
        
        auto pos = pNode->getPosition();
        pos.x += fXBy;
        pos.y += fYBy;
        pNode->setPosition(pos);
    }
    
    bool SCNodeUtils::setDock(cocos2d::Node* pNode,const int dockFlag)
    {
        SC_RETURN_IF(pNode==NULL || pNode->getParent()==NULL,false);
        
        auto ptPos = pNode->getPosition();
        
        if(SC_BIT_HAS_OR(dockFlag, kDockLeft|kDockRight|kDockMiddleX))
        {// x axis
            if(SC_BIT_HAS_AND(dockFlag,kDockMiddleX))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,0,true);
            }
            else if(SC_BIT_HAS_AND(dockFlag,kDockLeft))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,-1,true);
            }
            else if(SC_BIT_HAS_AND(dockFlag,kDockRight))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,1,true);
            }
        }
        
        if(SC_BIT_HAS_OR(dockFlag, kDockTop|kDockBottom|kDockMiddleY))
        {// y axis
            if(SC_BIT_HAS_AND(dockFlag,kDockMiddleY))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,0,false);
            }
            else if(SC_BIT_HAS_AND(dockFlag,kDockTop))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,1,false);
            }
            else if(SC_BIT_HAS_AND(dockFlag,kDockBottom))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,-1,false);
            }
        }
        
        pNode->setPosition(ptPos);
        
        return true;
    }
    
    float SCNodeUtils::getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX)
    {
        SC_RETURN_IF(pNode==NULL || pNode->getParent()==NULL,-999);
        float fRet = 0;
        
        const auto& frameSize = pNode->getParent()->getContentSize();
        const auto& nodeSize = pNode->getContentSize();
        
        const auto& ptAnchor = pNode->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : pNode->getAnchorPoint();
        
        if(bIsX)
        {// x
            const float fScaleX = pNode->getScaleX();
            // anchor offset by (0.5,0.5)
            float fAnchorOffset = (ptAnchor.x-0.5)*nodeSize.width*fScaleX;
            
            if(nPark>0)
            {// right
                fRet = (frameSize.width - nodeSize.width*fScaleX/2) + fAnchorOffset;
            }
            else if(nPark<0)
            {// left
                fRet = (nodeSize.width * fScaleX/2) + fAnchorOffset;
            }
            else
            {// mid-x
                fRet = frameSize.width/2 + fAnchorOffset;
            }
        }
        else
        {// y
            const float fScaleY = pNode->getScaleY();
            // anchor offset by (0.5,0.5)
            float fAnchorOffset = (ptAnchor.y-0.5)*nodeSize.height*fScaleY;
            if(nPark>0)
            {// top
                fRet = (frameSize.height - nodeSize.height*fScaleY/2) + fAnchorOffset;
            }
            else if(nPark<0)
            {// bottom
                fRet = (nodeSize.height * fScaleY/2) + fAnchorOffset;
            }
            else
            {// mid-y
                fRet = frameSize.height/2 + fAnchorOffset;
            }
        }
        
        return fRet;
    }
    
    void SCNodeUtils::setNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(pNode!=NULL);
        
        auto ptrClick = SCNodeClickable::create(pNode,ptrBvr);
        auto pClick = SCPtr2Ref::create(ptrClick);
        pNode->setUserObject(pClick);
    }
    
    void SCNodeUtils::removeNodeClickable(cocos2d::Node* pNode)
    {
        SCASSERT(pNode!=NULL);
        
        SC_RETURN_V_IF(pNode->getUserObject()==NULL);
        SCPtr2Ref* pRef = dynamic_cast<SCPtr2Ref*>(pNode->getUserObject());
        SC_RETURN_V_IF(pRef==NULL || pRef->getPtr()==NULL);
        SC_RETURN_V_IF(pRef->getPtr().cast<SCNodeClickable::Ptr>()==NULL);
        
        pNode->setUserObject(NULL);
    }
}
