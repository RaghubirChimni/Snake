// Raghubir Chimni
// Application.cpp 
// 7/31/2020

#include <windows.h>
#include <winuser.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "Game.h"
#include <chrono>
#include <thread>


#define WIDTH 40
#define HEIGHT 40

extern short direction;

bool gameOver = false;

int score = 0;

void initialize()
{
    glClear(GL_COLOR_BUFFER_BIT);    
    glClearColor(0, 0, 0, 1);   
    initializeGrid(WIDTH, HEIGHT);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        
        if (key == GLFW_KEY_W)
        {
            if (direction != DOWN)
                direction = UP;
        }
        else if (key == GLFW_KEY_S)
            {
                if (direction != UP)
                    direction = DOWN;
            }
        else if (key == GLFW_KEY_D)
        {
            if (direction != LEFT)
                direction = RIGHT;
        }
        else if (key == GLFW_KEY_A)
        {
            if (direction != RIGHT)
                direction = LEFT;
        }
        
    }
    
}

int main(int argc, char* argv[])
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 500, "SNAKE", NULL, NULL);


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    
    
    while (!glfwWindowShouldClose(window))
    {
        // display callback
        initialize();
        drawGrid();
        drawSnake();
        drawFood();
        glfwSwapBuffers(window);

        // display score if game is over
        if (gameOver)
        {
            char scoreC[10];
            _itoa_s(score, scoreC, 10);
            
            char msg[100] = "Your score: ";
            strcat_s(msg, scoreC);
           
            MessageBoxA(0, msg,"GAME OVER", MB_OK |MB_SYSTEMMODAL);
            exit(0);
        }

        // reshape callback
        glViewport(0, 0, (GLsizei)500, (GLsizei)500);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // to limit FPS
        sleep_for(nanoseconds(50000000));

        // keyboard callback
        glfwSetKeyCallback(window, key_callback);

        sleep_for(nanoseconds(50000000));

        /* Poll for and process events */
        glfwPollEvents();

    }
    
    glfwTerminate();
    
    return 0;
}
