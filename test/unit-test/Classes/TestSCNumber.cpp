
#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SpeedCC;
using namespace cocos2d;

TEST(TestSCNumber, Plus)
{
    SCInt numInt1;
    
    EXPECT_EQ(numInt1==0,true);
    
    numInt1 = 3;
    EXPECT_EQ(numInt1==3,true);
    EXPECT_EQ(3==numInt1,true);
    
    int p1 = numInt1 + 4;
    EXPECT_EQ(numInt1==3,true);
    EXPECT_EQ(p1==7,true);
    
    SCInt numInt2 = numInt1 + 4;
    EXPECT_EQ(numInt1==3,true);
    EXPECT_EQ(numInt2==7,true);
    
    int p3 = 4 + numInt1;
    EXPECT_EQ(numInt1==3,true);
    EXPECT_EQ(p3==7,true);
    
    numInt1 = 5;
    numInt1 += 3;
    EXPECT_EQ(numInt1==8,true);
    
    numInt1 = 2;
    numInt2 = 3;
    p1 = numInt1 + numInt2;
    EXPECT_EQ(p1==5,true);
    EXPECT_EQ(numInt1==2,true);
    EXPECT_EQ(numInt2==3,true);
    
    numInt1 = 2;
    p1 = 4;
    p1 += numInt1;
    EXPECT_EQ(p1==6,true);
    
    numInt1 = 2;
    numInt2 = 3;
    numInt1 += numInt2;
    EXPECT_EQ(numInt1==5,true);
    
    numInt1 = 2;
    numInt1 += 4.2f;
    EXPECT_EQ(numInt1==6,true);
    
    numInt1 = 3;
    numInt1 = numInt1 + 4.2f;
    EXPECT_EQ(numInt1==7,true);
    
    numInt1 = 1;
    EXPECT_EQ(numInt1++ == 1,true);
    EXPECT_EQ(numInt1 == 2,true);
    EXPECT_EQ(++numInt1 == 3,true);
}


TEST(TestSCNumber, Boolean)
{
    SCBool numBool;
    
    numBool = true;
    EXPECT_EQ(numBool==true,true);
    numBool = false;
    EXPECT_EQ(false==numBool,true);
    
    bool testBool = numBool;
    EXPECT_EQ(numBool==testBool,true);
}

