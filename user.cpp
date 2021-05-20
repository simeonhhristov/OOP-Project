#include "user.h"
#include <cstring>

User::User()
{
    this->username = "Undefined";
    this->email = "Undefined";
    this->password = "Undefined";
    this->friendsList = nullptr;
    this->numOfFriends = 0;
    this->currentLimitOfFriends = 0;
}
User::User(String _username, String _email, String _password, String friends)
{
    this->username = _username;
    this->email = _email;
    this->password = _password;
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
        // this->friendsList = new String[currentLimitOfFriends];

        // for (size_t i = 0; i < this->numOfFriends; i++)
        // {
        //     this->friendsList[i] = tempList[i];
        // }
        this->friendsList = tempList;
        this->numOfFriends++;
    }
    else
    {
        this->friendsList[this->numOfFriends] = newFriend;
        this->numOfFriends++;
    }
}
void User::updateDB()
{
    // String updatedList = "Friends:";
    // for (size_t i = 0; i < this->numOfFriends; i++)
    // {
    //     updatedList +=this->friendsList[i];
    //     updatedList += ",";
    // }
    // std::cout <<"-->" << updatedList << " <--";

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