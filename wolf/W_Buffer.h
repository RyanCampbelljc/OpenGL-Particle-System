//-----------------------------------------------------------------------------
// File:			W_Buffer.h
// Original Author:	Gordon Wood
//
// Base class for a buffer that is used by the rendering API. Concrete
// subclasses will be for an IndexBuffer and a VertexBuffer
//-----------------------------------------------------------------------------
#ifndef W_BUFFER_H
#define W_BUFFER_H

#include "W_Types.h"

namespace wolf
{
class Buffer
{
	friend class BufferManager;

public:
	//-------------------------------------------------------------------------
	// PUBLIC INTERFACE
	//-------------------------------------------------------------------------
	virtual void Bind() = 0;
	virtual void Write(const void* pData, int length = -1, GLenum usage = GL_STATIC_DRAW) = 0;
	//-------------------------------------------------------------------------

protected:
	//-------------------------------------------------------------------------
	// PROTECTED MEMBERS
	//-------------------------------------------------------------------------
	// Made protected to enforce creation and deletion via BufferManager
	Buffer()
	{
	}
	virtual ~Buffer()
	{
	}
	//-------------------------------------------------------------------------
};

} // namespace wolf

#endif
