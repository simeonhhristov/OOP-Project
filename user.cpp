#include "user.h"
#include <cstring>

User::User()
{
    this->username = "Undefined";
    this->email = "Undefined";
    this->password = "Undefined";
    this->friendsList = new String[8];
    this->numOfFriends = 0;
    this->currentLimitOfFriends = 8;
}
User::User(String _username, String _email, String _password, String friends)
{
    this->username = _username;
    this->email = _email;
    this->password = _password;
    this->friendsList = new String[8];
    this->currentLimitOfFriends = 8;
    this->numOfFriends = 0;

    if (friends == "NULL")
    {
        this->addFriend("]");
    }
    else
    {
        splitString(friends);
    }
}

User& User::operator=(const User& other)
{
    if (this!= &other)
    {
        delete [] this->friendsList;
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
    //starting from 8th index because Friends are stored as string starting with "Friends:"
    if (str =="Friends:")
    {
        return;
    }
    

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

void User::destinationGradeByFriends(char *)
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
        String *tempList = new String[currentLimitOfFriends];

        for (int i = 0; i < numOfFriends; i++)
        {
            tempList[i] = this->friendsList[i];
        }
        tempList[this->numOfFriends] = newFriend;

        this->friendsList = tempList;
        this->numOfFriends++;

        return;
    }

    this->friendsList[this->numOfFriends] = newFriend;
    this->numOfFriends++;
}

void User::printFriends()
{
}