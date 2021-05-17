#include "date.h"

bool Date::isLeap(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)); 
}

bool Date::isValidDate(int d, int m, int y)
{
    // If year, month and day
    // are not in given range
    if (m < 1 || m > 12)
    {
        return false;
    }
        
    if (d < 1 || d > 31)
    { 
        return false;
    }

    // February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
        {
            return (d <= 29);
        }      
        else
        {
            return (d <= 28);
        }        
    }

    // months April June September November
    if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        return (d <= 30);
    }
    return true;
}