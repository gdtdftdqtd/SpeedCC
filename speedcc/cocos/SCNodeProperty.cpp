

#include "SCNodeProperty.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    // keep order, so that it can apply binary search
    // go to http://textmechanic.com/Sort-Text-Lines.html for sorting
    SCNodeProperty::SPropertyPair SCNodeProperty::s_PropertyPairArray[] =
    {
        {SC_NODE_PROPERTY_ANCHOR        ,VEC2_TYPE},
        {SC_NODE_PROPERTY_ANCHOR_ON     ,BOOL_TYPE},
        {SC_NODE_PROPERTY_COLOR         ,COLOR3_TYPE},
        {SC_NODE_PROPERTY_COLOR_TEXT    ,COLOR4_TYPE},
        {SC_NODE_PROPERTY_FLIP_X        ,BOOL_TYPE},
        {SC_NODE_PROPERTY_FLIP_Y        ,BOOL_TYPE},
        {SC_NODE_PROPERTY_FONT_NAME     ,STRING_TYPE},
        {SC_NODE_PROPERTY_FONT_SIZE     ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_IMAGE         ,STRING_TYPE},
        {SC_NODE_PROPERTY_LABEL         ,STRING_TYPE},
        {SC_NODE_PROPERTY_OPACITY       ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_ROTATION      ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_ROTATION_X    ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_ROTATION_Y    ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_SCALE         ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_SCALE_X       ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_SCALE_Y       ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_SKEW_X        ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_SKEW_Y        ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_TAG           ,INT_TYPE},
        {SC_NODE_PROPERTY_VISIBLE       ,BOOL_TYPE},
        {SC_NODE_PROPERTY_X             ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_XY            ,VEC2_TYPE},
        {SC_NODE_PROPERTY_Y             ,FLOAT_TYPE},
        {SC_NODE_PROPERTY_Z             ,INT_TYPE},
    };
    
    
    void SCNodeProperty::setProperty(Node* pNode,const SCDictionary& dic)
    {
        SCASSERT(pNode!=NULL);
        SC_RETURN_IF_V(pNode==NULL);
        
        int nValue;
        float fValue;
        bool bValue;
        Color3B crValue;
        Vec2 vec2;
        
        if(SCNodeProperty::getInt(dic,SC_NODE_PROPERTY_TAG,nValue))
        {
            pNode->setTag(nValue);
        }
        
        if(SCNodeProperty::getColor3(dic,SC_NODE_PROPERTY_COLOR, crValue))
        {
            pNode->setColor(crValue);
        }
        
        if(SCNodeProperty::getVec2(dic,SC_NODE_PROPERTY_XY,vec2))
        {
            auto pos = SCNodeUtils::posR2A(vec2,pNode->getContentSize());
            pNode->setPosition(pos);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_X,fValue))
        {
            auto pos = SCNodeUtils::posR2A(Vec2(fValue,0),pNode->getContentSize());
            pNode->setPositionX(pos.x);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_Y,fValue))
        {
            auto pos = SCNodeUtils::posR2A(Vec2(0,fValue),pNode->getContentSize());
            pNode->setPositionY(pos.y);
        }
        
        if(SCNodeProperty::getInt(dic,SC_NODE_PROPERTY_Z,nValue))
        {
            pNode->setLocalZOrder(nValue);
        }
        
        if(SCNodeProperty::getVec2(dic,SC_NODE_PROPERTY_ANCHOR,vec2))
        {
            pNode->setAnchorPoint(vec2);
        }
        
        if(SCNodeProperty::getBool(dic,SC_NODE_PROPERTY_ANCHOR_ON,bValue))
        {
            pNode->setIgnoreAnchorPointForPosition(bValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_SCALE,fValue))
        {
            pNode->setScale(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_SCALE_X,fValue))
        {
            pNode->setScaleX(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_SCALE_Y,fValue))
        {
            pNode->setScaleY(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_OPACITY,fValue))
        {
            pNode->setOpacity(fValue);
        }
        
        if(SCNodeProperty::getBool(dic,SC_NODE_PROPERTY_VISIBLE,bValue))
        {
            pNode->setVisible(bValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_ROTATION,fValue))
        {
            pNode->setRotation(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_ROTATION_X,fValue))
        {
            pNode->setRotationSkewX(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_ROTATION_Y,fValue))
        {
            pNode->setRotationSkewY(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_SKEW_X,fValue))
        {
            pNode->setSkewX(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_SKEW_Y,fValue))
        {
            pNode->setSkewY(fValue);
        }
    }
    
    void SCNodeProperty::setProperty(Layer* pNode,const SCDictionary& dic)
    {
        SCASSERT(pNode!=NULL);
        SC_RETURN_IF_V(pNode==NULL);
        
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setProperty(Sprite* pNode,const SCDictionary& dic)
    {
        float fValue;
        SCString strValue;
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_FLIP_X,fValue))
        {
            pNode->setFlippedX(fValue);
        }
        
        if(SCNodeProperty::getFloat(dic,SC_NODE_PROPERTY_FLIP_Y,fValue))
        {
            pNode->setFlippedY(fValue);
        }
        
        if(SCNodeProperty::getString(dic, SC_NODE_PROPERTY_IMAGE, strValue))
        {
            auto pSprite = Sprite::create(strValue.c_str());
            pNode->setSpriteFrame(pSprite->getSpriteFrame());
        }
        
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setProperty(LayerColor* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setProperty(Menu* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setProperty(MenuItem* pNode,const SCDictionary& dic)
    {
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    void SCNodeProperty::setProperty(Label* pNode,const SCDictionary& dic)
    {
        SCString strValue;
        Color4B crValue;
        float fValue;
        
        if(SCNodeProperty::getString(dic, SC_NODE_PROPERTY_LABEL, strValue))
        {
            pNode->setString(strValue.c_str());
        }
        
        if(SCNodeProperty::getColor4(dic,SC_NODE_PROPERTY_COLOR_TEXT, crValue))
        {
            pNode->setTextColor(crValue);
        }
        
        if(SCNodeProperty::getString(dic, SC_NODE_PROPERTY_FONT_NAME, strValue))
        {
            pNode->setSystemFontName(strValue.c_str());
        }
        
        if(SCNodeProperty::getFloat(dic, SC_NODE_PROPERTY_FONT_SIZE, fValue))
        {
            pNode->setSystemFontSize(fValue);
        }
        
        SCNodeProperty::setProperty(dynamic_cast<Node*>(pNode),dic);
    }
    
    bool SCNodeProperty::convertString2Dic(const SCString& strProerty,SCDictionary& dic)
    {
        dic.removeAllKeys();
        SC_RETURN_IF(strProerty.isEmpty(), true);
        
        bool bRet = true;
        
        auto pCurrent = (char*)strProerty.c_str();
        auto pEnd = pCurrent + strProerty.getLength();
        
        SCString strKey;
        SCString strValue;
        SCValue data;
        
        while(pCurrent != pEnd)
        {
            do
            {
                if(!SCNodeProperty::readKey(strKey,pCurrent,pEnd))
                {
                    SCLog("property: ========== No.%d key read failed in '%s' ==========",n,strProerty.c_str());
                    SCASSERT(false);
                    SCNodeProperty::nextSemicolon(pCurrent,pEnd);
                    bRet = false;
                    break;
                }
                strKey.makeLower();
                
                auto keyType = SCNodeProperty::getKeyType(strKey);
                
                if(keyType==UNKNOWN_TYPE)
                {
                    SCLog("property: ========== No.%d key parse failed in '%s' ========== ",n,strProerty.c_str());
                    SCASSERT(false);
                    SCNodeProperty::nextSemicolon(pCurrent,pEnd);
                    bRet = false;
                    break;
                }
                
                if(!SCNodeProperty::readValue(strValue,keyType,pCurrent,pEnd))
                {
                    SCLog("property: ========== No.%d value read failed in '%s' ========== ",n,strProerty.c_str());
                    SCASSERT(false);
                    SCNodeProperty::nextSemicolon(pCurrent,pEnd);
                    bRet = false;
                    break;
                }
                
                if(!SCNodeProperty::parseValue(keyType,strValue,data))
                {
                    SCLog("property: ========== No.%d value parse failed in '%s' ========== ",n,strProerty.c_str());
                    SCASSERT(false);
                    SCNodeProperty::nextSemicolon(pCurrent,pEnd);
                    bRet = false;
                    break;
                }
                
                dic.setValue(strKey, data);
                SCNodeProperty::skipSpaces(pCurrent,pEnd);
            }
            while(0);
        }
        
        return bRet;
    }
    
    SCNodeProperty::EValueType SCNodeProperty::getKeyType(SCString& strKey)
    {
        SPropertyPair pair = {strKey,UNKNOWN_TYPE};
        auto it = std::lower_bound(s_PropertyPairArray,s_PropertyPairArray+SC_ARRAY_LENGTH(s_PropertyPairArray),pair);
        if(it!=s_PropertyPairArray+SC_ARRAY_LENGTH(s_PropertyPairArray) && strKey==(*it).pszKey)
        {
            return (*it).type;
        }
        return UNKNOWN_TYPE;
    }
    
    bool SCNodeProperty::readKey(SCString& strKey,char*& pCurrent, char*& pEnd)
    {
        bool bRet = false;
        
        SCNodeProperty::skipSpaces(pCurrent,pEnd);
        
        char* pBegin = pCurrent;
        
        do
        {
            SC_BREAK_IF(pCurrent==pEnd);
            SC_BREAK_IF(!SCNodeProperty::isValidKeyChar(*pCurrent));
            ++pCurrent;
        }
        while(1);
        
        char* pEnd2 = pCurrent;
        SCNodeProperty::skipSpaces(pCurrent,pEnd);
        
        if(pEnd2>pBegin && *pCurrent=='=' && pCurrent!=pEnd)
        {
            char szBuf[64+1] = {0};
            
            if(pEnd2-pBegin<sizeof(szBuf))
            {
                memcpy(szBuf,pBegin,pEnd2-pBegin);
                strKey = szBuf;
                strKey.makeLower();
                bRet = true;
            }
        }
        
        if(pEnd>pCurrent)
        {
            ++pCurrent; // skip '=' or invalide char
        }
        
        return bRet;
    }
    
    bool SCNodeProperty::readValue(SCString& strValue,const EValueType type,char*& pCurrent, char*& pEnd)
    {
        bool bRet = false;
        
        SCNodeProperty::skipSpaces(pCurrent,pEnd);
        
        char* pBegin = pCurrent;
        
        if(type==STRING_TYPE)
        {
            const char cQuote = '\'';
            int nQuoteStack = 0;
            char* pBeginQuote = NULL;
            char* pEndQuote = NULL;
            
            do
            {
                SC_BREAK_IF(pCurrent==pEnd);
                if(nQuoteStack>1)
                {
                    SC_BREAK_IF(*pCurrent==';');
                }
                
                if(nQuoteStack==0 && *pCurrent==cQuote)
                {// enter quote
                    nQuoteStack = 1;
                    pBeginQuote = pCurrent;
                }
                else if(nQuoteStack==1 && *pCurrent==cQuote && pEnd>pCurrent && *(pCurrent+1)!=cQuote)
                {// leave quote
                    nQuoteStack = 2;
                    pEndQuote = pCurrent;
                }
                
                ++pCurrent;
            }
            while(1);
            
            char szBuf[64+1] = {0};
            
            if(pBeginQuote!=NULL && pEndQuote-pBeginQuote<sizeof(szBuf))
            {
                memcpy(szBuf,pBeginQuote+1,pEndQuote-pBeginQuote-1);
                strValue = szBuf;
                while(!strValue.isEmpty() && strValue.find("''")>=0)
                {
                    strValue.replace("''", "'");
                }
                bRet = true;
            }
            
            while(pEnd>pBegin && *pCurrent==';')
            {
                ++pCurrent; // skip ';'
            }
        }
        else
        {
            do
            {
                SC_BREAK_IF(pCurrent==pEnd);
                SC_BREAK_IF(*pCurrent==';');
                ++pCurrent;
            }
            while(1);
            
            char* pEnd2 = pCurrent;
            SCNodeProperty::skipSpaces(pCurrent,pEnd);
            
            if(pEnd2>pBegin && *pCurrent==';')
            {
                ++pCurrent; // skip ';'
                char szBuf[64+1] = {0};
                
                while(*(pEnd2-1)==' ' && pEnd2>pBegin)
                {--pEnd2;}
                
                if(pEnd2-pBegin<sizeof(szBuf))
                {
                    memcpy(szBuf,pBegin,pEnd2-pBegin);
                    strValue = szBuf;
                    bRet = true;
                }
            }
        }
        
        return bRet;
    }
    
    void SCNodeProperty::skipSpaces(char*& pCurrent, char*& pEnd)
    {
        do
        {
            SC_BREAK_IF(pCurrent==pEnd);
            const char& c = *pCurrent;
            SC_BREAK_IF(c!=' ' && c!='\t' && c!='\r' && c!='\n');
            
            ++pCurrent;
        }
        while(1);
    }
    
    void SCNodeProperty::nextSemicolon(char*& pCurrent, char*& pEnd)
    {
        do
        {
            CC_BREAK_IF(pCurrent==pEnd);
            CC_BREAK_IF(*pCurrent==';');
            ++pCurrent;
        }
        while(1);
    }
    
    bool SCNodeProperty::parseValue(const EValueType type,const SCString& strValue,SCValue& value)
    {
        bool bRet = false;
        
        try
        {
            switch(type)
            {
                case UNKNOWN_TYPE: break;
                    
                case FLOAT_TYPE:
                    value.setFloat(strValue.asFloat());
                    bRet = true;
                    break;
                    
                case INT_TYPE:
                    value.setInt(strValue.asInt());
                    bRet = true;
                    break;
                case STRING_TYPE:
                    value.setString(strValue);
                    bRet = true;
                    break;
                case BOOL_TYPE:
                    value.setBool(strValue.asBool());
                    bRet = true;
                    break;
                case VEC2_TYPE:
                {
                    Vec2 vec;
                    if(SCNodeProperty::parseVec2(strValue,vec))
                    {
                        value.setObject(vec);
                        bRet = true;
                    }
                }
                    break;
                    
                case COLOR3_TYPE:
                {
                    Color4B cr;
                    if(SCNodeProperty::parseColor4(strValue,cr))
                    {
                        value.setObject(Color3B(cr));
                        bRet = true;
                    }
                }
                    break;
                    
                case COLOR4_TYPE:
                {
                    Color4B cr;
                    if(SCNodeProperty::parseColor4(strValue,cr))
                    {
                        value.setObject(cr);
                        bRet = true;
                    }
                }
                    break;
            }
            
        }catch(...){}
        
        return bRet;
    }
    
    SCDictionary SCNodeProperty::getProperty(Node* pNode)
    {
        SCDictionary retDic;
        
        
        return retDic;
    }
    
    /////-------------------
    bool SCNodeProperty::isValidKeyChar(const char& c)
    {
        return ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='-' || c=='_');
    }
    
    bool SCNodeProperty::getInt(const SCDictionary& dic,const SCString& strKey,int& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        const auto value = dic.getValue(strKey);
        SC_RETURN_IF(value.getType()!=SCValue::INT_TYPE, false);
        val = value.getInt();
        return true;
    }
    
    bool SCNodeProperty::getBool(const SCDictionary& dic,const SCString& strKey,bool& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        const auto value = dic.getValue(strKey);
        SC_RETURN_IF(value.getType()!=SCValue::BOOL_TYPE, false);
        val = value.getBool();
        return true;
    }
    
    bool SCNodeProperty::getFloat(const SCDictionary& dic,const SCString& strKey,float& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        const auto value = dic.getValue(strKey);
        SC_RETURN_IF(value.getType()!=SCValue::FLOAT_TYPE, false);
        val = value.getFloat();
        return true;
    }
    
    bool SCNodeProperty::getVec2(const SCDictionary& dic,const SCString& strKey,Vec2& vec)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        auto value = dic.getValue(strKey);
        
        if(value.getType()==SCValue::OBJECT_TYPE && value.isValidObject<Vec2>())
        {
            vec = value.getObject<Vec2>();
            return true;
        }

        return false;
    }
    
    bool SCNodeProperty::getString(const SCDictionary& dic,const SCString& strKey,SCString& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        const auto value = dic.getValue(strKey);
        SC_RETURN_IF(value.getType()!=SCValue::STRING_TYPE, false);
        val = value.getString();
        return true;
    }
    
    bool SCNodeProperty::getColorByName(const SCString& strKey,Color3B& val)
    {
        struct STemStruct
        {
            const char*     pszName;
            Color3B         crValue;
            
            inline bool operator>(const STemStruct& pair) const
            {
                return (strcmp(pair.pszName,pszName)<0);
            }
            
            inline bool operator<(const STemStruct& pair) const
            {
                return (strcmp(pair.pszName,pszName)>0);
            }
        };
        
        const STemStruct colorTableArray[] =
        {
            {"black",Color3B(0,0,0)},
            {"blue",Color3B(0,0,255)},
            {"gray",Color3B(166,166,166)},
            {"green",Color3B(0,255,0)},
            {"magenta",Color3B(255,0,255)},
            {"orange",Color3B(255,127,0)},
            {"red",Color3B(255,0,0)},
            {"white",Color3B(255,255,255)},
            {"yellow",Color3B(255,255,0)}
        };
        
        STemStruct pair = {strKey,Color3B(0,0,0)};
        bool bRet = false;
        auto it = std::lower_bound(colorTableArray,colorTableArray+SC_ARRAY_LENGTH(colorTableArray),pair);
        if(it!=colorTableArray+SC_ARRAY_LENGTH(colorTableArray) && strKey==(*it).pszName)
        {
            val = (*it).crValue;
            bRet = true;
        }
        return bRet;
    }
    
    bool SCNodeProperty::getColorByName(const SCString& strKey,Color4B& val)
    {
        Color3B cr;
        if(getColorByName(strKey,cr))
        {
            val.set(cr.r, cr.g, cr.b, 255);
            return true;
        }
        
        return false;
    }
    
    bool SCNodeProperty::getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val)
    {
        SC_RETURN_IF(!dic.hasKey(strKey), false);
        
        bool bRet = false;
        auto value = dic.getValue(strKey);
        if(value.getType()==SCValue::OBJECT_TYPE)
        {
            if(value.isValidObject<Color3B>())
            {
                val = Color4B(value.getObject<Color3B>());
                bRet = true;
            }
            else if(value.isValidObject<Color4B>())
            {
                val = value.getObject<Color4B>();
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    bool SCNodeProperty::getColor3(const SCDictionary& dic,const SCString& strKey,Color3B& val)
    {
        Color4B cr;
        SC_RETURN_IF(!SCNodeProperty::getColor4(dic,strKey,cr),false);
        val = Color3B(cr);
        return true;
    }
    
    ///----------- parse
    
    bool SCNodeProperty::parseVec2(SCString strValue,cocos2d::Vec2& vec2)
    {
        bool bRet = false;
        if(strValue.getLength()>5 &&
           ((strValue[0]=='(' && strValue[strValue.getLength()-1]==')') || (strValue[0]=='{' && strValue[strValue.getLength()-1]=='}')))
        {// {?,?} or (?,?)
            strValue.trimLeft('(');
            strValue.trimLeft('{');
            strValue.trimRight(')');
            strValue.trimRight('}');
            
            auto sl = strValue.split(",");
            
            if(sl.size()==2)
            {
                try
                {
                    vec2.x = sl[0].asFloat();
                    vec2.y = sl[1].asFloat();
                    bRet = true;
                }
                catch(...){}
            }
        }
        
        return bRet;
    }
    
    bool SCNodeProperty::parseColor4(SCString strValue,Color4B& val)
    {
        SC_RETURN_IF(strValue.isEmpty(), false);
        
        bool bRet = false;
        
        SC_RETURN_IF(SCNodeProperty::getColorByName(strValue,val), true);
        
        if(strValue.getLength()>1 && strValue.getLength()<=9 && strValue[0]=='#')
        {// #??????
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
        else if(strValue.getLength()>2 && strValue.getLength()<=10 && strValue[0]=='0' && strValue[1]=='x')
        {// 0x????????
            char* p = NULL;
            uint32_t uv=0;
            uv=(uint32_t)std::strtoul(strValue.c_str(), &p, 16);
            
            val.b = (uv&0x000000ff);
            val.g = ((uv&0x0000ff00)>>8);
            val.r = ((uv&0x00ff0000)>>16);
            val.a = ((uv&0xff000000)>>24);
            bRet = true;
        }else if(strValue.getLength()>6 &&
                 ((strValue[0]=='(' && strValue[strValue.getLength()-1]==')') || (strValue[0]=='{' && strValue[strValue.getLength()-1]=='}')))
        {// {?,?,?,?} or (?,?,?,?)
            strValue.trimLeft('(');
            strValue.trimLeft('{');
            strValue.trimRight(')');
            strValue.trimRight('}');
            
            auto sl = strValue.split(",");
            
            if(sl.size()>=3)
            {
                try
                {
                    val.r = sl[0].asInt();
                    val.g = sl[1].asInt();
                    val.b = sl[2].asInt();
                    val.a = (sl.size()==4) ? sl[3].asInt() : 255;
                    bRet = true;
                }
                catch(...){}
            }
        }
        
        return bRet;
    }
    
}

