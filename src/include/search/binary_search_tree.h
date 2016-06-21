#ifndef TREE
#define TREE

#include <memory>
#include <stdexcept>

template<typename K, typename V>
struct binary_search_tree
{
    private:
        template<typename KEY, typename VAL>
        struct TreeNode;

        typedef TreeNode<K, V> Node;

    public:
        binary_search_tree() = default;

        void insert( K const & k, V const & v )
        {
            if( contains( k ) )
                throw KeyExistsException();

            auto new_one = std::make_unique<Node>( k, v );

            Node * nearest = traverse( k );
            if( !nearest )
            {
                root = std::move( new_one );
                return;
            }

            new_one->parent_ = nearest;

            if( k > nearest->key_ )
                nearest->insert_right( std::move( new_one ) );
            else
                nearest->insert_left( std::move( new_one ) );
        }


        void remove( K const & k )
        {
            Node* nearest = traverse(k);
            if(nearest->key_ != k)
                throw KeyNotFoundException();

            // only left subtree
            if(nearest->right_ == nullptr && nearest->left_ != nullptr)
            {

            }

            // only right subtree
            if(nearest->right_ != nullptr && nearest->left_ == nullptr)
            {

            }

            // if both exists:
            // 1) find node with minimum key in the right subtree
            // 2) switch it with the current node
            // 3) remove that node
            if(nearest->right_ != nullptr && nearest->left_ != nullptr)
            {

            }

        }

        V & find( K const & k )
        {
            Node * result = traverse( k );
            if( !result || ( k != result->key_ ) )
                throw KeyNotFoundException();

            return result->val_;
        }


        bool contains( K const & k )
        {
            try
            {
                find( k );
                return true;
            }
            catch( KeyNotFoundException & ex )
            {
                return false;
            }
        }

    private:
        Node * traverse( K const & k )
        {
            if( !root )
                return nullptr;

            Node * curr = root.get();
            while( true )
            {
                if( curr->key_ == k )
                    break;

                Node * next = ( k > curr->key_ ) ? curr->right() : curr->left();
                if( !next )
                    break;

                curr = next;
            }
            return curr;
        }


    private:

        std::unique_ptr<Node> root;
        int size_ = 0;

        template<typename KEY, typename VAL>
        struct TreeNode
        {
            TreeNode( KEY const & key, VAL const & val )
                : key_( key )
                , val_( val )
                , parent_( nullptr )
                , left_( nullptr )
                , right_( nullptr )
            {}

            ~TreeNode() = default;

            TreeNode( TreeNode && src ) = default;
            TreeNode & operator=( TreeNode && src ) = default;

            TreeNode( const TreeNode & src ) = delete;
            TreeNode & operator=( const TreeNode & src ) = delete;

            void insert_right( std::unique_ptr<TreeNode> && ptr )
            {
                right_ = std::move( ptr );
            }

            void insert_left( std::unique_ptr<TreeNode> && ptr )
            {
                left_ = std::move( ptr );
            }

            std::unique_ptr<TreeNode> take_right()
            {
                return std::move( right_ );
            }

            std::unique_ptr<TreeNode> take_left()
            {
                return std::move( left_ );
            }

            TreeNode * right()
            {
                return right_.get();
            }

            TreeNode * left()
            {
                return left_.get();
            }

            KEY key_;
            VAL val_;
            TreeNode * parent_;
            std::unique_ptr<TreeNode> left_;
            std::unique_ptr<TreeNode> right_;

        };

        struct KeyNotFoundException
        {};

        struct KeyExistsException
        {};
};

#endif // TREE
