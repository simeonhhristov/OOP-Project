#include "user_factory.h"

User UserFactory::createUser()
{
    String username;
    String email;
    String password;
    String friends = "Friends:";

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

    return currentUser;
}