
#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

TEST(TestSCDictionary, Constructor)
{
    SCDictionary testPar;
    
    EXPECT_EQ(testPar.isEmpty(),true);
    EXPECT_EQ(testPar.getCount(),0);
    
    testPar.setValue("key1", 123);
    testPar.setValue("key2", "abc");
    testPar.setValue("key3", 'd');
    testPar.setValue("key4", 4.56f);
    
    EXPECT_EQ(testPar.isEmpty(),false);
    EXPECT_EQ(testPar.getCount(),4);
    
    EXPECT_EQ(testPar.hasKey("key10"),false);
    
    EXPECT_EQ(testPar.hasKey("key1"),true);
    EXPECT_EQ(testPar.getValue("key1").getInt(), 123);
    
    EXPECT_EQ(testPar.hasKey("key2"),true);
    EXPECT_EQ(testPar.getValue("key2").getString(), "abc");
    
    EXPECT_EQ(testPar.hasKey("key3"),true);
    EXPECT_EQ(testPar.getValue("key3").getChar(), 'd');
    
    EXPECT_EQ(testPar.hasKey("key4"),true);
    EXPECT_EQ(testPar.getValue("key4").getFloat(), 4.56f);
    
    testPar.removeKey("key1");
    EXPECT_EQ(testPar.hasKey("key1"),false);
}


TEST(TestSCDictionary, Json)
{
    SCString strJson = "{\"abc\":123}";
    
    SCDictionary testDic;
    
    EXPECT_EQ(testDic.loadFromJsonString(strJson),true);
}




