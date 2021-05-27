#include "authenticator.h"

User *Authenticator::authenticate()
{
    String username;
    String email;
    String password;

    User *returnUser;

    bool found = 0;
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
                    User *currentUser = new User(data1, data2, data3, friendsList);
                    returnUser = currentUser;
                    found = 1;

                    break;
                }
            }
            if (fin.eof())
            {
                std::cout << "No such username and password combination found, please try again." << std::endl;
            }
        }
        fin.close();
    }
    return returnUser;
}