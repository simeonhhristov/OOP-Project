#include "authenticator.h"

User *Authenticator::authenticate()
{
    User *returnUser;

    bool found = 0;
    while (!found)
    {

        String username;
        String email;
        String password;

        std::cout << "Enter your Username:";
        std::cin >> username;
        std::cout << "Enter your password:";
        std::cin >> password;
        encrypt(password);

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
                    fin.close();
                    return currentUser;
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

void Authenticator::encrypt(String &input)
{
    String encrypted = "";
    for (int i = 0; i < input.getSize(); i++)
    {
        char a;
        char b;
        char c;
        if (input[i] - 1 == 32)
        {
            a = (char)(input[i] + 32);
        }
        else
        {
            a = (char)(input[i] - 1);
        }

        if (input[i] + 4 >= 127)
        {
            b = (char)((input[i] + 6) % 95 + 33);
        }
        else
        {
            b = (char)(input[i] + 6);
        }
        if (input[i] + 2 >= 127)
        {
            c = (char)((input[i] + 2) % 95 + 33);
        }
        else
        {
            c = (char)(input[i] + 2);
        }
        encrypted.pushBack(a);
        encrypted.pushBack(b);
        encrypted.pushBack(c);
    }
    input = encrypted;
}