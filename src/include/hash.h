#ifndef HASH
#define HASH

#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include "sort.h"

template <typename K, typename V, typename Hashfunc>
struct HasTable_Chaining
{
    private:
        template<typename U, typename W>
        struct tree_chain_t;

    public:
        HasTable_Chaining( size_t size, Hashfunc func = std::hash<K> {} )
            : table( size )
            , hash_func( func )
        {}

        ~HasTable_Chaining()
        {
            for( auto i : table )
                i.clear_all();
        }

        void put( K key, V value )
        {
            int hash = hash_func( key );
            table[hash].put( key, value );
        }

        V get( K key )
        {
            int hash = hash_func( key );
            V result = table[hash].get( key );
            return result;
        }

        void remove( K key )
        {
            int hash = hash_func( key );
            table[hash].remove( key );
        }

    private:
        Hashfunc hash_func;
        vector<tree_chain_t<K, V>> table;

        template<typename U, typename W>
        struct tree_chain_t
        {
                void put( U key, W value )
                {
                    map_.emplace( key, value );
                }

                V get( U key )
                {
                    return map_[key];
                }

                void remove( U key )
                {
                    map_.erase( key );
                }

                void clear_all()
                {
                    map_.clear();
                }

            private:
                std::map<U, W> map_;
        };
};


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


template<typename Key, typename Hash = std::hash<Key>>
struct CountMinSketch
{
    /*
    *
    * Optimal width is sketch_width = 2.71 / epsilon
    * Optimal number of hash functions is sketch_depth = ln(1 / delta)
    *
    */

    protected:
        const size_t sketch_width;
        const size_t sketch_depth;
        const size_t prime;

        std::vector<uint64_t> a, b;
        Hash hasher;

        using CountArray = std::vector<uint64_t>;
        using CountTable = std::vector<CountArray> ;
        CountTable storage;

        size_t seen_count = 0;

        inline size_t next_hash(Key key, size_t i)
        {
            return ((a[i] * hasher(key) + b[i]) % prime ) % sketch_width;
        }

    public:
        CountMinSketch(float delta = 0.01, float epsilon = 0.001, uint64_t prime = 179426081)
            : sketch_width( std::ceil(std::exp(1) / epsilon))
            , sketch_depth( std::ceil(std::log(1/delta)))
            , prime(prime)
        {

            storage.assign(sketch_depth, CountArray(sketch_width));

            srand(42);
            for(size_t i = 0; i < sketch_depth; ++i)
            {
                a.emplace_back(rand() % prime + 1);
                b.emplace_back(rand() % prime);
            }
        }

        void update(Key key)
        {
            for(size_t i = 0; i < sketch_depth; ++i)
                storage[i][next_hash(key, i)] += 1;

            ++seen_count;
        }

        uint64_t count(Key key)
        {
            uint64_t min_count = std::numeric_limits<uint64_t>::max();
            for(size_t i = 0; i < sketch_depth; ++i)
                min_count = std::min(min_count, storage[i][next_hash(key, i)]);

            return min_count;
        }
};

template<typename Key, typename Hash = std::hash<Key> >
struct CountMeanMinSketch : public CountMinSketch<Key>
{
    /*
     *
     *  Correction to noise. Look at F. Deng, D. Rafiei paper
     *  "New Estimation Algorithms for Streaming Data: Count-min Can Do More"
     *
     */

    using CountMinSketch<Key>::seen_count;
    using CountMinSketch<Key>::sketch_depth;
    using CountMinSketch<Key>::sketch_width;
    using CountMinSketch<Key>::storage;
    using CountMinSketch<Key>::next_hash;


    CountMeanMinSketch(float delta = 0.01, float epsilon = 0.001, uint64_t prime = 179426081)
        : CountMinSketch<Key>(delta, epsilon, prime)
    {}

    uint64_t count(Key key)
    {
        std::vector<uint64_t> estimations(sketch_depth);
        uint64_t count_value = 0;
        uint64_t noise_value = 0;
        for(size_t i = 0; i < sketch_depth; ++i)
        {
            count_value = storage[i][next_hash(key, i)];
            noise_value = (seen_count - count_value) / (sketch_width - 1);
            estimations[i] = count_value - noise_value;
        }

        uint64_t result = quickselect(estimations, 0, sketch_depth - 1, sketch_depth/2);
        return result;
    }
};

#endif // HASH

