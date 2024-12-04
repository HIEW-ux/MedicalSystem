#include <iostream>
#include <string>
#include <limits>
#include "function_insert_user.h"
#include "user.h"
#include "Patient.h"
#include "User.h"
using namespace std;

void logIn();

void logIn(){
        Patient* p = new Patient();
        string cpassword;
        string cusername;
        string username;
        string password;
        int choice;
        bool flag = true;
        while(flag){
        cout << "Please select acc type: 1. admin 2. doctor 3. patient 4. exit\n";
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue; 
        }
        switch(choice){
            case 1: flag = false;
                    break;
            case 2: flag = false;
                    break;
            case 3: flag = false;
                    break;
            case 4: return;
            default: cout << "Invalid choose.\n";
        }
    }
        cout << "please enter username:\n";
        cin >> username;
        cout << "Please enter password\n";
        cin >> password;
        if(!(LoginAuth(username, password))){
            cout << "Username or Password incorrect, please try again";
        }else if(choice == 3){
            cout << "Patient login success!\n";
            p->patientPlatForm();
        }else if(choice == 2){
            cout << "Doctor login success!\n";
        }else if(choice == 1){
            cout << "Admin login success!\n";
        }
}
