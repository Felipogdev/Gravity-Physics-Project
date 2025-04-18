#ifndef CLASS_OBJECT_H
#define CLASS_OBJECT_H

#include <array>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class Object {
private:
    std::string name;
    double mass; // KG
    double radius; // M
    std::array<double, 3> position; // {x, y, z}
    std::array<double, 3> velocity; // {vx, vy, vz} m/s
    std::array<double, 3> acceleration; // {ax, ay, az} m/s^2
    std::array<float, 4> color; // {R, G, B, A}
    std::string texturePath;

public:
    Object(std::string name,double mass, double radius, std::array<double, 3> position, std::array<double, 3> velocity, std::array<double, 3> acceleration, std::array<float, 4> color, std::string texturePath = "");

    // Getters
    std::string getName() const;
    double getMass() const;
    double getRadius() const;
    std::array<double, 3> getPosition() const;
    std::array<double, 3> getVelocity() const;
    std::array<double, 3> getAcceleration() const;
    std::array<float, 4> getColor() const;
    std::string getTexturePath() const;

    // Setters
    void setName(const std::string& name);
    void setMass(double mass);
    void setRadius(double radius);
    void setPosition(std::array<double, 3> position);
    void setVelocity(std::array<double, 3> velocity);
    void setAcceleration(std::array<double, 3> acceleration);
    void setColor(std::array<float, 4> color);
    void setTexturePath(const std::string& texturePath);

    // Methods
    void generateSphere(std::vector<float>& vertices, int resolutionTheta, int resolutionPhi) const;
    void draw(int resolutionTheta = 100, int resolutionPhi = 100) const;
};

#endif
