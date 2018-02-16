

#ifndef __SPEEDCC__SCNODEPROPERTY_H__
#define __SPEEDCC__SCNODEPROPERTY_H__

#include "cocos2d.h"
#include "../base/SCDictionary.h"

namespace SpeedCC
{
// for better search algorithm, must keep macro name match string value
#define SC_NODE_STYLE_TAG                "tag"           // int
#define SC_NODE_STYLE_XY                 "xy"            // Vec2
#define SC_NODE_STYLE_X                  "x"             // float
#define SC_NODE_STYLE_Y                  "y"             // float
#define SC_NODE_STYLE_Z                  "z"             // int
#define SC_NODE_STYLE_ANCHOR             "anchor"        // Vec2
#define SC_NODE_STYLE_ANCHOR_ON          "anchor-on"     // bool
#define SC_NODE_STYLE_SCALE              "scale"         // float
#define SC_NODE_STYLE_SCALE_X            "scale-x"       // float
#define SC_NODE_STYLE_SCALE_Y            "scale-y"       // float
#define SC_NODE_STYLE_OPACITY            "opacity"       // float
#define SC_NODE_STYLE_VISIBLE            "visible"       // bool
#define SC_NODE_STYLE_ROTATION           "rotation"      // float
#define SC_NODE_STYLE_ROTATION_X         "rotation-x"    // float
#define SC_NODE_STYLE_ROTATION_Y         "rotation-y"    // float
#define SC_NODE_STYLE_SKEW_X             "skew-x"        // float
#define SC_NODE_STYLE_SKEW_Y             "skew-y"        // float
#define SC_NODE_STYLE_COLOR              "color"         // Color3B

#define SC_NODE_STYLE_FLIP_X             "flip-x"        // bool
#define SC_NODE_STYLE_FLIP_Y             "flip-y"        // bool
#define SC_NODE_STYLE_LABEL              "label"         // string
#define SC_NODE_STYLE_FONT_SIZE          "font-size"     // float
#define SC_NODE_STYLE_FONT_NAME          "font-name"     // string
#define SC_NODE_STYLE_COLOR_TEXT         "color-text"    // Color4B
#define SC_NODE_STYLE_IMAGE              "image"         // string
    
#define SC_NODE_STYLE_DOCK               "dock"          // SCNodeUtils::EDockType. e.g. left|top
#define SC_NODE_STYLE_X_BY               "x-by"          // float
#define SC_NODE_STYLE_Y_BY               "y-by"          // float
    
    class SCNodeStyle
    {
    private:
        
        enum EValueType
        {
            UNKNOWN_TYPE,
            FLOAT_TYPE,
            INT_TYPE,
            STRING_TYPE,
            BOOL_TYPE,
            VEC2_TYPE,
            COLOR3_TYPE,
            COLOR4_TYPE,
            DOCK_TYPE,
        };
        
        struct SStylePair
        {
            const char*         pszKey;
            EValueType          type;
            
            inline bool operator>(const SStylePair& pair) const
            {
                return (::strcmp(pair.pszKey,pszKey)<0);
            }
            
            inline bool operator<(const SStylePair& pair) const
            {
                return (::strcmp(pair.pszKey,pszKey)>0);
            }
        };
        
    public:
        struct SFilterConfig
        {
            std::vector<SCString> keyVtr;
            bool bExclude;
            
            void setupPosition(const bool bExclude0)
            {
                bExclude = bExclude0;
                keyVtr =
                {
                    SC_NODE_STYLE_XY,
                    SC_NODE_STYLE_X,
                    SC_NODE_STYLE_Y,
                    SC_NODE_STYLE_DOCK,
                    SC_NODE_STYLE_X_BY,
                    SC_NODE_STYLE_Y_BY
                };
            }
        };
        
    public:
        static void setStyle(cocos2d::Node* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::Layer* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::Sprite* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::LayerColor* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::Menu* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::MenuItem* pNode,const SCDictionary& dic);
        static void setStyle(cocos2d::Label* pNode,const SCDictionary& dic);
        
        template<typename T>
        static void setStyle(cocos2d::Node* pNode,const SCString& strStyle,SFilterConfig* pFilterConfig=NULL)
        {
            SCASSERT(pNode!=NULL);
            SC_RETURN_V_IF(pNode==NULL);
            
            SCDictionary dic;
            if(SCNodeStyle::convertString2Dic(strStyle,dic))
            {
                if(pFilterConfig!=NULL && !pFilterConfig->keyVtr.empty())
                {
                    if(pFilterConfig->bExclude)
                    {
                        for(const auto& it : pFilterConfig->keyVtr)
                        {
                            dic.removeKey(it);
                        }
                    }
                    else
                    {
                        SCDictionary dic2;
                        for(const auto& it : pFilterConfig->keyVtr)
                        {
                            if(dic.hasKey(it))
                            {
                                dic2.setValue(it,dic[it]);
                            }
                        }
                        dic = dic2;
                    }
                }
                SCNodeStyle::setStyle(dynamic_cast<T*>(pNode),dic);
            }
        }
        
        static bool convertString2Dic(const SCString& strStyle,SCDictionary& dic);
        static SCString extractKey(const SCString& strKey,const SCString& strStyle);
        static SCString removeKey(const SCString& strKey,const SCString& strStyle);
        
    private:
        static bool scanStyle(const SCString& strStyle,
                                 const std::function<bool(const SCString&,EValueType type,const SCString&)>& func);
        static bool readKey(SCString& strKey,char*& pCurrent, char*& pEnd);
        static bool readValue(SCString& strValue,const EValueType type,char*& pCurrent, char*& pEnd);
        static void skipSpaces(char*& pCurrent, char*& pEnd);
        static void nextSemicolon(char*& pCurrent, char*& pEnd);
        static EValueType getKeyType(SCString& strKey);
        static bool parseValue(const EValueType type,const SCString& strValue,SCValue& value);
        
        static bool getColorByName(const SCString& strKey,cocos2d::Color3B& val);
        static bool getColorByName(const SCString& strKey,cocos2d::Color4B& val);
        
        static bool getColor3(const SCDictionary& dic,const SCString& strKey,cocos2d::Color3B& val);
        static bool getColor4(const SCDictionary& dic,const SCString& strKey,cocos2d::Color4B& val);
        static bool getString(const SCDictionary& dic,const SCString& strKey,SCString& val);
        static bool getFloat(const SCDictionary& dic,const SCString& strKey,float& val);
        static bool getInt(const SCDictionary& dic,const SCString& strKey,int& val);
        static bool getBool(const SCDictionary& dic,const SCString& strKey,bool& val);
        static bool getVec2(const SCDictionary& dic,const SCString& strKey,cocos2d::Vec2& array);
        
        static bool parseColor4(SCString strValue,cocos2d::Color4B& val);
        static bool parseVec2(SCString strValue,cocos2d::Vec2& vec2);
        static bool parseDock(SCString strDock,int& nDock);
        
        static bool isValidKeyChar(const char& c);
        
    private:
        static SStylePair s_StylePairArray[];
    };
}

#endif // __SPEEDCC__SCNODEPROPERTY_H__