#include "Renderer.h"

#include <GL/glew.h>

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) const
{
	indexBuffer.bind();

	glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);

}
