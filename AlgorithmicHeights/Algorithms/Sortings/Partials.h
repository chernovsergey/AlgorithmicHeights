#ifndef PARTIALS_H
#define PARTIALS_H

#include <array>
#include "DataStructures/Heaps/BinaryHeap.h"

template<typename T>
std::vector<T> find_num_greatest(T* array, int size, const int num){

    std::vector<T> result;
    result.resize(num);

    //build max-heap
    MaxBinaryHeap<T> bheap(array, size);

    //extract %num elements
    for(auto &i : result){
        i = bheap.pop();
    }

    return result;
}


template<typename T>
std::vector<T> find_num_lowest(T* array, int size, int num){

    std::vector<T> result;
    result.resize(num);

    //build min-heap
    MinBinaryHeap<T> bheap(array, size);

    //extract %num elements
    for(auto &i : result){
        i = bheap.pop();
    }

    return result;
}

#endif // PARTIALS_H
