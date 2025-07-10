// Gerard Kramer
// COP4530
// Assignment 5 - proj5.cpp

#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu() {
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

int main() {
    size_t capacity;
    cout << "Enter preferred hash table capacity (integer): ";
    cin >> capacity;
    cout << capacity << endl;

    PassServer server(capacity);
    char choice;

    do {
        Menu();
        cin >> choice;
        choice = tolower(choice); // convert choice to lowercase for consistency in case enters capital
        cout << "choice: " << choice << endl;

        switch (choice) {
            case 'l': {
                string filename;
                cout << "Enter filename to load: " << endl;
                cin >> filename;
                if (server.load(filename.c_str())) {
                    cout << "Users loaded successfully." << endl;
                } else {
                    cout << "Failed to load users from file." << endl;
                }
                break;
            }
            case 'a': {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: " << endl;
                cin >> password;
                if (server.addUser({username, password})) {
                    cout << "User " << username << " added." << endl;
                } else {
                    cout << "*****Error: Could not add user" << endl;
                }
                break;
            }
            case 'r': {
                string username;
                cout << "Enter username: ";
                cin >> username;
                if (server.removeUser(username)) {
                    cout << "User " << username << " deleted." << endl;
                } else {
                    cout << "\n*****Error: User not found.  Could not delete user" << endl;
                }
                break;
            }
            case 'c': {
                string username, oldPassword, newPassword;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: " << endl;
                cin >> oldPassword;
                cout << "Enter new password: " << endl;
                cin >> newPassword;
                if (server.changePassword({username, oldPassword}, newPassword)) {
                    cout << "Password changed for user " << username << endl;
                } else {
                    cout << "*****Error: Could not change user password" << endl;
                }
                break;
            }
            case 'f': {
                string username;
                cout << "Enter username: " << endl;
                cin >> username;
                if (server.find(username)) {
                    cout << "User \'" << username << "\' found." << endl;
                } else {
                    cout << "*****Error: User \'" << username << "\' not found." << endl;
                }
                break;
            }
            case 'd': {
                server.dump();
                break;
            }
            case 's': {
                cout << "Size of hashtable: " << server.size() << endl;
                break;
            }
            case 'w': {
                string filename;
                cout << "Enter password file name to write to:" << endl;
                cin >> filename;
                if (server.write_to_file(filename.c_str())) {
                    cout << "Written successfully to " << filename << endl;
                } else {
                    cout << "*****Error: Failed to write to file" << endl;
                }
                break;
            }
            case 'x':
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'x');

    return 0;
}
