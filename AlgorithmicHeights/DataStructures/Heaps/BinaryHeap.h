#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <vector>
#include <memory>

template<typename T>
class MaxBinaryHeap{

    std::vector<T> data;

public:
    MaxBinaryHeap(T* array, int size){
        //Make heap procedure
        data.assign(array, array+size+1);
        for (int i = size / 2; i >= 0; i--){
           max_heapify(i);
        }
    }

    //Sift up. O(logN)
    void max_heapify(int i){
        int left_child;
        int right_child;
        int largest_child;
        int size = data.size();

        for(;;){

            left_child = 2 * i + 1;
            right_child = 2 * i + 2;
            largest_child = i;

            if(left_child < size && data[left_child] > data[largest_child]){
                largest_child = left_child;
            }

            if(right_child < size && data[right_child] > data[largest_child]){
                largest_child = right_child;
            }

            if(largest_child == i){
                break;
            }

            std::swap(data[i], data[largest_child]);
            i = largest_child;
        }
    }

    //Insert element to heap
    void push(T elem){
        data.push_back(elem);
        int i = data.size() - 1;
        int parent = (i-1)/2;

        while(i > 0 && data[parent] < data[i]){
            swap(data[parent], data[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    //Extracting max element
    T pop(){
        int size = data.size();
        T result = data[0];
        data[0] = data[size - 1];
        data.erase(data.begin()+size-1); //removing data[size-1]
        max_heapify(0);
        return result;
    }

};


template<typename T>
class MinBinaryHeap{

    std::vector<T> data;

public:
    MinBinaryHeap(T* array, int size){
        //Make heap procedure
        data.assign(array, array+size+1);
        for (int i = size / 2; i >= 0; i--){
           min_heapify(i);
        }
    }

    //Sift up. O(logN)
    void min_heapify(int i){}


    //Insert element to heap
    void push(T elem){}


    // Extracting min element
    T pop(){}
};
#endif // BINARYHEAP_H
