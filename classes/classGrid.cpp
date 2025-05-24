#include "classGrid.hpp"
#include <cmath>

Grid::Grid(int gridSize, float cellSize, std::array<float, 4> color)
    : gridSize(gridSize), cellSize(cellSize), color(color) {
    initialize();
}

// Getters
int Grid::getGridSize() const { return gridSize; }
float Grid::getCellSize() const { return cellSize; }
std::array<float, 4> Grid::getColor() const { return color; }

// Setters
void Grid::setGridSize(int size) { 
    gridSize = size;
    initialize();
}

void Grid::setCellSize(float size) { 
    cellSize = size;
    initialize();
}

void Grid::setColor(std::array<float, 4> newColor) { color = newColor; }

void Grid::initialize() {
    // Initialize vertices
    vertices.resize(gridSize + 1, std::vector<std::array<float, 3>>(gridSize + 1));
    velocities.resize(gridSize + 1, std::vector<std::array<float, 3>>(gridSize + 1));
    masses.resize(gridSize + 1, std::vector<float>(gridSize + 1, 1.0f));

    // Calculate grid dimensions
    float totalSize = gridSize * cellSize;
    float startX = -totalSize / 2.0f;
    float startZ = -totalSize / 2.0f;

    // Initialize vertex positions
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            vertices[i][j] = {
                startX + i * cellSize,
                0.0f,  // Y position at 0
                startZ + j * cellSize - 10.0f  // Move grid back in z-axis
            };
            velocities[i][j] = {0.0f, 0.0f, 0.0f};
        }
    }
}

void Grid::update(const std::vector<Object>& objects, double deltaTime) {
    // Reset velocities
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            velocities[i][j] = {0.0f, 0.0f, 0.0f};
        }
    }

    // Apply gravity from each object
    for (const auto& object : objects) {
        applyGravity(object, deltaTime);
    }

    // Update vertex positions
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            vertices[i][j][0] += velocities[i][j][0] * deltaTime;
            vertices[i][j][1] += velocities[i][j][1] * deltaTime;
            vertices[i][j][2] += velocities[i][j][2] * deltaTime;
        }
    }
}

void Grid::applyGravity(const Object& object, double deltaTime) {
    const double G = 6.67430e-11;  // Gravitational constant
    const std::array<double, 3>& objectPos = object.getPosition();
    double objectMass = object.getMass();

    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            // Calculate distance vector
            std::array<float, 3> direction = {
                static_cast<float>(objectPos[0]) - vertices[i][j][0],
                static_cast<float>(objectPos[1]) - vertices[i][j][1],
                static_cast<float>(objectPos[2]) - vertices[i][j][2]
            };

            // Calculate distance
            float distance = std::sqrt(
                direction[0] * direction[0] +
                direction[1] * direction[1] +
                direction[2] * direction[2]
            );

            if (distance < 0.0001f) continue;  // Avoid division by zero

            // Normalize direction
            direction[0] /= distance;
            direction[1] /= distance;
            direction[2] /= distance;

            // Calculate gravitational force
            float force = G * (objectMass * masses[i][j]) / (distance * distance);

            // Update velocity
            velocities[i][j][0] += direction[0] * force * deltaTime;
            velocities[i][j][1] += direction[1] * force * deltaTime;
            velocities[i][j][2] += direction[2] * force * deltaTime;
        }
    }
}

void Grid::draw() const {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0f);  // Thinner lines for background grid
    
    // Draw main grid lines with lower opacity
    glColor4f(color[0], color[1], color[2], color[3] * 0.3f);  // Reduce opacity
    
    // Draw horizontal lines
    for (int i = 0; i <= gridSize; ++i) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= gridSize; ++j) {
            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
        }
        glEnd();
    }

    // Draw vertical lines
    for (int j = 0; j <= gridSize; ++j) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= gridSize; ++i) {
            glVertex3f(vertices[i][j][0], vertices[i][j][1], vertices[i][j][2]);
        }
        glEnd();
    }
    
    // Draw center lines with different color and higher opacity
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);  // Red color for center lines with medium opacity
    glLineWidth(2.0f);  // Slightly thicker for center lines
    
    // Draw center horizontal line
    glBegin(GL_LINE_STRIP);
    for (int j = 0; j <= gridSize; ++j) {
        glVertex3f(vertices[gridSize/2][j][0], vertices[gridSize/2][j][1], vertices[gridSize/2][j][2]);
    }
    glEnd();
    
    // Draw center vertical line
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= gridSize; ++i) {
        glVertex3f(vertices[i][gridSize/2][0], vertices[i][gridSize/2][1], vertices[i][gridSize/2][2]);
    }
    glEnd();
    
    glLineWidth(1.0f);  // Reset line width
    glDisable(GL_BLEND);
} 