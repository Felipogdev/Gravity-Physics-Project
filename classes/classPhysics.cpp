#include "classObject.hpp"
#include "classPhysics.hpp"
#include <math.h>
#include <array>
#include <vector>

Physics::Physics(double gravityConstant, double deltaTime) 
  : gravityConstant(gravityConstant), deltaTime(deltaTime){}

// Getters
double Physics::getGravityConstant() const { return gravityConstant; }
double Physics::getDeltaTime() const { return deltaTime; }

//Setters
void Physics::setGravityConstant(double gravityConstant) { this->gravityConstant = gravityConstant; }
void Physics::setDeltaTime(double deltaTime) { this->deltaTime = deltaTime; }


void Physics::update(Object& object) {
    std::array<double, 3> position = object.getPosition();
    std::array<double, 3> velocity = object.getVelocity();

    for (int i = 0; i < 3; ++i) {
        position[i] += velocity[i] * deltaTime;
    }

    object.setPosition(position);

}

bool Physics::checkCollision(Object& object1, Object& object2) {
  double distanceSquared = 0.0;

  for (int i = 0; i < 3; ++i) {
    double distanceDifference = object1.getPosition()[i] - object2.getPosition()[i];
    distanceSquared += distanceDifference * distanceDifference;
  }

  double minDistance = object1.getRadius() + object2.getRadius();
  return distanceSquared <= (minDistance * minDistance);
}


