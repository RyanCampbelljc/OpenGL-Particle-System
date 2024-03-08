//-----------------------------------------------------------------------------
// File:			W_VertexBuffer.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "W_VertexBuffer.h"

namespace wolf
{
//----------------------------------------------------------
// Constructor
//----------------------------------------------------------
VertexBuffer::VertexBuffer(unsigned int p_uiLength, GLenum usage)
	: VertexBuffer(nullptr, p_uiLength, usage)
{
}

//----------------------------------------------------------
// Constructor
//----------------------------------------------------------
VertexBuffer::VertexBuffer(const void* p_pData, unsigned int p_uiLength, GLenum usage)
	: m_uiLength(p_uiLength)
{
	glGenBuffers(1, &m_uiBuffer);
	Write(p_pData, -1, usage);
}

//----------------------------------------------------------
// Destructor
//----------------------------------------------------------
VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_uiBuffer);
}

//----------------------------------------------------------
// Fills this vertex buffer with the given data
//----------------------------------------------------------
void VertexBuffer::Write(const void* p_pData, int p_iLength, GLenum usage)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, p_iLength == -1 ? m_uiLength : p_iLength, p_pData, usage);
}

//----------------------------------------------------------
// Binds this buffer
//----------------------------------------------------------
void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
}

} // namespace wolf
