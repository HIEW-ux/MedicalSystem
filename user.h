#pragma once
#include <string>
#include <iostream>
using namespace std;
class User {
private:
    string username;
    string password;
    string phonenumber;
    string ic;
public:
    User(){
    }
    User(string username, string password, string phonenumber, string ic)
        : username(username), password(password), phonenumber(phonenumber), ic(ic){}

    string username1() {
        return username;
    }

    void set_username(string username) {
        this->username = username;
    }

    string password1() {
        return password;
    }

    void set_password(string password) {
        this->password = password;
    }

    string phonenumber1() {
        return phonenumber;
    }

    void set_phonenumber(string phonenumber) {
        this->phonenumber = phonenumber;
    }

    string ic1() {
        return ic;
    }

    void set_ic(string ic) {
        this->ic = ic;
    }
};
