#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "EncryptString.h"
#include "Decryptor.h"

static std::string UserID = "TestUser";
static int UserPassword = 12345678;
static int clearanceLevel = 3;
static std::string defaultUniversalPassword = "password";
char c;
std::string encrypted = "";

int main() {
	//generate a key between 1 to 10 for the encryption
	srand(time(0));
	static int key = (rand() % 10) + 1;
	std::cout << key;
	//login 
	std::cout << "Input your UserID:" << std::endl;
	std::string UserInputID;
	std::cin >> UserInputID;
	if (UserInputID == UserID) {
		std::cout << "Input your password:" << std::endl;
		int UserInputPassword;
		std::cin >> UserInputPassword;
		if (UserInputPassword == UserPassword) {
			std::cout << "Login successful." << std::endl;
			std::cout << "Your clearance Level is 3." << std::endl;
		}
		else {
			std::cout << "Incorrect password." << std::endl;
			return 0;
		}
	}
	else {
		std::cout << "User does not exist." << std::endl;
		return 0;
	}
	//end login
	std::vector<EncryptString*> encryptText;
	std::ifstream myfile;
	std::ofstream encryptedFile;
	std::string filename;
	std::cout << "which file to open? (enter full directory)" << std::endl;
	std::cin >> filename;
	myfile.open(filename);
	std::string line;
	int currentClearance;
	EncryptString* newLine;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line == "#end") {
				myfile.close(); 
				break;
			}
			std::istringstream my_stream(line);
			my_stream >> currentClearance >> line;
			//encrypt the current line
			encrypted = "";
			std::istringstream encrypt_stream(line);
			while (encrypt_stream >> std::noskipws >> c) {
				int temp = (c + key);
				encrypted += (char)temp;
			}
			newLine = new EncryptString(line, currentClearance, encrypted);
			encryptText.push_back(newLine);
		}
	}

	for (auto i : encryptText) {
		if (i->getClerancelevel() <= clearanceLevel) {
			i->print();
		}
		else {
			i->printEncrypted();
			std::cout << "****";
			std::cout << "Clearance level needed: " << i->getClerancelevel();
			std::cout << "****";
			std::cout << "##your current Clearance level is ";
			std::cout << clearanceLevel;
			std::cout << "##" << std::endl;
		}
	}
	char choice;
	std::cout << "Test decrypt? (y/n): ";
	std::cin >> choice;
	std::cin.ignore();

	switch (choice) {
	case 'y': {
		//only perform decryption for lines with too high clearance level
		std::cout << "Input password to decrypt:" << std::endl;
		std::string UniversalPassword;
		std::cin >> UniversalPassword;
		if (UniversalPassword == defaultUniversalPassword) {
			/*for (auto i : encryptText) {
				if (i->getClerancelevel() <= clearanceLevel) {
					i->print();
				}
				else {
					std::string encryptedText = i->getEncrypted();
					for (size_t i = 0; i < std::strlen(encryptedText.c_str()); i++) {
						int temp = encryptedText[i] - key;
						std::cout << (char)temp;
					}
					std::cout << std::endl;
				}
			}*/
			Decryptor decryptor = Decryptor(encryptText, key, clearanceLevel);
			std::string decryptedText = decryptor.decrypt();
			std::cout << decryptedText << std::endl;
		}
		else {
			std::cout << "Incorrect password, you do not have the clearance.";
		}
		break;
	}
	default:
		break;
	}
	while (1) {
	};
}