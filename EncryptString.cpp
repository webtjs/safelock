#include "EncryptString.h"

EncryptString::EncryptString(std::string content, int clearanceLevel, std::string encryptedText) {
	this->clearanceLevel = clearanceLevel;
	this->content = content;
	this->encryptedText = encryptedText;
}

void EncryptString::print() {
	std::cout << content << std::endl;
}

void EncryptString::printEncrypted() {
	std::cout << encryptedText;
}

std::string EncryptString::getEncrypted() {
	return this->encryptedText;
}

int EncryptString::getClerancelevel() {
	return clearanceLevel;
}