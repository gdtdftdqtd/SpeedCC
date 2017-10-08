

#ifndef __SPEEDCC__SCDATABLOCK_H__
#define __SPEEDCC__SCDATABLOCK_H__

#include "SCString.h"
#include "SCBufferRefT.h"

namespace SpeedCC
{
    class SCDataBlock final : public SCBufferRefT<SCDataBlock>
    {
    public:
        SCDataBlock();
        SCDataBlock(const SCString& str);
        SCDataBlock(const SCDataBlock& data);
        SCDataBlock(void* pData,const int nDataSize);
        
    };
}

#endif // __SPEEDCC__SCDATABLOCK_H__
