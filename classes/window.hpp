#ifndef WINDOW_H
#define WINDOW_H

#include "classObject.hpp"
#include <vector>
#include <string>

class Window {
private:
  std::string name;
  int width;
  int height;
  std::string backgroundPath;

public:
  Window(std::string name, int width, int height, std::string backgroundPath = "");
  
  // Getters
  std::string getName() const;
  int getWidth() const;
  int getHeight() const;
  std::string getBackgroundPath() const;

  // Setters
  void setName(const std::string title);
  void setWidth(int width);
  void setHeight(int height);
  void setBackgroundPath(const std::string backgroundPath);

  void createWindow(const std::vector<Object>& objects);


};

#endif
