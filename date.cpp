#include "date.h"

bool Date::isLeap(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool Date::isValidDate(int d, int m, int y)
{
    // If year, month and day
    // are not in given range
    if (d < 1 || d > 31)
    {
        std::cout << "Invalid day, please try again." << std::endl;
        return false;
    }

    if (m < 1 || m > 12)
    {
        std::cout << "Invalid month, please try again." << std::endl;
        return false;
    }

    // February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
        {
            if (!(d <= 29))
            {
                std::cout << "Invalid day, please try again." << std::endl;
            }

            return (d <= 29);
        }
        else
        {
            if (!(d <= 28))
            {
                std::cout << "Invalid day, please try again." << std::endl;
            }
            return (d <= 28);
        }
    }

    // months April June September November
    if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        if (!(d <= 30))
        {
            std::cout << "Invalid day, please try again." << std::endl;
            return 0;
        }
        return (d <= 30);
    }
    return true;
}

int Date::operator-(const Date &other)
{
    //if negative then the time period is valid
    //if positive then it's not valid
    //if 0 then its the same day

    if (this->year - other.year != 0)
    {
        return this->year - other.year;
    }
    else if (this->month - other.month != 0)
    {
        return this->year - other.year;
    }
    else
    {
        return this->day - other.day;
    }
}