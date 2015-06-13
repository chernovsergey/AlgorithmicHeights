#ifndef BST_H
#define BST_H
#include <memory>
#include <iostream>
#include <assert.h>

struct KeyNotFoundException : public std::exception{
    std::string s;
    KeyNotFoundException(std::string _s):
        s(_s){}

    ~KeyNotFoundException() throw(){}

    const char* what() const throw(){
        return s.c_str();
    }
};

template<typename T>
class BST{

protected:

    struct Node{
        T val;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(T key):
            val(key),
            left(nullptr),
            right(nullptr)
        {}
    };

    std::shared_ptr<Node> root;
    int count_nodes = 0;

public:
    BST():
        root(nullptr),
        count_nodes(0)
    {}

    ~BST(){
        inOrder(root);
        cout << endl;
        preOrder(root);
        cout << endl;
        postOrder(root);
        cout << endl;
        cout << min(root) << endl;
        cout << max(root) << endl;
        clear(root);
    }

    BST& operator = (BST rhs) {
        this->swap(rhs);
    }

    BST& operator = (BST&& rhs) {
        this->swap(rhs);
    }

    bool isEmpty(){
        return root == nullptr;
    }

    virtual void insert(T key){

        //Creating new node
        std::shared_ptr<Node> new_node(new Node(key));
        std::shared_ptr<Node> parent(nullptr);

        //In case new tree
        if(isEmpty()){
            root = new_node;
            count_nodes++;
        }
        else{

            //Searchinf for the place to insert
            auto curr = root;
            while(curr){
                parent = curr;
                if(new_node->val > curr->val){
                    curr = curr->right;
                }
                else if(new_node->val < curr->val){
                    curr = curr->left;
                }
                // keys must be unique
                else{
                    return;
                }
            }

            if(new_node->val < parent->val)
                parent->left = new_node;
            else
                parent->right = new_node;

            count_nodes++;
        }
    }

    virtual T find(T key){
        T result;
        auto curr = root;
        while(curr){
            if(key > curr->val){
                curr = curr->right;
            }
            else if(key < curr->val){
                curr = curr->left;
            }
            else if(curr->val == key){
                result = curr->val;
                return result;
            }
        }
        throw KeyNotFoundException("Key not found");
    }

    virtual void remove(T key){

    }

    void clear(std::shared_ptr<Node> node){
        if(node){
            if(node->left)
                clear(node->left);
            if(node->right)
                clear(node->right);
            node.reset();
        }
    }

    //auxillary
    T max(std::shared_ptr<Node> node){
        if(node->right == nullptr)
            return node->val;
        max(node->right);
    }

    T min(std::shared_ptr<Node> node){
        if(node->left == nullptr)
            return node->val;
        min(node->left);
    }

    void inOrder(std::shared_ptr<Node> node){
        if(node != nullptr){
            if(node->left)
                inOrder(node->left);

            std::cout << node->val << std::endl;

            if(node->right)
                inOrder(node->right);
        }
    }

    void preOrder(std::shared_ptr<Node> node){
        if(node != nullptr){
            std::cout << node->val << std::endl;

            if(node->left)
                inOrder(node->left);

            if(node->right)
                inOrder(node->right);
        }
    }

    void postOrder(std::shared_ptr<Node> node){
        if(node != nullptr){
            if(node->left)
                inOrder(node->left);

            if(node->right)
                inOrder(node->right);

            std::cout << node->val << std::endl;

        }
    }

    //later
    std::shared_ptr<Node> inorderSuccessor(){}

    std::shared_ptr<Node> inorderPredecessor(){}
};
#endif // BST_H
