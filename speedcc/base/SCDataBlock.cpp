

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
    SCBufferRefT<SCDataBlock>((void*)str.c_str(),str.getLength()+1)
    {
    }
    
    SCDataBlock::SCDataBlock(void* pData,const int nDataSize):
    SCBufferRefT<SCDataBlock>(pData,nDataSize)
    {
    }
    
    SCDataBlock::SCDataBlock(const SCDataBlock& data):
    SCBufferRefT<SCDataBlock>((SCBufferRefT<SCDataBlock>)data)
    {
    }
}

