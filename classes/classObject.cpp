#include "classObject.hpp"
#include <cmath>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <string>

Object::Object(std::string name, double mass, double radius, std::array<double, 3> position, std::array<double, 3> velocity, std::array<double, 3> acceleration, std::array<float, 4> color, std::string texturePath)
    : name(name), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(acceleration), color(color), texturePath(texturePath) {}

// Getters
std::string Object::getName() const { return name; }
double Object::getMass() const { return mass; }
double Object::getRadius() const { return radius; }
std::array<double, 3> Object::getPosition() const { return position; }
std::array<double, 3> Object::getVelocity() const { return velocity; }
std::array<double, 3> Object::getAcceleration() const { return acceleration; }
std::array<float, 4> Object::getColor() const { return color; }
std::string Object::getTexturePath() const { return texturePath; }

// Setters
void Object::setName(const std::string& name) { this->name = name; }
void Object::setMass(double mass) { this->mass = mass; }
void Object::setRadius(double radius) { this->radius = radius; }
void Object::setPosition(std::array<double, 3> position) { this->position = position; }
void Object::setVelocity(std::array<double, 3> velocity) { this->velocity = velocity; }
void Object::setAcceleration(std::array<double, 3> acceleration) { this->acceleration = acceleration; }
void Object::setColor(std::array<float, 4> color) { this->color = color; }
void Object::setTexturePath(const std::string& texturePath) { this->texturePath = texturePath; }

void Object::generateSphere(std::vector<float>& vertices, int resolutionTheta, int resolutionPhi) const {
    for (int i = 0; i <= resolutionPhi; i++) {
        float phi = M_PI * float(i) / float(resolutionPhi); // POLAR (0-PI)
        for (int j = 0; j <= resolutionTheta; j++) {
            float theta = 2.0f * M_PI * float(j) / float(resolutionTheta); // AZIMUTAL (0-2PI)
            
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            // Translate the object position (including x, y, z)
            x += position[0];
            y += position[1];
            z += position[2];

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
}

void Object::draw(int resolutionTheta, int resolutionPhi) const {
    std::vector<float> vertices;
    generateSphere(vertices, resolutionTheta, resolutionPhi);

    glColor4f(color[0], color[1], color[2], color[3]);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < resolutionPhi; ++i) {
        for (int j = 0; j < resolutionTheta; ++j) {

            int first = (i * (resolutionTheta + 1)) + j;
            int second = ((i + 1) * (resolutionTheta + 1)) + j;
            int third = ((i + 1) * (resolutionTheta + 1)) + ((j + 1) % (resolutionTheta + 1));
            int fourth = (i * (resolutionTheta + 1)) + ((j + 1) % (resolutionTheta + 1));

            // First triangle
            glVertex3f(vertices[first * 3], vertices[first * 3 + 1], vertices[first * 3 + 2]);
            glVertex3f(vertices[second * 3], vertices[second * 3 + 1], vertices[second * 3 + 2]);
            glVertex3f(vertices[third * 3], vertices[third * 3 + 1], vertices[third * 3 + 2]);

            // Second triangle
            glVertex3f(vertices[first * 3], vertices[first * 3 + 1], vertices[first * 3 + 2]);
            glVertex3f(vertices[third * 3], vertices[third * 3 + 1], vertices[third * 3 + 2]);
            glVertex3f(vertices[fourth * 3], vertices[fourth * 3 + 1], vertices[fourth * 3 + 2]);
        }
    }
    glEnd();
}

