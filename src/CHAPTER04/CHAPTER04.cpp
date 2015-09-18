#include <sb6.h>
#include <math.h>

class my_application : public sb6::application
{
public:
	GLuint prog;
	GLuint vertex_array_object;

	void startup()
	{

	}

	void shoutdown()
	{

	}

	void render(double currentTime)
	{

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
