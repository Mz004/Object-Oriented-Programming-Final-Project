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
#include <cstring>
#include <iomanip>
#include <string.h>
#include <sstream>
#include "Utils.h"
#include "Item.h"

using namespace std;

namespace sdds
{
    bool Item::linear() const { return Item_linear; }

    Item::Item()
    {
        Item_price = 0.0;
        Item_qty = 0;
        Item_qtyNeeded = 0;
        Item_desc = nullptr;
        Item_linear = false;
    }

    Item::Item(const Item& I)
    {
        operator=(I);
    }

    Item& Item::operator=(const Item& another)
    {
        if (this != &another) {
            Item_price = another.Item_price;
            Item_qty = another.Item_qty;
            Item_qtyNeeded = another.Item_qtyNeeded;

            if (another.Item_desc != nullptr) {
                delete[] Item_desc;
                Item_desc = new char[strlen(another.Item_desc) + 1];
                strcpy(Item_desc, another.Item_desc);
            }
            i_state = another.i_state;
            i_sku = another.i_sku;
        }
        return *this;
    }

    Item::~Item() { delete[] Item_desc; }

    char* Item::desc() const
    {
        return Item_desc;
    }

    int Item::readSku(std::istream& istr)
    {
        int sku;
        sku = ut.getint(40000, 99999, "SKU: ");
        i_sku = sku;
        return sku;
    }

    int Item::qtyNeeded() const
    {
        return Item_qtyNeeded;
    }

    int Item::qty() const
    {
        return Item_qty;
    }

    void Item::linear(bool isLinear)
    {
        Item_linear = isLinear;
    }

    void Item::clear()
    {
        Item_price = 0.0;
        Item_qty = 0;
        Item_qtyNeeded = 0;
        delete[] Item_desc;
        Item_desc = nullptr;
        Item_linear = false;
        i_state = nullptr;
        i_sku = 0;
    }

    Item::operator double() const
    {
        return Item_price;
    }

    Item::operator bool() const
    {
        return i_state;
    }

    bool Item::operator==(int sku) const
    {
        return i_sku == sku;
    }

    bool Item::operator==(const char* description) const
    {
        return strstr(Item_desc, description);
    }

    int Item::operator-=(int qty)
    {
        Item_qty -= qty;
        return Item_qty;
    }

    int Item::operator+=(int qty)
    {
        Item_qty += qty;
        return Item_qty;
    }

    std::ofstream& Item::save(std::ofstream& ofstr) const
    {
        ofstr << i_sku << '\t' << Item_desc << '\t' << Item_qty << '\t' << Item_qtyNeeded << '\t' << fixed << setprecision(2) << Item_price;
        return ofstr;
    }

    std::ifstream& Item::load(std::ifstream& ifstr)
    {
        delete[] Item_desc;
        Item_desc = nullptr;
        string desc;

        ifstr >> i_sku;
        ifstr.ignore(10000, '\t');
        getline(ifstr, desc, '\t');
        ut.alocpy(Item_desc, desc.c_str());
        ifstr >> Item_qty;
        ifstr.ignore(10000, '\t');
        ifstr >> Item_qtyNeeded;
        ifstr.ignore(10000, '\t');
        ifstr >> Item_price;
        ifstr.ignore();
        if (ifstr.fail()) {
            i_state = "Input file stream read failed!";
        }
        return ifstr;
    }

    std::ostream& Item::display(std::ostream& ostr) const
    {
        if (!i_state) {
            ostr << i_state;
        }
        else {
            if (Item_linear) {
                ostr.width(5);
                ostr << i_sku << " | ";

                int i;
                for (i = 0; i < 35; i++) {

                    if (Item_desc[i] == '\0') {
                        break;
                    }
                    else {
                        cout << Item_desc[i];
                    }
                }
                while (i < 35) {
                    cout << " ";
                    i++;
                }

                ostr << " | ";
                ostr.setf(ios::right);
                ostr.width(4);
                ostr << Item_qty << " | ";
                ostr.unsetf(ios::right);
                ostr.setf(ios::right);
                ostr.width(4);
                ostr << Item_qtyNeeded << " | ";
                ostr.unsetf(ios::right);
                ostr.setf(ios::right);
                ostr.width(7);
                ostr << fixed << setprecision(2) << Item_price << " |";
            }
            else {
                ostr << "AMA Item:" << endl;
                ostr << i_sku << ": " << Item_desc << endl;
                ostr << "Quantity Needed: " << Item_qtyNeeded << endl;
                ostr << "Quantity Available: " << Item_qty << endl;
                ostr << "Unit Price: $" << Item_price << endl;
                ostr << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << Item_price * (Item_qtyNeeded - Item_qty) << endl;
            }
        }
        return ostr;
    }

    std::istream& Item::read(std::istream& istr)
    {
        string desc;
        cout << "AMA Item:" << endl;
        cout << "SKU: " << i_sku << endl;
        cout << "Description: ";
        getline(istr, desc);
        Item_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        Item_qty = ut.getint(0, Item_qtyNeeded, "Quantity On Hand: ");
        Item_price = ut.getdouble(0.00, 9999.00, "Unit Price: $");
        if (!istr) {
            i_state = "Console entry failed!";
        }
        ut.alocpy(Item_desc, desc.c_str());
        return istr;
    }
}