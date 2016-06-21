#ifndef LIST
#define LIST

#include <memory>

// TODO merge, sort

template<typename T>
struct LinkedList
{
        typedef T value_type;
        typedef value_type & reference;
        typedef value_type const & const_reference;
        typedef value_type * pointer;
        typedef value_type const * const_pointer;
        typedef size_t size_type;

    private:
        struct Node;

    public:
        LinkedList()
            : size_( 0 )
            , head_( nullptr )
        {}

        void push_back( value_type val )
        {
            auto new_element = std::make_shared<Node>( val, nullptr );
            if( head_ == 0 )
            {
                head_ = new_element;
                ++size_;
                return;
            }

            auto node = move_to_end();
            node->next = new_element;
            ++size_;
        }

        void push_front( value_type val )
        {
            auto new_element = std::make_shared<Node>( val, head_ );
            head_ = new_element;
            ++size_;
        }

        void pop_front()
        {
            head_ = head_->next;
            --size_;
        }

        void pop_back()
        {
            if( head_ == nullptr )
            {
                return;
            }

            if( head_->next == nullptr )
            {
                pop_front();
            }

            auto node = move_to_end();
            node->next = nullptr;

            --size_;
        }

        template<typename ...Args>
        void emplace_back( Args...args )
        {
            push_back( T( std::forward<Args>( args )... ) );
        }

        template<typename ...Args>
        void emplace_fromt( Args...args )
        {
            push_front( T( std::forward<Args>( args ) )... );
        }

        size_t size() const
        {
            return size_;
        }

        bool empty() const
        {
            return size_ == 0;
        }

        void clear()
        {
            head_.reset();
            size_ = 0;
        }

        friend std::ostream & operator<<( std::ostream & out , LinkedList<T> list )
        {
            for( auto p = list.head_; p != nullptr; p = p->next )
            {
                out << p->value << " ";
            }

            return out;
        }

    private:
        size_t size_;
        std::shared_ptr<Node> head_;

        Node * move_to_end()
        {
            auto node = head_;
            while( node->next != nullptr )
            {
                node = node->next;
            }

            return node.get();
        }

        struct Node
        {
            value_type value;
            std::shared_ptr<Node> next;

            Node( value_type val, std::shared_ptr<Node> nxt = nullptr )
                : value( val )
                , next( nxt )
            {}
        };
};

#endif // LIST

