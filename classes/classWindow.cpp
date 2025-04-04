#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "classObject.h"

Window::Window(std::string name, int width, int height) : name(name), width(width), height(height) {}

// Getters
std::string Window::getName() const { return name; }
int Window::getWidth() const { return width; }
int Window::getHeight() const { return height; }

// Setters
void Window::setName(const std::string title) { this->name = title; }
void Window::setWidth(int width) { this->width = width; }
void Window::setHeight(int height) { this->height = height; }

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
    Object earth("earth", 5.972e24, 0.4f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, "");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        earth.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
  
  Window window("My Window", 800, 800);
  window.createWindow();
}
