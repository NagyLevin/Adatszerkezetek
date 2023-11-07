//
// Created by Levi on 2023. 11. 07..
//
#include "Vehicle.h"

#ifndef OOP_CAR_H
#define OOP_CAR_H

class Car: public Vehicle{
protected:
    double consumption;
    double petrol;
    double petrolNeed(double km){
        return ((double) km/100) + consumption;
    }

public:

    Car() {} //konstruktor

    virtual ~Car() { //destruktor

    }


    Car(const std::string type,double consumption, int capacity, double kmh = 0) : Vehicle(type, kmh, capacity), consumption(consumption), petrol(0) {} //alapertekeket is adunk



    static int petrolCost;

    virtual double getCost(double liter){
        return petrolCost * liter;


    }

    virtual void refuel( double liter){ //tankolas
        petrol = petrol + liter;
    }

    double cost(double km){
        return petrolNeed(km) * petrolCost;

    }

    double moveOn(double km) {


        if(petrolNeed(km) <= petrol ){
            petrol = petrol - petrolNeed(km);
            kmh += km;
            std::cout << "Megtettunk: " << km << " osszesen" << std::endl;
            return km;

        }


    }

    double getPetrol() const;

    double getConsumption() const;

};

int Car::petrolCost = 600;

double Car::getPetrol() const {
    return petrol;
}

double Car::getConsumption() const {
    return consumption;
}
//itt kint kell hozza az ertekadas



#endif //OOP_CAR_H
