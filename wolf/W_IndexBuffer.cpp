//-----------------------------------------------------------------------------
// File:			W_IndexBuffer.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "W_IndexBuffer.h"

namespace wolf
{
//----------------------------------------------------------
// Constructor
//----------------------------------------------------------
IndexBuffer::IndexBuffer(unsigned int numIndices, GLenum usage)
	: m_lengthInBytes(numIndices * 2)
{
	glGenBuffers(1, &m_bufferId);
	Write(nullptr, -1, usage);
}

//----------------------------------------------------------
// Destructor
//----------------------------------------------------------
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
}

//----------------------------------------------------------
// Fills this Index buffer with the given data
//----------------------------------------------------------
void IndexBuffer::Write(const void* pData, int lengthInBytes, GLenum usage)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lengthInBytes == -1 ? m_lengthInBytes : lengthInBytes, pData, usage);
}

//----------------------------------------------------------
// Binds this buffer
//----------------------------------------------------------
void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
}

} // namespace wolf
