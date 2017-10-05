

#ifndef __SC__DATABLOCK_H__
#define __SC__DATABLOCK_H__

#include "SCString.h"
#include "SCBufferRefT.h"

namespace SPEEDCC
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

#endif // __SC__DATABLOCK_H__
