#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "classes/classObject.h"


const int windowWidth = 1000;
const int windowHeight = 1000;
using namespace std;

int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Gravity Simulation", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glViewport(0, 0, windowWidth, windowHeight);

    //Matrix Setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Mass, Radius, Position, Velocity, Acceleration, Color
    Object earth("Earth", 5.972e24, 0.4f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f});
    Object moon("Moon", 7.34767309e22, 0.1f, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        earth.draw();
        moon.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
