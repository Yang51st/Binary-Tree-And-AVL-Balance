#include "binary-search-tree.h"
#include<iostream>
#include<queue>
using namespace std;
BinarySearchTree::Node::Node(DataType newval) {
    val=newval;
    left= nullptr;
    right= nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {

}

BinarySearchTree::BinarySearchTree() {
    size_=0;
    root_= nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    while(size()>0){
        remove(min());
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* current=root_;
    while(true){
        if(current->right== nullptr){
            break;
        }
        current=current->right;
    }
    return current->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* current=root_;
    while(true){
        if(current->left== nullptr){
            break;
        }
        current=current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const {
    unsigned int depth=0;
    queue<Node*> que;
    queue<Node*> quel;
    que.push(root_);
    while(!que.empty()) {
        while (!que.empty()) {
            Node *temp = que.front();
            que.pop();
            if (temp->left != nullptr) {
                quel.push(temp->left);
            }
            if (temp->right != nullptr) {
                quel.push(temp->right);
            }
        }
        que=quel;
        depth++;
        while(!quel.empty()){
            quel.pop();
        }
    }
    return depth-1;
}

void BinarySearchTree::print() const {
    if(root_== nullptr){
        cout<<"empty"<<endl;
        return;
    }
    queue<Node*> que;
    queue<Node*> quel;
    que.push(root_);
    while(!que.empty()) {
        while (!que.empty()) {
            Node *temp = que.front();
            que.pop();
            cout<<temp->val<<" ";
            if (temp->left != nullptr) {
                quel.push(temp->left);
            }
            if (temp->right != nullptr) {
                quel.push(temp->right);
            }
        }
        cout<<endl;
        que=quel;
        while(!quel.empty()){
            quel.pop();
        }
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node* current=root_;
    while(true){
        if(current== nullptr){
            return false;
        }
        if(current->val==val){
            return true;
        }
        else if(val<current->val){
            current=current->left;
        }
        else if(val>current->val){
            current=current->right;
        }
    }
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if(root_== nullptr){
        root_=new Node(val);
        size_++;
        return true;
    }
    else{
        Node* current=root_;
        while(true){
            if(val<current->val){
                if(current->left== nullptr){
                    current->left=new Node(val);
                    size_++;
                    return true;
                }
                current=current->left;
            }
            else if(val>current->val){
                if(current->right== nullptr){
                    current->right=new Node(val);
                    size_++;
                    return true;
                }
                current=current->right;
            }
            else{
                return false;
            }
        }
    }
}

bool BinarySearchTree::remove(DataType val) {
    if(!exists(val)){
        return false;
    }
    if(size_==1){
        delete root_;
        root_= nullptr;
        size_--;
        return true;
    }
    else{
        Node* current=root_;
        Node* parent= nullptr;
        while(true){
            if(val<current->val){
                parent=current;
                current=current->left;
            }
            else if(val>current->val){
                parent=current;
                current=current->right;
            }
            else{
                break;
            }
        }
        if(current->left== nullptr && current->right== nullptr){
            if(parent->left==current){
                parent->left= nullptr;
            }
            if(parent->right==current){
                parent->right= nullptr;
            }
            delete current;
            size_--;
            return true;
        }
        else if(current->left== nullptr){
            if(parent== nullptr){
                root_=current->right;
            }
            else if(parent->left==current){
                parent->left=current->right;
            }
            else if(parent->right==current){
                parent->right=current->right;
            }
            delete current;
            size_--;
            return true;
        }
        else if(current->right== nullptr){
            if(parent== nullptr){
                root_=current->left;
            }
            else if(parent->left==current){
                parent->left=current->left;
            }
            else if(parent->right==current){
                parent->right=current->left;
            }
            delete current;
            size_--;
            return true;
        }
        else{
            Node* predecessor=current->left;
            Node* pparent=current;
            while(true){
                if(predecessor->right== nullptr){
                    break;
                }
                else{
                    pparent=predecessor;
                    predecessor=predecessor->right;
                }
            }
            current->val=predecessor->val;
            if(predecessor->right== nullptr && predecessor->left== nullptr){
                if(pparent->left==predecessor){
                    pparent->left=nullptr;
                }
                else if(pparent->right==predecessor){
                    pparent->right= nullptr;
                }
                delete predecessor;
                size_--;
                return true;
            }
            else if(predecessor->left== nullptr){
                if(pparent->left==predecessor){
                    pparent->left=predecessor->right;
                }
                else if(pparent->right==predecessor){
                    pparent->right=predecessor->right;
                }
                delete predecessor;
                size_--;
                return true;
            }
            else if(predecessor->right== nullptr){
                if(pparent->left==predecessor){
                    pparent->left=predecessor->left;
                }
                else if(pparent->right==predecessor){
                    pparent->right=predecessor->left;
                }
                delete predecessor;
                size_--;
                return true;
            }
        }
    }
}
