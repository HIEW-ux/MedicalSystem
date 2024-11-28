#include <iostream>
#include <string>
#include <limits>
#include "function_insert_user.h"
#include "user.h"
using namespace std;

void signIn();
void publicSignin();
bool checkUserName(string username);
bool contains(string username);
bool checkIc(string ic);
bool checkPhoneNumber(string phonenumber);
bool logInContains(User* userInfo);

 void signIn(){
        while(true){
            cout << "Please select account type: 1. Admin 2. Doctor 3. Patient 4. Exit\n";
            int choice;
            cin >> choice;
            if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a number.\n";
            continue; 
        }
            switch(choice){
                case 1: publicSignin();
                break;
                case 2: publicSignin();
                break;
                case 3: publicSignin();
                break;
                case 4: cout << "Exit\n";
                return;
                default: cout << "Invalid choice\n";
            }
        }
    }
    void publicSignin(){
        User* u = new User();
        string input;
        bool flag;
        while(true){
            cout << "Please enter username:\n";
            cin >> input;
            u->set_username(input);
            if(! checkUserName(u->username1()) || contains(u->username1())){
                cout << "Username format wrong or duplicate username, please try again\n";
                continue;
            }else{
                cout << "Username correct.\n";
                break;
            }
        }
        while(true){
            string confirmpassword;
            cout << "Please enter your password:\n";
            cin >> input;
            u->set_password(input);
            cout << "Confirm password\n";
            cin >> confirmpassword;
            if(u->password1() == confirmpassword){
                cout << "valid password\n";
                break;
            }else{
                cout << "Password different, please try again.\n";
            }
        }
        while(true){
            cout << "Please enter your IC:\n";
            cin >> input;
            u->set_ic(input);
            flag = checkIc(u->ic1());
            if(flag){
                cout << "Valid IC\n";
                break;
            }else{
                cout << "Invalid IC, please try again.\n";
            }
        }
        while(true){
            cout << "Please enter your phone number:\n";
            cin >> input;
            u->set_phonenumber(input);
            flag = checkPhoneNumber(u->phonenumber1());
            if(flag){
                cout << "Valid phone number.\n";
                break;
            }else{
                cout << "Invalid phone number, please try again.\n";
            }
        }
        InsertUserInfo(u);
    }
    bool checkUserName(string username){
        int len = username.length();
        if(len < 3 || len > 15){
            cout << "Username too short or too long, please try again.\n";
            return false;
        }
        for(int i = 0; i < username.length(); i++){
            char c = username.at(i);
            if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))){
                cout << "Invalid character, please try again.\n";
                return false;
            }
        }
        int count = 0;
        for(int i = 0; i < username.length(); i++){
            char c = username.at(i);
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                count++;
                break;
            }
        }
        return count > 0;
    }
    bool contains(string username){
         sqlite3* DB;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT 1 FROM users WHERE username = ?;";
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    if (exit != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(DB) << endl;
        return false;
    }

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return false;
    }

    // 将 username 绑定到 SQL 查询中
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    // 检查是否存在结果行
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    return exists;
    }
    bool checkIc(string ic){
        int len = ic.length();
        if(len != 12){
            cout << "Invalid IC number(Must be 12-digit), please try again\n";
            return false;
        }
        for(int i = 0; i < len; i++){
            char c = ic.at(i);
            if(!(c >= '0' && c <= '9')){
                return false;
            }
        }
        return true;
    }
    bool checkPhoneNumber(string phonenumber){
        int len = phonenumber.length();
        if(len < 10){
            return false;
        }
        for(int i = 0; i < len; i++){
            char c = phonenumber.at(i);
            if(!(c >= '0' && c <= '9')){
                return false;
            }
        }
        return true;
    }