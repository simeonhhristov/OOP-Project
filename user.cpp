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
    this->numOfFriends = 1;
    if (friends == "NULL")
    {
        this->friendsList[0] = "]";
    }
    else
    {
        splitString(friends);
    }
    
}

void User::splitString(String str)
{
    String temp = "";
    for (int i = 0 ; str[i] != '\0'; i++)
    {   
        temp.pushBack(str[i]);
        std::cout << temp;
        std::cout << " ";
        if (str[i + 1] == ',')
        {
            this->addFriend(temp);
            temp = "";
            i++;
        }
    }
}

void User::destinationGradeByFriends(char*)
{

}
void User::destinationGradeByAll(char*)
{

}

void User::addFriend(String newFriend)
{
    if (this->numOfFriends == this->currentLimitOfFriends - 1)
    {
        this->currentLimitOfFriends *= 2;
        String * tempList = new String[currentLimitOfFriends];

        for (int i = 0; i < numOfFriends; i++)
        {
            tempList[i] = this->friendsList[i];
        }
        tempList[this->numOfFriends] = newFriend;

        this->friendsList = tempList;
        this->numOfFriends++;

        return;
    }
    
    if (this->friendsList[0][0] == ']')
    {
        this->friendsList[0] = newFriend;
        return;
    }
    

    this->friendsList[this->numOfFriends] = newFriend;
    this->numOfFriends++;
}

void User::printFriends()
{
    
}