#include "user.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName);
void InsertUserInfo(User* u);
void SelectUserInfo();
bool LoginAuth(string username, string password);