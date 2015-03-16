#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <map>
#include <string>
using namespace std;

typedef int (*HASHFUNC)();

template<typename K, typename V>
class TREE_CHAIN{

    map<K, V> m;

public:
    void put(K key, V value){
        m.emplace(key, value);
    }

    V get(K key){
        return m[key];
    }

    void remove(K key){
        m.erase(key);
    }

    void clear_all(){
        m.clear();
    }
};


template <typename K, typename V>
class HasTable_Chaining{

    const int TABLE_SIZE = 0;
    vector<TREE_CHAIN<K,V>> table;

    typedef int (*HASHFUNC)(K, int);
    HASHFUNC hash_func;

public:
    HasTable_Chaining(int size, HASHFUNC func):
        TABLE_SIZE(size), hash_func(func){
        table.resize(TABLE_SIZE);
    }

    ~HasTable_Chaining(){
        for(auto i : table){
            i.clear_all();
        }
    }

    void put(K key, V value){
        int hash = hash_func(key, TABLE_SIZE);
        table[hash].put(key, value);
    }

    V get(K key){
        int hash = hash_func(key, TABLE_SIZE);
        V result = table[hash].get(key);
        return result;
    }

    void remove(K key){
        int hash = hash_func(key, TABLE_SIZE);
        table[hash].remove(key);
    }
};
#endif // HASHTABLE_H
