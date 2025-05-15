// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;

  Car* current = first->next;
  while (current != first) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};

  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  if (!first) return 0;

  countOp = 0;
  Car* current = first;

  if (!current->light) {
    current->light = true;
  }

  while (true) {
    int steps = 0;
    do {
      current = current->next;
      countOp++;
      steps++;
    } while (!current->light && current != first);

    if (current == first && !current->light) {
      return steps;
    }

    current->light = false;

    for (int i = 0; i < steps; i++) {
      current = current->prev;
      countOp++;
    }

    if (current == first && !current->light) {
      return steps;
    }
  }
}
