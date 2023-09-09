#include <iostream>
#include <vector>
#include "EncryptString.h"

#pragma once
class Decryptor
{
    private:
    std::vector<EncryptString*> encryptedText;
    int key;
    int clearanceLevel;

    public:
        Decryptor(std::vector<EncryptString*>, int, int);
        std::string decrypt();
};
