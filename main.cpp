#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "classes/classObject.hpp"
#include "classes/window.hpp"
#include <vector>

using namespace std;
const int windowWidth = 1000;
const int windowHeight = 1000;

int main() {

//Name, Mass, Radius, Position, Velocity, Acceleration, Color, Texture
    std::vector<Object> objects;
    objects.push_back(Object("Earth", 5.972e24, 0.1f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, ""));
    objects.push_back(Object("Mars", 5.972e24, 0.1f, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.0f}, ""));
    objects.push_back(Object("Moon", 5.972e24, 0.1f, {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 0.0f}, ""));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    Window window ("Gravity Simulator", windowWidth, windowHeight, "");
    window.createWindow(objects);

     glfwTerminate();
    return 0;
}

