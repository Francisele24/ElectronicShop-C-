#ifndef STORE_H
#define STORE_H


#include <iostream>
#include <string>
using namespace std;

class item {    //Class to implement the item
protected:
    string name; //Item name
    double price; //Item price

public:
    item() { //Default constructor
        name = "Name";
        price = 0.00;
    }

    item(string NAME, double PRICE) {  //Parametrized constructor
        name = NAME;
        price = PRICE;
    }

    void disp() {   
        cout << name << "_____________" << price << '$' << endl;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    void setName(string Name) {
        name = Name;
    }

    void setPrice(double Price) {
        price = Price;
    }
};

       //Linked list to implement the BINARY TREE

struct tree {     //Struct to implement the root linked list
    item value;
    tree* left;
    tree* right;
};


class store {  // Class store to implement the seller's function
protected:
    tree* root;
public:

    store() {       //Default constructor
        root = NULL;
        return;
    }

    tree* duplicate(tree* P) {  //  Returns a duplicate version of the root
        tree* duplicate;
        duplicate = new tree();
        *duplicate = *P;
        duplicate->left = NULL;
        duplicate->right = NULL;
        return duplicate;
    }

    item duplicateToSearch(tree* P) { // Returns the item of the duplicate version of the root
        tree* duplicate;
        duplicate = new tree();
        *duplicate = *P;
        duplicate->left = NULL;
        duplicate->right = NULL;
        return duplicate->value;
    }

    tree* search(string key) {               // Binary search implementation:
        tree* temp;                         //search an item on the tree using its name and returns the node

        temp = root;
        while ((temp != NULL) && (temp->value.getName() != key))
        {
            if (key < temp->value.getName())
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp == NULL) return temp;
        else
            return(duplicate(temp));
    }

    item searchProduct(string key) {      // Returns the item. It is used in the customer class
        tree* temp;

        temp = root;
        while ((temp != NULL) && (temp->value.getName() != key))
        {
            if (key < temp->value.getName())
                temp = temp->left;
            else
                temp = temp->right;
        }
        if (temp == NULL) return temp->value;
        else
            return(duplicateToSearch(temp));
    }

    void search() {  // Check if the items exits in the store
        string key;
        cout << "Enter the name\n";
        getline(cin >> ws, key);

        tree* newNode = new tree();
        newNode = search(key);
        if (newNode != NULL) {
            printItem(newNode);
            delete newNode;
        }
        else
            cout << "No item matches the input key\n";
    }

    bool insert(tree* newNode) {  // Returns true when an node is successfully added in the tree
        tree* temp;
        tree* back;

        temp = root;
        back = NULL;

        while (temp != NULL) {
            back = temp;
            if (newNode->value.getName() < temp->value.getName())
                temp = temp->left;
            else
                temp = temp->right;
        }

        if (back == NULL)
            root = newNode;
        else {
            if (newNode->value.getName() < back->value.getName())
                back->left = newNode;
            else
                back->right = newNode;
        }
        return true;
    }

    bool insert(string name, double price) { // Returns trur when an item is successfully added
        tree* newNode;

        newNode = new tree();
        item newItem(name, price);
        newNode->value = newItem;
        newNode->left = newNode->right = NULL;

        return(insert(newNode));
    }

    void printItem(tree* P) {  //Displays an item 
        P->value.disp();
    }

    void printStock(tree* P) { // Implement the in-Order 
        if (P != NULL) {
            printStock(P->left);
            printItem(P);
            printStock(P->right);

        }
    }

    void printTree() { // Call the printStock function to print all the items
        printStock(root); 
    }
};

#endif