#include <iostream>
#include <random>
#include <memory>
#include <array>
#include <algorithm>
#include <assert.h>
#include <string>

#include "Algorithms/Sortings/Sortings.h"
#include "Algorithms/Sortings/Partials.h"
#include "DataStructures/Lists/List.h"
#include "Algorithms/OrderStatistics/OrderStatistics.h"
#include "DataStructures/Hashing/HashTable.h"

using namespace std;

template<typename T>
void fill(T* x, int size){
    default_random_engine generator;
    int R = rand()/1000000;
    uniform_real_distribution<T> UNIFORM_X(-R, R);
    for(int i = 0; i < size; i++){
        x[i] = UNIFORM_X(generator);
    }
}

template<typename T>
void show(T *x, int size){
    for(int i = 0; i < size; i++){
        cout << x[i] << endl;
    }
    cout << endl << endl;
}


int hash_int(int value, int size){
    return value % size;
}

int hash_double(double value, int size){
    return ((int)value) % size;

}

int hash_string(string s, int size){
    return 1;
}


int main()
{

    //    const int TABLE_SIZE = 20;
    //    HasTable_Chaining<string, int> hashtable(TABLE_SIZE, &hash_string);
    //    hashtable.put("fuck", 7);
    //    hashtable.put("you", 17);
    //    hashtable.put("bitch", 70);
    //    cout << hashtable.get("fuck") << endl;
    //    cout << hashtable.get("you") << endl;
    //    cout << hashtable.get("bitch") << endl;

    //    int A[] = {-1,-2,-3, 0, 1, 2, -30, 4, 5};
    //    MinBinaryHeap<int> mheap(A, 8);
    //    cout << mheap.pop() << endl;
    //    cout << mheap.pop() << endl;
    //    cout << mheap.pop() << endl;
    //    MaxBinaryHeap<int> mheap(A, 8);
    //    cout << mheap.pop() << endl;
    //    cout << mheap.pop() << endl;
    //    cout << mheap.pop() << endl;


    //    int A[] = {-1,-2,-3, 0, 1, 2, -30, 4, 5};

    //    auto arr = find_num_greatest<int>(A, 8, 5);
    //    for(auto &i : arr)cout << i << " ";

    //    cout << endl << endl;

    //    arr = find_num_lowest<int>(A, 8, 5);
    //    for(auto &i : arr)cout << i << " ";

    return 0;
}

