#include "draw.h"


void init()
{
	GLuint vertex_shader;
	GLuint fragment_shader;

	GLchar *vertex_shader_source =
	{
		"#version 450 core \n"
		" \n"
		"void main(void) \n"
		"{ \n"
		" gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
		"} \n"
	};

	GLchar *fragment_shader_source =
	{
		"#version 450 core \n"
			" \n"
			"out vec4 color; \n"
			" \n"
			"void main(void) \n"
			"{ \n"
			" color = vec4(0.0, 0.8, 1.0, 1.0); \n"
			"} \n"
	};

	LOADOPENGLPROC(PFNGLSHADERSOURCEARBPROC, glShaderSource);
	LOADOPENGLPROC(PFNGLCREATESHADERPROC, glCreateShader);
	LOADOPENGLPROC(PFNGLCOMPILESHADERPROC, glCompileShader);
	LOADOPENGLPROC(PFNGLATTACHSHADERPROC, glAttachShader);
	LOADOPENGLPROC(PFNGLLINKPROGRAMPROC, glLinkProgram);
	LOADOPENGLPROC(PFNGLDELETESHADERPROC, glDeleteShader);
	LOADOPENGLPROC(PFNGLCREATEPROGRAMPROC, glCreateProgram);
	LOADOPENGLPROC(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
	LOADOPENGLPROC(PFNGLBINDVERTEXARRAYAPPLEPROC, glBindVertexArray);
	LOADOPENGLPROC(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
	LOADOPENGLPROC(PFNGLUSEPROGRAMPROC, glUseProgram);
	LOADOPENGLPROC(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
	LOADOPENGLPROC(PFNGLDELETEPROGRAMPROC, glDeleteProgram);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	rendering_program = glCreateProgram();
	glAttachShader(rendering_program, vertex_shader);
	glAttachShader(rendering_program, fragment_shader);
	glLinkProgram(rendering_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
}

void update()
{
	const GLfloat color[] = {1.0, 0.0, 0.0, 1.0};
	glClearBufferfv(GL_COLOR, 0, color);
	glUseProgram(rendering_program);
	glDrawArrays(GL_POINTS, 0, 1);
	swap_buffers();
}

void cleanup()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glDeleteVertexArrays(1, &vertex_array_object);
}
