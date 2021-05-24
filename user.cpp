#include "user.h"
#include "date.h"
#include <cstring>

User::User()
{
    this->username = "Undefined";
    this->email = "Undefined";
    this->password = "Undefined";
    this->allUsers = nullptr;
    this->friendsList = nullptr;
    this->numOfFriends = 0;
    this->currentLimitOfFriends = 0;
}
User::User(String _username, String _email, String _password, String friends)
{
    this->username = _username;
    this->email = _email;
    this->password = _password;
    this->allUsers = new String[10];
    this->friendsList = new String[8];
    this->currentLimitOfFriends = 8;
    this->numOfFriends = 0;
    splitString(friends);
}

User &User::operator=(const User &other)
{
    if (this != &other)
    {
        delete[] this->friendsList;
        this->username = other.username;
        this->email = other.email;
        this->password = other.password;
        this->currentLimitOfFriends = other.currentLimitOfFriends;
        this->numOfFriends = other.numOfFriends;
        this->friendsList = new String[numOfFriends];
        for (size_t i = 0; i < numOfFriends; i++)
        {
            this->friendsList[i] = other.friendsList[i];
        }
    }
    return *this;
}
void User::splitString(String str)
{
    String temp = "";
    if (str == "Friends:")
    {
        return;
    }
    //starting from 8th index because Friends are stored as string starting with "Friends:"
    for (int i = 8; str[i] != '\0'; i++)
    {
        temp.pushBack(str[i]);
        if (str[i + 1] == ',')
        {
            this->addFriend(temp);
            temp = "";
            i++;
        }
    }
}

void User::addJourney()
{
    std::cout << std::endl;
    String location;
    char temp[300];
    Date start;
    Date end;
    int grade = 0;
    String comment;
    String images;

    std::cin.ignore();
    std::cin.getline(temp, 100);
    location = temp;

    std::cout << "Date period. From: " << std::endl;
    std::cin >> start;
    std::cout << "To: " << std::endl;
    std::cin >> end;

    while (start - end > 0)
    {
        std::cout << "Invalid period, try again. From: " << std::endl;
        std::cin >> start;
        std::cout << "To: " << std::endl;
        std::cin >> end;
    }

    while (grade < 1 || grade > 5)
    {
        std::cout << "Select a grade from 1 - 5: ";
        std::cin >> grade;
    }

    std::cout << "Add a comment about your experience: " << std::endl;
    std::cin.ignore();
    std::cin.getline(temp, 300);
    comment = temp;

    std::cout << "Add some images you'd like to share: " << std::endl;

    bool correct = 0;
    while (!correct)
    {
        std::cin.getline(temp, 300);
        bool foundSpace = 0;

        for (int i = 0; temp[i] != '\0'; i++)
        {
            if (!((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z') || temp[i] == '_' || temp[i] == ' ' || temp[i] == '.'))
            {
                std::cout << "Invalid symbols detected, valid symbols are a - z, A - Z and _" << std::endl;
                break;
            }
            if (temp[i] == ' ' && foundSpace)
            {
                std::cout << "No spaces in file names allowed. Please Try again." << std::endl;
                break;
            }
            else if (temp[i] == ' ')
            {
                foundSpace = 1;
            }

            if (temp[i] == '.')
            {
                foundSpace = 0;

                if (temp[i - 1] == ' ')
                {
                    std::cout << "Invalid file name detected. Please Try again." << std::endl;
                    break;
                }
                if (!((temp[i + 1] == 'p' && temp[i + 2] == 'n' && temp[i + 3] == 'g') || (temp[i + 1] == 'j' && temp[i + 2] == 'p' && temp[i + 3] == 'e' && temp[i + 4] == 'g')))
                {
                    std::cout << "Invalid file extensions detected. Valid are .png, .jpeg" << std::endl;
                    break;
                }
            }

            if (temp[i + 1] == '\0')
            {
                correct = 1;
            }
        }
    }

    images = temp;
    location.charReplace(' ', '`');
    comment.charReplace(' ', '`');
    images.charReplace(' ', '`');

    String file = "users/";
    file.append(this->username);
    file.append(".db");
    std::ofstream fout;
    fout.open(file.getData(), std::ios::app);
    fout << location << " " << start << " " << end << " " << grade << " " << comment << " " << images;
    fout.close();
}

void User::destinationGradeByFriends(/*char **/)
{
}
void User::destinationGradeByAll(char *)
{
}

void User::addFriend(String newFriend)
{
    if (this->numOfFriends == this->currentLimitOfFriends - 1)
    {
        this->currentLimitOfFriends *= 2;
        String *tempList = new String[this->currentLimitOfFriends];

        for (int i = 0; i < numOfFriends; i++)
        {
            tempList[i] = this->friendsList[i];
        }

        tempList[this->numOfFriends] = newFriend;

        delete[] this->friendsList;
        this->friendsList = tempList;
        this->numOfFriends++;
    }
    else
    {
        this->friendsList[this->numOfFriends] = newFriend;
        this->numOfFriends++;
    }
}

bool User::isExistingUser(String user)
{
    if (user == this->username)
    {
        std::cout << "You can't add yourself as a friend." << std::endl;
        return 0;
    }
    for (int i = 0; i < this->numOfFriends; i++)
    {
        if (this->friendsList[i] == user)
        {
            std::cout << friendsList[i] << " is already your friend." << std::endl;
            return 0;
        }
    }

    String field1;
    String field2;
    String field3;
    String field4;

    std::ifstream fin("users.db");
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            if (field1 == user)
            {
                fin.close();
                return 1;
            }
        }
        if (fin.eof())
        {
            fin.close();
            return 0;
        }
    }
    fin.close();

    return 0;
}

void User::updateDB()
{
    String field1;
    String field2;
    String field3;
    String field4;

    std::ifstream fin("users.db");
    std::ofstream fout("update.db", std::ios::app);
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            if (field1 == this->username)
            {
                fout << *this << std::endl;
                continue;
            }
            fout << field1 << " " << field2 << " " << field3 << " " << field4 << std::endl;
        }
    }
    if (fin.eof())
    {
        remove("users.db");
        rename("update.db", "users.db");
        fin.close();
        fout.close();
    }
}

void User::printFriends()
{
}