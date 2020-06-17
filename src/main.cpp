#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

unsigned int compileShader(int type,const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}
unsigned int createBuffer(const std::string& vertexShader, const std::string& fragmentShader) {
		
	unsigned int  program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	//auto vs = glCompileShader()

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	
	return program;
}

int main(int argc, char const *argv[])
{
    GLFWwindow* window;
    if(!glfwInit()){
        std::cout << "Couldn't initilize GLFW\n";
        return 1;
    }

    window = glfwCreateWindow(640,480,"Hello opengl",NULL,NULL);
    if(!window){
        std::cout << "Couldn't create window\n";
		return EXIT_FAILURE;
    }

    //// Create Buffer
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error initialize glew\n";
		return EXIT_FAILURE;
	}
	printf("%s\n", glGetString(GL_VERSION));
    
	float poses[6] = {
		-0.5f,-0.5f,
		 0.0f,-0.5f,
		 -0.5f,0.5f
	};

	//GLuint VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

    // Create Handler for the buffer
    GLuint handler;
    // Create one buffer and give me the 
	glGenBuffers(1, &handler);
	glBindBuffer(GL_ARRAY_BUFFER, handler);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), poses, GL_STATIC_DRAW);
    
	//glClearColor(1, 1, 1, 1);
	/* Loop until the user closes the window */
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE ,sizeof(float) * 2,0);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"void main()\n"
		"{\n"
		" gl_Position = position;"
		"}\n";
	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"void main()\n"
		"{\n"
		" color = vec4(1.0,0.0,0.0,1.0);"
		"}\n";

	unsigned int shader = createBuffer(vertexShader, fragmentShader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
    
    return 0;
}
