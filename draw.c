#include "draw.h"


void init()
{
	GLint count = 0;
	GLint major_version = 0;
	GLint minor_version = 0;

	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint tessellation_control_shader;
	GLuint tessellation_evaluation_shader;
	GLuint geometry_shader;

	GLchar *vertex_shader_source;
	GLchar *fragment_shader_source;
	GLchar *tessellation_control_shader_source;
	GLchar *tessellation_evaluation_shader_source;
	GLchar *geometry_shader_source;
	
	LOADSHADERFROMFILE(vertex_shader_source, "vertex.glsl");
	LOADSHADERFROMFILE(fragment_shader_source, "fragment.glsl");
	LOADSHADERFROMFILE(tessellation_control_shader_source, "tessellation_control.glsl");
	LOADSHADERFROMFILE(tessellation_evaluation_shader_source, "tessellation_evaluation.glsl");
	LOADSHADERFROMFILE(geometry_shader_source, "geometry.glsl");

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
	LOADOPENGLPROC(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
	LOADOPENGLPROC(PFNGLPATCHPARAMETERIPROC, glPatchParameteri);
	LOADOPENGLPROC(PFNGLDETACHSHADERPROC, glDetachShader);
	LOADOPENGLPROC(PFNGLGETSTRINGIPROC, glGetStringi);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	free(vertex_shader_source);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	free(fragment_shader_source);
	
	tessellation_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tessellation_control_shader, 1, &tessellation_control_shader_source, NULL);
	glCompileShader(tessellation_control_shader);
	free(tessellation_control_shader_source);

	tessellation_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tessellation_evaluation_shader, 1, &tessellation_evaluation_shader_source, NULL);
	glCompileShader(tessellation_evaluation_shader);
	free(tessellation_evaluation_shader_source);

	geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry_shader, 1, &geometry_shader_source, NULL);
	glCompileShader(geometry_shader);
	free(geometry_shader_source);
	
	rendering_program = glCreateProgram();
	glAttachShader(rendering_program, vertex_shader);
	glAttachShader(rendering_program, fragment_shader);
	glAttachShader(rendering_program, tessellation_control_shader);
	glAttachShader(rendering_program, tessellation_evaluation_shader);
	glAttachShader(rendering_program, geometry_shader);
	glLinkProgram(rendering_program);

	glDetachShader(rendering_program, vertex_shader);
	glDetachShader(rendering_program, fragment_shader);
	glDetachShader(rendering_program, tessellation_control_shader);
	glDetachShader(rendering_program, tessellation_evaluation_shader);
	glDetachShader(rendering_program, geometry_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(tessellation_control_shader);
	glDeleteShader(tessellation_evaluation_shader);
	glDeleteShader(geometry_shader);

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(1.5);

	printf("Version string:\n\t%s\n", glGetString(GL_VERSION));
	glGetIntegerv(GL_MAJOR_VERSION, &major_version);
	glGetIntegerv(GL_MINOR_VERSION, &minor_version);
	printf("Version decimal:\n\t%d.%d\n", major_version, minor_version);
	printf("Vendor:\n\t%s\n", glGetString(GL_VENDOR));
	printf("Renderer:\n\t%s\n", glGetString(GL_RENDERER));
	printf("GLSL:\n\t%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	puts("Supported GLSL versions:");
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &count);
	for (; count; count--)
	{
		putchar('\t');
		puts((char*)glGetStringi(GL_SHADING_LANGUAGE_VERSION, count - 1));
	}

	puts("Extensions list:");
	glGetIntegerv(GL_NUM_EXTENSIONS, &count);
	for(; count; count--)
	{
		putchar('\t');
		puts((char*)glGetStringi(GL_EXTENSIONS, count - 1));
	}
}

void update()
{
	double time = GetSecMsecTime();

	GLfloat color[] = { 
		(float)sin(time) * 0.5f + 0.5f, 
		(float)cos(time) * 0.5f + 0.5f, 
		0.0f, 
		1.0f 
	};

	GLfloat attrib[] = {
		(float)sin(time) * 0.5f, 
		(float)cos(time) * 0.6f, 
		0.0f, 
		0.0f 
	};

	glClearBufferfv(GL_COLOR, 0, color);
	glUseProgram(rendering_program);
	glVertexAttrib4fv(0, attrib);
	glDrawArrays(GL_PATCHES, 0, 3);
	swap_buffers();
}

void cleanup()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);				//тут зависает при выключении
}

GLchar *LoadFromFile(char *filename)
{
	FILE *file;
	long int size;
	GLchar* result;

	if (!(file = fopen(filename, "rb"))) return NULL;

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (!(result = (GLchar *)malloc(size + 1)))
	{
		fclose(file);
		return NULL;
	}

	fread(result, 1, size, file);
	result[size] = '\0';

	fclose(file);

	return result;
}

double GetSecMsecTime()
{
	SYSTEMTIME systemtime;
	
	GetSystemTime(&systemtime);

	return ((double)time(NULL)) + ((double)systemtime.wMilliseconds / 1000.0f);
}
