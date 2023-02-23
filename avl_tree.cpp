#include<iostream>

using namespace std;

template<typename T>
class node {
public:
    T key;
    int height;
    node *left;
    node *right;

    node() {
        height = 0;
        left = nullptr;
        right = nullptr;
    }

    node(T k, node *l, node *r) : key(k), left(l), right(r), height(0) {};

    node(T k) {
        height = 1;
        key = k;
        left = NULL;
        right = NULL;
    }
};

template<typename T>
class AVL {
public:
    node<T> *root = NULL;
    int num;

    void insert(T x) {
        root = insertUtil(root, x);
    }

    void remove(T x) {
        node<T> *del = searchUtil(root, x);
        if(del != NULL)
            root = removeUtil(root, del);
    }

    node<T> *search(T x) {
        return searchUtil(root, x);
    }

    void inorder() {
        inorderUtil(root);
        cout << endl;
    }

private:
    int height(node<T> *head) {
        if (head == NULL) return 0;
        return head->height;
    }

    node<T> *rightRotation(node<T> *head) {
        node<T> *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node<T> *leftRotation(node<T> *head) {
        node<T> *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node<T> *leftRightRotation(node<T> *head) {
        head->left = leftRotation(head->left);
        return rightRotation(head);
    }

    node<T> *rightLeftRotation(node<T> *head) {
        head->right = rightRotation(head->right);
        return leftRotation(head);
    }

    // Traverse and print AVL tree
    void inorderUtil(node<T> *head) {
        if (head == NULL) return;
        inorderUtil(head->left);
        cout << head->key << " ";
        inorderUtil(head->right);
    }

    node<T> *insertUtil(node<T> *head, T x) {
        // TODO: finish insertUtil
        if (root == nullptr) {
            auto *tmp = new node<T>(x);
            root = tmp;
            return root;
        }
        if (head == NULL) {
            head = new node<T>(x, nullptr, nullptr);
        }
        else if (x < head->key) {//key is inserted to the left tree
            head->left = insertUtil(head->left, x);
            //The method has found the position.
            if(height(head->left) - height(head->right) == 2) {
                if(x < (head->left->key)) head = rightRotation(head);
                else head = leftRightRotation(head);
            }
        }
        else if (x > head->key) {// key is inserted to the right tree
            head->right = insertUtil(head->right, x);
            if(height(head->right) - height(head->left) == 2) {
                if(x > (head->right->key)) head = leftRotation(head);
                else head = rightLeftRotation(head);
            }
        }
        else cerr << "[Invalid Insert]Insert the same node is not allowed\n";
        head->height = max(height(head->left),height(head->right)) + 1;
        return head;
    }

    node<T> *removeUtil(node<T> *head, node<T> *del) {
        // TODO: finish removeUtil
        //case 1 : delete leaf node
        //case 2 : delete a node which only has right child or left child
        //case 3 : delete a node which has both left child and right child
        if(head == NULL || del == NULL) return NULL;

        if(del->key < head->key) {//del is in the left tree
            head->left = removeUtil(head->left, del);
            //the method has found the destination
            if(height(head->right) - height(head->left) == 2) {
                node<T> *r = head->right;
                if(height(r->left) > height(r->right)) head = rightLeftRotation(head);
                else head = leftRotation(head);
            }
        }
        else if(del->key > head->key) {//del is in the right tree
            head->right = removeUtil(head->right, del);
            //the method has found the destination
            if(height(head->left)-height(head->right) == 2) {
                node<T> *l =head->left;
                if(height(l->right) > height(l->left)) head = leftRightRotation(head);
                else head = rightRotation(head);
            }
        }
        else {// del is the head
            if((head->left != NULL) && (head->right != NULL)) { //left and right are not empty
                if(height(head->left) > height(head->right)) {//left.h > right.h
                    node<T> *max = maximum(head->left);
                    head->key = max->key;
                    head->left = removeUtil(head->left, max);
                }
                else {
                    node<T> *min = minimum(head->right);
                    head->key = min->key;
                    head->right = removeUtil(head->right, min);
                }
            }
            else {//node has one child
                node<T> *tmp = head;
                head = head->left != NULL ? head->left : head->right;
                delete tmp;
            }
        }
        return head;
    }

    node<T> *searchUtil(node<T> *head, T x) {
        T k = head->key;
        if (head == NULL || head->key == x) return head;
        if (k > x) return searchUtil(head->left, x);
        if (k < x) return searchUtil(head->right, x);
    }
    node<T> *maximum(node<T> *head) {
        if(head == NULL) return NULL;
        while(head->right != NULL) {
            head = head->right;
        }
        return head;
    }
    node<T> *minimum(node<T> *head) {
        if(head == NULL) return NULL;
        while(head->left != NULL) {
            head = head->left;
        }
        return head;
    }
};


template<typename T>
class BST {
public:
    node<T> *root;
    int num;
    BST(){root = nullptr, num = 0;};

public:
    void insert(T x) {
        node<T> *ans = new node<T>(x);
        if(root == nullptr) root = ans;
        node<T> *z = root;
        node<T> *des = root;
        while(z != nullptr) {
            des = z;
            if(x > z->key) z = z->right;
            else if(x < z->key) z = z->right;
            else cerr << "[Invalid Insert]Insert the same enum.\n";
        }
        if(ans->key > des->key) des->right = ans;
        else if(ans->key < des->key) des->left = ans;
    }
    void remove(T x) {
        //case 1: without left or right;
        //case 2: has only left or right;(judge the node is root or not)
        //case 3: has both left and right;
        if(root == nullptr) {
            cerr << "[Invalid Remove]The BST is empty.";
            return;
        }
        node<T> *del = root;
        node<T> *delP = root;
        while(x != del->key) {
            delP = del;
            if(x > del->key) del = del->right;
            else if(x < del->key) del = del->left;
        }
        if(del->left == nullptr && del->right == nullptr) {

        }
    }
    node<T> * search(T x) {

    }
};


int main() {
    AVL<int> avl;
    BST<int> bst;
    AVL<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    tree.insert(16);
    tree.insert(15);
    tree.insert(14);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(10);
    tree.insert(8);
    tree.insert(9);


    tree.inorder();
    cout << endl;

    tree.remove(8);
    tree.inorder();
    cout << endl;
    tree.remove(7);
    tree.remove(6);
    tree.inorder();
    cout << endl;

    return 0;
    // Design your program
}





