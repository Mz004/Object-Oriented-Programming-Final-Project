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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <fstream>
#include "iProduct.h"
#include "Status.h"

namespace sdds
{
    class Item : public iProduct
    {
        double Item_price;
        int Item_qty;
        int Item_qtyNeeded;
        char* Item_desc = nullptr;

    protected:
        bool Item_linear;
        Status i_state;
        int i_sku{};
        bool linear()const;

    public:
        Item();
        Item(const Item& I);
        Item& operator=(const Item& I);
        ~Item();

        char* desc() const;
        virtual int readSku(std::istream& istr);
        virtual int qtyNeeded()const;
        virtual int qty()const;
        virtual void linear(bool isLinear);
        virtual void clear();
        virtual operator double()const;
        virtual operator bool() const;

        virtual bool operator==(int sku)const;
        virtual bool operator==(const char* description) const;
        virtual int operator-=(int qty);
        virtual int operator+=(int qty);

        virtual std::ofstream& save(std::ofstream& ofstr)const;
        virtual std::ifstream& load(std::ifstream& ifstr);
        virtual std::ostream& display(std::ostream& ostr)const;
        virtual std::istream& read(std::istream& istr);
    };
}

#endif // !SDDS_ITEM_H
