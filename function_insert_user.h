#include "user.h"
#include <iostream>
#include <string>
#include "sqlite3.h"
#include "Patient.h"
using namespace std;

class Patient;

static int callback(void* data, int argc, char** argv, char** azColName);
void initializedDatabase(sqlite3* db);
void SelectInfo();
void InsertUserInfo(User* u);
void InsertPatientInfo(Patient* p, string username);
bool LoginAuth(string username, string password);
void getPatientInfo(string username);

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName);
void InsertUserInfo(User* u);
void SelectUserInfo();
bool LoginAuth(string username, string password);
