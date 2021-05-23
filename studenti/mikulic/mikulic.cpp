#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>

#include "pathconfig.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <fstream>
#include <sstream>

#include "shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexbufferlayout.h"
#include "vertexarray.h"
#include "renderer.h"

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
//maknuti iz .gitignore sve foldere prije predaje!!!!!!!!!!!
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "mikulic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    unsigned int err = glewInit();
    if(err != GLEW_OK) {std::cout << "error\n"; return -1;}


    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
