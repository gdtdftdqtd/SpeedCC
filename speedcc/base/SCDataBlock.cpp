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

