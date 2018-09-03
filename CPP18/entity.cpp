#include "entity.h"

Entity::Entity(QWidget *parent) : QWidget(parent) { genEntity(); }

int Entity::genNumber(int min, int max) {
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> distNumber(min, max);

  return int(distNumber(rng));
}

void Entity::genEntity() {
  speed = genNumber(minSpeed, maxSpeed);
  posX = genNumber(0, maxPosX);
  posY = genNumber(0, maxPosY);
  if (genNumber(0, 100) % 5 == 0) {
    pickUp = true;
  }
}
