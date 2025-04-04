#ifndef CLASS_OBJECT_H
#define CLASS_OBJECT_H

#include <array>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

using namespace std;

class Object {
private:
    double mass; // KG
    double radius; // M
    array<double, 3> position; // {x, y, z}
    array<double, 2> velocity; // {vx, vy} m/s
    array<double, 2> acceleration; // {ax, ay} m/s^2
    array<float, 4> color; // {R, G, B, A}

public:
    Object(double mass, double radius, array<double, 3> position, array<double, 2> velocity, array<double, 2> acceleration, array<float, 4> color);

    // Getters
    double getMass() const;
    double getRadius() const;
    array<double, 3> getPosition() const;
    array<double, 2> getVelocity() const;
    array<double, 2> getAcceleration() const;
    array<float, 4> getColor() const;

    // Setters
    void setMass(double mass);
    void setRadius(double radius);
    void setPosition(array<double, 3> position);
    void setVelocity(array<double, 2> velocity);
    void setAcceleration(array<double, 2> acceleration);
    void setColor(array<float, 4> color);

    // Methods
    void generateSphere(vector<float>& vertices, int resolutionTheta, int resolutionPhi);
    void draw(int resolutionTheta = 100, int resolutionPhi = 100);
};

#endif
