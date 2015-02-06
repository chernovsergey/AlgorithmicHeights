#ifndef SORTINGS_H
#define SORTINGS_H
#include "DataStructures/Heaps/BinaryHeap.h"
#include <thread>
#include <future>

template<typename T>
void Merge(T* array, int left, int mid, int right, int size){
    T *result = new T[size];
    int i = 0, j = 0;

    for(i = mid + 1; i > left; i--){
        result[i-1] = array[i-1];
    }

    for(j = mid; j < right; j++){
        result[right + mid - j] = array[j+1];
    }

    for(int k = left; k <= right; k++){
        if(result[j] < result[i])
            array[k] = result[j--];
        else
            array[k] = result[i++];
    }

    delete[] result;
}

template<typename T>
void MergeSort(T* array, int left, int right){
    if(right <= left){
        return;
    }
    int mid = (left + right)/2;
    MergeSort(array, left, mid);
    MergeSort(array, mid + 1, right);
    Merge(array, left, mid, right, right + 1);
}

template<typename T>
void QuickSort(T* array, int N){
    int i = 0, j = N;
    T pivot = array[ N/2 ];

    do{
        while(array[i] < pivot) i++;
        while(array[j] > pivot) j--;

        if(i <= j){
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }while(i <= j);

    if( j > 0) QuickSort(array, j);
    if( i < N) QuickSort(array + i, N - i);
}

template<typename T>
void HeapSort(T* array, int N){
    BinaryHeap<T> bheap(array, N);
    for(int i = N; i > 0; i--){
        array[i] = bheap.pop();
        bheap.heapify(0);
    }
}

template<typename T>
void InsertionSort(T* array, int N){
    if(N < 2) return;
    for( int i = 1; i < N; i++){
        for(int j = i; j > 0 && array[j-1] > array[j]; j--){
            std::swap(array[j-1], array[j]);
        }
    }
}
#endif // SORTINGS_H
