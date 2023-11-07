
#ifndef OOP_VEHICLE_H
#define OOP_VEHICLE_H
using namespace std;

class Vehicle{
    protected:
    std::string type;
    double kmh;
    int capacity;

    public:

    Vehicle(){}

    Vehicle(std::string type, double kmh, int capacity) : type(type), kmh(kmh),capacity(capacity){

    }
    virtual double moveOn(double km) = 0;

    virtual double getKmh(){
        return kmh;

    }

    virtual std::string getType(){
        return  type;
    }

    virtual int getCapacity() {
        return capacity;
    }







};

#endif //OOP_VEHICLE_H
