#include <sb6.h>
#include <math.h>

#define EX2_9

#if defined(EX2_6)
class my_application : public sb6::application
{
public:
	GLuint prog;
	GLuint vertex_array_object;

	void startup()
	{
		prog = compile_shader();
		glGenVertexArrays(1, &this->vertex_array_object);
		glBindVertexArray(this->vertex_array_object);
	}

	void shoutdown()
	{
		glDeleteVertexArrays(1, &this->vertex_array_object);
		glDeleteProgram(this->prog);
	}

	void render(double currentTime)
	{
		const GLfloat color[] = {1.0f, 0.5+0.5*sin(3.0*currentTime), 0.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);
		
		glUseProgram(this->prog);
		glPointSize(20.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}

	GLuint compile_shader(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] = 
		{
			"#version 430 core								\n"
			"												\n"
			"void main(void)								\n"
			"{												\n"
			"	gl_Position = vec4(0.0, 0.0, 0.5, 1.0);		\n"
			"}												\n"
		};

		static const GLchar * fragment_shader_source[] = 
		{
			"#version 430 core								\n"
			"												\n"
			"out vec4 color;								\n"
			"												\n"
			"void main(void)								\n"
			"{												\n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);			\n"
			"}												\n"
		};
		GLint status;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Compiling vertex shader failed\n");
			glDeleteShader(vertex_shader);
			return -1;//TODO : right?
		}

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Compiling fragment shader failed\n");
			glDeleteShader(fragment_shader);
			return -1;//TODO : right?
		}

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Link failed\n");
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteProgram(program);
			return -1;
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}
};
#elif defined(EX2_9)
class my_application : public sb6::application
{
public:
	GLuint prog;
	GLuint vertex_array_object;

	void startup()
	{
		prog = compile_shader();
		glGenVertexArrays(1, &this->vertex_array_object);
		glBindVertexArray(this->vertex_array_object);
	}

	void shoutdown()
	{
		glDeleteVertexArrays(1, &this->vertex_array_object);
		glDeleteProgram(this->prog);
	}

	void render(double currentTime)
	{
		const GLfloat color[] = {0.0f, 0.2f, 0.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);
		
		glUseProgram(this->prog);
	
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	GLuint compile_shader(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] = 
		{
			"#version 430 core													\n"
			"																	\n"
			"void main(void)													\n"
			"{																	\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4(-0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4(0.25, 0.25, 0.5, 1.0));	\n"
			"																	\n"
			"	gl_Position = vertices[gl_VertexID];							\n"
			"}																	\n"
		};

		static const GLchar * fragment_shader_source[] = 
		{
			"#version 430 core								\n"
			"												\n"
			"out vec4 color;								\n"
			"												\n"
			"void main(void)								\n"
			"{												\n"
			"	color = vec4(0.0, 0.8, 1.0, 1.0);			\n"
			"}												\n"
		};
		GLint status;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Compiling vertex shader failed\n");
			glDeleteShader(vertex_shader);
			return -1;//TODO : right?
		}

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Compiling fragment shader failed\n");
			glDeleteShader(fragment_shader);
			return -1;//TODO : right?
		}

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if(status == GL_FALSE)
		{
			printf("Link failed\n");
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);
			glDeleteProgram(program);
			return -1;
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}
};
#else

#endif


DECLARE_MAIN(my_application);
