#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
struct ShaderSrc
{
	std::string vertexShader;
	std::string fragmentShader;
};

static ShaderSrc getShaders(const std::string& path) {
	
	enum class shaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};
	
	std::stringstream ss[2];
	std::fstream shaderPath(path);
	std::string line;
	shaderType myType = shaderType::NONE;
	//int myType;
	while (std::getline(shaderPath,line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				 myType = shaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				myType = shaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)myType] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };
}
unsigned int compileShader(int type,const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	// Shader checking
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = new char[length];
		std::vector<char> vec;
		vec.resize(length);
		glGetShaderInfoLog(id, length, &length, msg);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader" << std::endl;
		std::cout << msg << "\n";
		glDeleteShader(id);
		return 0;
	}
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
	
	//glDeleteShader(vs);
	//glDeleteShader(fs);
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
    
	float poses[12] = {
		-0.5f,-0.5f, // 0
		 0.5f,-0.5f, // 1
		 0.5f,0.5f,  // 2
		 -0.5f,0.5f  // 3
	};

	unsigned int indcies[6] = {
	0, 1 , 2,
	0, 3 , 2
	};
    // Create Handler for the buffer
    GLuint handler;
    // Create one buffer and give me the 
	glGenBuffers(1, &handler);
	glBindBuffer(GL_ARRAY_BUFFER, handler);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), poses, GL_STATIC_DRAW);
    
	GLuint ib;
	// Create one buffer and give me the 
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indcies, GL_STATIC_DRAW);

	//glClearColor(1, 1, 1, 1);
	/* Loop until the user closes the window */
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE ,sizeof(float) * 2,0);
	std::string shaderPath(R"(E:\cpp-projects\video-app\res\shader\basic.shader)");
	ShaderSrc Shaders = getShaders(shaderPath);
	
	unsigned int shader = createBuffer(Shaders.vertexShader, Shaders.fragmentShader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);

	glfwTerminate();
    
    return 0;
}
