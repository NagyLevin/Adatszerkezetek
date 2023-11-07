#include <iostream>
#include "Car.h"
#include "Taxi.h"
#include "Bus.h"
#include "Bike.h"

using namespace std;

int main() {
    cout << "70 liter benzin ara: " << Car::getCost(70) << endl;


    cout << endl << "Car teszt" << endl << endl;

    Car bmw("BMW", 14, 5, 10);

    cout << bmw.getCapacity() << " ferohelyes, " << bmw.getConsumption() << " literes fogyasztasu " << bmw.getType() << " Car letrehozva.\n";
    cout << "A benzin ara: " << Car::petrolCost << endl;
    //cout << "A benzin ara: " << bmw.petrolCost << endl; // Ez működik, de ronda
    bmw.refuel(70);
    bmw.moveOn(12);
    //bmw.moveOn(1000);

    cout << endl << "Taxi teszt" << endl << endl;

    Taxi taxi("Audi", 11, 4, 230);
    cout << taxi.getCapacity() << " ferohelyes, " << taxi.getConsumption() << " literes fogyasztasu " << taxi.getType() << " taxi letrehozva.\n";
    taxi.refuel(70);
    taxi.carriage(100);
    cout << "100 km-es fuvar es 70 literes tankolas utan a taxis penztarcaja: " << taxi.getPocket() << endl;
    cout << "4 fo eseten 100 km ut koltsege / fo: " << taxi.memberCost(100, 4) << endl;
    cout << "10 fo eseten 100 km ut koltsege / fo: " << taxi.memberCost(100,10) << endl;

    cout << endl << "Bus teszt" << endl << endl;


    Bus Bus("Man", 10, 80, 250);
    cout << Bus.getCapacity() << " ferohelyes, " << Bus.getConsumption() << " literes fogyasztasu " << Bus.getType() << " Bus letrehozva.\n";
    Bus.refuel(70);
    Bus.carriage(10, 80);
    cout << "80 fo eseten 10 km-es fuvar es 70 literes tankolas utan a vallalat penztarcaja: " << Bus.getPocket() << endl;
    cout << "A vallalat haszna ezen a fuvaron: " << Bus.profit(10, 80) << endl;
    cout << "80 fo eseten 10 km ut koltsege / fo: " << Bus.memberCost(10, 80) << endl;

    cout << endl << "Bike teszt" << endl << endl;

    Bike mBike("Mountain Bike");
    cout << mBike.getType() << " tipusu Bike letrehozva.\n";
    mBike.moveOn(120);
    cout << "A Bike kilometer orajanak allasa: " << mBike.getKmh() << endl;

    /******************************************* Polimorfizmus es dinamikus kotes ****************************************/

    //itt nincs dinamikuskotes!!!
    cout << endl << "Nem dinamikus kotes teszt" << endl << endl;

    Car ta1 = taxi;
    cout << "Ennyi lenne a taxi koltsege: " << taxi.cost(11) << endl;
    cout << "De mivel nincs dinamikus kotes, az Car koltseg fuggvenye fut le: " << ta1.cost(11) << endl;

    cout << endl << "Dinamikus kotes teszt" << endl << endl;

    //itt mar igen:

    Car& ta2 = taxi;
    cout << "Taxi koltsege: " << ta2.cost(11) << endl;

    cout << "Uzemanyag: " << ta2.getPetrol() <<endl;
    cout << "Penz " << taxi.getPocket() <<endl;
    ta2.refuel(10);			// itt a Car::refuel(double) metódus fog lefutni!
    cout << "Uzemanyag " << ta2.getPetrol() <<endl;
    cout << "Penz " << taxi.getPocket() <<endl;		// nem változik a taxi pénze, pedig kéne...

    Car* a = new Taxi("Mercedes", 11, 2, 400);
    cout << "A Taxi koltsege: " << a->cost(100) << endl;

    delete a;

    Vehicle* vehicles[3];

    vehicles[0] = &mBike;
    vehicles[1] = &bmw;
    vehicles[2] = &taxi;

    for (int i = 0; i < 3; i++) {
        vehicles[i]->moveOn(100);
    }

    return 0;
}