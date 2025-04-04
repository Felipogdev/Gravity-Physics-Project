#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "classes/classObject.h"
#include "classes/window.h"

const int windowWidth = 1000;
const int windowHeight = 1000;
using namespace std;

int main() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    Window window ("Gravity Simulator", windowWidth, windowHeight);

    window.createWindow();

    glfwTerminate();
    return 0;
}
