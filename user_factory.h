#pragma once
#include <fstream>
#include <iostream>
#include "user.h"
#include "string.h"

class UserFactory
{
public:
    User *createUser();
    int checkIfUsed(String, String);
    bool validEmail(String);
    bool validSymbols(String);
};