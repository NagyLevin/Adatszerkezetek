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

    Bus(){};

    ~Bus(){

    }

    virtual double carriage(int member ,double km){

        if(moveOn(km) ==km){
            pocket = pocket + memberCost(km,member); //mennyit fizet az utas


            return km;




        } else{
            return 0;
        }


    }
    double memberCost(double km, int member) {
        if(member > capacity-1){
            return 0;//szebben egy exception osztaly meghivasa lenne
        } //mert sofor es utasok
        else{
            return ticketCost*member;

        }


    }
    double profit(double km, int member){
        return memberCost(km,member) - kmhCost*km;

    }



};
int Bus::ticketCost = 450;


#endif //OOP_BUS_H
