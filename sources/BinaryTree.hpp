#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <iostream>

namespace ariel {
    
template<typename T>
class BinaryTree{
    private:
        struct Node {
            T _data;
            bool _mark;
            Node *_left, *_right, *_parent;
            Node(const T& data, bool mark=false, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr)
                : _data(data), _left(left), _right(right), _parent(parent), _mark(mark){}
        };

        Node* _root=nullptr;
        std::set<T>tree_nodes;
        std::map<T,Node*> map;

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
            delete _root;
        }

        BinaryTree(BinaryTree &&other) noexcept{
            this->_root = other._root;
            other._root = nullptr;
        }
        
        BinaryTree& operator=(BinaryTree<T> other){
            if (this == &other){
                return *this;
            }
            delete this->_root;
            this->_root = new Node(other._root->_data);
            return *this;
        }

        T &operator*() const{
            return this->current->_data;
        }

        T *operator->() const{
            return &(this->_current->_data);
        }
        class preorder_iterator{
            private:
                std::vector<Node*>pre_it;
                Node* current; 
                unsigned long index;

            public:
                preorder_iterator(Node* root):current(root),index(0){ //constructor

                    if(current!=nullptr){
                        define_preorder(root);
                        pre_it.push_back(nullptr);
                    }
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
                    if(index<pre_it.size()-1){
                        ++index;
                        return *this;
                    }
                    current=nullptr;
                    return *this;
                }
                //i++
                preorder_iterator operator++(int) {
                    if(index<pre_it.size()){
                        preorder_iterator temp=*this;
                        ++index;
                        return temp;
                    }
                    current=nullptr;
                    return *this;
                }
                bool operator==(const preorder_iterator& other) const {
                    return this->pre_it.at(index) == other.pre_it.at(index);
                }

                bool operator!=(const preorder_iterator& other) const {
                    return pre_it.at(index) != other.pre_it.at(index);
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
                Node* current;
                unsigned long index;
            public:
                inorder_iterator(Node* root=nullptr):current(root),index(0){ //constructor
                    if(current!=nullptr){
                        define_inorder(root);
                        in_it.push_back(nullptr);
                        current=in_it.at(0);
                    }
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
                    if(index<in_it.size()-1){
                        ++index;
                        current= in_it.at(index);
                        return *this;
                    }
                    current=nullptr;
                    return *this;
                }

                //i++
                inorder_iterator operator++(int) {
                    if(index<in_it.size()){
                        inorder_iterator temp=*this;
                        ++index;
                        current= in_it.at(index-1);
                        return temp;
                    }
                    current=nullptr;
                    return *this;
                }
                
                bool operator==(const inorder_iterator& other) const {
                    return this->in_it.at(index) == other.in_it.at(index);
                }

                bool operator!=(const inorder_iterator& other) const {
                    return this->in_it.at(index) != other.in_it.at(index);
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
                postorder_iterator(Node* root=nullptr):current(root),index(0){ //constructor
                    if(current!=nullptr){
                        define_postorder(root);
                        post_it.push_back(nullptr);
                    }
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
                    if(index<post_it.size()-1){
                        ++index;
                        current= post_it.at(index);
                        return *this;
                    }
                    current=nullptr;
                    return *this;
                }
                //i++
                postorder_iterator operator++(int) {
                    if(index<post_it.size()){
                        postorder_iterator temp=*this;
                        ++index;
                        current= post_it.at(index-1);
                        return temp;
                    }
                    current=nullptr;
                    return *this;
                }
                bool operator==(const postorder_iterator& other) const {
                    return this->post_it.at(index) == other.post_it.at(index);
                }

                bool operator!=(const postorder_iterator& other) const {
                    return this->post_it.at(index) != other.post_it.at(index);
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
            map[node]=_root;
            return *this;
        }
        BinaryTree<T>& add_left(const T& node, const T& node_to_add_left){
            if(tree_nodes.count(node)==0){ //node is not in the tree
                throw"execption";
            }
            map[node_to_add_left]=new Node(node_to_add_left);
            map[node]->_left=map[node_to_add_left];
            tree_nodes.insert(node_to_add_left);
            map[node_to_add_left]->_parent=map[node];
            map[node_to_add_left]->_parent->_data=node;
            return *this;
        }
        BinaryTree<T>& add_right(const T& node, const T& node_to_add_right){
            if(tree_nodes.count(node)==0){ //node is not in the tree
                throw"execption";
            }
            map[node_to_add_right]=new Node(node_to_add_right);
            map[node]->_right=map[node_to_add_right];
            tree_nodes.insert(node_to_add_right);
            map[node_to_add_right]->_parent=map[node];
            map[node_to_add_right]->_parent->_data=node;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const BinaryTree<T> &bt){
            out<<"ss";
            return out;
        }

        preorder_iterator begin_preorder() {  
            return preorder_iterator(this->_root); 
        } 
        preorder_iterator end_preorder() {
            return preorder_iterator(nullptr); 
        }
        inorder_iterator begin_inorder() {
            return inorder_iterator(_root); 
        }
        inorder_iterator end_inorder() {
            return inorder_iterator(nullptr); 
        }
        postorder_iterator begin_postorder(){
            return postorder_iterator(_root); 
        }
        postorder_iterator end_postorder(){
            return postorder_iterator(nullptr);
        }

        inorder_iterator begin(){
            return inorder_iterator(_root); 
        }
        inorder_iterator end(){
            return inorder_iterator(nullptr); 
        }
};
}      