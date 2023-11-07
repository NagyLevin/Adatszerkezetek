//
// Created by Levi on 2023. 11. 07..
//
#include "Vehicle.h"

#ifndef OOP_BIKE_H
#define OOP_BIKE_H

class Bike : public Vehicle{


public:




    Bike() {}

    Bike(const std::string type, double kmh = 0, int capacity = 1) : Vehicle(type, kmh, capacity) {} //alapertekeket is adunk

    double moveOn(double km) override{
        kmh += km;
        std::cout << "Megtettunk: " << km << " osszesen" << std::endl;
        return km;

    }




};

#endif //OOP_BIKE_H
