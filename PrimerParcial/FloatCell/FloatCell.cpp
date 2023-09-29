#include "FloatCell.h"

// Default constructor
FloatCell::FloatCell(float newValue) : storedValue(newValue) {}

// Copy constructor
FloatCell::FloatCell(const FloatCell &rhs) : storedValue(rhs.storedValue) {}

// Move constructor
FloatCell::FloatCell(FloatCell &&rhs) noexcept : storedValue(rhs.storedValue)
{
    rhs.storedValue = 0;
}
// Copy assignment operator
FloatCell &FloatCell::operator=(const FloatCell &rhs){
    if (this != &rhs)
    {
        storedValue = rhs.storedValue;
    }
    return *this;
}

// Remove Move assignment operator
FloatCell &FloatCell::operator=(FloatCell &&rhs) noexcept {
    if (this != &rhs)
    {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0;
    }
    return *this;
}

// Removed overloaded assignment operator to accept any data

// Overloaded assignment operator to accept only integer data
FloatCell &FloatCell::operator=(float rhs){
    storedValue = rhs;
    return *this;
}