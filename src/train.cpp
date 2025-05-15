// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : start(nullptr),  countOp(0) {}

Train::~Train() {
  if (!start)  return;

  Car* current = start->next;
  while (current != start) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete start;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{ light,  nullptr,  nullptr };

  if (!start) {
    start = newCar;
    start->next = start;
    start->prev = start;
  } else {
    Car* last = start->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = start;
    start->prev = newCar;
  }
}

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  Car* current = start;
  countOp = 0;

  while (!current->light) {
    current->light = true;
    current = current->next;
    countOp++;
  }

  int len = 1;
  current = current->next;
  countOp++;
  while (!current->light) {
    current = current->next;
    countOp++;
    len++;
  }

  return len;
}
