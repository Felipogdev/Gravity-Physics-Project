#include <vector>
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "classObject.hpp"
#include <string>


Window::Window(std::string name, int width, int height, std::string backgroundPath)
    : name(name), width(width), height(height), backgroundPath(backgroundPath) {}
// Getters
std::string Window::getName() const { return name; }
int Window::getWidth() const { return width; }
int Window::getHeight() const { return height; }
std::string Window::getBackgroundPath() const { return backgroundPath; }

// Setters
void Window::setName(const std::string title) { this->name = title; }
void Window::setWidth(int width) { this->width = width; }
void Window::setHeight(int height) { this->height = height; }
void Window::setBackgroundPath(const std::string backgroundPath) { this->backgroundPath = backgroundPath; }

void Window::createWindow() {
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
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::renderObjects(const std::vector<Object>& objects) {
  for(const auto& object : objects) {
    object.draw();

  }
}

