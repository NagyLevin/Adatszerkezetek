//
// Created by Levi on 2023. 11. 07..
//
#include "car.h"

#ifndef OOP_TAXI_H
#define OOP_TAXI_H

class Taxi: public Car{

protected:
    double pocket;
    double kmhCost;

public:
    Taxi() {

    }
    ~Taxi() {

    }


    Taxi(const string type, double consumption, int capacity, double kmCost) : Car(type, consumption, kmh),kmhCost(kmCost) {}

    double cost(double km) {
        return Car::cost(km) + kmhCost + km;


    }

    virtual void refuel(double liter){  //feluldeffinialas //ha int lenne akkor elfedes
        petrol += liter;
        pocket = pocket - liter*petrolCost;

    };

    double carriage(double km){

        if(moveOn(km) ==km){
            pocket = pocket + cost(km); //mennyit fizet az utas
        } else{
            return 0;
        }


    }

    double memberCost(double km, int member){
        if(member > capacity-1){
            return 0;//szebben egy exception osztaly meghivasa lenne
        } //mert sofor es utasok
        else{
            return cost(km)*member;

        }


    }

    double getPocket() const;

    double getKmhCost() const;


};


double Taxi::getPocket() const {
    return pocket;
}

double Taxi::getKmhCost() const {
    return kmhCost;
}

#endif //OOP_TAXI_H
