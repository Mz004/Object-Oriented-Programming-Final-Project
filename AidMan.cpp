/******************************************************************************
                         Milestone - #56
Full Name   : Manav Alpeshbhai Zadafiya
Student ID# : 144095221
Email       : mazadafiya@myseneca.ca
Section     : ZCC
Date        : 2023-12-07
Authenticity Declaration:
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
#include "AidMan.h"
#include "Utils.h"
#include "Item.h"
#include "Perishable.h"

using namespace std;

namespace sdds
{
    unsigned int AidMan::menu()
    {
        return mainMenu.run();
    }

   
    AidMan::AidMan(const char* fileName) : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database")
    {
        if (fileName && strlen(fileName) > 0) {
            filename = new char[strlen(fileName) + 1];
            strcpy(filename, fileName);
        }
        else {
            filename = nullptr;
        }
    }

    AidMan::~AidMan()
    {
        deallocateItems();
        delete[] filename;
    }

    void AidMan::run() 
    {
        string input;
        int temp;
        bool check = true;
        while (true) {
            std::cout << "Aid Management System" << std::endl;
            std::cout << "Date: 2023/12/09" << std::endl;
            std::cout << "Data file: " << (filename ? filename : "No file") << std::endl;
            std::cout << "---------------------------------\n";

            unsigned int choice = menu();
            if (check) {
                check = false;
                choice = 7;
            }
            switch (choice) {
            case 0:
                std::cout << "Exiting Program!" << std::endl;
                return;
            case 1:
                std::cout << "\n****List Items****\n";
                list();
                cout << "Enter row number to display details or <ENTER> to continue:\n> ";
                input = "";
                getline(cin, input, '\n');
                if (input != "") {
                    temp = stoi(input);
                    items[temp - 1]->linear(false);
                    items[temp - 1]->display(cout);
                }
                save();
                break;
            case 2:
                std::cout << "\n****Add Item****\n";
                addItem();
                save();
                break;
            case 3:
                std::cout << "\n****Remove Item****\n";
                removeItem();
                save();
                break;
            case 4:
                std::cout << "\n****Update Quantity****\n";
                updateQuantity();
                save();
                break;
            case 5:
                std::cout << "\n****Sort****\n";
                sort();
                save();
                break;
            case 6:
                std::cout << "\n****Ship Items****\n";
                ship();
                save();
                break;
            case 7:
                std::cout << "\n****New/Open Aid Database****\n";
                load();
                break;
            default:
                std::cout << "Invalid option!" << std::endl;
            }
            cout << endl;
        }
        cout << "Exiting Program!" << endl;
        save();
        deallocateItems();
    }

    void AidMan::save()
    {
        if (filename != nullptr) {
            ofstream file(filename);
            for (int i = 0; i < noOfItems; i++) {
                items[i]->save(file);
                file << endl;
            }
            file.close();
        }
    }

    void AidMan::deallocateItems()
    {
        for (int i = 0; i < noOfItems; i++) {
            delete items[i];
        }
        noOfItems = 0;
    }

    bool AidMan::load()
    {
        string temp = "";
        save();
        deallocateItems();

        cout << "Enter file name: ";
        getline(cin, temp, '\n');
        ut.alocpy(filename, temp.c_str());

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open" << filename << "for reading!" << endl;
            cout << "Would you like to create a new data file?" << endl;
            cout << "1- Yes!" << endl;
            cout << "0- Exit" << endl;
            if (ut.getint(0, 1, "> ")) {
                ofstream temp(filename);
                temp.close();
            }
        }
        else {
            while (!file.eof() && file) {
                if (file.peek() == '1' || file.peek() == '2' || file.peek() == '3') {
                    items[noOfItems] = new Perishable();
                }
                else if (file.peek() == '4' || file.peek() == '5' || file.peek() == '6' || file.peek() == '7' || file.peek() == '8' || file.peek() == '9') {
                    items[noOfItems] = new Item();
                }
                else {
                    file.setstate(ios::failbit);
                }
                if (!file.fail()) {
                    items[noOfItems]->load(file);
                    if (items[noOfItems]->operator bool()) {
                        noOfItems++;
                    }
                    else {
                        delete items[noOfItems];
                    }
                }
            }
            if (noOfItems > 0) {
                cout << noOfItems << " records loaded!\n";
                return true;
            }
        }
        file.close();
        return false;
    }

    int AidMan::list(const char* sub_desc)
    {
        int temp = 0;
        cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        for (int i = 0; i < noOfItems; i++) {
            if (!(sub_desc) || items[i]->operator==(sub_desc)) {
                items[i]->linear(true);
                cout << setw(4) << setfill(' ') << right << (i + 1) << " | ";
                items[i]->display(cout);
                cout << endl;
                temp++;
            }
        }
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        return temp;
    }

    int AidMan::search(int sku) const
    {
        ifstream file(filename);
        for (int i = 0; i < noOfItems; i++) {
            if (items[i]->operator==(sku)) {

                return i;
            }
        }
        return -1;
    }

    void AidMan::addItem()
    {
        int choice;
        if (noOfItems >= sdds_max_num_items) {
            cout << "Database full!" << endl;
        }
        std::cout << "1- Perishable\n";
        std::cout << "2- Non-Perishable\n";
        std::cout << "-----------------\n";
        std::cout << "0- Exit\n";
        choice = ut.getint(0, 2, "> ", nullptr);
        if (choice == 0) {
            cout << "Aborted\n";
            return;
        }

        iProduct* new_item = nullptr;
        if (choice == 1) {
            new_item = new Perishable();
        }
        else if (choice == 2) {
            new_item = new Item();
        }
        else {
            std::cout << "Invalid choice!\n";
            return;
        }

        int found;
        int xy;
        found = new_item->readSku(cin);
        xy = search(found);
        if (xy != -1) {
            cout << "Sku: " << found << " is already in the system, try updating quantity instead.\n";
            delete new_item;
            return;
        }
        else {
            new_item->read(cin);
        }

        if (new_item->operator bool()) {
            items[noOfItems] = new_item;
            noOfItems++;
        }
        else {
            new_item->display(std::cout);
            delete new_item;
            return;
        }

    }
    void AidMan::remove(int index)
    {
        delete items[index];
        if (index < noOfItems - 1) {
            for (int i = index; i < noOfItems - 1; i++) {
                items[i] = items[i + 1];
            }
            items[noOfItems - 1] = nullptr; 
            noOfItems--;
        }
    }
    void AidMan::removeItem()
    {
        char desc[1000 + 1];
        int ch, idx, code;

        cout << "Item description: ";
        cin >> desc;

        if (list(desc) > 0) {
            code = ut.getint(10000, 99999, "Enter SKU: ", nullptr);
            idx = search(code);

            if (idx == -1) {
                cout << "SKU not found!";
            }
            else {
                cout << "Following item will be removed: " << endl;
                items[idx]->linear(false);
                items[idx]->display(cout);
                cout << endl;

                cout << "Are you sure?" << endl;
                cout << "1- Yes!" << endl;
                cout << "0- Exit" << endl;

                ch = ut.getint(0, 1, "> ", nullptr);

                if (ch == 1) {
                    remove(idx);
                    cout << "Item removed!" << endl;

                }
                else if (ch == 2) {
                    cout << "Aborted!" << endl;
                    cout << endl;
                }
            }
        }

    }

    void AidMan::updateItem(int itemIndex) {
        int selection, remainingQty = 0, userInputQty = 0;

        cout << "1- Add" << endl;
        cout << "2- Reduce" << endl;
        cout << "0- Exit" << endl;

        selection = ut.getint(0, 2, "> ", nullptr);

        switch (selection) {
        case 0:
            cout << "Aborted!" << endl;
            break;

        case 1:
            remainingQty = items[itemIndex]->qtyNeeded() - items[itemIndex]->qty();

            if (remainingQty != 0) {
                userInputQty = ut.getint(1, remainingQty, "Quantity to add: ", nullptr);
                *items[itemIndex] += userInputQty;
                cout << userInputQty << " items added!" << endl;

            }
            else {
                cout << "Quantity Needed already fulfilled!" << endl;

            }
            break;

        case 2:
            remainingQty = items[itemIndex]->qty();

            if (remainingQty != 0) {
                userInputQty = ut.getint(1, items[itemIndex]->qty(), "Quantity to reduce: ", nullptr);
                *items[itemIndex] -= userInputQty;
                cout << userInputQty << " items removed!" << endl;

            }
            else {
                cout << "Quantity on hand is zero!" << endl;

            }
            break;
        }
    }

    void AidMan::updateQuantity()
    {
        char productDescription[1000 + 1];
        int itemIndex, productSKU;

        cout << "Item description: ";
        cin >> productDescription;

        if (list(productDescription) > 0) {
            productSKU = ut.getint(10000, 99999, "Enter SKU: ", nullptr);
            itemIndex = search(productSKU);

            if (itemIndex == -1) {
                cout << "SKU not found!";
            }
            else {
                updateItem(itemIndex);
            }
        }
    }

    void AidMan::sort() {
        iProduct* sort;
        bool swapped;

        for (int i = 0; i < noOfItems - 1; i++) {
            swapped = false;
            for (int j = 0; j < noOfItems - i - 1; j++) {             
                int difference1 = items[j]->qtyNeeded() - items[j]->qty();
                int difference2 = items[j + 1]->qtyNeeded() - items[j + 1]->qty();

                if (difference1 < difference2) {
                    sort = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = sort;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
        cout << "Sort completed!\n";
    }

    void AidMan::ship()
    {
        ofstream shippingFile("shippingOrder.txt");
        if (!shippingFile.is_open()) {
            cout << "Failed to open shippingOrder.txt File for writing!" << endl;
            return;
        }

        Date currentDate;
        shippingFile << "Shipping Order, Date: " << currentDate << endl;
        shippingFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        int shippedItems = 0;
        int i = 0;
        while (i < noOfItems) {
            if (items[i]->qty() == items[i]->qtyNeeded()) {
                items[i]->linear(true);
                shippingFile << "   " << shippedItems + 1 << " | ";
               // items[i]->display(shippingFile);
                shippingFile << endl;
                delete items[i];

                for (int j = i; j < noOfItems - 1; ++j) {
                    items[j] = items[j + 1];
                }
                noOfItems--;
                shippedItems++;
            }
            else {
                i++;
            }
        }
        shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        cout << "Shipping Order for " << (int)shippedItems << " times saved!" << endl;
        cout << endl;
        save();
    }
}