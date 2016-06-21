#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <cmath>

template<typename Key, typename Hash = std::hash<Key>>
struct BloomFilter
{
        /*
        * Bloom filter optimal parameters:
        *
        *   - False positive error is p = (1 - exp((-k*n)/m))^k
        *   - Filter size is m = -(n*ln_p)/(ln2)^2, where n is number of inserted keys
        *   - Number of hash functions is k = (m/n)*ln2
        */

    private:
        size_t filter_size;
        size_t num_hashers;
        const uint64_t prime;         //supposed to be big prime
        std::vector<bool> storage;

        Hash hasher;
        std::vector<uint64_t> a;
        std::vector<uint64_t> b;

        inline size_t next_hash( Key key , size_t i ) const
        {
            return ( ( a[i] * hasher( key ) + b[i] ) % prime ) % filter_size;
        }

    public:
        BloomFilter( size_t n_keys, float fp_rate = 0.05, uint64_t p = 179426081 )
            : prime( p )
        {
            filter_size = ( double ) - 1 / std::pow( std::log( 2 ), 2 ) * n_keys * std::log( fp_rate );
            num_hashers = filter_size / n_keys * std::log( 2 );
            storage.resize( filter_size );

            // generate and memorize <a> and <b> parameters for
            // hash function family size of <count_hashers>
            srand( 42 );
            for( size_t i = 0; i < num_hashers; ++i )
            {
                a.emplace_back( rand() % p + 1 );
                b.emplace_back( rand() % p );
            }
        }

        void add( Key key )
        {
            for( size_t i = 0; i < num_hashers; ++i )
                storage[next_hash( key , i )] = true;
        }

        bool maybe_contains( Key const & key ) const
        {
            for( size_t i = 0; i < num_hashers; ++i )
                if( storage[next_hash( key, i )] == false )
                    return false;

            return true;
        }

};

#endif // BLOOM_FILTER_H
