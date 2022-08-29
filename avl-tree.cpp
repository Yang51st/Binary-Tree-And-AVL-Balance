#include "avl-tree.h";

bool AVLTree::insert(DataType val) {
    if(!BinarySearchTree::insert(val)){
        return false;
    }
    else{
        Node* closest=getRootNode();
        Node* closestParent= nullptr;
        update_AVLs(BinarySearchTree::getRootNode());
        Node* temp=getRootNode();
        Node* tempParent= nullptr;
        Node* capitalism= nullptr;
        bool flag=false;
        while(temp->val!=val){
            if(temp->avlBalance>1 || temp->avlBalance<-1){
                closestParent=tempParent;
                closest=temp;
                flag=true;
            }
            tempParent=temp;
            if(temp->val<val){
                temp=temp->right;
            }
            else{
                temp=temp->left;
            };
        }
        if(closest->avlBalance<0){
            capitalism=closest->right;
        }
        else{
            capitalism=closest->left;
        }
        if(!flag){
            return true;
        }
        //Right Rotation
        if(val<closest->val && val<capitalism->val){
            Rrot(closestParent,closest,capitalism);
        }

        //Left Rotation
        else if(val>closest->val && val>capitalism->val){
            Lrot(closestParent,closest,capitalism);
        }

        //Right-Left Rotation
        else if(val>closest->val && val<capitalism->val){
            Node* bolshevism=capitalism->left;
            Rrot(closest,capitalism,bolshevism);
            Lrot(closestParent,closest,bolshevism);
        }

        //Left-Right Rotation
        else if(val<closest->val && val>capitalism->val){
            Node* fascism=capitalism->right;
            Lrot(closest,capitalism,fascism);
            Rrot(closestParent,closest,fascism);
        }
        return true;
    }
}

bool AVLTree::remove(DataType val) {
    if(!BinarySearchTree::exists(val)){
        return false;
    }
    else{
        BinarySearchTree::remove(val);
        if(getRootNode()!= nullptr) {
            update_AVLs(BinarySearchTree::getRootNode());
            Rection(BinarySearchTree::getRootNode(), nullptr);
        }
        return true;
    }
}

int AVLTree::update_AVLs(Node* curr) {
    int lefty=0;
    int righty=0;
    if(curr->left!= nullptr){
        lefty=1+update_AVLs(curr->left);
    }
    if(curr->right!= nullptr){
        righty=1+update_AVLs(curr->right);
    }
    curr->avlBalance=lefty-righty;
    return (lefty>righty)?lefty:righty;
}

void AVLTree::Lrot(Node *alphaParent, Node *alpha, Node *A) {
    alpha->right=A->left;
    A->left=alpha;
    if(alphaParent!= nullptr){
        if(alphaParent->right==alpha){
            alphaParent->right=A;
        }
        else{
            alphaParent->left=A;
        }
    }
    else{
        *getRootNodeAddress()=A;
    }
}

void AVLTree::Rrot(Node *alphaParent, Node *alpha, Node *A) {
    alpha->left=A->right;
    A->right=alpha;
    if(alphaParent!= nullptr){
        if(alphaParent->right==alpha){
            alphaParent->right=A;
        }
        else{
            alphaParent->left=A;
        }
    }
    else{
        *getRootNodeAddress()=A;
    }
}

void AVLTree::Rection(Node* current,Node* currentParent) {
    if(current->left!= nullptr){
        Rection(current->left,current);
    }
    if(current->right!= nullptr){
        Rection(current->right,current);
    }
    update_AVLs(BinarySearchTree::getRootNode());
    if(current->avlBalance>1 || current->avlBalance<-1){
        Node* cappA= nullptr;
        if(gNode(current->left)> gNode(current->right)){
            cappA=current->left;
            if(gNode(cappA->left)>=gNode(cappA->right)){
                //Single Right
                Rrot(currentParent,current,cappA);
            }
            else{
                //Left Right
                Lrot(current,cappA,cappA->right);
                Rrot(currentParent,current,current->left);
            }
        }
        else{
            cappA=current->right;
            if(gNode(cappA->left)>gNode(cappA->right)){
                //Right Left
                Rrot(current,cappA,cappA->left);
                Lrot(currentParent,current,current->right);
            }
            else{
                //Single Left
                Lrot(currentParent,current,cappA);
            }
        }
    }
}

int AVLTree::gNode(Node *current) {
    if(current== nullptr){
        return 0;
    }
    int lefty=0;
    int righty=0;
    lefty=1+gNode(current->left);
    righty=1+gNode(current->right);
    return (lefty>righty)?lefty:righty;
}
