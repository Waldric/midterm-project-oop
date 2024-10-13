#include <iostream>       // midterm project in Ooprog - inventory management system
#include <string>         
using namespace std;

const int maxItems = 100; // maximum number of items in an inventory

string toLowerCase(const string& str) { // function to make sure the program case friendly
    string lowerStr = str;
        for (char& ch : lowerStr) {
            ch = tolower(ch); 
        }
        return lowerStr;
    }

class Category { // class for the categories

protected:
    string categoryName;  // member class

public:
    Category(string name) : categoryName(name) {}

    virtual string getCategoryName() const = 0;  // pure virtual function (abstraction)
};

class Clothing : public Category { // class for the clothing category

public:
    Clothing() : Category("Clothing") {}

    string getCategoryName() const override {  // over ride (abstraction)
        return categoryName;
    }
};

class Electronics : public Category { // class for the electronics category

public:
    Electronics() : Category("Electronics") {}

    string getCategoryName() const override {
        return categoryName;
    }
};

class Entertainment : public Category { // class for the entertainment category

public:
    Entertainment() : Category("Entertainment") {}

    string getCategoryName() const override {
        return categoryName;
    }
};

class Item { // class for the items

private:
    string id;
    string name;
    int quantity;      // Encapsulated data member
    double price; 
    Category* category;

public:   
    Item() : id(""), name(""), quantity(0), price(0.0), category(nullptr) {} // constructor

    Item(string id, string name, int quantity, double price, Category* category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getId() const {
         return id;
    }
    string getName() const { 
         return name; 
    }
    int getQuantity() const {
         return quantity;
    }
    double getPrice() const { 
         return price;
    }
    string getCategory() const {
         return category->getCategoryName(); 
    }

    void setQuantity (int newQuantity) { quantity = newQuantity; }
    void setPrice (double newPrice) { price = newPrice; }

};

bool validNumber(const string& str) {  // validation for numerical inputs
    for (char const &ch : str) {
        if (!isdigit(ch)) {
            return false; 
        }
    }
    return true; 
}

bool isFloat(const string& str) {  // validation for numberical inputs
    int dotCount = 0;
    for (char const &ch : str) {
        if (ch == '.') {
            dotCount++;
            if (dotCount > 1) return false; 
        } else if (!isdigit(ch)) {
            return false; 
        }
    }
    return true;
}

class Inventory   // class for the inventory that manage and organize the items
{
private:
    Item items [maxItems];
    int itemCount = 0;

public:
    Inventory() : itemCount() {} // constructor

    void addItem(Category* category, string id, string name, int quantity, double price) { // add item function (option 1)

        if (itemCount >= maxItems) {
            cout << "Inventory is full! Cannot add more Items. \n" << endl;
            return;
        }

        items[itemCount] = Item(id, name, quantity, price, category);
        itemCount++;
            cout << "Item added successfully! \n" << endl;
    }

    bool isCategoryValid(const string& categoryInput) {   // case validation
        string lowerCategory = toLowerCase(categoryInput);
        return (lowerCategory == "clothing" || lowerCategory == "electronics" || lowerCategory == "entertainment");
    }

    void updateItem (string id) {    // update item function (option 2)
        int index = findItemById(id);
        string quantityStr, priceStr;
        bool found = true;
        int choice;

        if (index == -1) {
            cout << "Item not found!" << endl;
           return;
        }

        do {
            cout << "Do you want to update quantity or price? (1 for quantity, 2 for price): ";
            cin >> choice;
            if (cin.fail()) {  // validation for non numerical inputs   
                cin.clear();
                cin.ignore(512, '\n');
                cout << "Invalid Input! Please Try Again." << endl;
            } else if (choice < 1 || choice > 2) {
                cout << "Invalid Input! Please Try Again." << endl;
            }
        } while (choice < 1 || choice > 2);

        if (choice == 1) {
            int newQuantity;
            do {
                cout << "Enter new quantity: ";
                cin >> quantityStr;
                if (!validNumber(quantityStr)) {          // validation
                    cout << "Invalid input! Please enter a valid number for quantity." << endl;
                }
            } while (!validNumber(quantityStr));

            newQuantity = stoi(quantityStr);   // STring tO Int value
            int oldQuantity = items[index].getQuantity();

            if (newQuantity == oldQuantity) {
                cout << "The new quantity is the same as the current quantity (" << oldQuantity << "). No update performed." << endl << endl;
                return;  
            }

            cout << "Quantity of Item " << items[index].getName() << " is updated from "
                 << oldQuantity << " to " << newQuantity << endl;
            items[index].setQuantity(newQuantity);

        } else if (choice == 2) {
            double newPrice;
            do {
                cout << "Enter new price: ";
                cin >> priceStr;
                if (!isFloat(priceStr)) {
                    cout << "Invalid input! Please enter a valid number for price." << endl;
                }
            } while (!isFloat(priceStr));

            newPrice = stod(priceStr);
            double oldPrice = items[index].getPrice();

        // Validation- Check if new price is the same as old
            if (newPrice == oldPrice) {
                cout << "The new price is the same as the current price (" << oldPrice << "). No update performed." << endl;
                return;  
            }

            cout << "Price of Item " << items[index].getName() << " is updated from "
                 << oldPrice << " to " << newPrice << endl;
            items[index].setPrice(newPrice);
        }
    }

        

    void removeItem(string id) { // remove item function (option 3)

        int index = findItemById(id);

        if (index == -1) {
            cout << "Item not found!" << endl;
            return;
        }
        cout << "Item " << items[index].getName() << " has been removed from the inventory" << endl;
        for (int i = index; i < itemCount - 1; ++i) {
            items[i] = items[i + 1];
        }
        itemCount--;
    }

    void displayItemsCategory (string categoryInput) { // display the items by category function (option 4)

        bool found = false;
        string categoryLower = toLowerCase(categoryInput);

        for (int i = 0; i < itemCount; i++) {
        if (toLowerCase(items[i].getCategory()) == categoryLower) {
            found = true; 
            break; 
        }
    }

    if (found) {
        
        cout << "\nID\t\t\tName\t\t\tQuantity\t\t\tPrice\t\t\tCategory" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

      
        for (int i = 0; i < itemCount; i++) {
            if (toLowerCase(items[i].getCategory()) == categoryLower) {
                cout << items[i].getId() 
                     << "\t\t\t" << items[i].getName()
                     << "\t\t\t" << items[i].getQuantity() 
                     << "\t\t\t\t" << items[i].getPrice()
                     << "\t\t\t" << items[i].getCategory() << endl;
            }
        }
        
        } else {
     
            cout << "\nCategory " << categoryInput << " does not exist!" << endl;
            cout <<"--------------------------------------------------------------------" << endl;
            cout << "If the category exists, there must be no items! " << endl;
          }
        }

    void displayAllItems () {   // display all the items in a table format function (option 5)

        if (itemCount == 0)
        {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
            return;
        }

        cout << "\nID\t\t\tName\t\t\tQuantity\t\t\tPrice\t\t\tCategory" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            cout << items[i].getId() 
                 << "\t\t\t" << items[i].getName() 
                 << "\t\t\t" << items[i].getQuantity()
                 << "\t\t\t\t" << items[i].getPrice()
                 << "\t\t\t" << items[i].getCategory() << endl;
        }
    }


    void searchItem(string id) {  // search item and display in a table format function (option6)

        int index = findItemById(id);

        if (index == -1) {
            cout << "Item not found!" << endl;
        } else {
            cout << "\nID: " << items[index].getId() << endl;
            cout << "Name: " << items[index].getName() << endl;
            cout << "Quantity: " << items[index].getQuantity() << endl;
            cout << "Price: " << items[index].getPrice() << endl;
            cout << "Category: " << items[index].getCategory() << endl << endl;
        }
    }
   
    void sortItems() {  // sort items in ascending or descending order and if it is by price or quantity function (option 7)

        int criteria, order;
        cout << "Sort Items by (1) Quantity (2) Price: ";
        cin >> criteria;
        
        if (cin.fail() || (criteria < 1 || criteria > 2)) {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "Invalid Input! Please enter 1 for Quantity or 2 for Price." << endl;
            return;
        }

        cout << "Sort Order: (1) Ascending (2) Descending: ";
        cin >> order;

        if (cin.fail() || (order < 1 || order > 2)) {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "Invalid Input! Please enter 1 for Ascending or 2 for Descending." << endl;
            return;
        }

        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = i + 1; j < itemCount; j++) {
                bool shouldSwap = false;
                if (criteria == 1) { // Sort by Quantity
                    if ((order == 1 && items[i].getQuantity() > items[j].getQuantity()) || 
                        (order == 2 && items[i].getQuantity() < items[j].getQuantity())) {
                        shouldSwap = true;
                    }
                } else { // Sort by Price
                    if ((order == 1 && items[i].getPrice() > items[j].getPrice()) || 
                        (order == 2 && items[i].getPrice() < items[j].getPrice())) {
                        shouldSwap = true;
                    }
                }

                if (shouldSwap) {
                    // Swap the items
                    Item temp = items[i];
                    items[i] = items[j];
                    items[j] = temp;
                }
            }
        }

        cout << "Items sorted successfully!" << endl;
        displayAllItems(); // Display sorted items
    }    


    void displayLowStockItems () { // display low stock items [5 and below] function (option 8)

        cout << "\nID\t\t\tName\t\t\tQuantity\t\t\tPrice\t\t\tCategory" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------" << endl;

        bool hasLowStockItems = false; // to check if any low stock items exist

        for (int i = 0; i < itemCount; i++) {
            if (items[i].getQuantity() <= 5) {
                hasLowStockItems = true; 
                cout << items[i].getId() 
                     << "\t\t\t" << items[i].getName() 
                     << "\t\t\t" << items[i].getQuantity() 
                     << "\t\t\t\t" << items[i].getPrice() 
                     << "\t\t\t" << items[i].getCategory() << endl;
            }
        }

        if (!hasLowStockItems) {
            cout << "No low stock items available." << endl;
        }
    }    

bool isEmpty() const {          // used for validation (if inventory is empty)
        return itemCount == 0;
    }
    
    ~Inventory () {  // destructor

        cout << "Cleaning Inventory history... " << endl;

    }
private: 
  int findItemById(string id) const {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].getId() == id) {
                return i;
            }
        }
        return -1; 
    }

};

void Menu () {  // menu display

    cout << "\nMenu " << endl;
    cout << "1 - Add Item " << endl;
    cout << "2 - Update Item " << endl;
    cout << "3 - Remove Item " << endl;
    cout << "4 - Display Items by Category " << endl;
    cout << "5 - Display All Items " << endl;
    cout << "6 - Search Item " << endl;
    cout << "7 - Sort Items " << endl;
    cout << "8 - Display Low Stock Items " << endl;
    cout << "9 - Exit " << endl;

}

int main () {  // main function
    
    Inventory inventory;
    int choice;
    char exitChoice;
    bool mainMenu = true;

do {
    do {
    Menu();
    cout << "Enter your option: ";
    cin >> choice;
    {
        if (cin.fail() || choice < 1 || choice > 9) {  // validation para sa iba't ibang characters (&,A,b,+, etc...)
                cin.clear();
                cin.ignore(512, '\n');
                cout << "Invalid Input! Please Try Again." << endl;
                }
    }
    } while (choice < 1 || choice > 9);
    

    switch (choice)
    {
    case 1 :
{
    string id;
    string name;
    string quantityStr, priceStr;  
    int quantity;
    double price;
    string categoryInput;

    cout << "Input Category (Clothing, Electronics, Entertainment): ";
    cin >> categoryInput;

    if (!inventory.isCategoryValid(categoryInput)) {
        cout << "Category " << categoryInput << " does not exist!" << endl;
        break;
    }

    cout << "Input item ID: ";
    cin >> id;
    for (char& c : id) {
        c = std::toupper(c);
    }

    cin.ignore(); 
    cout << "Input item name: ";
    getline(cin, name); 

    do {
        cout << "Enter quantity: ";
        cin >> quantityStr;
        if (!validNumber(quantityStr)) {
            cout << "Invalid input! Please enter a valid number for quantity." << endl;
        }
    } while (!validNumber(quantityStr));
    
    quantity = stoi(quantityStr);

    do {
        cout << "Enter price: ";
        cin >> priceStr;
        if (!isFloat(priceStr)) {
            cout << "Invalid input! Please enter a valid number for price." << endl;
        }
    } while (!isFloat(priceStr));
    
    price = stod(priceStr);

    Category* category = nullptr; // to access the elements
    if (toLowerCase(categoryInput) == "clothing") {
        category = new Clothing();
    } else if (toLowerCase(categoryInput) == "electronics") {
        category = new Electronics();
    } else if (toLowerCase(categoryInput) == "entertainment") {
        category = new Entertainment();
    }

    inventory.addItem(category, id, name, quantity, price);
    break;
    }
    case 2 :
    {   
        string id;
        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
              cout << "Enter item ID to update: ";
              cin >> id;
              for (char& c : id) {
                  c = std::toupper(c);  // to make the id in upper case for emphasization 
              }
              inventory.updateItem(id);
        }
        break;
    }    

    case 3 : 
    {
        string id;

        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
            cout << "Enter item ID to remove: ";
            cin >> id;
            for (char& c : id) {
                  c = std::toupper(c);
              }
            inventory.removeItem(id);
        }
        break;       
    }
    case 4 : 
    {
        string category;
        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
            cout << "Enter category (Clothing, Electronics, Entertainment): ";
            cin >> category;
            inventory.displayItemsCategory(category);
        }
        break;
    }
    case 5 :
    {
        inventory.displayAllItems ();
        break;
    }    
    case 6 :
    {
        string id;
        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
            cout << "Enter item ID to search: ";
            cin >> id;
            for (char& c : id) { 
                    c = std::toupper(c); 
                    } 
            inventory.searchItem(id);
        }
        break;
    }
        break;
    case 7 : {
        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
            inventory.sortItems();
        }
        break;
    }
    case 8 :{
        if (inventory.isEmpty()) {
            cout << "Inventory is empty! Please add an item first [option 1] to proceed." << endl;
        } else {
            inventory.displayLowStockItems ();
        }
        break;
    }
    case 9 : // exit option (last option)
    {
      do {
                cout << "Are you sure you want to Exit? (Y/N): ";  // may chance ang user na pagisipan ang kanyang desisyon
                cin >> exitChoice;
                if (exitChoice == 'Y' || exitChoice == 'y') {
                    mainMenu = false;  
                } else if (exitChoice != 'Y' && exitChoice != 'y' && exitChoice != 'n' && exitChoice != 'N')
                    cout << "Invalid Input! Please Try again " << endl;
                } while (exitChoice != 'Y' && exitChoice != 'y' && exitChoice != 'n' && exitChoice != 'N');         
                break;                         
    }    
    default :

         cout << "Invalid Input! Please try again: " << endl;
         break;
    }
} while (mainMenu);

    return 0;
}
// end of the code