#ifndef CLASSPHYSICS_HPP
#define CLASSPHYSICS_HPP

#include "classObject.hpp"

class Physics {
  private:
    double gravityConstant;
    double deltaTime;

  public:
  Physics(double gravityConstant = 6.67430e-11, double deltaTime = 0.016);
  
  //Getters
  double getGravityConstant() const;
  double getDeltaTime() const;
  
  //Setters
  void setGravityConstant(double gravityConstant);
  void setDeltaTime(double deltaTime);

  void update(Object& object);
  bool checkCollision(Object& object1, Object& object2);
  void resolveCollision(Object& object1, Object& object2);
  void applyGravity(Object& object1, Object& object2);
  void simulate(std::vector<Object>& objects);
  void keepObjectInBounds(Object& object);

};

#endif
