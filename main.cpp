#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include "user.h"
#include "string.h"
#include "date.h"


User signUp()
{
    String username;
    String email;
    String password;
    String friends = "NULL";

    std::cout << "Enter your Username:";
    std::cin >> username;
    std::cout << "Enter your Email:";
    std::cin >> email;
    std::cout << "Enter your password:";
    std::cin >> password;



    User currentUser(username, email, password, friends);

    std::ofstream fout;
    fout.open("users.db", std::ios::app);
    fout << currentUser;
    fout.close();

    currentUser.addFriend(username);
    std::cout << currentUser.friendsList[0];
    return currentUser;
}



int main()
{   
    String null = "NULL";
    std::cout << (null == "NULL")<<"<<";

    //login / register prompt
    std::cout << "Welcome to Simeon's traveler app!" <<std::endl;
    std::cout << "Press R to sign up or L to log in:"<< std::endl << "[R]/[L] :" ;
    char action;
    std::cin >> action;

    while (!(action == 'R' || action == 'r' || action == 'L' || action == 'l'))
    {
        std::cout << "Please enter a valid key value:"<< std::endl << "[R]/[L] :" ;
        std::cin >> action;
    } 

    

    //login form
    if (action == 'L' || action == 'l')
    {
        String username;
        String email;
        String password;

        bool found= 0;
        while (!found)
        {
            
            std::cout << "Enter your Username:";
            std::cin >> username;
            std::cout << "Enter your password:";
            std::cin >> password;

            //Strings to see if information is indeed in the database
            String data1;
            String data2;
            String data3;
            String friendsList(512);

            std::ifstream fin("users.db");
            if (fin.is_open())
            {
                while (fin >> data1 >> data2 >> data3 >> friendsList)
                {
                    if (data1 == username && data3 == password)
                    {
                        // initialize class with this data...
                        User currentUser(data1, data2, data3, friendsList);
                        found = 1;
                        std::cout << currentUser;
                        break; // so i dont trigger eof
                    }                      
                }
                if (fin.eof())
                {
                    std::cout  << "No such username and password combination found, please try again." << std::endl;
                } 
            }
            fin.close();
        }
    }
    
    if (action == 'R' || action =='r')
    {   
        signUp();
    }
    
    

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