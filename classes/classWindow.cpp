#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <vector>
#include "window.hpp"
#include "classPhysics.hpp"
#include "classObject.hpp"

Physics physics(6.67430e-11, 1e-10);

Window::Window(std::string name, int width, int height, std::string backgroundPath)
    : name(name), width(width), height(height), backgroundPath(backgroundPath) {}
// Getters
std::string Window::getName() const { return name; }
int Window::getWidth() const { return width; }
int Window::getHeight() const { return height; }
std::string Window::getBackgroundPath() const { return backgroundPath; }

// Setters
void Window::setName( std::string title) { this->name = title; }
void Window::setWidth(int width) { this->width = width; }
void Window::setHeight(int height) { this->height = height; }
void Window::setBackgroundPath( std::string backgroundPath) { this->backgroundPath = backgroundPath; }

void Window::createWindow( std::vector<Object>& objects) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    GLFWwindow* window = glfwCreateWindow(this->width, this->height, this->name.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, this->width, this->height);

    // Matrix Setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //fovY, aspect, zNear, zFar
    gluPerspective(100.0f, (float)this->width / (float)this->height, 0.1f, 100.0f);
    glTranslatef(0.0f, 0.0f, -5.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        physics.simulate(objects);

        for(auto& object : objects) {
            object.draw();
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}


