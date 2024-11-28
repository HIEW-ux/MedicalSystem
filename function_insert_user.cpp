#include "function_insert_user.h"

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

void InsertUserInfo(User* u){
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("medical_appointment_system.db",&DB);
    string sql("INSERT INTO users(username,password,phonenumber,IC)VALUES('"+u->username1()+"','"+u->password1()+"','"+u->phonenumber1()+"','"+u->ic1()+"');");
    exit = sqlite3_exec(DB, sql.c_str() ,NULL ,0 ,&messageError);
    if(exit != SQLITE_OK){
        cerr << "Error Insert" << messageError;
        sqlite3_free(messageError);
    }else{
        cout << "Records insert successfully\n";
    }
    sqlite3_close(DB);
}
void SelectUserInfo(){
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("medical_appointment_system.dg",&DB);
    string query = "SELECT * FROM userTable;";
    sqlite3_close(DB);
}
bool LoginAuth(string username, string password){
    sqlite3* DB;
    int exit = sqlite3_open("medical_appointment_system.db",&DB);
    const char* sql = "SELECT 1 FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << std::endl;
        return false;
    }
     sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    bool isAuthenticated = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return isAuthenticated;
}