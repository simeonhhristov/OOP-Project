#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <filesystem>
#include "user.h"
#include "string.h"
#include "date.h"
#include "user_factory.h"
#include "authenticator.h"

int main()
{
    //login / register prompt
    std::cout << "Welcome to Simeon's traveler app!" << std::endl;
    std::cout << "Press S to sign up or L to log in:" << std::endl
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
    std::cout << "You are logged as: " << currentUser->getUsername() << std::endl;


    bool loop = 1;

    while (loop)
    {
        char option;
        std::cout << std::endl;
        std::cout << "Select one of the options below:"<< std::endl;
        std::cout << "1: Add a Friend."<< std::endl;
        std::cout << "2: Add a journey."<< std::endl;
        std::cout << "3: Look up information about a destination."<< std::endl;
        std::cout << "4: Look up a Friend's journeys."<< std::endl;
        std::cout << "5: Close the program."<< std::endl;

        std::cin >> option;

        switch (option)
        {
        case '1':
            //add friend method
            currentUser->manualAdd();
            break;
        case '2':
            //add friend method
            currentUser->addJourney();
            break;
        case '3':
            //search for a destination information
            currentUser->destinationGradeByAll();
            break;
        case '4':
            //look up a friend's trips
            currentUser->visitedByFriend();
            break;

        case '5':
            // when program ends..
            currentUser->updateDB();
            loop = 0;
            break;
        }
    }

    std::cout << std::endl;
}