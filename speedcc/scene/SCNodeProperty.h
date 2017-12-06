

#ifndef __SPEEDCC__SCNODEPROPERTY_H__
#define __SPEEDCC__SCNODEPROPERTY_H__

#include "cocos2d.h"
#include "../base/SCDictionary.h"

namespace SpeedCC
{

#define SC_NODE_PROPERTY_TAG                "tag"           // int
#define SC_NODE_PROPERTY_POSITION           "xy"            // [float,float]
#define SC_NODE_PROPERTY_POSITION_X         "x"             // float
#define SC_NODE_PROPERTY_POSITION_Y         "y"             // float
#define SC_NODE_PROPERTY_POSITION_Z         "z"             // int
#define SC_NODE_PROPERTY_ANCHOR             "anchor"        // [float,float]
#define SC_NODE_PROPERTY_ANCHOR_ON          "anchor-on"     // bool
#define SC_NODE_PROPERTY_SCALE              "scale"         // float
#define SC_NODE_PROPERTY_SCALE_X            "scale-x"       // float
#define SC_NODE_PROPERTY_SCALE_Y            "scale-y"       // float
#define SC_NODE_PROPERTY_OPACITY            "opacity"       // float
#define SC_NODE_PROPERTY_VISIBLE            "visible"       // bool
#define SC_NODE_PROPERTY_ROTATION           "rotation"      // float
#define SC_NODE_PROPERTY_ROTATION_X         "rotation-x"    // float
#define SC_NODE_PROPERTY_ROTATION_Y         "rotation-y"    // float
#define SC_NODE_PROPERTY_SKEW_X             "skew-x"        // float
#define SC_NODE_PROPERTY_SKEW_Y             "skew-y"        // float
#define SC_NODE_PROPERTY_COLOR              "color"         // Color3B

#define SC_NODE_PROPERTY_FLIP_X             "flip-x"        // bool
#define SC_NODE_PROPERTY_FLIP_Y             "flip-y"        // bool
#define SC_NODE_PROPERTY_LABEL              "label"         // string
#define SC_NODE_PROPERTY_FONT_SIZE          "font-size"     // float
#define SC_NODE_PROPERTY_FONT_NAME          "font-name"     // string
#define SC_NODE_PROPERTY_COLOR_TEXT         "color-text"    // Color4B
#define SC_NODE_PROPERTY_IMAGE              "image"         // string
    
    class SCNodeProperty
    {
    public:
        static void setNodeProperty(cocos2d::Node* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::Layer* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::Sprite* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::LayerColor* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::Menu* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::MenuItem* pNode,const SCDictionary& dic);
        static void setNodeProperty(cocos2d::Label* pNode,const SCDictionary& dic);
    };
}

#endif // __SPEEDCC__SCNODEPROPERTY_H__
