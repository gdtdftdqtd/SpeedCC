
#include <sys/time.h>

#include "gtest/gtest.h"
#include "SpeedCC.h"

using namespace SPEEDCC;

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
    
    int nTem = 0;
    bool bTem = false;
    long lTem = 0;
    float fTem = 0.0f;
    double dTem = 0.0;
    SCString strValue;
    SCDateTime dt;
    SCDataBlock db;
    std::vector<SCValue> vetArray;
    
    EXPECT_EQ(value1.getType(), SCValue::UNKNOWN_TYPE);
    EXPECT_EQ(value1.getRefCount(), 1);
    
    EXPECT_EQ(value2.getType(), SCValue::INT_TYPE);
    EXPECT_EQ(value2.getInt(nTem), true);
    EXPECT_EQ(nTem, 123);
    EXPECT_EQ(value2.getLong(lTem), false);
    EXPECT_EQ(value2.getRefCount(), 1);
    
    EXPECT_EQ(value3.getType(), SCValue::BOOL_TYPE);
    EXPECT_EQ(value3.getBool(bTem), true);
    EXPECT_EQ(bTem, true);
    EXPECT_EQ(value3.getLong(lTem), false);
    EXPECT_EQ(value3.getRefCount(), 1);
    
    EXPECT_EQ(value4.getType(), SCValue::FLOAT_TYPE);
    EXPECT_EQ(value4.getFloat(fTem), true);
    EXPECT_EQ(fTem, 1.23f);
    EXPECT_EQ(value4.getLong(lTem), false);
    EXPECT_EQ(value4.getRefCount(), 1);
    
    EXPECT_EQ(value5.getType(), SCValue::STRING_TYPE);
    EXPECT_EQ(value5.getString(strValue), true);
    EXPECT_STREQ(strValue,"abc");
    EXPECT_EQ(value5.getLong(lTem), false);
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value6.getType(), SCValue::DOUBLE_TYPE);
    EXPECT_EQ(value6.getDouble(dTem), true);
    EXPECT_EQ(dTem, 1.23);
    EXPECT_EQ(value6.getFloat(fTem), false);
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
        EXPECT_EQ(value5.getString(strValue), true);
        EXPECT_STREQ(strValue,"abc");
        EXPECT_EQ(value5.getRefCount(), 2);
        
        EXPECT_EQ(value101.getType(), SCValue::STRING_TYPE);
        EXPECT_EQ(value101.getString(strValue), true);
        EXPECT_STREQ(strValue,"abc");
        EXPECT_EQ(value101.getRefCount(), 2);
    }
    
    EXPECT_EQ(value5.getType(), SCValue::STRING_TYPE);
    EXPECT_EQ(value5.getString(strValue), true);
    EXPECT_STREQ(strValue,"abc");
    EXPECT_EQ(value5.getRefCount(), 1);
    
    EXPECT_EQ(value7.getRefCount(), 1);
    EXPECT_EQ(value7.getType(), SCValue::DATETIME_TYPE);
    EXPECT_EQ(value7.getDateTime(dt), true);
    EXPECT_EQ(dt.getYear(), dtTest.getYear());
    EXPECT_EQ(dt.getMonth(), dtTest.getMonth());
    EXPECT_EQ(dt.getDayOfMonth(), dtTest.getDayOfMonth());
    EXPECT_EQ(dt.getHour(), dtTest.getHour());
    EXPECT_EQ(dt.getMinute(), dtTest.getMinute());
    EXPECT_EQ(dt.getSeconds(), dtTest.getSeconds());
    
    EXPECT_EQ(value8.getRefCount(), 1);
    EXPECT_EQ(value8.getType(), SCValue::DATABLOCK_TYPE);
    EXPECT_EQ(value8.getDataBlock(db), true);
    EXPECT_STREQ((char*)db.getDataPtr(),"12345");
    
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
    EXPECT_EQ(value9.getArray(vetArray), true);
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
    
    const int nTest = 234;
    int nValue = 0;
    value1.setInt(nTest);
    EXPECT_EQ(value1.getType(),SCValue::INT_TYPE);
    EXPECT_EQ(value1.getInt(nValue),true);
    EXPECT_EQ(nValue,nTest);
    
    const bool bTest = true;
    bool bValue = false;
    value1.setBool(bTest);
    EXPECT_EQ(value1.getType(),SCValue::BOOL_TYPE);
    EXPECT_EQ(value1.getBool(bValue),true);
    EXPECT_EQ(bValue,bTest);
    
    const float fTest = 1.23f;
    float fValue = 0.0f;
    value1.setFloat(fTest);
    EXPECT_EQ(value1.getType(),SCValue::FLOAT_TYPE);
    EXPECT_EQ(value1.getFloat(fValue),true);
    EXPECT_EQ(fValue,fTest);
    
    const double dTest = 1.23;
    double dValue = 0.0;
    value1.setDouble(dTest);
    EXPECT_EQ(value1.getType(),SCValue::DOUBLE_TYPE);
    EXPECT_EQ(value1.getDouble(dValue),true);
    EXPECT_EQ(dValue,dTest);
    
    const SCString strTest = "abc123";
    SCString strValue = "";
    value1.setString(strTest);
    EXPECT_EQ(value1.getType(),SCValue::STRING_TYPE);
    EXPECT_EQ(value1.getString(strValue),true);
    EXPECT_STREQ(strValue, strTest);
    
    const SCDateTime dtTest("2017-10-01 12:34:56","%Y-%m-%d %H:%M:%S");
    SCDateTime dtValue;
    value1.setDateTime(dtTest);
    EXPECT_EQ(value1.getType(),SCValue::DATETIME_TYPE);
    EXPECT_EQ(value1.getDateTime(dtValue),true);
    EXPECT_EQ(dtTest.getStamp(), dtValue.getStamp());
    
    const SCDataBlock dbTest("12345");
    SCDataBlock dbValue;
    value1.setDataBlock(dbTest);
    EXPECT_EQ(value1.getType(),SCValue::DATABLOCK_TYPE);
    EXPECT_EQ(value1.getDataBlock(dbValue),true);
    EXPECT_EQ(dbTest.getSize(),dbValue.getSize());
    EXPECT_EQ(memcmp(dbTest.getDataPtr(),dbValue.getDataPtr(),dbValue.getSize()),0);
    
    const SCValue valueTest(123);
    SCValue value2;
    nValue = 0;
    value1.setValue(valueTest);
    EXPECT_EQ(value1.getType(),SCValue::VALUE_TYPE);
    EXPECT_EQ(value1.getValue(value2),true);
    EXPECT_EQ(value2.getType(),SCValue::INT_TYPE);
    EXPECT_EQ(value2.getInt(nValue),true);
    EXPECT_EQ(nValue,123);
    
    std::vector<SCValue> vetArrayTest;
    value1.setInt(nTest);
    nValue = 0;
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
    EXPECT_EQ(value1.getArray(vetArrayValue),true);
    EXPECT_EQ(vetArrayValue.size(),vetArrayTest.size());
    
//    vetArrayValue[0].getInt(<#int &nValue#>)
}




