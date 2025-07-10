// Gerard Kramer
// COP4530
// Assignment 5 - passserver.cpp

#include "passserver.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <crypt.h>
#include <unistd.h>
#include <cstring>

using namespace std;
using namespace cop4530;

// constructor
PassServer::PassServer(size_t size) : table(size), numItems(0) {}

// destructor = default
PassServer::~PassServer() = default;

// check if user exists - calls HT function
bool PassServer::find(const string &user) const {
    return table.contains(user);
}

// encryption function
string PassServer::encrypt(const string &str) {
    // define the salt
    char salt[] = "$1$########";

    // hash using crypt()
    char *hashed_password = crypt(str.c_str(), salt);

    if (hashed_password == nullptr) {
        throw std::runtime_error("crypt() failed to hash the password");
    }

    // convert to std::string
    string encryptedPass = std::string(hashed_password);

    size_t pos = encryptedPass.find('$', 3);
    
    if (pos != string::npos) {
        encryptedPass = encryptedPass.substr(pos + 1);
    }

    return encryptedPass;

}

// load password file
bool PassServer::load(const char *filename) {
    return table.load(filename);
}

bool PassServer::addUser(pair<string, string> &kv) {
    // check if the username already exists
    if (find(kv.first)) {
        return false;
    }

    kv.second = encrypt(kv.second);

    table.insert(std::make_pair(kv.first, kv.second));
    ++numItems;
    return true;
}

bool PassServer::addUser(pair<string, string> &&kv) {
    // check if the username already exists
    if (find(kv.first)) {
        return false;
    }

    kv.second = encrypt(kv.second);

    table.insert(std::make_pair(std::move(kv.first), std::move(kv.second)));
    ++numItems;
    return true;
}

// remove a user by their username.
bool PassServer::removeUser(const string &k) {
    if (find(k)) {
        table.remove(k);
        --numItems;
        return true;
    }
    return false;
}

string PassServer::getPassword(const string& username) {
    auto result = table.find(username);  // find the entry in the table

    if (result != nullptr) {  // check if the result is not nullptr
        for (const auto& pair : *result) {
            if (pair.first == username) {  // match the username
                return pair.second;  // return the associated password (second)
            }
        }
    }
    
    return "";  // return empty string if not found
}

bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) {
    // find the user in the hash table.
    if (!find(p.first)) {
        return false;
    }

    // retrieve the current password for comparison
    string currentPassword = getPassword(p.first);

    // check if the current password matches.
    if (currentPassword != encrypt(p.second)) {
        return false;  // Passwords don't match
    }

    // ensure the new password is different.
    if (p.second == newpassword) {
        return false;  // the new password must differ from the current one.
    }

    // encrypt and update the password.
    table.remove(p.first);
    table.insert(std::make_pair(p.first, encrypt(newpassword)));
    return true;
}

void PassServer::dump() {
    table.dump();
}

size_t PassServer::size() const {
    return numItems;
}

bool PassServer::write_to_file(const char *filename) const {
    return table.write_to_file(filename);
}
