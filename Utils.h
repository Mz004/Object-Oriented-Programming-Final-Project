/***********************************************************************
// Final project Milestone 5
//
// File: main51.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// --------------------------------------------------------------------
// Name                 Date            Reason
// Manav                2023-12-07      ms51
***********************************************************************/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include <iostream>
#include <cstring>

namespace sdds
{
    // Testing date values for application testing and debugging
    // these values must not change at submission time.
    const int sdds_testYear = 2023;
    const int sdds_testMon = 12;
    const int sdds_testDay = 9;

    class Utils
    {
        bool m_testMode = false;
    public:
        // this function will be used to get the current system date or the test date if m_testMode is true
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
        // this function will return the number of days in a month based on the year
        // 1<=mon<=12  year: four digit number (example: 2023)cd
        int daysOfMon(int mon, int year)const;
        void testMode(bool testmode = true); //default value: true
        void alocpy(char*& destination, const char* source);
        int getint(const char* prompt = nullptr); //point to NULL by default
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
        double getdouble(const char* prompt = nullptr, const char* errMes = nullptr);
        double getdouble(double min, double max, const char* prompt, const char* errMes = nullptr);
        void extractChar(std::istream& istr, char ch) const;
    };

    extern Utils ut;
}
#endif // !SDDS_UTILS_H