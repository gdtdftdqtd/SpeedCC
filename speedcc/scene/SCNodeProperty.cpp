

#include "SCNodeProperty.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    bool getColor3(const SCDictionary& dic,const SCString& strKey,cocos2d::Color3B& val);
    bool getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val);
    bool getString(const SCDictionary& dic,const SCString& strKey,SCString& val);
    bool getFloat(const SCDictionary& dic,const SCString& strKey,float& val);
    bool getInt(const SCDictionary& dic,const SCString& strKey,int& val);
    bool getBool(const SCDictionary& dic,const SCString& strKey,bool& val);
    bool getArrayFloat(const SCDictionary& dic,const SCString& strKey,std::vector<float>& array);
    
    
    void SCNodeProperty::setNodeProperty(cocos2d::Node* pNode,const SCDictionary& dic)
    {
        SCASSERT(pNode!=NULL);
        SC_RETURN_IF_V(pNode==NULL);
        
        int nValue;
        float fValue;
        bool bValue;
        Color3B crValue;
        std::vector<float> fValueVtr;
        
        if(getInt(dic,SC_NODE_PROPERTY_TAG,nValue))
        {
            pNode->setTag(nValue);
        }
        
        if(getColor3(dic,SC_NODE_PROPERTY_COLOR, crValue))
        {
            pNode->setColor(crValue);
        }
        
        if(getArrayFloat(dic,SC_NODE_PROPERTY_POSITION,fValueVtr) && fValueVtr.size()==2)
        {
            auto pos = SCNodeUtils::posR2A(Vec2(fValueVtr[0],fValueVtr[1]),pNode->getContentSize());
            pNode->setPosition(pos);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_POSITION_X,fValue))
        {
            auto pos = SCNodeUtils::posR2A(Vec2(fValue,0),pNode->getContentSize());
            pNode->setPositionX(pos.x);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_POSITION_Y,fValue))
        {
            auto pos = SCNodeUtils::posR2A(Vec2(0,fValue),pNode->getContentSize());
            pNode->setPositionY(pos.y);
        }
        
        if(getInt(dic,SC_NODE_PROPERTY_POSITION_Z,nValue))
        {
            pNode->setLocalZOrder(nValue);
        }
        
        if(getArrayFloat(dic,SC_NODE_PROPERTY_ANCHOR,fValueVtr) && fValueVtr.size()==2)
        {
            pNode->setAnchorPoint(Vec2(fValueVtr[0],fValueVtr[1]));
        }
        
        if(getBool(dic,SC_NODE_PROPERTY_ANCHOR_ON,bValue))
        {
            pNode->setIgnoreAnchorPointForPosition(bValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_SCALE,fValue))
        {
            pNode->setScale(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_SCALE_X,fValue))
        {
            pNode->setScaleX(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_SCALE_Y,fValue))
        {
            pNode->setScaleY(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_OPACITY,fValue))
        {
            pNode->setOpacity(fValue);
        }
        
        if(getBool(dic,SC_NODE_PROPERTY_VISIBLE,bValue))
        {
            pNode->setVisible(bValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_ROTATION,fValue))
        {
            pNode->setRotation(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_ROTATION_X,fValue))
        {
            pNode->setRotationSkewX(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_ROTATION_Y,fValue))
        {
            pNode->setRotationSkewY(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_SKEW_X,fValue))
        {
            pNode->setSkewX(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_SKEW_Y,fValue))
        {
            pNode->setSkewY(fValue);
        }
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::Layer* pNode,const SCDictionary& dic)
    {
        SCASSERT(pNode!=NULL);
        SC_RETURN_IF_V(pNode==NULL);
        
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::Sprite* pNode,const SCDictionary& dic)
    {
        float fValue;
        SCString strValue;
        
        if(getFloat(dic,SC_NODE_PROPERTY_FLIP_X,fValue))
        {
            pNode->setFlippedX(fValue);
        }
        
        if(getFloat(dic,SC_NODE_PROPERTY_FLIP_Y,fValue))
        {
            pNode->setFlippedY(fValue);
        }
        
        if(getString(dic, SC_NODE_PROPERTY_IMAGE, strValue))
        {
            auto pSprite = Sprite::create(strValue.c_str());
            pNode->setSpriteFrame(pSprite->getSpriteFrame());
        }
        
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::LayerColor* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::Menu* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::MenuItem* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setNodeProperty(cocos2d::Label* pNode,const SCDictionary& dic)
    {
        SCString strValue;
        Color4B crValue;
        float fValue;
        
        if(getString(dic, SC_NODE_PROPERTY_LABEL, strValue))
        {
            pNode->setString(strValue.c_str());
        }
        
        if(getColor4(dic,SC_NODE_PROPERTY_COLOR_TEXT, crValue))
        {
            pNode->setTextColor(crValue);
        }
        
        if(getString(dic, SC_NODE_PROPERTY_FONT_NAME, strValue))
        {
            pNode->setSystemFontName(strValue.c_str());
        }
        
        if(getFloat(dic, SC_NODE_PROPERTY_FONT_SIZE, fValue))
        {
            pNode->setSystemFontSize(fValue);
        }
        
        SCNodeProperty::setNodeProperty(dynamic_cast<cocos2d::Node*>(pNode),dic);
    }
    
    
    /////-------------------
    bool getInt(const SCDictionary& dic,const SCString& strKey,int& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        val = dic.getValue(strKey).getInt();
        return true;
    }
    
    bool getBool(const SCDictionary& dic,const SCString& strKey,bool& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        val = dic.getValue(strKey).getBool();
        return true;
    }
    
    bool getFloat(const SCDictionary& dic,const SCString& strKey,float& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        val = dic.getValue(strKey).getFloat();
        return true;
    }
    
    bool getArrayFloat(const SCDictionary& dic,const SCString& strKey,std::vector<float>& array)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        auto value = dic.getValue(strKey);
        SC_RETURN_IF(value.getType()!=SCValue::ARRAY_TYPE, false);
        
        auto vArray = value.getArray();
        array.resize(vArray.size());
        int i = 0;
        for(const auto& it : vArray)
        {
            array[i] = it.getFloat();
            ++i;
        }
        
        return true;
    }
    
    bool getString(const SCDictionary& dic,const SCString& strKey,SCString& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        val = dic.getValue(strKey).getString();
        return true;
    }
    
    bool getColor3(const SCDictionary& dic,const SCString& strKey,cocos2d::Color3B& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        
        bool bRet = false;
        auto value = dic.getValue(strKey);
        
        if(value.getType()==SCValue::ARRAY_TYPE)
        {
            auto array = value.getArray();
            if(array.size()==3)
            {
                val.r = array[0].getInt();
                val.g = array[1].getInt();
                val.b = array[2].getInt();
                bRet = true;
            }
        }
        else
        {
            auto strValue = value.getString();
            if((strValue.getLength()==7 || strValue.getLength()==9) && strValue[0]=='#')
            {
                strValue.format("0x%s",strValue.c_str()+1);
                
                char* p = NULL;
                uint32_t uv=0;
                uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
                
                val.b = (uv&0x000000ff);
                val.g = ((uv&0x0000ff00)>>8);
                val.r = ((uv&0x00ff0000)>>16);
                bRet = true;
            }
            else if(strValue.getLength()==8 && strValue[0]=='0' && strValue[0]=='x')
            {
                char *p;
                uint32_t uv=0;
                uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
                
                val.r = (uv&0x000000ff);
                val.g = ((uv&0x0000ff00)>>8);
                val.b = ((uv&0x00ff0000)>>16);
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    bool getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        
        bool bRet = false;
        auto value = dic.getValue(strKey);
        
        if(value.getType()==SCValue::ARRAY_TYPE)
        {
            auto array = value.getArray();
            if(array.size()==4)
            {
                val.r = array[0].getInt();
                val.g = array[1].getInt();
                val.b = array[2].getInt();
                val.a = array[3].getInt();
                bRet = true;
            }
        }
        else
        {
            auto strValue = value.getString();
            if((strValue.getLength()==7 || strValue.getLength()==9) && strValue[0]=='#')
            {
                strValue.format("0x%s",strValue.c_str()+1);
                
                char* p = NULL;
                uint32_t uv=0;
                uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
                
                val.b = (uv&0x000000ff);
                val.g = ((uv&0x0000ff00)>>8);
                val.r = ((uv&0x00ff0000)>>16);
                val.a = ((uv&0xff000000)>>24);
                bRet = true;
            }
            else if(strValue.getLength()==8 && strValue[0]=='0' && strValue[0]=='x')
            {
                char* p = NULL;
                uint32_t uv=0;
                uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
                
                val.r = (uv&0x000000ff);
                val.g = ((uv&0x0000ff00)>>8);
                val.b = ((uv&0x00ff0000)>>16);
                val.a = ((uv&0xff000000)>>24);
                bRet = true;
            }
        }
        
        return bRet;
    }
}

