#include "Decryptor.h"

Decryptor::Decryptor(std::vector<EncryptString*> encryptedText, int key, int clearanceLevel) {
    this->encryptedText = encryptedText;
    this->key = key;
    this->clearanceLevel = clearanceLevel;
}

std::string Decryptor::decrypt() {
    std::string decryptedText;
    for (auto i : encryptedText) {
			if (i->getClerancelevel() <= clearanceLevel) {
				i->print();
			}
			else {
				std::string encryptedText = i->getEncrypted();
				for (size_t i = 0; i < std::strlen(encryptedText.c_str()); i++) {
					int temp = encryptedText[i] - key;
					decryptedText.push_back((char)temp);
				}
            }
    }
    return decryptedText;
}