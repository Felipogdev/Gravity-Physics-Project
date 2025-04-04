#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

class Window {
public:
  Window(std::string name, int width, int height);
  
  // Getters
  std::string getName() const;
  int getWidth() const;
  int getHeight() const;

  // Setters
  void setName(const std::string title);
  void setWidth(int width);
  void setHeight(int height);

  void createWindow();

private:
  std::string name;
  int width;
  int height;
};

#endif
