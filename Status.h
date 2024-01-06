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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <iostream>
#include <cstring>

namespace sdds
{
    class Status
    {
        char* m_description = nullptr;
        int m_code;
    public:
        Status();
        Status(const char* description);
        Status(const Status& stat);
        Status& operator =(const Status& other);
        Status& operator =(const char* description);
        Status& operator =(int code);
        operator int() const;
        operator const char* () const;
        operator bool() const;
        Status& clear();
        std::ostream& print(std::ostream& ostr) const;
        ~Status();
    };
    std::ostream& operator<<(std::ostream& os, const Status& stat);
}
#endif  //!SDDS_STATUS_H