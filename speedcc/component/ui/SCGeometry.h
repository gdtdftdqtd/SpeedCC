

#ifndef __SPEEDCC__SCGEOMETRY_H__
#define __SPEEDCC__SCGEOMETRY_H__

#include "../SCComponent.h"
#include "cocos2d.h"

namespace SpeedCC
{
    class SCGeometry : public SCComponent
    {
    private:
        SC_AVOID_CLASS_COPY(SCGeometry);
        SCGeometry():
        _pNode(NULL)
        {}
        
    public:
        SC_DEFINE_CLASS_PTR(SCGeometry);
        
        void setRotation(const float rotation);
        float getRotation() const;
        void setRotationSkewX(float rotationX);
        float getRotationSkewX() const;
        void setRotationSkewY(float rotationY);
        float getRotationSkewY() const;
        void setVisible(bool visible);
        bool isVisible() const;
        void setScaleX(float scaleX);
        float getScaleX() const;
        void setScaleY(float scaleY);
        float getScaleY() const;
        void setScale(float scale);
        float getScale() const;
        void setPosition(const cocos2d::Vec2 &position);
        const cocos2d::Vec2& getPosition() const;
        void setPositionZ(float positionZ);
        float getPositionZ() const;
        void setSkewX(float skewX);
        float getSkewX() const;
        void setSkewY(float skewY);
        float getSkewY() const;
        void setAnchorPoint(const cocos2d::Vec2& anchorPoint);
        const cocos2d::Vec2& getAnchorPoint() const;
        
    private:
        cocos2d::Node*    _pNode;
    };
}

#endif // __SPEEDCC__SCGEOMETRY_H__
