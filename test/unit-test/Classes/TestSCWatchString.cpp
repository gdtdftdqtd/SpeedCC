
#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;
using namespace cocos2d;

TEST(TestSCWatchString, Constructor)
{
    SCWatchString::Ptr watch1 = SCWatchString::create();
    
    *watch1 = "abc";
    EXPECT_EQ(*watch1 == "abc",true);
}




