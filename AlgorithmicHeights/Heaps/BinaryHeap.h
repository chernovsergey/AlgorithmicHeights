#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include <vector>
#include <memory>

template<typename T>
class BinaryHeap{

    std::vector<T> data;

public:
    BinaryHeap(T* array, int size){
        data.assign(array, array+size+1);
        for (int i = size / 2; i >= 0; i--){
           heapify(i);
        }
    }

    void heapify(int i){
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

    void push(T elem){ //pushed an element to heap
        data.push_back(elem);
        int i = data.size() - 1;
        int parent = (i-1)/2;

        while(i > 0 && data[parent] < data[i]){
            swap(data[parent], data[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    T pop(){ //returned max element
        int size = data.size();
        T result = data[0];
        data[0] = data[size - 1];
        data.erase(data.begin()+size-1); //removing data[size-1]
        return result;
    }

};

#endif // BINARYHEAP_H
