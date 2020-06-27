#pragma once
#include <Renderer.h>
namespace Impl {
	class VertexBuffer {
	public:
		VertexBuffer(void* data, unsigned int size);
		~VertexBuffer();

		void bind();
		void unbind();
	private:
		unsigned int mBufferId;
	};
}