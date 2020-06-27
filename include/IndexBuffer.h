#pragma once
#include <Renderer.h>
namespace Impl {
	class Index {
	public:
		IndexBuffer(void* data, unsigned int size);
		~IndexBuffer();

		void bind();
		void unbind();
	private:
		unsigned int mBufferId;
	};
}