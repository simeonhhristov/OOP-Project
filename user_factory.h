#pragma once
#include <fstream>
#include <iostream>
#include "user.h"
#include "string.h"

class UserFactory
{
private:
    int checkIfUsed(String, String);
    bool validEmail(String);
    bool validSymbols(String);
    void encrypt(String &);

public:
    User *createUser();
    
};