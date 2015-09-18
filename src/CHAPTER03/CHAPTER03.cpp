#include <sb6.h>
#include <math.h>

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
#ifdef MOVE_ALONE
	void render(double currentTime)
	{
		const GLfloat color[] = {0.0f, 0.2f, 0.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(this->prog);
		GLfloat offset[] = {sin(currentTime) * 0.5, cos(currentTime) * 0.5, 0.0, 0.0};
		glVertexAttrib4fv(0, offset);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
#else
	/*
	Key board animation.
	*/
	void render(double currentTime)
	{
		static GLfloat offset[] = {0.0, 0.0, 0.0, 0.0};
		const GLfloat color[] = {0.0f, 0.2f, 0.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(this->prog);

		if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
			offset[1] += 0.01;
		if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
			offset[1] -= 0.01;
		if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
			offset[0] -= 0.01;
		if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
			offset[0] += 0.01;

		glVertexAttrib4fv(0, offset);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
#endif
	


	GLuint compile_shader(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] = 
		{
			"#version 430 core													\n"
			"																	\n"
			"layout (location=0) in vec4 offset;								\n"
			"void main(void)													\n"
			"{																	\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4(-0.25, -0.25, 0.5, 1.0),	\n"
			"									 vec4(0.25, 0.25, 0.5, 1.0));	\n"
			"																	\n"
			"	gl_Position = vertices[gl_VertexID] + offset;					\n"
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

int main(int argc, const char ** argv)              
{                                                   
    my_application *app = new my_application;       
    app->run(app);                                  
    delete app;                                     
    return 0;                                       
}

//DECLARE_MAIN(my_application);
