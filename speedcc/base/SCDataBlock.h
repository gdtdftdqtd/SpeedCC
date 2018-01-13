

#ifndef __SPEEDCC__SCDATABLOCK_H__
#define __SPEEDCC__SCDATABLOCK_H__

#include "SCBufferRefT.h"
#include "SCString.h"

namespace SpeedCC
{
    class SCDataBlock :
    public SCBufferRefT<SCBufferRefCookie>,
    public SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCDataBlock)
        SCDataBlock();
        SCDataBlock(const SCString& str);
        SCDataBlock(const SCDataBlock& data);
        SCDataBlock(void* pData,const int nDataSize);
    };
}

#endif // __SPEEDCC__SCDATABLOCK_H__
