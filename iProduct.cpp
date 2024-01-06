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

#include "iProduct.h"

namespace sdds
{
    std::ostream& operator<<(std::ostream& ostr, const iProduct& iP) { return iP.display(ostr); }
    std::istream& operator>>(std::istream& istr, iProduct& iP) { return iP.read(istr); }
}
