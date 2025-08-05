#ifndef CLASSGRID_HPP
#define CLASSGRID_HPP

#include <vector>
#include <array>
#include <GLFW/glfw3.h>
#include "classObject.hpp"

class Grid {
private:
    int gridSize;  // Number of cells in each dimension
    float cellSize;  // Size of each cell
    std::array<float, 4> color;  // Grid color
    std::vector<std::vector<std::array<float, 3>>> vertices;  // Grid vertices
    std::vector<std::vector<std::array<float, 3>>> velocities;  // Velocity of each vertex
    std::vector<std::vector<float>> masses;  // Mass of each vertex
    unsigned int VAO, VBO;  // OpenGL objects

public:
    Grid(int gridSize = 30, float cellSize = 0.5f, std::array<float, 4> color = {0.5f, 0.5f, 0.5f, 1.0f});
    
    // Getters
    int getGridSize() const;
    float getCellSize() const;
    std::array<float, 4> getColor() const;
    
    // Setters
    void setGridSize(int size);
    void setCellSize(float size);
    void setColor(std::array<float, 4> color);
    
    // Methods
    void initialize();
    void update(const std::vector<Object>& objects, double deltaTime);
    void draw() const;
    void applyGravity(const Object& object, double deltaTime);
};

#endif 