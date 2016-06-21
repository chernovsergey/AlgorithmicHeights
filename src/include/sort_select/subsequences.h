#ifndef SUBSEQUENCES_H
#define SUBSEQUENCES_H

#include <vector>

template<typename T>
std::vector<int> longest_increasing_subseq( std::vector<T> array )
{
    auto N = array.size();
    std::vector<int> dest( N );
    std::vector<int> parent( N );

    for( int i = 0; i < N; ++i )
    {
        dest[i] = 1;
        parent[i] = -1;

        for( int j = 0; j < i; ++j )
        {
            if( array[j] < array[i]  &&  dest[i] < 1 + dest[j] )
            {
                parent[i] = j;
                dest[i] = 1 + dest[j];
            }
        }
    }


    // Obtain path
    std::vector<int> path;
    auto argmax = std::distance( dest.begin(), std::max_element( dest.begin(), dest.end() ) );

    T LIS_length = dest[argmax];
    ( void )LIS_length;

    while( argmax != -1 )
    {
        path.push_back( argmax );
        argmax = parent[argmax];
    }
    reverse( path.begin(), path.end() );

    return path;
}

#endif // SUBSEQUENCES_H
