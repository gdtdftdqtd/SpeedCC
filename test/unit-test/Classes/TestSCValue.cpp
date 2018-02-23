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

TEST(TestSCValue, Constructor)
{
    SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    SCDataBlock dbTest("12345");
    std::vector<SCValue> vetArrayTest;
    
    SCValue value1;
    SCValue value2(123);
    SCValue value3(true);
    SCValue value4(1.23f);
    SCValue value5("abc");
    SCValue value6(1.23);
    SCValue value7(dtTest);
    SCValue value8(dbTest);
    
    bool bResult = false;
    SCString strValue;
    SCDateTime dt;
    SCDataBlock db;
    std::vector<SCValue> vetArray;
    
    EXPECT_EQ(value1.getType(), SCValue::UNKNOWN_TYPE);
    EXPECT_EQ(value1.getRefCount(), 1);
    
    EXPECT_EQ(value2.getType(), SCValue::INT_TYPE);
    EXPECT_EQ(value2.getInt(&bResult), 123);
    EXPECT_EQ(bResult, true);
    value2.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value2.getRefCount(), 1);
    
    EXPECT_EQ(value3.getType(), SCValue::BOOL_TYPE);
    EXPECT_EQ(value3.getBool(&bResult), true);
    EXPECT_EQ(bResult, true);
    value3.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value3.getRefCount(), 1);
    
    EXPECT_EQ(value4.getType(), SCValue::FLOAT_TYPE);
    EXPECT_EQ(value4.getFloat(&bResult), 1.23f);
    EXPECT_EQ(bResult, true);
    value4.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value4.getRefCount(), 1);
    
    EXPECT_EQ(value5.getType(), SCValue::STRING_TYPE);
    EXPECT_EQ(value5.getString(&bResult), "abc");
    EXPECT_EQ(bResult,true);
    value5.getLong(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value6.getType(), SCValue::DOUBLE_TYPE);
    EXPECT_EQ(value6.getDouble(&bResult), 1.23);
    EXPECT_EQ(bResult, true);
    value6.getFloat(&bResult,true);
    EXPECT_EQ(bResult, false);
    EXPECT_EQ(value6.getRefCount(), 1);
    
    {
        SCValue value100(value1);
        EXPECT_EQ(value1.getType(), SCValue::UNKNOWN_TYPE);
        EXPECT_EQ(value1.getRefCount(), 2);
        EXPECT_EQ(value100.getType(), SCValue::UNKNOWN_TYPE);
        EXPECT_EQ(value100.getRefCount(), 2);
    }
    
    EXPECT_EQ(value1.getType(), SCValue::UNKNOWN_TYPE);
    EXPECT_EQ(value1.getRefCount(), 1);
    
    
    {
        SCValue value101(value5);
        EXPECT_EQ(value5.getType(), SCValue::STRING_TYPE);
        EXPECT_STREQ(value5.getString(&bResult),"abc");
        EXPECT_EQ(bResult, true);
        EXPECT_EQ(value5.getRefCount(), 2);
        
        EXPECT_EQ(value101.getType(), SCValue::STRING_TYPE);
        EXPECT_STREQ(value101.getString(&bResult),"abc");
        EXPECT_EQ(bResult, true);
        EXPECT_EQ(value101.getRefCount(), 2);
    }
    
    EXPECT_EQ(value5.getType(), SCValue::STRING_TYPE);
    EXPECT_STREQ(value5.getString(&bResult),"abc");
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value7.getRefCount(), 1);
    EXPECT_EQ(value7.getType(), SCValue::DATETIME_TYPE);
    dt = value7.getDateTime(&bResult);
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(dt.getYear(), dtTest.getYear());
    EXPECT_EQ(dt.getMonth(), dtTest.getMonth());
    EXPECT_EQ(dt.getDayOfMonth(), dtTest.getDayOfMonth());
    EXPECT_EQ(dt.getHour(), dtTest.getHour());
    EXPECT_EQ(dt.getMinute(), dtTest.getMinute());
    EXPECT_EQ(dt.getSeconds(), dtTest.getSeconds());
    
    EXPECT_EQ(value8.getRefCount(), 1);
    EXPECT_EQ(value8.getType(), SCValue::DATABLOCK_TYPE);
    EXPECT_STREQ((char*)value8.getDataBlock(&bResult).getDataPtr(),"12345");
    EXPECT_EQ(bResult, true);
    
    vetArrayTest.push_back(value1);
    vetArrayTest.push_back(value2);
    vetArrayTest.push_back(value3);
    vetArrayTest.push_back(value4);
    vetArrayTest.push_back(value5);
    vetArrayTest.push_back(value6);
    vetArrayTest.push_back(value7);
    vetArrayTest.push_back(value8);
    SCValue value9(vetArrayTest);
    
    EXPECT_EQ(value1.getRefCount(), 3);
    EXPECT_EQ(value2.getRefCount(), 3);
    EXPECT_EQ(value3.getRefCount(), 3);
    EXPECT_EQ(value4.getRefCount(), 3);
    EXPECT_EQ(value5.getRefCount(), 3);
    EXPECT_EQ(value6.getRefCount(), 3);
    EXPECT_EQ(value7.getRefCount(), 3);
    EXPECT_EQ(value8.getRefCount(), 3);
    EXPECT_EQ(value9.getRefCount(), 1);
    EXPECT_EQ(value9.getType(), SCValue::ARRAY_TYPE);
    vetArray = value9.getArray(&bResult);
    EXPECT_EQ(bResult, true);
    EXPECT_EQ(vetArray[0]==value1, true);
    EXPECT_EQ(vetArray[1]==value2, true);
    EXPECT_EQ(vetArray[2]==value3, true);
    EXPECT_EQ(vetArray[3]==value4, true);
    EXPECT_EQ(vetArray[4]==value5, true);
    EXPECT_EQ(vetArray[5]==value6, true);
    EXPECT_EQ(vetArray[6]==value7, true);
    EXPECT_EQ(vetArray[7]==value8, true);
}


TEST(TestSCValue, Assignment)
{
    SCValue value1;
    
    bool bResult = false;
    const int nTest = 234;
    
    value1.setInt(nTest);
    EXPECT_EQ(value1.getType(),SCValue::INT_TYPE);
    EXPECT_EQ(value1.getInt(&bResult),nTest);
    EXPECT_EQ(bResult,true);
    
    const bool bTest = true;
    value1.setBool(bTest);
    EXPECT_EQ(value1.getType(),SCValue::BOOL_TYPE);
    EXPECT_EQ(value1.getBool(&bResult),bTest);
    EXPECT_EQ(bResult,true);
    
    const float fTest = 1.23f;
    value1.setFloat(fTest);
    EXPECT_EQ(value1.getType(),SCValue::FLOAT_TYPE);
    EXPECT_EQ(value1.getFloat(&bResult),fTest);
    EXPECT_EQ(bResult,true);
    
    const double dTest = 1.23;
    value1.setDouble(dTest);
    EXPECT_EQ(value1.getType(),SCValue::DOUBLE_TYPE);
    EXPECT_EQ(value1.getDouble(&bResult),dTest);
    EXPECT_EQ(bResult,true);
    
    const SCString strTest = "abc123";
    SCString strValue = "";
    value1.setString(strTest);
    EXPECT_EQ(value1.getType(),SCValue::STRING_TYPE);
    EXPECT_STREQ(value1.getString(&bResult), strTest);
    EXPECT_EQ(bResult,true);
    
    const SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    SCDateTime dtValue;
    value1.setDateTime(dtTest);
    EXPECT_EQ(value1.getType(),SCValue::DATETIME_TYPE);
    EXPECT_EQ(dtTest.getStamp(), value1.getDateTime(&bResult).getStamp());
    EXPECT_EQ(bResult,true);
    
    const SCDataBlock dbTest("12345");
    SCDataBlock dbValue;
    value1.setDataBlock(dbTest);
    EXPECT_EQ(value1.getType(),SCValue::DATABLOCK_TYPE);
    dbValue = value1.getDataBlock(&bResult);
    EXPECT_EQ(dbTest.getSize(),dbValue.getSize());
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(memcmp(dbTest.getDataPtr(),dbValue.getDataPtr(),dbValue.getSize()),0);
    
    const SCValue valueTest(123);
    SCValue value2 = valueTest;
    
    EXPECT_EQ(value2.getType(),SCValue::INT_TYPE);
    EXPECT_EQ(value2.getInt(&bResult),123);
    EXPECT_EQ(bResult,true);
    
    std::vector<SCValue> vetArrayTest;
    value1.setInt(nTest);
    
    vetArrayTest.push_back(value1);
    value1.setString(strTest);
    strValue = "";
    vetArrayTest.push_back(value1);
    value1.setDataBlock(dbTest);
    dbValue.clear();
    vetArrayTest.push_back(value1);
    value1.setArray(vetArrayTest);
    
    std::vector<SCValue> vetArrayValue;
    EXPECT_EQ(value1.getType(),SCValue::ARRAY_TYPE);
    vetArrayValue = value1.getArray(&bResult);
    EXPECT_EQ(bResult,true);
    EXPECT_EQ(vetArrayValue.size(),vetArrayTest.size());
}




