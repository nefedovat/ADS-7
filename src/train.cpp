// Copyright 2021 NNTU-CS
#include "train.h"

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
    
    // Включаем свет в начальном вагоне, если он выключен
    if (!current->light) {
        current->light = true;
    }
    
    while (true) {
        // Двигаемся вперед, пока не найдем включенный свет
        int steps = 0;
        do {
            current = current->next;
            countOp++;
            steps++;
        } while (!current->light && current != first);
        
        // Если полный круг пройден и свет не найден - возвращаем количество шагов
        if (current == first && !current->light) {
            return steps;
        }
        
        // Выключаем найденный свет
        current->light = false;
        
        // Возвращаемся назад на то же количество шагов
        for (int i = 0; i < steps; i++) {
            current = current->prev;
            countOp++;
        }
        
        // Если вернулись в начальный вагон и свет выключен - это длина поезда
        if (current == first && !current->light) {
            return steps;
        }
    }
}
