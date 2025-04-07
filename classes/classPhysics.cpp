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

//Atualiza a posição do objeto baseado na sua velocidade
void Physics::update(Object& object) {
    std::array<double, 3> position = object.getPosition();
    std::array<double, 3> velocity = object.getVelocity();

    for (int i = 0; i < 3; ++i) {
        position[i] += velocity[i] * deltaTime;
    }

    object.setPosition(position);

}

bool Physics::checkCollision(Object& object1, Object& object2) {
    const std::array<double, 3>& positionObj1 = object1.getPosition();
    const std::array<double, 3>& positionObj2 = object2.getPosition();

    double distanceSquared = 0.0;
    for (int i = 0; i < 3; ++i) {
        double distanceDifference = positionObj1[i] - positionObj2[i];
        distanceSquared += distanceDifference * distanceDifference;
    }

    double minDistance = object1.getRadius() + object2.getRadius();

    return distanceSquared <= (minDistance * minDistance);
}

//Checa a colisão entre dois objetos, pelo raio dos dois objetos
void Physics::resolveCollision(Object& object1, Object& object2) {
  std::array<double, 3> positionObject1 = object1.getPosition();
  std::array<double, 3> positionObject2 = object2.getPosition();
  std::array<double, 3> velocityObject1 = object1.getVelocity();
  std::array<double, 3> velocityObject2 = object2.getVelocity();
  double massObject1 = object1.getMass();
  double massObject2 = object2.getMass();

  std::array<double, 3> normal;
  double distance = 0.0f;

  for (int i = 0; i < 3; ++i) {
    normal[i] = positionObject2[i] - positionObject1[i];
    distance += normal[i] * normal[i];
  }

  distance = std::sqrt(distance);
  for (int i = 0; i < 3; ++i) {
    normal[i] /= distance;
  }

  double vel_along_normal = 0.0f;
  for (int i = 0; i < 3; ++i) {
    vel_along_normal += (velocityObject1[i] - velocityObject2[i]) * normal[i];
  }

  if (vel_along_normal > 0) return;

  double restitution = 0.8f; // Coeficiente de restituição
  double j = -(1 + restitution) * vel_along_normal / (1 / massObject1 + 1 / massObject2);

  //Impulso
  for (int i = 0; i < 3; ++i) {
    velocityObject1[i] -= (j * normal[i]) / massObject1;
    velocityObject2[i] += (j * normal[i]) / massObject2;
  }

  object1.setVelocity(velocityObject1);
  object2.setVelocity(velocityObject2);
}

//F = G * ((m1 * m2) / r^2)
// a = F / m
// v+= a * dt

// Metodo para aplicar a gravidade
void Physics::applyGravity(Object& object1, Object& object2) {

  std::array<double, 3> positionObject1 = object1.getPosition();
  std::array<double, 3> positionObject2 = object2.getPosition();

  double massObject1 = object1.getMass();
  double massObject2 = object2.getMass();

  std::array<double, 3> direction;
  double distanceSquared = 0.0f;

  for (int axis = 0; axis < 3; ++axis) {
    direction[axis] = positionObject2[axis] - positionObject1[axis];
    distanceSquared += direction[axis] * direction[axis];
  }

  double distance = std::sqrt(distanceSquared);

  if (distance == 0) return;

  double gravityForce = gravityConstant * (massObject1 * massObject2) / distanceSquared;
  double acceleration = gravityForce / massObject1;

  for (int axis = 0; axis < 3; ++axis) {
    direction[axis] /= distance;
  }

  std::array<double, 3> velocity = object1.getVelocity();

  for (int axis = 0; axis < 3; ++axis) {
    velocity[axis] += direction[axis] * acceleration * deltaTime;
  }

  object1.setVelocity(velocity);
}


//Chama os métodos
void Physics::simulate(std::vector<Object>& objects) {
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            applyGravity(objects[i], objects[j]);
            applyGravity(objects[j], objects[i]);
        }
    }

    for (auto& object : objects) {
        update(object);
        keepObjectInBounds(object);
    }

    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (checkCollision(objects[i], objects[j])) {
                resolveCollision(objects[i], objects[j]);
            }
        }
    }
}


void Physics::keepObjectInBounds(Object& object) {
    std::array<double, 3> position = object.getPosition();
    double radius = object.getRadius();

    // Get the boundaries of the screen (near and far planes)
    const double nearPlane = 0.1f;   // Near clipping plane (from gluPerspective)
    const double farPlane = 100.0f;  // Far clipping plane (from gluPerspective)

    // Assume the screen width and height determine the left/right/top/bottom boundaries
    const double leftBound = -4.0f;  // Adjust this based on your scene scale
    const double rightBound = 4.0f;  // Adjust this based on your scene scale
    const double topBound = 4.0f;    
    const double bottomBound = -4.0f; // Adjust this based on your scene scale

    for (int i = 0; i < 3; ++i) {
        if (position[i] - radius < leftBound) {
            position[i] = leftBound + radius; 
        } 
        if (position[i] + radius > rightBound) {
            position[i] = rightBound - radius; 
        }
        if (position[i] - radius < bottomBound) {
            position[i] = bottomBound + radius; 
        }
        if (position[i] + radius > topBound) {
            position[i] = topBound - radius;
        }
        if (position[2] - radius < nearPlane) {
            position[2] = nearPlane + radius;
        }
        if (position[2] + radius > farPlane) {
            position[2] = farPlane - radius;
        }
    }

    object.setPosition(position);
}
