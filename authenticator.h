#pragma once
#include <fstream>
#include <iostream>
#include "user.h"

class Authenticator
{
public:
    User *authenticate();
};