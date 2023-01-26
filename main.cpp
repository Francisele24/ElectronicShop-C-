#include <iostream>
#include <string>
#include "store.cpp"
#include "client.cpp"
using namespace std;

int main() {

	store seller;
	tree* newProduct;

	//Offered items in the store;
	newProduct = new tree();
	//Add new item to the store
	newProduct->value.setName("Farcry 6");
	newProduct->value.setPrice(69);
	seller.insert(newProduct);
	seller.insert("Iphone 13", 1199);
	seller.insert("Iphone 12", 1099);
	seller.insert("Samsung Galaxy S22", 1299);
	seller.insert("Samsung Galaxy S21", 1199);
	seller.insert("Playstation 5", 499);
	seller.insert("Playstation 4", 299);
	seller.insert("Mac Book Pro", 3999);
	seller.insert("Ipad pro", 1299);
	seller.insert("GTA 5", 49);
	seller.insert("Xbox x", 699);

	int choice = 100;
	cout << "Welcome to Electronic's Shop\n";
	cout << "Please enter your name and your address\n";
	string name, address;
	getline(cin, name);  getline(cin, address);
	customer example(name, address);
	example.setProducts(seller);
	string theItem;


	do {  // Do-While loop to give the customer the chance to do more options
		cout << "\nPress 1: To View our catalogue\n";
		cout << "Press 2: To add an item to your Cart\n";
		cout << "Press 3: To view your Cart\n";
		cout << "Press 4: To checkout\n";
		cout << "Press 5: To choose any item and check it out\n";
		cout << "Press 6: To view your previous purchase\n";
		cout << "Press 7: To return your last order\n";
    cout << "Press 8: To search  an item\n";
		cout << "Press 0: To Quit\n";
		cin >> choice;
		switch (choice) {
		case 1:
			example.catalogue();
			break;
		case 2:

			cout << "Enter the name of the Item you would like to add to your cart\n";
			getline(cin >> ws, theItem);
			example.addToCar(theItem);
			break;
		case 3:
			cout << "This is your Cart\n";
			example.DisplayCustomCart();
			break;
		case 4:
			example.carCheckout();
			break;
		case 5:
			example.CheckoutForAnyItem();
			continue;
		case 6:
			example.displayOrderList();
			break;
		case 7:
			example.returnLastOrder();
			break;
    case 8:
      example.search();
      break;
		case 0:
			cout << "\nThank you! We hope to see you soon\n\n";
			example.displayOrderList();
			cout << "\nThese items were shiped to this address: " << example.getAddress();
			break;

		}
	} while (choice != 0);


	return 0;
}
