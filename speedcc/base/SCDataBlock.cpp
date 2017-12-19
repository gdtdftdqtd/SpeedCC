

#include "SCDataBlock.h"
#include "SCMemAllocator.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    SCDataBlock::SCDataBlock()
    {
        this->clear();
    }
    
    SCDataBlock::SCDataBlock(const SCString& str):
    SCBufferRefT<SCBufferRefCookie>((void*)str.c_str(),str.getLength()+1)
    {
    }
    
    SCDataBlock::SCDataBlock(void* pData,const int nDataSize):
    SCBufferRefT<SCBufferRefCookie>(pData,nDataSize)
    {
    }
    
    SCDataBlock::SCDataBlock(const SCDataBlock& data):
    SCBufferRefT<SCBufferRefCookie>((SCBufferRefT)data)
    {
    }
}

