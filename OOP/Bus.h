//
// Created by Levi on 2023. 11. 07..
//
#include "Taxi.h"
#ifndef OOP_BUS_H
#define OOP_BUS_H

class Bus : public Taxi{
protected:
    static int ticketCost;

public:
    Bus(const string type, double consumption, int capacity, double kmCost) : Taxi(type, consumption, capacity,kmCost) {}

    ~Bus(){

    }

    virtual double carriage(int member ,double km){

        if(moveOn(km) ==km){
            pocket = pocket + member*ticketCost - kmhCost*km; //mennyit fizet az utas


            return km;




        } else{
            return 0;
        }


    }
    double memberCost(double km, int member) {
        return ticketCost;

    }



    double profit(double km, int member){
        return member * ticketCost -kmhCost*km;

    }



};
int Bus::ticketCost = 450;


#endif //OOP_BUS_H
