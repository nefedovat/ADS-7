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

  int length = 1;
  
  while (true) {
    bool lightFound = false;
    for (int i = 0; i < length; i++) {
      current = current->next;
      countOp++;
      
      if (current->light) {
        current->light = false;
        lightFound = true;
        for (int j = 0; j <= i; j++) {
          current = current->prev;
          countOp++;
        }
        break;
      }
    }

    if (!lightFound) {
      return length;
    }
    
    length++;
  }
}
