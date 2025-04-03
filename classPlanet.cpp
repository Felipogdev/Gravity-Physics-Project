#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>

using namespace std;

class Planet {
private:
    string name;
    double mass; // in kg
    double radius; // in meters
    array<double, 2> position; // {x, y}
    array<double, 2> velocity; // {vx, vy}
    array<double, 2> acceleration; // {ax, ay}

public:
  Planet(string name, double mass, double radius, array<double, 2> position, array<double, 2> velocity, array<double,2> acceleration)
    : name(name), mass(mass), radius(radius), position(position), velocity(velocity), acceleration(acceleration) {}

//Getters
string getName() const { return name; }
double getMass() const { return (mass); }
double getRadius() const { return (radius); }
array<double, 2> getPosition() const { return position; }
array<double, 2> getVelocity() const { return velocity; }
array<double, 2> getAcceleration() const { return acceleration; }

//Setters
void setName(string name) { this->name = name; }
void setMass(double mass) { this->mass = mass; }
void setRadius(double radius) { this->radius = radius; }
void setPosition(array<double, 2> position) { this->position = position; }
void setVelocity(array<double, 2> velocity) { this->velocity = velocity; }
void setAcceleration(array<double, 2> acceleration) { this->acceleration = acceleration; }

};



