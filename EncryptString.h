#include <iostream>

#pragma once
class EncryptString
{
private:
	std::string content;
	int clearanceLevel;
	std::string encryptedText;

public:
	EncryptString(std::string, int, std::string);
	void print();
	void printEncrypted();
	std::string getEncrypted();
	int getClerancelevel();
};

