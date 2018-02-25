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

#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;
using namespace cocos2d;

TEST(TestSCNodeStyle, Space)
{
    SCDictionary dic;
    SCString strTest;
    
    strTest = "tag=123;";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("tag"),true);
    EXPECT_EQ(dic.getValue("tag").getType(),SCValue::INT_TYPE);
    EXPECT_EQ(dic.getValue("tag").getInt(),123);
    
    strTest = "tag  = 123 ;";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("tag"),true);
    EXPECT_EQ(dic.getValue("tag").getType(),SCValue::INT_TYPE);
    EXPECT_EQ(dic.getValue("tag").getInt(),123);
    
    strTest = " tag=123 ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("tag"),true);
    EXPECT_EQ(dic.getValue("tag").getType(),SCValue::INT_TYPE);
    EXPECT_EQ(dic.getValue("tag").getInt(),123);
    
    strTest = " tag  = 123 ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("tag"),true);
    EXPECT_EQ(dic.getValue("tag").getType(),SCValue::INT_TYPE);
    EXPECT_EQ(dic.getValue("tag").getInt(),123);
    
}


TEST(TestSCNodeStyle, StringValue)
{
    SCDictionary dic;
    SCString strTest;
    
    strTest = "text='abc'; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), "abc");
    
    strTest = " text = 'abc' ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), "abc");
    
    strTest = " text = ' abc ' ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), " abc ");
    
    strTest = " text = ' ' ;";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), " ");
    
    strTest = " text = '' ;";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), "");
    
    strTest = " text = '''' ;";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.hasKey("text"),true);
    EXPECT_EQ(dic.getValue("text").getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(dic.getValue("text").getString().c_str(), "'");
}

TEST(TestSCNodeStyle, Color3BValue)
{
    SCDictionary dic;
    SCString strTest;
    
    // Color3B
    strTest = "color=#123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(0x12,0x34,0x56));
    
    strTest = "color=0x123456 ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(0x12,0x34,0x56));
    
    strTest = "color=gray ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(166,166,166));
    
    strTest = "color=(12,34,56) ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(12,34,56));
    
    // Color4B
    strTest = "color=#00123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(0x12,0x34,0x56));
    
    strTest = "color=0x00123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(0x12,0x34,0x56));
    
    strTest = "color=(12,34,56,78) ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color").getObject<Color3B>(), Color3B(12,34,56));
}

TEST(TestSCNodeStyle, Color4BValue)
{
    SCDictionary dic;
    SCString strTest;
    
    // Color3B
    strTest = "color-text=#123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(0x12,0x34,0x56,0x00));
    
    strTest = "color-text=0x123456 ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(0x12,0x34,0x56,0x00));
    
    strTest = "color-text=gray ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(166,166,166,255));
    
    strTest = "color-text=(12,34,56) ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(12,34,56,255));
    
    // Color4B
    strTest = "color-text=#78123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(0x12,0x34,0x56,0x78));
    
    strTest = "color-text=0x78123456; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(0x12,0x34,0x56,0x78));
    
    strTest = "color-text=(12,34,56,78) ; ";
    dic.removeAllKeys();
    EXPECT_EQ(SCNodeStyle::convertString2Dic(strTest,dic),true);
    EXPECT_EQ(dic.getCount(),1);
    EXPECT_EQ(dic.getValue("color-text").getType(),SCValue::OBJECT_TYPE);
    EXPECT_EQ(dic.getValue("color-text").getObject<Color4B>(), Color4B(12,34,56,78));
}



