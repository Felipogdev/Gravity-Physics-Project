
#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

const int screenWidth = 1000;
const int screenHeight = 1000;

int main() {
  if (!glfwInit()) {
    cout << "Failed to initialize GLFW" << endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Gravity Simulation", NULL, NULL);
  if (window == NULL) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //BG color
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  //Area to render the window
  glViewport(0, 0, screenWidth, screenHeight);

  //Matrix setup
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float centerX = 0.0f;
  float centerY = 0.0f;
  float radius = 0.5f;
  int res = 100;
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= res; i++) {
      float angle = 2.0f * M_PI * float(i) / float(res);
      float x = radius * cos(angle);
      float y = radius * sin(angle);
      glVertex2f(centerX + x, centerY + y);
    }

    glEnd();

    glFlush();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
