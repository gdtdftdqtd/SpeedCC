
#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;

TEST(TestSCDictionary, Constructor)
{
    SCDictionary testPar;
    testPar.setValue("key1", 123);
    testPar.setValue("key2", "abc");
    testPar.setValue("key3", 'd');
    testPar.setValue("key4", 4.56f);
    
    EXPECT_EQ(testPar.getValue("key1").getInt(), 123);
    EXPECT_EQ(testPar.getValue("key2").getString(), "abc");
    EXPECT_EQ(testPar.getValue("key3").getChar(), 'd');
    EXPECT_EQ(testPar.getValue("key4").getFloat(), 4.56f);
}


TEST(TestSCDictionary, Assignment)
{
    
}




