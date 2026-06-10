
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ---------------------------------------------
//  Global Customer Data
// ---------------------------------------------
string customerName;
string customerContact;
string orderType;
int    numPersons;

// 1D Arrays: food item names and prices
string itemNames[8]  = {"Chicken Burger", "Zinger Burger", "Pizza Small",
                        "Pizza Large",    "Chicken Biryani", "BBQ Platter",
                        "Fries",          "Cold Drink"};
double itemPrices[8] = {450, 550, 900, 1800, 350, 1200, 250, 120};

// Order storage
int orderedItems[50];
int orderedQty[50];
int totalOrderedItems = 0;

// ---------------------------------------------
//  FUNCTION PROTOTYPES
// ---------------------------------------------
void   registerCustomer();
void   displayFoodMenu();
void   placeOrder();
double calculateFoodBill();
double calculateServiceCharges(double foodBill);
double calculateGST(double foodBill);
double calculateDiscount(double foodBill);
void   addFreeDelivery(double totalBill);
void   displayFinalBill();
void   displayCustomerDetails();
bool   displayMenu();

// ---------------------------------------------
//  1. REGISTER CUSTOMER
// ---------------------------------------------
void registerCustomer() {
  
    cout << "====RESTAURANT CUSTOMER REGISTRATION====="<<endl;
 

    cout << "Enter Customer Name  : ";
    cin  >> customerName;

    cout << "Enter Contact Number : ";
    cin  >> customerContact;

    int typeChoice;
    cout << "Order Type (press 1 for dine-in press 2 for takeaway)"<<endl;
    cin  >> typeChoice;

    
    if (typeChoice == 1){
    	cout<<"Dine in"<<endl;
	}
       
    else if(typeChoice == 2){
    	
    	cout<<"Takeaway"<<endl;
	}
	else
	cout<<"Invalid"<<endl;
        
    cout << "Enter Number of Persons: ";
    cin  >> numPersons;

    while (numPersons <= 0) {
        cout << "Invalid Enter at least 1: ";
        cin  >> numPersons;
    }

    cout << "Registration Successful"<<endl;
}

// ---------------------------------------------
//  2. DISPLAY FOOD MENU
// ---------------------------------------------
void displayFoodMenu() {

    cout << "==========FOOD MENU=========="<<endl;

    cout << " 1 Chicken Burger       Rs. 450"<<endl;
    cout << " 2 Zinger Burger        Rs. 550"<<endl;
    cout << " 3 Pizza Small          Rs. 900"<<endl;
    cout << " 4 Pizza Large          Rs. 1800"<<endl;
    cout << " 5 Chicken Biryani      Rs. 350"<<endl;
    cout << " 6 BBQ Platter          Rs. 1200"<<endl;
    cout << " 7 Fries                Rs. 250"<<endl;
    cout << " 8 Cold Drink           Rs. 120"<<endl;

}

// ---------------------------------------------
//  3. PLACE ORDER
// ---------------------------------------------
void placeOrder() {
    displayFoodMenu();

    cout << "==== Place Your Order ===="<<endl;
    cout << "Enter 0 when your order item is selected press 0"<<endl;

    int itemChoice;
    while (true) {
        cout << "Enter Item No (1-8) ";
        cin  >> itemChoice;

        if (itemChoice == 0)
            break;

        if (itemChoice < 1 || itemChoice > 8) {
            cout << "Invalid Enter 1-8 or 0 to stop"<<endl;
            continue;
        }

        int qty;
        cout << "Enter Quantity   : ";
        cin  >> qty;

        while (qty <= 0) {
            cout << "Invalid Enter at least 1 ";
            cin  >> qty;
        }

        orderedItems[totalOrderedItems] = itemChoice;
        orderedQty[totalOrderedItems]   = qty;
        totalOrderedItems++;

        cout << "  Added: " << itemNames[itemChoice - 1]
             << " x" << qty << "\n";
    }

    cout << " ===Order placed successfully!==="<<endl;
}

// ---------------------------------------------
//  4. CALCULATE FOOD BILL
//     food bill = price x quantity  (each item)
// ---------------------------------------------
double calculateFoodBill() {
    double total = 0;
    int i = 0;
    while (i < totalOrderedItems) {
        int    itemIndex = orderedItems[i] - 1;  // array index
        double price     = itemPrices[itemIndex]; // price of that item
        int    qty       = orderedQty[i];          // how many ordered
        total = total + (price * qty);
        i++;
    }
    return total;
}

// ---------------------------------------------
//  5. CALCULATE SERVICE CHARGES
//     Dine-in  = foodBill * 10 / 100
//     Takeaway = foodBill *  5 / 100
// ---------------------------------------------
double calculateServiceCharges(double foodBill) {
    double serviceCharges;
    if (orderType == "Dine-in")
        serviceCharges = foodBill * 10 / 100;
    else
        serviceCharges = foodBill * 5 / 100;
    return serviceCharges;
}

// ---------------------------------------------
//  6. CALCULATE GST
//     GST = foodBill * 16 / 100
// ---------------------------------------------
double calculateGST(double foodBill) {
    double gst = foodBill * 16 / 100;
    return gst;
}

// ---------------------------------------------
//  7. CALCULATE DISCOUNT
//     3000 - 5000  =  5%
//     5001 - 10000 = 10%
//     above 10000  = 15%
// ---------------------------------------------
double calculateDiscount(double foodBill) {
    double discount;
    if (foodBill >= 3000 && foodBill <= 5000)
        discount = foodBill * 5 / 100;
    else if (foodBill > 5000 && foodBill <= 10000)
        discount = foodBill * 10 / 100;
    else if (foodBill > 10000)
        discount = foodBill * 15 / 100;
    else
        discount = 0;
    return discount;
}

// ---------------------------------------------
//  9. FREE DELIVERY
//     totalBill > 5000 and Takeaway = free
// ---------------------------------------------
void addFreeDelivery(double totalBill) {
    if (totalBill > 5000 && orderType == "Takeaway")
        cout << "Free Delivery    : YES (Bill > Rs. 5000)"<<endl;
}

// ---------------------------------------------
//  8. DISPLAY FINAL BILL
// ---------------------------------------------
void displayFinalBill() {
    if (totalOrderedItems == 0) {
        cout << "  No order placed yet Place an order first "<<endl;
        return;
    }

    double foodBill       = calculateFoodBill();
    double serviceCharges = calculateServiceCharges(foodBill);
    double gst            = calculateGST(foodBill);
    double discount       = calculateDiscount(foodBill);
    double totalPayable   = foodBill + serviceCharges + gst - discount;

    cout << fixed << setprecision(2);
    cout << "========== RESTAURANT BILL =========="<<endl;
    cout << "\nCustomer Name    : " << customerName;
    cout << "\nContact          : " << customerContact;
    cout << "\nOrder Type       : " << orderType;
    cout << "\nNo. of Persons   : " << numPersons << "\n";
    cout << "Items Ordered:"<<endl;

    int i = 0;
    while (i < totalOrderedItems) {
        int    itemIndex = orderedItems[i] - 1;
        double price     = itemPrices[itemIndex];
        int    qty       = orderedQty[i];
        cout << "  " << itemNames[itemIndex]
             << " x" << qty
             << " = Rs. " << (price * qty) << "\n";
        i++;
    }

    cout << "Food Bill        : Rs " << foodBill       << endl;
    cout << "Service Charges  : Rs " << serviceCharges << endl;
    cout << "GST (16%)        : Rs " << gst            << endl;
    cout << "Discount         : Rs " << discount       << endl;
    addFreeDelivery(totalPayable);
    cout << "Total Payable    : Rs " << totalPayable   << endl;
    cout << "   Enjoy Your Meal :)    "<<endl;
}

// ---------------------------------------------
//  10. DISPLAY CUSTOMER DETAILS
// ---------------------------------------------
void displayCustomerDetails() {
    cout << "====== CUSTOMER DETAILS ======="<<endl;
    cout << "Customer Name   : " << customerName    << endl;
    cout << "Contact Number  : " << customerContact << endl;
    cout << "Order Type      : " << orderType       << endl;
    cout << "No. of Persons  : " << numPersons      << endl;
}

// ---------------------------------------------
//  DISPLAY MENU — sab kuch yahan handle hota hai
// ---------------------------------------------
bool displayMenu() {
    cout << "========RESTAURANT MAIN MENU======="<<endl;
  
    cout << "  1. View Food Menu"<<endl;
    cout << "  2. Place Order"<<endl;
    cout << "  3. View Bill"<<endl;
    cout << "  4. View Customer Details"<<endl;
    cout << "  5. Exit"<<endl;

    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
        displayFoodMenu();
    else if (choice == 2)
        placeOrder();
    else if (choice == 3)
        displayFinalBill();
    else if (choice == 4)
        displayCustomerDetails();
    else if (choice == 5) {
        cout << "Thank you for visiting Goodbye!"<<endl;
        return false;
    }
    else
        cout << "\nInvalid choice! Enter 1-5"<<endl;

    return true;
}

// ---------------------------------------------
//  MAIN FUNCTION
// ---------------------------------------------
int main() {
    registerCustomer();
    while (displayMenu());
    return 0;
}
