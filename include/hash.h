#ifndef HASH
#define HASH

#include <vector>
#include <map>

template <typename K, typename V, typename Hashfunc>
struct HasTable_Chaining
{
    private:
        template<typename U, typename W>
        struct tree_chain_t;

    public:
        HasTable_Chaining( size_t size, Hashfunc func = std::hash<K>{} )
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

#endif // HASH

