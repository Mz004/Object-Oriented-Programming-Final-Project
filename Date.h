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
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include <cstring>
#include <sstream>
#include "Status.h"

namespace sdds 
{
    const int MAXIMUM_YEAR_VALUE = 2030;
    class Date
    {
        Status status; // Object of Class Status
        int m_year;
        int m_month;
        int m_day;
        bool m_format;
        bool invalid;
        bool validate(); // public method to validates the date entered by the user  
     
    public:
        Date();  
        Date(int year, int month, int day);
        Date& formatted(bool slash);
        operator bool() const;
        const Status& state();
        int uniqueDateValue() const;

        //Overloaded Operator
        bool operator==(const Date& right) const;  // used to check if both object is equal or not 
        bool operator!=(const Date& right) const; // inverse of (==)
        bool operator>=(const Date& right) const;
        bool operator<=(const Date& right) const;
        bool operator<(const Date& right) const;
        bool operator>(const Date& right) const;
        std::ostream& write(std::ostream& os, bool format = true) const;    
        std::istream& read(std::istream& istr);
    };
    //Helper function Operator  
    std::ostream& operator<<(std::ostream& os, const Date& dat);
    std::istream& operator>>(std::istream& is, Date& dat);
}
#endif // !SDDS_DATE_H