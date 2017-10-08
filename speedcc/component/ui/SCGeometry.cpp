

#include "SCGeometry.h"

namespace SpeedCC
{
    void SCGeometry::setRotation(const float rotation)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setRotation(rotation);
    }
    
    float SCGeometry::getRotation() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getRotation();
    }
    
    void SCGeometry::setRotationSkewX(float rotationX)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setRotationSkewX(rotationX);
    }
    
    float SCGeometry::getRotationSkewX() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getRotationSkewX();
    }
    
    void SCGeometry::setRotationSkewY(float rotationY)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setRotationSkewY(rotationY);
    }
    
    float SCGeometry::getRotationSkewY() const
    {
        SCASSERT(_pNode!=NULL);
        _pNode->getRotationSkewY();
    }
    
    void SCGeometry::setVisible(bool visible)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setVisible(visible);
    }
    
    bool SCGeometry::isVisible() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->isVisible();
    }
    
    void SCGeometry::setScaleX(float scaleX)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setScaleX(scaleX);
    }
    
    float SCGeometry::getScaleX() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getScaleX();
    }
    
    void SCGeometry::setScaleY(float scaleY)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setScaleY(scaleY);
    }
    
    float SCGeometry::getScaleY() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getScaleY();
    }
    
    void SCGeometry::setScale(float scale)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setScale(scale);
    }
    
    float SCGeometry::getScale() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getScale();
    }
    
    void SCGeometry::setPosition(const cocos2d::Vec2 &position)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setPosition(position);
    }
    
    const cocos2d::Vec2& SCGeometry::getPosition() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getPosition();
    }
    
    void SCGeometry::setPositionZ(float positionZ)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setPositionZ(positionZ);
    }
    
    float SCGeometry::getPositionZ() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getPositionZ();
    }
    
    void SCGeometry::setSkewX(float skewX)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setSkewX(skewX);
    }
    
    float SCGeometry::getSkewX() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getSkewX();
    }
    
    void SCGeometry::setSkewY(float skewY)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setSkewY(skewY);
    }
    
    float SCGeometry::getSkewY() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getSkewY();
    }
    
    void SCGeometry::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->setAnchorPoint(anchorPoint);
    }
    
    const cocos2d::Vec2& SCGeometry::getAnchorPoint() const
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getAnchorPoint();
    }
}

