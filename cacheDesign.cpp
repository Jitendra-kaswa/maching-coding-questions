#include<bits/stdc++.h>
using namespace std;

//design a cache system that supports the following operations - 
// 1. PUT : allow user to put a value against a key
// 2. GET : allow user to get value corresponding to a key
// 3. Eviction : cache should follow removal of keys, if cache a full and we are trying to add new keys

class List{
    int value;
    List* next = nullptr;
    List* prev = nullptr;
    public:
    List(int val){
        this->value = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};


class EvictionPolicy{
    public:
    virtual int evictKey() = 0;
    virtual void keyAccessed(int key) = 0;
};
class Storage{
    public:
    virtual bool isFull() = 0;
    virtual void add(int key, int val) = 0;
    virtual void removeKey(int key) = 0;
    virtual int get(int key) = 0;
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
class HashMapBasedStorage{
    int size=100;
    map<int,int> mp;
    public:
    bool isFull(){return mp.size()==size;}
    void add(int key,int val){mp[key]=val;}
    void removeKey(int key){mp.erase(key);}
    void get(int key){return mp[key];}
};


class CacheService{
    EvictionPolicy *eploicy;
    Storage *storage;
    public:
    CacheService(EvictionPolicy *epolicy, Storage *storage){
        this->eploicy = eploicy;
        this->storage = storage;
    }
    void put(int key, int val){
        if(storage->isFull()){
            int key = eploicy->evictKey();
            storage->removeKey(key);
        }
        storage->put(key,val);
        eploicy->keyAccessed(key);
    }
    int get(int key){
        int value = storage->get(key);
        epolicy->keyAccessed(key);
        return value;
    }
};