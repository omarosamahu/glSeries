#include <VertexBuffer.h>

namespace Impl {
	VertexBuffer::VertexBuffer(void* data, unsigned int size) {
		glGenBuffers(1, &mBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &mBufferId);
	}
	void VertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
	}
	void VertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
}