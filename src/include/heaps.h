#ifndef HEAPS
#define HEAPS

#include <algorithm>
#include <queue>

template<typename T>
struct binary_heap
{
        binary_heap( T* array, size_t size )
            : size(size)
        {
            data.assign( array, array + size + 1 );
        }

        void heapify()
        {
            for( size_t i = size / 2; i >= 0; i-- )
                sift_down( i );
        }

        void sift_down( size_t i )
        {
            size_t size = data.size();
            while( true )
            {
                size_t id_l = 2 * i + 1;  // index of left child
                size_t id_r = 2 * i + 2;  // index of right child
                size_t max = i;           // index of largest child

                if( id_l < size && data[id_l] > data[max] )
                    max = id_l;

                if( id_r < size && data[id_r] > data[max] )
                    max = id_r;

                if( max == i )
                    break;

                std::swap( data[i], data[max] );
                i = max;
            }
        }

        void sift_up(size_t i)
        {
            int parent = ( i - 1 ) / 2;
            while( i > 0 && data[parent] < data[i] )
            {
                swap( data[parent], data[i] );
                i = parent;
                parent = ( i - 1 ) / 2;
            }
        }

        void push_heap( T elem )
        {
            data.push_back( elem ); // push new element at the end of the array. It may break balance
            int i = data.size() - 1;
            sift_up(i); // sift it up to make balance
        }

        T pop_heap()
        {
            T result = data[0]; // root is about to be returned

            int size = data.size();
            data[0] = data[size - 1]; // move last element to root which is breaks balance
            data.erase( data.begin() + size - 1 ); // removing data[size-1] which is root now
            sift_down( 0 ); // sift down root value to make balance

            return result;
        }


private:
        size_t size;
        std::vector<T> data;
};

#endif // HEAPS

