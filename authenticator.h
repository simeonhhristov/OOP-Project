#pragma once
#include <fstream>
#include <iostream>
#include "user.h"

class Authenticator
{
private:
    void encrypt(String& input);
public:
    User *authenticate();

};