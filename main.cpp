#include <iostream>
#include "sqlite3.h"
#include "Login.h"
#include "Signin.h"
using namespace std;

int main() {
    sqlite3 *db;
    int exitCode;

    exitCode = sqlite3_open("medical_appointment_system.db", &db);

    if (exitCode) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db);
        return exitCode;
    }
    initializedDatabase(db);
     while(true) {
        cout << "-----Welcome to New Era medical appointment schedule system------\n";
        cout << "Please enter your choice: 1. Login 2. Sign in 3. forget password 4. Exit\n";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch(choice) {
            case 1: logIn();
            break;
            case 2: signIn();
            break;
            case 3: cout << "forget password\n";
            break;
            case 4: cout << "Exit\n";
            return 0;
            default: cout << "Invalid choice\n";
        }
    }
}