

#ifndef __SPEEDCC__SCDATABLOCK_H__
#define __SPEEDCC__SCDATABLOCK_H__

#include "SCBufferRefT.h"
#include "SCString.h"

namespace SpeedCC
{
    class SCDataBlock : public SCBufferRefT<SCBufferRefCookie>
    {
    public:
        SCDataBlock();
        SCDataBlock(const SCString& str);
        SCDataBlock(const SCDataBlock& data);
        SCDataBlock(void* pData,const int nDataSize);
    };
}

#endif // __SPEEDCC__SCDATABLOCK_H__
