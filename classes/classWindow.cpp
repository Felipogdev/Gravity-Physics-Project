#include <vector>
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "classObject.hpp"
#include <string>
#include <vector>




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
    glOrtho(-3, 3, -3, 3, -3, 3);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //std::vector<Object> objects;
    //objects.push_back(Object("Earth", 5.972e24, 0.1f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, ""));
    //objects.push_back(Object("Mars", 5.972e24, 0.1f, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f}, ""));


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for( auto& object : objects) {

            object.draw();
        }

        //this->renderObjects(objects);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}


