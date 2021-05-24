#pragma once
#include <iostream>
#include <fstream>
#include "date.h"
#include "string.h"

class User
{
public:
    String email;
    String username;
    String password;
    String *allUsers;
    String *friendsList;
    int numOfFriends;
    int currentLimitOfFriends;

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

    void splitString(String);
    void updateDB();

    void addJourney();
    void destinationGradeByFriends(/*char*/);
    void destinationGradeByAll(char *);

    void addFriend(String);
    bool isExistingUser(String);
    void printFriends();
};