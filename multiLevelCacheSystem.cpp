#include<bits/stdc++.h>
using namespace std;

// Design and implement a multiple level cache management system with N levels, say:
// L1 -> L2 -> L3 ... LN each layer will store the key-value pair, key and value both are of string type
// L1 is the top layer with most priority and LN is the last layer with least priority, you are given the following details

// 1. number of layer in the cache
// 2. the capacity of each layer
// 3. read time of each layer
// 4. write time of each layer

// The cache should be able to support the following operations 

// 1. READ KEY operation - read operation will start from L1
// if the key is found at this layer then return otherwise check in the next alyer
// if the value of a KEY found at any layer, then this value should also be witten into all previous layers
// total read time is the sum of read times of all the levels where read operation was performed and write time is where write operation was performed
// we have to print key value and total time taken

// 2. WRITE KEY operation - write will start from L1 level
// write the value of key at this level and all the levels below this
// if at any level value of key is same as given value then don't write and return 
// total write time is where write operation was performed and read time is total of read where read was performed
// have to print total time taken to print this key-value



class Storage{
    public:
    virtual bool isFull() = 0;
    virtual void add(int key, int val) = 0;
    virtual void removeKey(int key) = 0;
    virtual int get(int key) = 0;
};
class HashMapBasedStorage{
    int size=100;
    map<int,int> mp;
    public:
    HashMapBasedStorage(int size){
        this->size = size;
    }
    bool isFull(){return mp.size()==size;}
    void add(int key,int val){mp[key]=val;}
    void removeKey(int key){mp.erase(key);}
    void get(int key){
        if(map.find(key)==mp.end()) return -1;
        return mp[key];
    }
};
class EvictionPolicy{
    public:
    virtual int evictKey() = 0;
    virtual void keyAccessed(int key) = 0;
};
class LRUEvictionPolicy{
    List* dll;
    map<int,List*> mapper;

    public:
    LRUEvictionPolicy(){
        dll = new List(-1); // to define the root node
    }
    void keyAccessed(int key){
        // move the key to last position, front will always be the lest frequent key;
    }
    int evictKey(){
        // return take the front key , take it out and remove the same from map and return the key
    }
};

class ReadResponse{
    int value;
    double timeTaken;
    public:
    ReadResponse(int value,int totalTime){
        this->value = value;
        this->timeTaken = totalTime;
    }
    int getValue(){return value;}
    double getTotalTime(){return timeTaken;}
};
class WriteResponse{
    double timeTaken;
    public:
    WriteResponse(double timeTaken){
        this->timeTaken = timeTaken;
    }
    double getTimeTaken(){return timeTaken;}
};
class LevelCacheData {
    double readTime;
    double writeTime;
    public:
    LevelCacheData(double readTime, double writeTime){
        this->readTime;
        this->writeTime;
    }
    double getReadTime(){return readTime;}
    double getWriteTime(){return writeTime;}
};

class Cache{
    Storage *storage;
    EvictionPolicy *evictionPolicy;
    public:
    Cache(Storage *storage, EvictionPolicy *evictionPolicy){
        this->storage = storage;
        this->evictionPolicy = evictionPolicy;
    }
    void set(int key,int val){
        if(storage->isFull()){
            int keyToRemove = evictionPolicy->evictKey();
            storage->removeKey(keyToRemove);
        }
        storage->add(key,val);
        evictionPolicy->keyAccessed(key);
    }
    int get(int key){
        int value = storage->get(key);
        evictionPolicy->keyAccessed(key);
        return value;
    }
};

class ILevelCache{
    Cache *cache;
    ILevelCache *nextCache;
    LevelCacheData *levelCacheData;
    public:
    ILevelCache(Cache *cache,LevelCacheData *levelCacheData;){
        this->cache = cache;
        this->levelCacheData = levelCacheData;
    }
    ReadResponse* get(int key){
        double curTime = 0.0;
        int curLevelValue = cache.get(key);
        curTime += levelCacheData.getReadTime();

        // L1 -> L2 -> L3 -> L4
        if (curLevelValue == -1) {
            ReadResponse *nextResponse = nextCache->get(key);
            curTime += nextResponse->getTotalTime();
            curLevelValue = nextResponse.getValue();
            if (curLevelValue != -1) {
                cache.set(key, curLevelValue);
                curTime += levelCacheData.getWriteTime();
            }
        }
        return new ReadResponse(curLevelValue, curTime);
    }
    WriteResponse* set(int key,int value){
        double curTime = 0.0;
        int curLevelValue = cache.get(key);
        curTime += levelCacheData.getReadTime();
        if (value!=curLevelValue) {
            cache.set(key, value);
            curTime += levelCacheData.getWriteTime();
        }

        curTime += nextCache->set(key, value).getTimeTaken();
        return new WriteResponse(curTime);
    }
};

class MainCacheService{
    MainCache* defaultCache = nullptr;
    public:
    void addCache(int size, double readTime, double writeTime, Storage *storage=nullptr, EvictionPolicy *evictionPolicy){
        if(!storage) Srorage *storage = new HashMapBasedStorage(size);
        if(!evictionPolicy) EvictionPolicy *evictionPolicy = new LRUEvictionPolicy();
        LevelCacheData *levelCacheData = new LevelCacheData(readTime,writeTime);
        Cache *cache = new Cache(storage,evictionPolicy);

        if(!defaultCache) defaultCache = new ILevelCache(cache, levelCacheData);
        else{
            while(defaultCache->nextCache) defaultCache = defaultCache->nextCache;
            defaultCache->next = new ILevelCache(cache, levelCacheData);
        }
    }
    ReadResponse* get(int key){
        return defaultCache->get(key);
    }
    WriteResponse* set(int key,int value){
        return defaultCache(key,value)
    }
};

// ReadResponse -> {value, totalTimeTaken}
// WriteResponse -> {totalTimeTaken}