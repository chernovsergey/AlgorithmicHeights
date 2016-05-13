#ifndef TREE
#define TREE

#include <memory>

template<typename T>
struct binary_search_tree
{
        typedef T value_type;
        typedef value_type& reference;
        typedef value_type const& const_reference;
        typedef value_type* pointer;
        typedef value_type const* const_pointer;
        typedef size_t size_type;

    private:
        struct Node;

    public:
        binary_search_tree()
            : root( nullptr )
            , size_( 0 )
        {}

        void insert( T key )
        {
            auto new_node = std::make_shared<Node>( key );
            std::shared_ptr<Node> parent( nullptr );

            if( empty() )
            {
                root = new_node;
                size_++;
                return;
            }

            auto curr = root;
            while( curr )
            {
                parent = curr;
                if( new_node->val > curr->val )
                    curr = curr->right;
                else if( new_node->val < curr->val )
                    curr = curr->left;
                else
                    return;
            }

            if( new_node->val < parent->val )
                parent->left = new_node;
            else
                parent->right = new_node;

            size_++;
        }

        value_type find( value_type key )
        {
            T result;
            auto curr = root;
            while( curr )
            {
                if( key > curr->val )
                    curr = curr->right;
                else if( key < curr->val )
                    curr = curr->left;
                else if( curr->val == key )
                {
                    result = curr->val;
                    return result;
                }
            }
            throw KeyNotFoundException();
        }

        void remove( value_type key )
        {

        }

        binary_search_tree& operator = ( binary_search_tree rhs )
        {
            std::swap( size_, rhs.size_ );
            std::swap( root, rhs.root );
            return *this;
        }

        bool empty()
        {
            return size_ == 0;
        }

        void clear( std::shared_ptr<Node> const& node )
        {
            if( node )
            {
                if( node->left )
                    clear( node->left );
                if( node->right )
                    clear( node->right );
                node.reset();
            }
        }

        T max( std::shared_ptr<Node> const& node )
        {
            if( node->right == nullptr )
                return node->val;
            max( node->right );
        }

        T min( std::shared_ptr<Node> const& node )
        {
            if( node->left == nullptr )
                return node->val;
            min( node->left );
        }

        void inOrder( std::shared_ptr<Node> const& node )
        {
            if( node != nullptr )
            {
                if( node->left )
                    inOrder( node->left );

                std::cout << node->val << std::endl;

                if( node->right )
                    inOrder( node->right );
            }
        }

        void preOrder( std::shared_ptr<Node> const& node )
        {
            if( node != nullptr )
            {
                std::cout << node->val << std::endl;

                if( node->left )
                    inOrder( node->left );

                if( node->right )
                    inOrder( node->right );
            }
        }

        void postOrder( std::shared_ptr<Node> const& node )
        {
            if( node != nullptr )
            {
                if( node->left )
                    inOrder( node->left );

                if( node->right )
                    inOrder( node->right );

                std::cout << node->val << std::endl;

            }
        }


        std::shared_ptr<Node> inorderSuccessor()
        {}

        std::shared_ptr<Node> inorderPredecessor()
        {}

    private:

        std::shared_ptr<Node> root;
        int size_ = 0;

        struct Node
        {
            value_type val;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;

            Node( value_type key ):
                val( key ),
                left( nullptr ),
                right( nullptr )
            {}
        };

        struct KeyNotFoundException : public std::runtime_error
        {};
};

#endif // TREE

