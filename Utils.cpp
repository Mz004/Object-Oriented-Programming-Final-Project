/***********************************************************************
// Final project Milestone 56
//
// File: main51.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// --------------------------------------------------------------------
// Name                 Date            Reason
// Manav                2023-12-05      ms51
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <iomanip>
#include "Utils.h"

using namespace std;

namespace sdds
{
    // The ut object of type Utils that is accessible to any file including "Utils.h" to call the Utils
    Utils ut;

    void Utils::getSystemDate(int* year, int* mon, int* day)
    {
        if (m_testMode) {
            if (day) {
                *day = sdds_testDay;
            }
            if (mon) {
                *mon = sdds_testMon;
            }
            if (year) {
                *year = sdds_testYear;
            }
        }
        else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) {
                *day = lt.tm_mday;
            }
            if (mon) {
                *mon = lt.tm_mon + 1;
            }
            if (year) {
                *year = lt.tm_year + 1900;
            }
        }
    }

    int Utils::daysOfMon(int month, int year) const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return (days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)));
    }

    // assign value for test
    void Utils::testMode(bool testmode)
    {
        m_testMode = testmode;
    }

    void Utils::alocpy(char*& destination, const char* source)
    {
        delete[] destination;
        destination = nullptr;
        if (source != nullptr && strcmp(source, "") != 0) {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    int Utils::getint(const char* prompt)
    {
        int input;
        if (prompt != nullptr) {
            cout << prompt;
        }
        bool valid = true;
        while (valid) {
            cin.clear();
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cout << "Invalid Integer, retry: ";
                cin.ignore(1000, '\n');
            }
            else {
                valid = false;
            }
        }
        return input;
    }

    int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
        int input;
        char buffer;
        bool flag = false;
        if (prompt) {
            cout << prompt;
        }
        do {
            cin >> input;
            if (!cin) {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                cin.get(buffer);
                if (buffer != '\n') {
                    cout << "Enter only an integer, try again: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else if (input < min || input > max) {
                    if (errMes) {
                        cout << errMes << ", retry: ";
                    }
                    else {
                        cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                    }
                }
                else {
                    flag = true;
                }
            }
        } while (!flag);
        return input;
    }

    double Utils::getdouble(const char* prompt, const char* errMes)
    {
        double userInput = 0;
        if (prompt != nullptr) {
            cout << prompt;
        }
        do {
            cin >> userInput;
            if (!cin) {
                cout << "Invalid number, retry: ";
                cin.clear();
                cin.ignore(2000, '\n');
            }
        } while (!userInput);
        return userInput;
    }

    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes)
    {
        double input;
        char buffer;
        bool flag = false;
        if (prompt) {
            cout << prompt;
        }
        do {
            cin >> input;
            if (!cin) {
                cout << "Invalid number, retry: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                cin.get(buffer);
                if (buffer != '\n') {
                    cout << "Enter only a double, try again: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else if (input < min || input > max) {
                    if (errMes) {
                        cout << errMes << ", retry: ";
                    }
                    else {
                        cout << "Value out of range [" << fixed << setprecision(2) << min << "<=val<=" << max << "]: ";
                    }
                }
                else {
                    flag = true;
                }
            }
        } while (!flag);
        return input;
    }

    void Utils::extractChar(std::istream& is, char temp) const
    {
        if (is.peek() != temp) {
            is.ignore(1000, temp);
            is.setstate(ios::failbit);
        }
        else {
            is.ignore();
        }
    }
}
