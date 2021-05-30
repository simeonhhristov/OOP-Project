#pragma once
#include <iostream>
#include <fstream>
#include "date.h"
#include "string.h"

class User
{
private:
    String email;
    String username;
    String password;
    String *friendsList;
    int numOfFriends;
    int currentLimitOfFriends;

    bool validFile(String);
    void splitString(String);
    bool isExistingUser(String);
    bool isFriend(String);
    void addFriend(String);

public:
    User();
    User(String, String, String, String);
    User &operator=(const User &);

    friend std::istream &operator>>(std::istream &in, User &user)
    {
        in >> user.username >> user.email >> user.password;
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const User &user)
    {
        out << user.username << " " << user.email << " " << user.password << " Friends:";

        for (int i = 0; i < user.numOfFriends; i++)
        {
            out << user.friendsList[i] << ",";
        }
        return out;
    }
    String getUsername();

    void addJourney();
    void visitedByFriend();
    void destinationGradeByAll();
    void manualAdd();

    void printFriends();
    void updateDB();
};