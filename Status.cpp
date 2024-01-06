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
#include"Status.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    Status::Status()
    {
        m_description = 0;
        m_code = 0;
    }

    Status::Status(const char* description)
    {
        m_code = 0;
        if (description != nullptr) {
            ut.alocpy(m_description, description);
        }
    }

    Status::Status(const Status& stat)
    {
        m_code = stat.m_code;
        if (m_description != nullptr) {
            size_t len = strlen(stat.m_description);
            m_description = new char[len + 1];
            strcpy(m_description, stat.m_description);
        }
        else {
            m_description = nullptr;
        }

    }

    Status& Status::operator =(const Status& other)
    {
        if (this != &other) {
            m_code = other.m_code;
            ut.alocpy(m_description, other.m_description);

        }
        return *this;
    }

    Status& Status::operator =(const char* description)
    {
        if (description != nullptr) {
            ut.alocpy(m_description, description);
        }
        return *this;
    }

    Status& Status::operator =(int code)
    {
        m_code = code;
        return *this;
    }

    Status::operator int() const
    {
        return m_code;
    }

    Status::operator const char* () const
    {
        return m_description;
    }

    Status::operator bool() const
    {
        if (m_description == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    Status& Status::clear()
    {
        if (m_description != nullptr) {
            delete[] m_description;
            m_description = nullptr;
            m_code = 0;
        }
        return *this;
    }

    Status::~Status()
    {
        delete[] m_description;
    }

    std::ostream& Status::print(std::ostream& ostr) const
    {
        if (m_code == 0) {
            ostr << m_description;
        }
        else {
            ostr << "ERR#" << m_code << ": ";
            ostr << m_description;
        }
        return ostr;
    }

    std::ostream& operator<<(std::ostream& os, const Status& stat)
    {
        if (stat) {}
        else {
            stat.print(os);
        }
        return os;
    }
}