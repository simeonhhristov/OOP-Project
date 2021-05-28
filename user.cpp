#include "user.h"
#include "date.h"
#include <cstring>

User::User()
{
    this->username = "Undefined";
    this->email = "Undefined";
    this->password = "Undefined";
    this->allUsers = nullptr;
    this->friendsList = nullptr;
    this->numOfFriends = 0;
    this->currentLimitOfFriends = 0;
}
User::User(String _username, String _email, String _password, String friends)
{
    this->username = _username;
    this->email = _email;
    this->password = _password;
    this->allUsers = new String[10];
    this->friendsList = new String[8];
    this->currentLimitOfFriends = 8;
    this->numOfFriends = 0;
    splitString(friends);
}
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        delete[] this->friendsList;
        this->username = other.username;
        this->email = other.email;
        this->password = other.password;
        this->currentLimitOfFriends = other.currentLimitOfFriends;
        this->numOfFriends = other.numOfFriends;
        this->friendsList = new String[numOfFriends];
        for (size_t i = 0; i < numOfFriends; i++)
        {
            this->friendsList[i] = other.friendsList[i];
        }
    }
    return *this;
}
String User::getUsername()
{
    return this->username;
}

void User::splitString(String str)
{
    String temp = "";
    if (str == "Friends:")
    {
        return;
    }
    //starting from 8th index because Friends are stored as string starting with "Friends:"
    for (int i = 8; str[i] != '\0'; i++)
    {
        temp.pushBack(str[i]);
        if (str[i + 1] == ',')
        {
            this->addFriend(temp);
            temp = "";
            i++;
        }
    }
}
bool User::validFile(String fileName)
{
    bool foundDot = 0;
    for (int i = 0; fileName[i] != '\0'; i++)
    {
        if (!((fileName[i] >= 'a' && fileName[i] <= 'z') || (fileName[i] >= 'A' && fileName[i] <= 'Z') || fileName[i] == '_' || fileName[i] == ' ' || fileName[i] == '.'))
        {
            std::cout << "Invalid symbols detected, valid symbols are a - z, A - Z and _" << std::endl;
            return 0;
        }
        if (fileName[i] == ' ')
        {
            std::cout << "No Spaces in file names allowed." << std::endl;
            return 0;
        }

        if (fileName[i] == '.')
        {
            foundDot = 1;

            if (!((fileName[i + 1] == 'p' && fileName[i + 2] == 'n' && fileName[i + 3] == 'g') || (fileName[i + 1] == 'j' && fileName[i + 2] == 'p' && fileName[i + 3] == 'e' && fileName[i + 4] == 'g')))
            {
                std::cout << "Invalid file extensions detected. Valid are .png, .jpeg" << std::endl;
                return 0;
            }
            continue;
        }

        if (fileName[i] == '.' && foundDot)
        {
            std::cout << "Invalid symbol extension." << std::endl;
            return 0;
        }
    }
    if (!foundDot)
    {
        std::cout << "Invalid file." << std::endl;
        return 0;
    }
    return 1;
}

void User::addJourney()
{
    std::cout << std::endl;
    String location;
    char temp[300];
    Date start;
    Date end;
    int grade = 0;
    String comment;
    String images = "";
    String separateImg = "";

    std::cout << "Enter destination name: " << std::endl;
    std::cin.ignore();
    std::cin.getline(temp, 100);
    location = temp;

    std::cout << "Date period (Date format - [YYYY]-[MM]-[DD]). From: " << std::endl;
    std::cin >> start;
    std::cout << "To: " << std::endl;
    std::cin >> end;

    while (start - end > 0)
    {
        std::cout << "Invalid period, try again. From: " << std::endl;
        std::cin >> start;
        std::cout << "To: " << std::endl;
        std::cin >> end;
    }

    while (grade < 1 || grade > 5)
    {
        std::cout << "Select a grade from 1 - 5: ";
        std::cin >> grade;
    }

    std::cout << "Add a comment about your experience: " << std::endl;
    std::cin.ignore();
    std::cin.getline(temp, 300);
    comment = temp;
    std::cout << std::endl;

    std::cout << "Add some images you'd like to share: " << std::endl;
    std::cout << "Instructions: type the name of your file and press enter, type 'done' when you are ready. " << std::endl;

    while (1)
    {
        std::cin >> separateImg;
        if (separateImg == "done")
        {
            break;
        }

        if (!validFile(separateImg))
        {
            continue;
        }

        images.append(separateImg);
        images.append(",");
    }

    location.charReplace(' ', '`');
    comment.charReplace(' ', '`');

    String file = "users/";
    file.append(this->username);
    file.append(".db");
    if (images.getSize() == 0)
    {
        images = "none";
    }

    std::ofstream fout;
    fout.open(file.getData(), std::ios::app);
    fout << location << " " << start << " " << end << " " << grade << " " << comment << " " << images << std::endl;
    fout.close();

    std::cout << std::endl;
}

void User::visitedByFriend()
{
    if (this->numOfFriends == 0)
    {
        std::cout << "You don't have any friends." << std::endl;
        return;
    }

    this->printFriends();
    String friendName;
    std::cout << "Enter the name of the friend whom you want to look up: ";
    std::cin >> friendName;
    while (!isFriend(friendName))
    {
        std::cout << friendName << " is not your friend, please try again.";
        std::cin >> friendName;
    }

    String field1;
    String field2;
    String field3;
    String field4;
    String field5;
    String field6;

    String file = "users/";
    file.append(friendName);
    file.append(".db");

    int count = 0;
    std::ifstream fin(file.getData());
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4 >> field5 >> field6)
        {
            field1.charReplace('`', ' ');
            field5.charReplace('`', ' ');
            std::cout << field1 << " " << field2 << "-" << field3 << " " << field4 << " " << field5 << " " << field6 << std::endl;
            count++;
        }
    }
    fin.close();
    if (count == 0)
    {
        std::cout << friendName << " hasn't published any journeys yet." << std::endl;
    }
    
}

void User::destinationGradeByAll()
{
    String destination;
    std::cout << "Enter destination name, make sure it's as short as possible for more results." << std::endl;
    std::cin >> destination;
    int n = 20;
    String *users = new String[n];

    std::ifstream fin("users.db");
    int i = 0;
    if (fin.is_open())
    {
        String field1;
        String field2;
        String field3;
        String field4;

        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            if (field1 == username)
                continue;

            if (i == n - 1)
            {
                n *= 2;
                String *temp = new String[n];
                for (int j = 0; j < i; j++)
                {
                    temp[j] = users[j];
                }
                temp[i] = field1;

                delete[] users;
                users = temp;
                i++;
            }
            else
            {
                users[i] = field1;
                i++;
            }
        }
    }
    fin.close();

    for (size_t j = 0; j < i; j++)
    {
        String fileName = "users/";
        users[j] = fileName.append(users[j]);
        users[j].append(".db");
    }

    double averageGrade = 0;
    int count = 0;
    for (int j = 0; j < i; j++)
    {
        String field1;
        String field2;
        String field3;
        int field4;
        String field5;
        String field6;

        std::ifstream fin(users[j].getData());
        if (fin.is_open())
        {
            while (fin >> field1 >> field2 >> field3 >> field4 >> field5 >> field6)
            {
                field1.charReplace('`', ' ');
                if (destination.isContained(field1))
                {
                    field5.charReplace('`', ' ');
                    std::cout << field1 << ", Period: " << field2 << "-" << field3 << ", Grade: " << field4 << ", Comment:" << field5 << " Shared images: " << field6 << std::endl;
                    averageGrade += field4;
                    count++;
                }
            }
        }
        fin.close();
    }
    if (count == 0)
    {
        std::cout << "No information found for " << destination << std::endl;
    }
    else
    {
        std::cout << "Average grade for " << destination << ": " << averageGrade / count << std::endl;
    }
}
void User::manualAdd()
{
    std::cout << "Name of friend you want to add: ";
    String newFriend;
    std::cin >> newFriend;

    if (isExistingUser(newFriend) && !isFriend(newFriend))
    {
        this->addFriend(newFriend);
        return;
    }
}
void User::addFriend(String newFriend)
{
    if (this->numOfFriends == this->currentLimitOfFriends - 1)
    {
        this->currentLimitOfFriends *= 2;
        String *tempList = new String[this->currentLimitOfFriends];

        for (int i = 0; i < numOfFriends; i++)
        {
            tempList[i] = this->friendsList[i];
        }

        tempList[this->numOfFriends] = newFriend;

        delete[] this->friendsList;
        this->friendsList = tempList;
        this->numOfFriends++;
    }
    else
    {
        this->friendsList[this->numOfFriends] = newFriend;
        this->numOfFriends++;
    }
}

bool User::isExistingUser(String user)
{
    if (user == this->username)
    {
        std::cout << "You can't add yourself as a friend." << std::endl;
        return 0;
    }
    for (int i = 0; i < this->numOfFriends; i++)
    {
        if (this->friendsList[i] == user)
        {
            std::cout << friendsList[i] << " is already your friend." << std::endl;
            return 0;
        }
    }

    String field1;
    String field2;
    String field3;
    String field4;

    std::ifstream fin("users.db");
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            if (field1 == user)
            {
                fin.close();
                return 1;
            }
        }
        if (fin.eof())
        {
            fin.close();
            std::cout << "User not found." << std::endl;
            return 0;
        }
    }
    fin.close();

    return 0;
}
bool User::isFriend(String name)
{
    for (int i = 0; i < this->numOfFriends; i++)
    {
        if (friendsList[i] == name)
        {
            return 1;
        }
    }
    return 0;
}

void User::updateDB()
{
    String field1;
    String field2;
    String field3;
    String field4;

    std::ifstream fin("users.db");
    std::ofstream fout("update.db", std::ios::app);
    if (fin.is_open())
    {
        while (fin >> field1 >> field2 >> field3 >> field4)
        {
            if (field1 == this->username)
            {
                fout << *this << std::endl;
                continue;
            }
            fout << field1 << " " << field2 << " " << field3 << " " << field4 << std::endl;
        }
    }
    if (fin.eof())
    {
        remove("users.db");
        rename("update.db", "users.db");
        fin.close();
        fout.close();
    }
}

void User::printFriends()
{
    std::cout << "Your Friends:" << std::endl;
    for (size_t i = 0; i < this->numOfFriends; i++)
    {
        std::cout << this->friendsList[i] << std::endl;
    }
}