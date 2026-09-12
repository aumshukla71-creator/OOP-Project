#include "../include/SecureNote.h"

SecureNote::SecureNote(int id, const char* t, const char* content, const char* cat)
    : VaultItem(id, t) {
    std::strncpy(noteContent, content, sizeof(noteContent) - 1);
    noteContent[sizeof(noteContent) - 1] = '\0';

    std::strncpy(category, cat, sizeof(category) - 1);
    category[sizeof(category) - 1] = '\0';
}

void SecureNote::displayDetails() const {
    std::cout << "[Note]  ID: " << id 
              << " | Title: " << title 
              << " | Category: " << category 
              << " | Content: " << noteContent 
              << " | Entropy: " << calculateStrength() << "/100\n";
}

int SecureNote::calculateStrength() const {
    size_t len = std::strlen(noteContent);
    if (len > 100) return 100;
    return static_cast<int>(len);
}

void SecureNote::writeBinary(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(title, sizeof(title));
    out.write(reinterpret_cast<const char*>(&createdAt), sizeof(createdAt));
    out.write(noteContent, sizeof(noteContent));
    out.write(category, sizeof(category));
}

void SecureNote::readBinary(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(title, sizeof(title));
    in.read(reinterpret_cast<char*>(&createdAt), sizeof(createdAt));
    in.read(noteContent, sizeof(noteContent));
    in.read(category, sizeof(category));
}