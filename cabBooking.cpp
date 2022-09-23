#include<bits/stdc++.h>
using namespace std;

// build a cab booking system to allow a rider to book a cab

// we will fetch only the cabs which are in a given radious

// the location is represented in (x,y) coordinates 
// distance between two points (x1,y1) and (x2,y2) will be sqrt((x1-x2)^2+(y1-y2)^2);
// nearest free dirver will pick the rider
// a cab has only one driver
// sharing of cab is not allowed 
// there is a single type of cab only 

// -- features -- 

// register a rider
// register a driver/cab
//update a cab's location
//a driver can switch on/off his availability
// a rider can book a cab
// fetch hisory of all the rides taken by a rider
// end the trip

class Cab{
    string id;
    string driver;
    string isAvailable;
    Location *location;
    public:
    Cab(string id, string driver){
        this->id = id;
        this->driver = driver;
        this->isAvailable = true;
        this->location = nullptr;
    }

    bool getAvailability(){ return isAvailable;}
    Location* getLocation(){return location;}
    string getId(){return id;}

    void updateAvailability(bool status){isAvailable = status; return;}
    void updateLocation(Location *location){location = location; return;}
};
class Rider{
    string id;
    string name;
    public:
    Rider(string id, string name){
        this->id = id;
        this->name = name;
    }
    string getId(){return id;}
    string getName(){return name;}
};
class Location{
    double x;
    double y;
    public:
    Location(double x, double y){
        this->x = x;
        this->y = y;
    }
    double getDistance(Location *l){
        return sqrt((this->x-l->x)(this->x-l->x)+(this->y-l->y)(this->y-l->y));
    }
};
enum TripStatus{IN_PROGRESS, FINISHED};
class Trip{
    Rider *rider;
    Cab *cab;
    TripStatus status;
    double price;
    Location *pickup;
    Location *drop;
    public:
    Trip(Rider *rider, Cab *cab, double price, Location *pickup, Location *drop){
        this->rider = rider;
        this->cab = cab;
        this->status = IN_PROGRESS;
        this->price = price;
        this->pickup = pickup;
        this->drop = drop;
    }
    void endTrp(){this->status = FINISHED; return; }
};
class CabsManager{
    map<string, Cab*> cabs;
    CabFindingStrategy *cfs;
    public:
    CabsManager(double distance){
        cfs = new CabFindingStrategy(distance);
    }
    void createCab(string cabId){
        Cab *cab = new Cab(cabId);
        cabs[cabId] = cab;
        return;
    }
    Cab* getCab(string cabId){
        if(cabs.find(cabId)!=cabs.end()) return cabs[cabId];
        return nullptr;
    }
    void updateCabLocation(string cabId, Locaion *newLocation){
        Cab* cab = getCab(cabId);
        if(cab) cab->updateLocation(newLocation);
        return;
    }
    void updateAvailability(string cabId, bool availability){
        Cab *cab = getCab(cabId);
        if(cab) cab->updateAvailability(availability);
        return; 
    }
    vector<Cab*> getCabs(Location *pickup){
        vector<Cab*> result;
        for(auto at:cabs){
            Cab *cab = at.second;
            if(cab->getAvailability() && cfs->isMatching(cab,pickup))
                result.push_back(cab);
        }
        return result;
    }
};
class CabFindingStrategy{
    double distance=5;
    public:
    CabFindingStrategy(double distance){
        this->distance = distance;
    }
    bool isMatching(Cab* cab, Location *pickup){
        Location *cabLocation = cab->getLocation();
        double dist = cabLocation->getDistance(pickup);
        return dist<=distance;
    }
};
class RidersManager{
    map<string,Rider*> riders;
    map<Rider*, Trip*> currentTrip;
    public:
    Rider* getRider(string riderId){
        if(riders.find(riderId)==riders.end()) return nullptr;
        return riders[riderId];
    }
    void createRider(string riderId){
        Rider *rider = new Rider(riderId);
        riders[rider->getId()] = rider;
        return;
    }
    Trip* getCurrentTrip(Rider *rider){return currentTrip[rider];}
    void addTripToCurrentTrip(Rider* rider, Trip* trip){currentTrip[rider] = trip; return;}
    void removeActiveTrip(Rider *rider){currentTrip.erase(rider); return;}
};
class CabMatchingStrategy{
    public:
    vector<Cab*> findMatchingCabForRider(vector<Cab*> &candidates, Loation *pickup, Location *drop){
        return {}; // write your strategy here;
    }
};
class PricingStrategy{
    double perKmRate = 10.0;
    public:
    double getPrice(Location *pickup, Location *drop){
        double distance = pickup->getDistance(drop);
        return distance*perKmRate;
    }
};
class TripsManager{
    RidersManager *rm;
    CabsManager *cm;
    CabMatchingStrategy *cms; 
    PricingStrategy *ps;
    map<Rider*, vector<Trip*>> trips; // single user can have multiple trips
    public:
    TripsManager(RidersManager *rm, CabsManager *cm, CabMatchingStrategy *cms, PricingStrategy *ps){
        this->rm = rm;
        this->cm = cm;
        this->cms = cms;
        this->ps = ps;
    }
    Trip* createTrip(Rider* rider,Location* pickup, Location *drop){
        vector<Cab*> nearbyCabs = cm->getCabs(pickup);
        vector<Cab*> filteredCabs = cms(nearbyCabs,pickup,drop);

        Cab* cab = filteredCabs[0];
        double price = ps->getPrice(pickup,drop);
        Trip* trip = new Trip(rider, can, price, pickup, drop);
        trips[rider].push_back(trip);
        cab->updateAvailability(false);
        rm.addTripToCurrentTrip(rider, trip);
    };
    vector<Trip*> getTripHistory(Rider *rider){
        if(trips.find(rider)!=trips.end()) return {};
        return trips[rider];
    }
    void endTrip(Rider *rider){
        Trip *trip = rm->getCurrentTrip(Rider *rider);
        Cab* cab = trip->cab;
        cab->updateLocation(trip->drop);
        cab->updateAvailability(true);
        trip->endTrp();
        rm->removeActiveTrip(Rider *rider);

        return;
    }
};

class Service{
    TripsManager *tm;
    public:
    Service(){
        RidersManager *rm = new RidersManager();
        CabsManager *cm = new CabsManager();
        CabFindingStrategy *cms = new CabMatchingStrategy;
        PricingStrategy *ps = new PricingStrategy;
        this-> tm = new TripsManager(rm,cm,cms,ps);
    }
    public:
    Trip* createTrip(string riderId,double pickup_x,double pickup_y, double drop_x, double drop_y){
        Rider *rider = tm->rm->gerRider();
        if(!rider) rider = tm->rm->createRider(riderId);
        Location *pickup = new Location(pickup_x,pickup_y);
        Location *drop = new Location(drop_x,drop_y);
        tm->createTrip(rider,pickup,drop);
    }
    void endTrip(string riderId){
        Rider* rider = tm->rm->getRider(riderId);
        tm->rm->endTrip(rider);
    }
    void createRider(string riderId){
        tm->rm->createRider(riderId);
        return;
    }
    void createCab(string cabId){
        tm->cm->createCab(cabId);
        return;
    }
    void setCabAvalibility(string cabId, bool avalibility){
        Cab *cab = tm->cm->getCab(cabId);
        cab->updateAvailability(avalibility);
        return;
    }
};
