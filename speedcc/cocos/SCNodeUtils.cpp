

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
    
    bool SCNodeUtils::setPositionPer(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer)
    {
        SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,false);
        
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
        SC_RETURN_V_IF(pNode==nullptr);
        
        auto pos = pNode->getPosition();
        pos.x += fXBy;
        pos.y += fYBy;
        pNode->setPosition(pos);
    }
    
    cocos2d::Vec2 SCNodeUtils::getDockPosition(cocos2d::Node* pNode,const int nDockFlag)
    {
        SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,cocos2d::Vec2::ZERO);
        
        auto ptPos = pNode->getPosition();
        
        if(SC_BIT_HAS_OR(nDockFlag, kDockLeft|kDockRight|kDockMiddleX))
        {// x axis
            if(SC_BIT_HAS_AND(nDockFlag,kDockMiddleX))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,0,true);
            }
            else if(SC_BIT_HAS_AND(nDockFlag,kDockLeft))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,-1,true);
            }
            else if(SC_BIT_HAS_AND(nDockFlag,kDockRight))
            {
                ptPos.x = SCNodeUtils::getDockPosition(pNode,1,true);
            }
        }
        
        if(SC_BIT_HAS_OR(nDockFlag, kDockTop|kDockBottom|kDockMiddleY))
        {// y axis
            if(SC_BIT_HAS_AND(nDockFlag,kDockMiddleY))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,0,false);
            }
            else if(SC_BIT_HAS_AND(nDockFlag,kDockTop))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,1,false);
            }
            else if(SC_BIT_HAS_AND(nDockFlag,kDockBottom))
            {
                ptPos.y = SCNodeUtils::getDockPosition(pNode,-1,false);
            }
        }
        
        return ptPos;
    }
    
    bool SCNodeUtils::setDock(cocos2d::Node* pNode,const int nDockFlag)
    {
        SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,false);
        auto ptPos = SCNodeUtils::getDockPosition(pNode,nDockFlag);
        pNode->setPosition(ptPos);
        
        return true;
    }
    
    float SCNodeUtils::getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX)
    {
        SC_RETURN_IF(pNode==nullptr || pNode->getParent()==nullptr,-999);
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
    
    void SCNodeUtils::addClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(pNode!=nullptr);
        
        auto ptrClick = SCNodeUtils::getUserObj<SCNodeClickable::Ptr>(pNode);
        
        if(ptrClick==nullptr)
        {
            ptrClick = SCNodeClickable::create(pNode,ptrBvr);
            SCNodeUtils::addUserObj(pNode, ptrClick);
        }
        else
        {
            ptrClick->setBehavior(ptrBvr);
        }
    }
    
    void SCNodeUtils::removeClickable(cocos2d::Node* pNode)
    {
        SCASSERT(pNode!=nullptr);
        SCNodeUtils::removeUserObj<SCNodeClickable::Ptr>(pNode);
    }
    
    SCRefHolder* SCNodeUtils::getUserHolder(cocos2d::Node* pNode,const bool bCreate)
    {
        SC_RETURN_IF(pNode==nullptr,nullptr);
        auto pUserObj = pNode->getUserObject();
        SC_RETURN_IF(pUserObj==nullptr && !bCreate,nullptr);
        
        SCRefHolder* pHolder = nullptr;
        
        if(pUserObj==nullptr)
        {
            pHolder = SCRefHolder::create();
        }
        else
        {
            pHolder = dynamic_cast<SCRefHolder*>(pUserObj);
            
            if(pHolder==nullptr)
            {
                pHolder = SCRefHolder::create();
                pHolder->addObj(pUserObj);
            }
        }
        
        pNode->setUserObject(pHolder);
        return pHolder;
    }
    
    void SCNodeUtils::addUserObj(cocos2d::Node* pNode,cocos2d::Ref* pRef)
    {
        SC_RETURN_V_IF(pNode==nullptr || pRef==nullptr);
        
        auto pHolder = SCNodeUtils::getUserHolder(pNode,true);
        pHolder->addObj(pRef);
    }
    
    void SCNodeUtils::addUserObj(cocos2d::Node* pNode,SCObject::Ptr ptrObj)
    {
        SC_RETURN_V_IF(pNode==nullptr || ptrObj==nullptr);
        
        auto pHolder = SCNodeUtils::getUserHolder(pNode,true);
        pHolder->addObj(ptrObj);
    }
    
    cocos2d::Sprite* SCNodeUtils::createSprite(const SCString& strName)
    {
        // find in sprite frame cache
        auto pSpriteFrame = SCCCSpriteFrameCache()->getSpriteFrameByName(strName.c_str());
        SC_RETURN_IF(pSpriteFrame!=nullptr, cocos2d::Sprite::createWithSpriteFrame(pSpriteFrame));
        
        // find in file
        auto strFile = SCCCFileUtils()->fullPathForFilename(strName.c_str());
        SC_RETURN_IF(!strFile.empty(), cocos2d::Sprite::create(strFile.c_str()));
        
        CCLOG("Can't Found Match Name: %s",strName.c_str());
        SCASSERT(false);
        return nullptr;
    }
}
