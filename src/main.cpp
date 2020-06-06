#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(int argc, char const *argv[])
{
    GLFWwindow* window;
    if(!glfwInit()){
        std::cout << "Couldn't initilize GLFW\n";
        return 1;
    }

    window = glfwCreateWindow(640,480,"Hellow opengl",NULL,NULL);
    if(!window){
        std::cout << "Couldn't create window\n";
    }

    // Create Buffer
    unsigned char* data = new unsigned char[100*100*3];
    for (size_t i = 0; i < 100; ++i)
    {
        for (size_t j = 0; j < 100; ++j)
        {
            data[i * 100 * 3 + j * 3]     = 0xff;
            data[i * 100 * 3 + j * 3 + 1] = 0x00;
            data[i * 100 * 3 + j * 3 + 2] = 0x00;
        }
         
    }
    for (size_t i = 25; i < 75; ++i)
    {    
        for (size_t j = 25; j < 75; ++j)
        {
            data[i * 100 * 3 + j * 3]     = 0x00;
            data[i * 100 * 3 + j * 3 + 1] = 0x00;
            data[i * 100 * 3 + j * 3 + 2] = 0xff;
        }
        
    }
    // Create Handler for the texture
    GLuint tx_handler;
    // Create one texture and give me the 
    glGenTextures(1,&tx_handler);
    glBindTexture(GL_TEXTURE_2D,tx_handler);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,100,100,0,GL_RGB,GL_UNSIGNED_BYTE,data);

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        int w,h;
        glfwGetFramebufferSize(window,&w,&h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        
        glMatrixMode(GL_MODELVIEW);
        // Render here 
        // glDrawPixels(100,100,GL_RGB,GL_UNSIGNED_BYTE,data);
        // glfwSwapBuffers(window);
        // Wait from event from user to close
        glfwWaitEvents();
    }
    
    return 0;
}
