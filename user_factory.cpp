#include "user_factory.h"

User *UserFactory::createUser()
{
    String username;
    String email;
    String password;
    String friends = "Friends:";

    String existingUsername;
    String existingEmail;
    String data1;
    String data2;

    std::cout << "Enter your Username:";
    std::cin >> username;
    while (!validSymbols(username))
    {
        std::cin >> username;
    }

    std::cout << "Enter your Email:";
    std::cin >> email;
    while (!validEmail(email))
    {
        std::cout << "Invalid email address, try again: ";

        std::cin >> email;
    }
    std::cout << "Enter your password (min 8 symbols): ";
    std::cin >> password;
    while (password.getSize() < 8)
    {
        std::cout << "Password must be 8 or more symbols: ";
        std::cin >> password;
    }

    int status = checkIfUsed(username, email);

    while (status != 0)
    {
        if (status == 1)
        {
            std::cout << "The username and email you chose are both already used, please choose different:" << std::endl;
            std::cin >> username;
            while (!validSymbols(username))
            {
                std::cin >> username;
            }

            std::cin >> email;
            while (!validEmail(email))
            {
                std::cin >> email;
            }
            status = checkIfUsed(username, email);
        }
        if (status == 2)
        {
            std::cout << "The username you chose is already used, please choose different:" << std::endl;
            while (!validSymbols(username))
            {
                std::cin >> username;
            }
            status = checkIfUsed(username, email);
        }
        if (status == 3)
        {
            std::cout << "The email you chose is already used, please choose different:" << std::endl;
            std::cin >> email;
            while (!validEmail(email))
            {
                std::cin >> email;
            }
            status = checkIfUsed(username, email);
        }
    }

    User *currentUser = new User(username, email, password, friends);
    std::ofstream fout;
    fout.open("users.db", std::ios::app);
    fout << *currentUser;
    fout.close();

    return currentUser;
}

int UserFactory::checkIfUsed(String username, String email)
{
    String field1;
    String field2;
    String field3;
    String field4;

    std::ifstream fin("users.db");
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            //different return code depending on what needs changing..
            if (field1 == username && field2 == email)
            {
                return 1;
            }
            if (field1 == username)
            {
                return 2;
            }
            if (field2 == email)
            {
                return 3;
            }
        }
    }
    else
    {
        return 0;
    }
    fin.close();

    return 0;
}

bool UserFactory::validEmail(String email)
{
    if (!validSymbols(email))
    {
        return false;
    }

    if (!((email[0] >= 'a' && email[0] <= 'z') || (email[0] >= 'A' && email[0] <= 'Z')))
    {
        //email must start with an alphabeth symbol..
        return false;
    }

    int at = -1;
    int dot = -1;

    //searching for '.' and '@'..
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            //in case there is a second @ in the string
            if (at > 0)
            {
                return false;
            }

            at = i;
        }
        else if (email[i] == '.')
        {
            dot = i;
        }
    }

    //if not present..
    if (dot == -1 || at == -1)
    {
        return false;
    }

    //if dot is before @
    if (at > dot)
    {
        return false;
    }

    //if dot is at end
    return !(dot >= (email.getSize() - 1));
}
bool UserFactory::validSymbols(String string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            continue;
        }
        else if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
        {
            continue;
        }
        else if (string[i] == '@' || string[i] == '.' || string[i] == '_' || string[i] == '!' || (string[i] >= '#' && string[i] <= '&') || string[i] == '*' || string[i] == '+' || string[i] == '-')
        {
            continue;
        }
        else if ((string[i] >= '{' && string[i] <= '~'))
        {
            continue;
        }
        else
        {
            std::cout << string[i] << " Is not a valid symbol! Please try again.";
            return false;
        }
    }
    return true;
}