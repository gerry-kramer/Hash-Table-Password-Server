// Gerard Kramer
// COP4530
// Assignment 5 - passserver.h

#ifndef PASSSERVER_H
#define PASSSERVER_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "hashtable.h"

using namespace cop4530;

// descriptions pulled from assignment descriptions

class PassServer {
    private:
        HashTable<std::string, std::string> table;
        size_t numItems;
        std::string encrypt(const std::string & str); //encrypt the parameter str and return the encrypted string.
    public:
        PassServer(size_t size = 101); /*constructor, create a hash table of the specified size. 
        You just need to pass this size parameter to the constructor of the HashTable. 
        Therefore, the real hash table size could be different from the parameter size 
        (because prime_below() will be called in the constructor of the HashTable).*/
        ~PassServer(); /*destructor. You need to decide what you should do based on your design 
        of PassServer (how you develop the adaptor class based on the adaptee HashTable). In essence, we do not want to have memory leak.*/
        bool load(const char *filename); /*load a password file into the HashTable object. 
        Each line contains a pair of username and encrypted password.*/
        bool addUser(std::pair<std::string, std::string> & kv); /*add a new username and password.  The password passed in is in 
        plaintext, it should be encrypted before insertion. The pair should not be added if the username already exists in the hash table.*/
        bool addUser(std::pair<std::string, std::string> && kv); //move version of addUser
        bool removeUser(const std::string & k); // delete an existing user with username k.
        bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); /*change an existing user's password. 
        Note that both passwords passed in are in plaintext. They should be encrypted before you interact with the hash table. 
        If the user is not in the hash table, return false. If p.second does not match the current password, return false. 
        Also return false if the new password and the old password are the same (i.e., we cannot update the password).*/
        bool find(const std::string & user) const; // check if a user exists (if user is in the hash table).
        void dump(); /*show the structure and contents of the HashTable object to the screen. Same format as 
        the dump() function in the HashTable class template.*/
        size_t size() const; // return the size of the HashTable (the number of username/password pairs in the table).
        bool write_to_file(const char *filename) const; /*save the username and password combination into a file. 
        Same format as the write_to_file() function in the HashTable class template.*/

        std::string getPassword(const std::string& username);
};


#endif 
