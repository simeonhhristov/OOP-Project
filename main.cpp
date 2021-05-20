#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include "user.h"
#include "string.h"
#include "date.h"
#include "user_factory.h"
#include "authenticator.h"

int main()
{
    String str = "hi";
    //login / register prompt
    std::cout << "Welcome to Simeon's traveler app!" << std::endl;
    std::cout << "Press R to sign up or L to log in:" << std::endl
              << "[R]/[L] :";
    char action;
    std::cin >> action;

    while (!(action == 'R' || action == 'r' || action == 'L' || action == 'l'))
    {
        std::cout << "Please enter a valid key value:" << std::endl
                  << "[R]/[L] :";
        std::cin >> action;
    }

    User *currentUser = new User();
    UserFactory userFactory;
    Authenticator auth;

    //login form
    if (action == 'L' || action == 'l')
    {
        currentUser = auth.authenticate();
    }
    else if (action == 'R' || action == 'r')
    {
        currentUser = userFactory.createUser();
    }

    currentUser->addFriend("friend1");

    currentUser->updateDB();

    User date;

    String data1;
    String data2;
    String data3;
    String data4;

    //subtring

    // std::cin >> data1;
    // std::cout << data1;

    // std::ifstream fin("users.db");
    // if (fin.is_open())
    // {
    //     while(fin >> data1  >> data2 >> data3 >> data4)
    //     {
    //         if (data1 == "georgi123")
    //         {
    //             std::cout << data1 << data2 << data3 << " "<<  data4;
    //             std::cout << std::endl;
    //         }
    //     }
    // }

    //std::cout << date;

    //fin.close();

    // char*  str = new char[256];
    // std::cin.getline(str,3);
    // std::cout <<  str;
    std::cout << std::endl;
}