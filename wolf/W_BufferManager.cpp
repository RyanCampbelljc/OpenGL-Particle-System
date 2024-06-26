//-----------------------------------------------------------------------------
// File:			W_BufferManager.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "W_BufferManager.h"

namespace wolf
{

//----------------------------------------------------------
// Creates a new Vertex Buffer
//----------------------------------------------------------
VertexBuffer* BufferManager::CreateVertexBuffer(unsigned int length, GLenum usage)
{
	return new VertexBuffer(length, usage);
}

//----------------------------------------------------------
// Creates a new Vertex Buffer
//----------------------------------------------------------
VertexBuffer* BufferManager::CreateVertexBuffer(const void* pData, unsigned int length, GLenum usage)
{
	return new VertexBuffer(pData, length, usage);
}

//----------------------------------------------------------
// Creates a new Index Buffer
//----------------------------------------------------------
IndexBuffer* BufferManager::CreateIndexBuffer(unsigned int numIndices)
{
	return new IndexBuffer(numIndices);
}

//----------------------------------------------------------
// Creates a new Index Buffer
//----------------------------------------------------------
IndexBuffer* BufferManager::CreateIndexBuffer(const unsigned short* pData, unsigned int numIndices)
{
	IndexBuffer* pRet = new IndexBuffer(numIndices);
	pRet->Write(pData);
	return pRet;
}

//----------------------------------------------------------
// Destroys a buffer.
//----------------------------------------------------------
void BufferManager::DestroyBuffer(Buffer* pBuf)
{
	if (!pBuf)
		return;
	delete pBuf;
}

} // namespace wolf
