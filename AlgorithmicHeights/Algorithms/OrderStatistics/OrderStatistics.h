#ifndef ORDERSTATISTICS_H
#define ORDERSTATISTICS_H

template<typename T>
T findOrderStatistics(T* array, int left, int right, int k){
    int i = left, j = right;
    T pivot = array[ (left + right)/2 ];

    do{
        while(array[i] < pivot) i++;
        while(array[j] > pivot) j--;

        if(i <= j){
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }while(i <= j);

    if(left <= k && k <= j) findOrderStatistics(array, left, j, k);
    if(i <= k && k <= right) findOrderStatistics(array, i, right, k);
    return array[k];
}
#endif // ORDERSTATISTICS_H
