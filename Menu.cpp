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

#include <string>
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    Menu::Menu()
    {
        m_Content = nullptr;
        m_numOpt = 0;
    }
    Menu::Menu(const char* content)
    {
        int opt = 0;
        for (size_t i = 0; i < strlen(content); i++) {
            if (content[i] == '\t') {
                opt++;
            }
        }

        if (content && opt <= 15) {
            // dynamically allocating memory for the c-string 
            m_Content = new char[strlen(content) + 1];
            strcpy(m_Content, content);
            m_numOpt = opt + 1;
        }
        else  //  if the number of options is more than 15 or if the C-String is null, then the menu is rendered invalid.
        {
            m_Content = nullptr;
            m_numOpt = 0;
        }
    }

    Menu::~Menu() {
        delete[] m_Content; // making sure there is no memory leaks 
    }


    /*
    The run method will first displays the menu content in a menu format, prints a separator line and then prints "0- Exit"
    and finally goes to a new line. Then it will display "> " as a prompt and waits for the user to enter an integer
    */
    unsigned int Menu::run()
    {
        if (!m_Content) {
            std::cout << "Invalid Menu!" << std::endl;
            return 0;
        }

        while (true) {

            size_t optionNum = 1;
            std::istringstream stream(m_Content);
            std::string token;

            while (std::getline(stream, token, '\t')) {
                std::cout << optionNum << "- " << token << std::endl;
                optionNum++;
            }

            std::cout << "---------------------------------" << std::endl;
            std::cout << "0- Exit" << std::endl;

            unsigned int choice; // stores the choice enterd by user 
            do {
                std::cout << "> ";
                choice = ut.getint(0, 7);

                if (std::cin.fail()) // If the user enters a non-integer value and we check it by calling the fail function 
                {
                    std::cout << "Invalid Integer, retry: ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cin >> choice;
                }
                else if (choice < 0 || choice > m_numOpt) // If the user enters an invalid integer  
                {
                    std::cout << "Value out of range [0<=val<=" << m_numOpt << "]: ";
                    std::cin >> choice;
                }
            } while (choice < 0 || choice > m_numOpt);

            if (choice == 0) {
                return choice;
            }

            return choice; // returns the option selected by user
        }


    }
}