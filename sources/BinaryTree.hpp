#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include<algorithm>
using namespace std;
namespace ariel {
    
template<typename T>
class BinaryTree{
    private:
        struct Node {
            T _data;
            Node *_left, *_right;
            Node(const T& data, Node* left = nullptr, Node* right = nullptr)
                : _data(data), _left(left), _right(right){}
        };

        Node* _root;
        std::set<T>tree_nodes;
        
    public:
        BinaryTree(){}

        void copy_tree(Node *&this_root, Node *&other_root){
            if (other_root == NULL){
                this_root = NULL;
            }
            else{
                this_root = new Node(other_root->_data);
                copy_tree(this_root->_left, other_root->_left);
                copy_tree(this_root->_right, other_root->_right);
            }
        }

        BinaryTree(BinaryTree &other){
            if (other._root == NULL){
                _root = NULL;
            }
            else{
                copy_tree(_root, other._root);
            }
            other.tree_nodes=this->tree_nodes;
            std::set<T>tree_nodes;
            for(auto node : this->tree_nodes) {
                    other.tree_nodes.insert(node);
            }
        }
        Node* get_root(){
            return this->_root;
        }
        ~BinaryTree(){
            if (_root!=nullptr){
                delete _root;
            }
        }

        BinaryTree &operator=(BinaryTree &&other) noexcept{
            _root = other._root;
            other._root = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree &&other) noexcept{
            this->_root = other._root;
            other._root = nullptr;
        }
        
        BinaryTree& operator=(BinaryTree other){
            if (this == &other){
                return *this;
            }
            delete _root;
            _root = new Node(other._root->_data);
            return *this;
        }

        class preorder_iterator{
            private:
                std::vector<Node*>pre_it;
                Node* current; 
                unsigned long index;

            public:
                preorder_iterator(Node* root){ //constructor
                    pre_it.clear();
                    index=0;
                    define_preorder(root);
                    pre_it.push_back(nullptr);
                } 
                void define_preorder(Node* root){
                    if (root == nullptr){
                        return;
                    }
                    pre_it.push_back(root);
                    define_preorder(root->_left);
                    define_preorder(root->_right);
                } 

                //++i
                preorder_iterator &operator++() {
                    ++index;
                    return *this;
                }
                //i++
                preorder_iterator operator++(int) {
                    preorder_iterator temp=*this;
                    ++index;
                    return temp;
                }
                bool operator==(const preorder_iterator& other) const {
                    return pre_it.at(index) == other.pre_it.at(other.index);
                }

                bool operator!=(const preorder_iterator& other) const {
                    return pre_it.at(index) != other.pre_it.at(other.index);
                }
                T &operator*() {
                    return pre_it.at(index)->_data;
                }
                T *operator->() const{
                    return &(pre_it.at(index)->_data);
                }

            };
       
        class inorder_iterator{
            private:
                std::vector<Node*> in_it;
                unsigned long index;
            public:
                inorder_iterator(Node* root=nullptr){ 
                    in_it.clear();
                    index=0;
                    define_inorder(root);
                    in_it.push_back(nullptr);
                } 
                void define_inorder(Node* root){
                    if (root==nullptr){
                        return;
                    }
                    define_inorder(root->_left);
                    in_it.push_back(root);
                    define_inorder(root->_right);
                }
                const inorder_iterator &operator++() {
                    ++index;
                    return *this;
                }

                //i++
                inorder_iterator operator++(int) {
                    inorder_iterator temp=*this;
                    ++index;
                    return temp;
                }
                
                bool operator==(const inorder_iterator& other) const {
                    return this->in_it.at(index) == other.in_it.at(other.index);
                }

                bool operator!=(const inorder_iterator& other) const {
                    return this->in_it.at(index) != other.in_it.at(other.index);
                }
                T &operator*() {
                    return this->in_it.at(index)->_data;
                }
                T *operator->() const{
                    return &(this->in_it.at(index)->_data);
                }

            };

        class postorder_iterator{
            private:
                std::vector<Node*>post_it;
                Node* current;
                unsigned long index;
            public:
                postorder_iterator(Node* root=nullptr){ //constructor
                    post_it.clear();
                    index=0;
                    define_postorder(root);
                    post_it.push_back(nullptr);
                } 
                void define_postorder(Node* root){
                     if (root == nullptr){
                        return;
                    }
                    define_postorder(root->_left);
                    define_postorder(root->_right);
                    post_it.push_back(root);
                }

                //++i
                postorder_iterator &operator++() {
                    ++index;
                    return *this;
                    }
                //i++
                postorder_iterator operator++(int) {
                    postorder_iterator temp=*this;
                    ++index;
                    return temp;
                    }
                bool operator==(const postorder_iterator& other) const {
                    return this->post_it.at(index) == other.post_it.at(other.index);
                }

                bool operator!=(const postorder_iterator& other) const {
                    return this->post_it.at(index) !=other.post_it.at(other.index);
                }
                T &operator*() {
                    return this->post_it.at(index)->_data;
                }
                T *operator->() const{
                    return &(this->post_it.at(index)->_data);
                }

            };
            
        BinaryTree& add_root(const T& node){
            if(_root==nullptr){
                this->_root =new Node(node);   
            }
            else{
                this->_root->_data=node;
            }
            tree_nodes.insert(node);
            return *this;
        }
        Node *search_parent(Node *root,T parent){
            if(root==nullptr||root->_data==parent){ 
                return root;
            }
            Node *node=search_parent(root->_left, parent);
            if(node==nullptr){
                return search_parent(root->_right, parent); 
            }
            return node;
        }

        BinaryTree<T> &add_left(T parent, T child){
            Node *node=search_parent(_root, parent);
            if(node==nullptr){
                throw "parent is not exist";
            }
            if(node->_left==nullptr){
                node->_left=new Node(child);
            }
            else{
                node->_left->_data=child;
            }   
            tree_nodes.insert(child);
            return *this;
        }

        BinaryTree<T> &add_right(T parent, T child){
            Node *node=search_parent(_root, parent);
            if(node==nullptr){
                throw "parent is not exist";
            }
            if(node->_right==nullptr){
                node->_right=new Node(child);
            }
            else{
                node->_right->_data=child;
            }
            tree_nodes.insert(child);
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& out, const BinaryTree<T> &bt){
            out<<"ss";
            return out;
        }

        preorder_iterator begin_preorder() {  
            return preorder_iterator(_root); 
        } 
        preorder_iterator end_preorder(){
            return preorder_iterator(nullptr); 
        }
        inorder_iterator begin_inorder() const{
            return inorder_iterator(_root); 
        }
        inorder_iterator end_inorder()const{
            return inorder_iterator(nullptr); 
        }
        postorder_iterator begin_postorder(){
            return postorder_iterator(_root); 
        }
        postorder_iterator end_postorder(){
            return postorder_iterator(nullptr);
        }

        inorder_iterator begin()const{
            return inorder_iterator(_root); 
        }
        inorder_iterator end()const{
            return inorder_iterator(nullptr); 
        }
};
}      