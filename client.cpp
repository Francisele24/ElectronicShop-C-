
#include <iostream>
#include "store.cpp"
using namespace std;

//Doubly linked list to manage the queue: 
//the Queue is used to implement our CART
struct cart
{
    item Data;
    cart* nextItem;
    cart* prevItem;
};

//Single linked list to manage the stack:
//the stack is used to implement ORDER LIST
struct order {
    item Data;
    order* nextItem;
};

//class custumer: is the stucture for our CLIENTS
class customer {
private:
    string name;          //The name of the CUSTOMER
    string address;       //The address of the CUSTOMER            
    cart* customHead;
    cart* customTail;
    order* orderHead;
    int cartSize;         //The current size of the doubly linked list CART
    store products;       //Object of class store to implemnt the view of the catalogue

public:
    //Constructor
    customer(string Name, string ads) {
        name = Name;
        address = ads;
        cartSize = 0;
        customHead = customTail = NULL;
        orderHead = NULL;    
    }

    string getAddress() {
        return address;
    }

    void setProducts(store theCatalogue) {  //Initializes the store object
        products = theCatalogue;
    }

    //Caltalogue
    void catalogue() {
        cout << "This  is our catalogue\n";    //Displays the catalogue using the store object 
        
        products.printTree();
    }

    item find(string tosearch) {      
        return products.searchProduct(tosearch);
        //Function, get a string and search in the catologue 
        //if there is an item with name of the string and return the item.
    }

    bool cartIsEmpty() {        //To check if your cart is empty or not
        if (customHead == NULL)
            return true;
        else
            return false;
    }

    void search(){
      products.search();
    }

    void addToCar(string theItem)   //Functiom that adds an item to your cart (enqueue)
    {
        item itemToCart = find(theItem);
        cart* newItem = new cart();
        newItem->Data = itemToCart;
        newItem->nextItem = NULL;
        newItem->prevItem = NULL;

        if (customHead == NULL) {
            customHead = customTail = newItem;
        }
        else {
            customTail->nextItem = newItem;
            newItem->prevItem = customTail;
            customTail = newItem;
        }
        cout << "Item added to the cart: " << newItem->Data.getName() << endl;
        cartSize++;
    }

    void DisplayCustomCart() {   //Fucntion that displays the customer's cart
        cart* temp = customHead;
        int count = 1;
        if (customHead == NULL) {
            cout << "Your car is empty" << endl;
            return;
        }
        else {
            while (temp != NULL) {
                cout << count << ' ';
                temp->Data.disp();
                temp = temp->nextItem;
                count++;
            }
            cout << endl << "You currently have " << numberOfItems() << " items in your cart\n";
        }
    }

    void CheckOutLastItem() {       //Function to check out the last item of your cart (dequeue)
        cart* temp = customHead;
        if (customHead == NULL) {
            cout << "Your cart is empty" << endl;
            return;
        }
        else {
            customHead = customHead-> nextItem;
            cout << "You checked out for: " << temp->Data.getName() << endl;
            addOrder(temp->Data); // Save a checked out item to the order list (push)
            delete temp;
            cartSize--;
        }
    }

    void carCheckout() {    // Function to check out all the items in the cart 
        cart* temp = customHead;
        int count = 1;
        if (customHead == NULL) {
            cout << "Your car is empty" << endl;
            return;
        }
        else {
            while (temp != NULL) {
                cout << count << ' ';
                CheckOutLastItem();
                temp = temp->nextItem;
                count++;
            }
            cout << endl;
        }
    }

    void deleteHead() {     //Function that deletes the head if needed
        if (customHead != NULL) {
            cart* temp = customHead;
            cout << "You checked out for: " << customHead->Data.getName() << endl;
            customHead = customHead->nextItem;
            addOrder(temp->Data); // Save a checked out item to the order list (push)
            temp = NULL;
            cartSize--;
        }
        else {
            cout << "Your cart is empty" << endl;
        }
    }


    void CheckoutForAnyItem() {  // Function that checks out a specific item from the cart
        if (cartIsEmpty() == true) {
            cout << "Your cart is empty" << endl;
        }
        else {
            int position;
            cout << "Enter the number you would like to check out\n";
            cin >> position;

            if (position == 1) {
                deleteHead(); // Call the deleteHead function if the user chooses to delete the first item
            }
            else if (position == cartSize) { 
                CheckOutLastItem();
            }
            else {
                cart* objective = customHead;
                cart* previous = customHead;
                for (int x = 1; x < position; x++) {
                    previous = objective;
                    objective = objective->nextItem;
                }

                previous->nextItem = objective->nextItem;
                objective->nextItem->prevItem = previous;
                cout << "You checked out for: " << objective->Data.getName() << endl; 
                addOrder(objective->Data); // Save a checked out item to the order list (push)
                objective = NULL;
                cartSize--;
            }
        }
    }

    int numberOfItems() {  // Function to know the number of items in your cart (queue: getSize)
        return cartSize;
    }

    //Order List (stack)
    void addOrder(item value) { //Function to save an item to the order list (push)
        order* newItem;
        if (orderHead == NULL) {
            orderHead = newItem;
        }
        else {
            order* temp;
            temp->Data = value;
            temp->nextItem = orderHead;
            orderHead = temp;
        }
    }

    void returnLastOrder() { // Function that removes and return the last item in the order list (POP)
        order* temp = orderHead;
        if (orderHead == NULL) {
            cout << "Sorry, you haven't order any item yet\n";
        }
        else {
            orderHead = orderHead->nextItem;
            temp->Data.disp();
            cout << "Was sussecesfully returned\n";
            delete temp;
        }
        cout << endl;
    }

    void displayOrderList() {  //Display the Order list
        order* temp = orderHead;
        if (orderHead == NULL) {
            cout << "Sorry, you haven't order any item yet\n";
        }
        else {
            int count = 1;
            cout << "\nThis are your previus orders: \n" << endl;
            while (temp != NULL) {
                cout << count << ' ';
                temp->Data.disp();
                temp = temp->nextItem;
                count++;
            }
            cout << endl;
        }
    }
};
