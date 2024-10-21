#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function declarations
void login();
void subProcess();
void addBakeryItem();
void delBakeryItem();
void upBakeryItem();
void bakeryItemDetails();
void salesDetails();
void comDetails();
void logout();
void check();
void fetchAll();

string userType;


int main()
{
    check();
    system("pause");
    return 0;
}

void fetchAll() {
    fstream bData;
    string bName, bType, bNumber;
    int bQuantity;

    bData.open("Bakery Data.txt", ios::in);

    while (bData >> bName >> bType >> bNumber >> bQuantity)
    {
        cout << "\n\tBakery Item Name  : " << bName << endl;
        cout << "\tBakery Item Type  : " << bType << endl;
        cout << "\tBakery Item Number: " << bNumber << endl;
        cout << "\tQuantity         : " << bQuantity << endl<<endl<<endl;
    }

    cout << setw(29) << left << "\n\t Bakery Name" << setw(5) << " : "
        << setw(29) << right << "Amber's Bakery"
        << setw(29) << left << "\n\t Owner" << setw(5) << " : "
        << setw(29) << right << "Amber"
        << setw(29) << left << "\n\t Contact Number" << setw(5) << " : "
        << setw(29) << right << "081 234 5678"
        << setw(29) << left << "\n\t Address" << setw(5) << " : "
        << setw(29) << right << "1234, Baker Street, City."
        << setw(29) << left << "\n\t Email" << setw(5) << " : "
        << setw(29) << right << "amberbakery@gmail.com" << endl << endl;

    bData.close();
}

void check() {
    int type;
    cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
    cout << "\t\tPress 1 for Customer"<<endl;
    cout << "\t\tPress 2 for Reciptionist"<<endl;
    cout << "\t\tPress 3 for Manager"<<endl<< endl;
    cout << "\t\tYour Choice : ";
    cin >> type;
    switch (type)
    {
    case 1:
    	system("CLS");
        fetchAll();
        break;
    case 2:
    	system("CLS");
        login();
        break;
    case 3:
    	system("CLS");
        login();
        break;
    default:
        system("CLS");
        cout << "\t\t\Invalid Input!";
        check();
        break;
    }
}

void login()
{
    string userName, pWord, dbusername, dbpassword;
    fstream logindata;
    bool check = false;

    cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
    cout << setw(37) << "Enter Username : ";
    cin >> userName;
    cin.ignore(); // Ignore the newline character left by cin
    cout << setw(37) << "Enter Password : ";
    getline(cin, pWord);

    logindata.open("Login Data.txt", ios::in);

    while (logindata >> dbusername >> dbpassword >> userType)
    {
        if (dbusername == userName && dbpassword == pWord)
        {
            cout << "   Access Granted!\n\n";
            check = true;
            system("CLS");
            subProcess();
            break;
        }
    }

    if (!check)
    {
        system("CLS");
        cout << "\n\n\t Your Username or Password is incorrect. Please try Again!";
        login();
    }

    logindata.close();
}

void subProcess()
{
    int userChoice;

    cout << "\n\t\tPress 1 to add new bakery items" << endl;
    cout << "\t\tPress 2 to delete bakery items" << endl;
    cout << "\t\tPress 3 to update bakery items" << endl;
    cout << "\t\tPress 4 to view bakery items" << endl;
    cout << "\t\tPress 5 to manage sales details" << endl;
    cout << "\t\tPress 6 to Company Details" << endl;
    // Need to add package details
    cout << "\t\tPress 7 to Log Out" << endl;
    cout << "\t\tPress 8 Exit" << endl << endl;

    cout << "\t Enter your choice : ";
    cin >> userChoice;

    switch (userChoice)
    {
    case 1:
    	system("CLS");
        addBakeryItem();
        break;
    case 2:
    	system("CLS");
        if (userType == "M") {
            delBakeryItem();
            break;
        }
        else
        {
            system("CLS");
            cout << "That function is only for Administration!" << endl;
            subProcess();
            break;
        }
    case 3:
    	system("CLS");
        if (userType == "M") {
            upBakeryItem();
            break;
        }
        else
        {
            system("CLS");
            cout << "That function is only for Administration!" << endl;
            subProcess();
            break;
        }
    case 4:
    	system("CLS");
        bakeryItemDetails();
        break;
    case 5:
    	system("CLS");
        salesDetails();
        break;
    case 6:
    	system("CLS");
        comDetails();
        break;
    case 7:
    	system("CLS");
        logout();
        break;
    case 8:
    	system("CLS");
        exit(0);
    default:
        system("CLS");
        cout << "\n\n\t\t\t Retry!" << endl;
        subProcess();
    }
}

void addBakeryItem()
{
    fstream bakerydata;
    string bName, bType, bNumber;
    int bQuantity = 0;
    char choice;

    bakerydata.open("Bakery Data.txt", ios::app);

    cout << "\nEnter Name of the Bakery Item : ";
    cin.ignore();
    getline(cin, bName);

    cout << "Enter Type of the Bakery Item : ";
    getline(cin, bType);

    cout << "Enter Bakery Item ID : ";
    getline(cin, bNumber);

    cout << "Enter quantity of the bakery item : ";
    cin >> bQuantity;

    bakerydata << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
    bakerydata.close();

    cout << "Do you want to add new bakery items? (Y/N) : ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
        addBakeryItem();
    else
    {
        system("CLS");
        cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
        subProcess();
    }
}

void delBakeryItem()
{
    fstream bakerydata, update;
    string bName, bType, bNumber, choice;
    int bQuantity = 0;
    char choice2;
    bool delp = true;

    bakerydata.open("Bakery Data.txt", ios::in);
    update.open("Update.txt", ios::out);

    cout << "\t Enter the Bakery Item Name to Delete : ";
    cin.ignore();
    getline(cin, choice);

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity)
    {
        if (choice != bName)
        {
            update << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
        }
        else
            delp = false;
    }

    if (delp == false)
        cout << "\t Bakery Item Deleted Successfully!";
    else
        cout << "\t Bakery Item Not Found!";

    bakerydata.close();
    update.close();

    bakerydata.open("Bakery Data.txt", ios::out);
    update.open("Update.txt", ios::in);

    while (update >> bName >> bType >> bNumber >> bQuantity)
    {
        bakerydata << bName << "  " << bType << "   " << bNumber << "   " << bQuantity << endl;
    }

    bakerydata.close();
    update.close();

    cout << "\n\t Do you want to delete another bakery item? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        delBakeryItem();
    else
    {
        system("CLS");
        cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
        subProcess();
    }
}

void upBakeryItem()
{
    fstream update, bakerydata;
    string bName, bType, bNumber, choice, text;
    char choice2;
    int bQuantity = 0;
    bool found = false;

    cout << "\t Enter the name of the bakery item to update : ";
    cin.ignore();
    getline(cin, choice);

    update.open("Update.txt", ios::out);
    text = "";
    update << text;
    update.close();

    bakerydata.open("Bakery Data.txt", ios::in);
    update.open("Update.txt", ios::app);

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity)
    {
        if (choice == bName)
        {
            found = true;
            cout << "\n\t Enter New Name : ";
            getline(cin, bName);

            cout << "\t Enter New Type : ";
            getline(cin, bType);

            cout << "\t Enter New bakery item number : ";
            getline(cin, bNumber);

            cout << "\t Enter New quantity : ";
            cin >> bQuantity;

            update << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
            cout << "\n \t Successfully Bakery Item Updated!" << endl;
        }
        else
        {
            update << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
        }
    }
    if (found == false)
        cout << "\n \t Bakery Item Not Found!" << endl;

    bakerydata.close();
    update.close();

    bakerydata.open("Bakery Data.txt", ios::out);
    update.open("Update.txt", ios::in);

    while (update >> bName >> bType >> bNumber >> bQuantity)
    {
        bakerydata << bName << "  " << bType << "  " << bNumber << "  " << bQuantity << endl;
    }
    bakerydata.close();
    update.close();

    update.open("Update.txt", ios::out);
    text = "";
    update << text;
    update.close();

    cout << "\n\t Do you want to update another bakery item? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        upBakeryItem();
    else
    {
        system("CLS");
        cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
        subProcess();
    }
}

void bakeryItemDetails()
{
    fstream bakerydata;
    string bName, bType, bNumber, choice, text = "";
    char choice2;
    int bQuantity = 0;

    cout << "\n\t Enter Bakery Item Name that you want to search : ";
    cin.ignore();
    getline(cin, choice);

    bakerydata.open("Bakery Data.txt", ios::in);

    while (bakerydata >> bName >> bType >> bNumber >> bQuantity)
    {
        if (bName == choice)
        {
            cout << "\n\tBakery Item Name  : " << bName << endl;
            cout << "\tBakery Item Type  : " << bType << endl;
            cout << "\tBakery Item Number: " << bNumber << endl;
            cout << "\tQuantity         : " << bQuantity << endl;
            text = "Found";
            break;
        }
    }

    if (text != "Found")
    {
        cout << "\n\t Bakery Item is Unavailable! " << endl;
    }

    cout << "\n\t Do you want to search another bakery item? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        bakeryItemDetails();
    else
    {
        system("CLS");
        cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
        subProcess();
    }
}

void salesDetails()
{
    int sales;
    string date, income;
    fstream salesdata;
    char choice2;

    void subProcess();
    cout << "\n\t Sales Details" << endl;
    cout << "\t Enter the Date (dd/mm/yyyy) : ";
    cin >> date;
    cout << "\t Enter Number of Sales : ";
    cin >> sales;
    cout << "\t Enter Total Income : ";
    cin >> income;

    salesdata.open("Sales.txt", ios::app);
    salesdata << "Date : " << date << "     " << "Number of Sales : " << sales << "     " << "Total daily income : " << income << endl;

    cout << "\n\t Sales.txt Updated Successfully!" << endl;

    cout << "\n\t Do you want to add another log? (Y/N) : ";
    cin >> choice2;

    if (choice2 == 'Y' || choice2 == 'y')
        salesDetails();
    else
    {
        system("CLS");
        cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
        subProcess();
    }
}

void comDetails()
{
    string choice;
    bool loop = true;
    void subProcess();

    cout << setw(29) << left << "\n\t Bakery Name" << setw(5) << " : "
        << setw(29) << right << "Amber's Bakery"
        << setw(29) << left << "\n\t Owner" << setw(5) << " : "
        << setw(29) << right << "Amber"
        << setw(29) << left << "\n\t Contact Number" << setw(5) << " : "
        << setw(29) << right << "081 234 5678"
        << setw(29) << left << "\n\t Address" << setw(5) << " : "
        << setw(29) << right << "1234, Baker Street, City."
        << setw(29) << left << "\n\t Email" << setw(5) << " : "
        << setw(29) << right << "amberbakery@gmail.com" << endl << endl;

    while (loop == true)
    {
        cout << "\t\n Press B to go Back : ";
        cin >> choice;
        if (choice == "B" || choice == "b")
        {
            loop = false;
            system("CLS");
            cout << endl << endl << "============== Welcome to Amber's Bakery System ==============" << endl << endl;
            subProcess();
        }
        else
        {
            loop = true;
        }
    }
}

void logout()
{
    system("CLS");
    cout << "\n\n\t\t\t\t Log Out Success!";
    login();
}
