#include <IndexBuffer.h>

namespace Impl {
	IndexBuffer::IndexBuffer(void* data, unsigned int size) {
		glGenBuffers(1, &mBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &mBufferId);
	}
	void IndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
	}
	void IndexBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}