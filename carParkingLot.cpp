#include<bits/stdc++.h>

// design parking lot to park a car, car shold park in nearest free slot.
// give registeration number of all the parked car of a particular color.
// slot number in which a particular car with given registeration number is parked
// slot number of all the slots where a particulr color car is parked


// create <number> - to create a parking lot
// park <car number> <color> - to park a car
// leave <slot> - unpark a car
// status - status of parking not, all the filled slots
// registeration_numbers_or_cars_with_color <color> - return registeration numbers
// slot_number_for_cars_with_color <color> - slot numbers
// exit


class Car{
    string number;
    string color;
    public:
    Car(string number,string color){
        this->number = number;
        this->color = color;
    }
    string getCarNumber(){return number;}
    string getColor(){return color;}
};

class Slot{
    int number;
    Car* parkedCar;
    public:
    Slot(int number,Car* c=nullptr){
        this->number = number;
        this->parkedCar = c;
    }
    Car* getParkedCar(){return parkedCar;}
    bool isFree(){return parkedCar==nullptr;}
    int getSlotNumber(){return number;}
    void parkCar(Car* car){return parkedCar = car;}
    void unparkCar(){parkedCar = nullptr; return;}
};
class OutPutPrinter{

};
class ParkingLot{
    int max_capacity = INT_MAX;
    int capacity  = 100;
    map<int,Slot*> slots;

    public:
    ParkingLot(int capacity){
        if(capacity>max_capacity) = this->capacity = this->max_capacity;
        else this->capacity = capacity;
        slots.clear();
    }
    int getCapacity(){return capacity;}
    map<int,Slot*> getSlots(){return slots;}
    Slot* getSlot(int number){
        if(number>capacity) return nullptr;
        if(slots.find(number)==slots.end) slots[number] = new Slot(number);
        return slots.find(number);
    }
    // we will take slot number from parking strategy, that is the deciding where to park
    Slot* park(Car* car,int slotNumber){
        Slot* slot = getSlot(slotNumber);
        if(!slot->isFree()) return nullptr;
        slot->parkCar(car);
        return slot;
    }
    Slot* makeSlotFree(int slotNumber){
        if(slots.find(slotNumber)==slots.end()) return nullptr;
        Slot* slot = getSlot(slotNumber);
        slot->unparkCar();
        return slot;
    }
};
class ParkingStrategy{
    public:
    virtual void addSlot(int slotNumber) = 0;
    virtual void removeSlot(int slotNumber) = 0;
    virtual int nextSlot() = 0;
};
class NatuarlOrdering : ParkingStrategy{
    set<int> slots;
    public:
    NatuarlOrdering(){slots.clear();}
    void addSlot(int slotNumber){
        slots.insert(slotNumber);
    }
    void removeSlot(int slotNumber){
        slots.erase(slotNumber);
    }
    int nextSlot(){
        if(slots.empty()) return -1;
        return *(slots.begin()):
    }
}
class ParkingLotService{
    ParkingLot *parkingLot;
    ParkingStrategy *parkingStrategy;
    public:
    ParkingLotService(ParkingLot *parkingLot, ParkingStrategy *parkingStrategy){
        this-> parkingLot = parkingLot;
        this-> parkingStrategy = parkingStrategy;

        for(int i=1;i<=parkingLot->getCapacity();i++)
            this->parkingStrategy->addSlot(i);
    }
    int parkCar(Car* car){
        int freeSlot = parkingStrategy->nextSlot();
        if(freeSlot == -1) return freeSlot;
        Slot* slot = parkingLot->park(car,freeSlot);
        parkingStrategy->removeSlot(freeSlot);
    }
    int makeSlotFree(int slotNumber){
        parkingLot->makeSlotFree(slotNumber);
        parkingStrategy->addSlot(slotNumber);
    }
    vector<Slot*> getOccupiedSlots(){
        map<int,Slot*> allSlots = parkingLot->getSlots();
        vector<Slot*> occSlots;
        for(auto at: allSlots)
            if(at.second->isFree()==false)
                occSlots.push_back(at.second);
        return occSlots;
    }
};

int main{
    ParkingLot *pl = new ParkingLot(500);
    ParkingStrategy ps;
    public:
    ParkingLotService *pls = new ParkingLotService(pl,&ps);
    Car *car = new Car("ka-09-bd-0444", "white");
    pls->parkCar(car);
    pls.makeSlotFree(1);
}