/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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

TEST(TestSCDataBlock, Constructor)
{
    const char testData[] = "abcdef";
    
    SCDataBlock db1;
    SCDataBlock db2(db1);
    
    EXPECT_EQ(db1.getSize(), 0);
    EXPECT_EQ(db2.getSize(), 0);
    EXPECT_EQ(db1.getDataPtr(),db2.getDataPtr());
    
    SCDataBlock db3((void*)testData,sizeof(testData));
    EXPECT_EQ(db3.getSize(), sizeof(testData));
    EXPECT_EQ(memcmp(db3.getDataPtr(), testData, sizeof(testData)),0);
    EXPECT_EQ(db3.getRefCount(), 1);
    
    SCDataBlock db4(db3);
    EXPECT_EQ(db3.getSize(), db4.getSize());
    EXPECT_EQ(db3.getDataPtr(), db4.getDataPtr());
    EXPECT_EQ(db3.getRefCount(), 2);
    
    db4.clear();
    EXPECT_EQ(db4.getRefCount(), 0);
    EXPECT_EQ(db3.getRefCount(), 1);
    
    SCString str = "123456";
    SCDataBlock db5(str);
    EXPECT_EQ(db5.getSize(), str.getLength()+1);
    EXPECT_EQ(memcmp(db5.getDataPtr(), str.c_str(), db5.getSize()),0);
}

TEST(TestSCDataBlock, Assignment)
{
    const char testData[] = "abcdef";
    
    SCDataBlock db1;
    db1.assign(testData, sizeof(testData));
    EXPECT_EQ(db1.getSize(), sizeof(testData));
    EXPECT_EQ(memcmp(db1.getDataPtr(), testData, sizeof(testData)),0);
    
    SCDataBlock db2;
    db2.assign(db1);
    EXPECT_EQ(db1.getSize(), db2.getSize());
    EXPECT_EQ(memcmp(db1.getDataPtr(), db2.getDataPtr(), db2.getSize()),0);
    
    SCDataBlock db3;
    db3 = db1;
    EXPECT_EQ(db1.getSize(), db3.getSize());
    EXPECT_EQ(memcmp(db1.getDataPtr(), db3.getDataPtr(), db3.getSize()),0);
}

TEST(TestSCDataBlock, Append)
{
    const char testData1[] = "abcdef";
    const char testData2[] = "123456";
    
    SCDataBlock db1;
    db1.append(testData1, (int)strlen(testData1));
    EXPECT_EQ(db1.getSize(), strlen(testData1));
    EXPECT_EQ(memcmp(db1.getDataPtr(), testData1, strlen(testData1)),0);
    
    db1.append(testData2, sizeof(testData2));
    EXPECT_EQ(db1.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db1.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    SCDataBlock db2;
    db1.clear();
    db2.append(testData1, (int)strlen(testData1));
    db1.append(testData2, sizeof(testData2));
    db2.append(db1);
    EXPECT_EQ(db2.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db2.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    db1.clear();
    db2.clear();
    db2.append(testData1, (int)strlen(testData1));
    db1.append(testData2, sizeof(testData2));
    db2 += db1;
    EXPECT_EQ(db2.getSize(), strlen(testData1)+sizeof(testData2));
    EXPECT_EQ(memcmp(db2.getDataPtr(), "abcdef123456", strlen("abcdef123456")),0);
    
    db1.clear();
    db2.clear();
    db1.append(testData2, sizeof(testData2));
    db2 += db1;
    EXPECT_EQ(memcmp(db2.getDataPtr(), testData2, strlen(testData2)),0);
}



