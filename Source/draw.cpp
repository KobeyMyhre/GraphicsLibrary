#include "glinc.h"
#include "graphics\draw.h"
#include "graphics\RenderObjects.h"


void draw(const FrameBufer & f, const Shader & s, const Geometry & g)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	glViewport(0, 0, f.width, f.height);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);*/


}

void setUniform(const Shader & shader, int location, float value)
{
	glProgramUniform1f(shader.handle, location, value);
}

void setUniform(const Shader & shader, int location, int value)
{
	glProgramUniform1i(shader.handle, location, value);
}

void setUniform(const Shader & shader, int location, double value)
{
	glProgramUniform1d(shader.handle, location, value);
}

void setUniform(const Shader & shader, int location, const Texture & value, int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shader.handle, location, slot);


}

void clearFrameBuffer(const FrameBufer & fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
