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
    String hi = "";
    hi.pushBack('`');
    std::cout << hi;
    //login / register prompt
    std::cout << "Welcome to Simeon's traveler app!" << std::endl;
    std::cout << "Press R to sign up or L to log in:" << std::endl
              << "[S]/[L] :";
    char action;
    std::cin >> action;

    while (!(action == 'S' || action == 's' || action == 'L' || action == 'l'))
    {
        std::cout << "Please enter a valid key value:" << std::endl
                  << "[S]/[L] :";
        std::cin >> action;
    }

    User *currentUser = new User();
    UserFactory userFactory;
    Authenticator auth;

    if (action == 'L' || action == 'l')
    {
        currentUser = auth.authenticate();
    }
    else if (action == 'S' || action == 's')
    {
        currentUser = userFactory.createUser();
    }

    // String newFriend;
    // std::cin >> newFriend;
    // if (currentUser->isExistingUser(newFriend))
    // {
    //     currentUser->addFriend(newFriend);
    // }
    std::cout << *currentUser;
    currentUser->addJourney();
    // when program ends..
    // currentUser->updateDB();

    std::cout << std::endl;
}