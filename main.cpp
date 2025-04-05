#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "classes/classObject.hpp"
#include "classes/window.hpp"

using namespace std;
const int windowWidth = 1000;
const int windowHeight = 1000;


int main() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    Window window ("Gravity Simulator", windowWidth, windowHeight, "");

    window.createWindow();
     glfwTerminate();
    return 0;
}
