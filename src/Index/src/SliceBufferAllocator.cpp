// The MIT License (MIT)

// Copyright (c) 2016, Microsoft

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <inttypes.h>
#include <iostream>  // TODO: remove.

#include "BitFunnel/Utilities/Factories.h"
#include "LoggerInterfaces/Logging.h"
#include "SliceBufferAllocator.h"

namespace BitFunnel
{
    SliceBufferAllocator::SliceBufferAllocator(size_t blockSize, size_t blockCount)
        : m_blockAllocator(Factories::CreateBlockAllocator(blockSize, blockCount))
    {
    }


    void* SliceBufferAllocator::Allocate(size_t byteSize)
    {
        // TODO: should this be more strict and allow only exactly sized blocks?
        LogAssertB(m_blockAllocator->GetBlockSize() <= byteSize,
                   "Allocate byteSize < block size.");

        return m_blockAllocator->AllocateBlock();
    }


    void SliceBufferAllocator::Release(void* buffer)
    {
        m_blockAllocator->ReleaseBlock(reinterpret_cast<uint64_t*>(buffer));
    }


    size_t SliceBufferAllocator::GetSliceBufferSize() const
    {
        return m_blockAllocator->GetBlockSize();
    }
}