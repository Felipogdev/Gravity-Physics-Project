#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include <vector>


using namespace std;

class Object {
private:
    string name;
    double mass; // in kg
    double radius; // in meters
    array<double, 2> position; // {x, y}
    array<double, 2> velocity; // {vx, vy}
    array<double, 2> acceleration; // {ax, ay}
    array<float, 4> color; // {R, G, B, A}

public:
  Object(string name, double mass, double radius, array<double, 2> position, array<double, 2> velocity, array<double,2> acceleration, array<float, 4> color)
    : name(name), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(acceleration), color(color) {}

//Getters
string getName() const { return name; }
double getMass() const { return (mass); }
double getRadius() const { return (radius); }
array<double, 2> getPosition() const { return position; }
array<double, 2> getVelocity() const { return velocity; }
array<double, 2> getAcceleration() const { return acceleration; }
array<float, 4> getColor() const { return color; }

//Setters
void setName(string name) { this->name = name; }
void setMass(double mass) { this->mass = mass; }
void setRadius(double radius) { this->radius = radius; }
void setPosition(array<double, 2> position) { this->position = position; }
void setVelocity(array<double, 2> velocity) { this->velocity = velocity; }
void setAcceleration(array<double, 2> acceleration) { this->acceleration = acceleration; }
void setColor(array<float, 4> color) { this->color = color; }

//Methods
void generateSpere(vector<float>& vertices, int resolutionTheta, int resolutionPhi) {
  for (int i = 0; i <= resolutionPhi; i++) {
    float phi = M_PI * float(i) / float(resolutionPhi); //POLAR (0-PI)
        for (int j = 0; j <= resolutionTheta; j++) {
          float theta = 2.0f * M_PI * float(j) / float(resolutionTheta); //AZIMUTAL (0-2PI)
          
          float x = radius * sin(phi) * cos(theta);
          float y = radius * sin(phi) * sin(theta);
          float z = radius * cos(phi);
          
          //Translação do objeto 
          x += position[0];
          y += position[1];

          vertices.push_back(x);
          vertices.push_back(y);
          vertices.push_back(z);
        }
  }
}

void draw(int resolutionTheta = 100, int resolutionPhi = 100) {
  vector<float> vertices;
  generateSpere(vertices, resolutionTheta, resolutionPhi);

  glColor4f(color[0], color[1], color[2], color[3]);

  glBegin(GL_TRIANGLES);

  for (int i = 0; i < resolutionPhi; ++i) {
    for (int j = 0; j < resolutionTheta; ++j) {

      int first = (i * (resolutionTheta + 1)) + j;
      int second = ((i + 1) * (resolutionTheta + 1)) + j;
      int third = ((i + 1) * (resolutionTheta + 1)) + (j + 1) % (resolutionTheta + 1);
      int fourth = (i * (resolutionTheta + 1)) + (j + 1) % (resolutionTheta + 1);

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
};




