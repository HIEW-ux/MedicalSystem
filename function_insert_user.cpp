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
//Create all tables in database
void initializedDatabase(sqlite3* db){
    //User table
    string userTable("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT,username TEXT NOT NULL UNIQUE,password TEXT NOT NULL,phonenumber TEXT NOT NULL,IC TEXT NOT NULL UNIQUE)");
    char* messageError;
    if (sqlite3_exec(db, userTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    } else {
        cout << "Table initialize successfully.\n";
    }
    //Patient table
    string patientTable("CREATE TABLE IF NOT EXISTS Patient (id INTEGER PRIMARY KEY AUTOINCREMENT,P_Name TEXT NOT NULL UNIQUE,P_Age INT NOT NULL,P_Gender TEXT NOT NULL,User_id INTEGER,FOREIGN KEY (User_id) REFERENCES users (id))");
    if (sqlite3_exec(db, patientTable.c_str(), nullptr, nullptr, &messageError) != SQLITE_OK) {
        cerr << "Error creating table: " << messageError;
        sqlite3_free(messageError);
    } else {
        cout << "Table initialize successfully.\n";
    }
}

//Insert User info when register
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

//Insert Patient info, also add foreign key data into table
void InsertPatientInfo(Patient* p, string username){
     sqlite3* DB;
    int exit = sqlite3_open("medical_appointment_system.db", &DB);

    if (exit != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    const char* sql = R"(
        INSERT INTO Patient (P_Name, P_Age, P_Gender, User_id)
        VALUES (?, ?, ?, (SELECT id FROM users WHERE username = ?));
    )";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    sqlite3_bind_text(stmt, 1, p->getName().c_str(), -1, SQLITE_STATIC);  
    sqlite3_bind_int(stmt, 2, p->getAge());                               
    sqlite3_bind_text(stmt, 3, p->getGender().c_str(), -1, SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 4, username.c_str(), -1, SQLITE_STATIC);      

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        cerr << "Error inserting patient: " << sqlite3_errmsg(DB) << endl;
    } else {
        cout << "Patient inserted successfully.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

//Select all data in table (for all tables)
void SelectInfo(string table){
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open("medical_appointment_system.dg",&DB);
    string query = "SELECT * FROM "+table+";";
    sqlite3_close(DB);
}
//Authentication when login

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
//Display Patient infomation when user input username
void getPatientInfo(string username){
    sqlite3* DB;
    int exit = sqlite3_open("medical_appointment_system.db",&DB);
    const char* sql = R"(
        SELECT 
            Patient.id, Patient.P_Name, Patient.P_Age, Patient.P_Gender, Patient.User_id
        FROM 
            users 
        INNER JOIN 
            Patient 
        ON 
            users.id = Patient.User_id 
        WHERE 
            users.username = ?;
    )";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        int patientId = sqlite3_column_int(stmt, 0);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        string gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int User_id = sqlite3_column_int(stmt, 4);
        cout << "Patient ID: " << patientId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Gender: " << gender << "\n";
        cout << "User ID: " << User_id << "\n";
    } else if (result == SQLITE_DONE) {
        cout << "No patient information found for username: " << username << "\n";
    } else {
        cerr << "Query failed: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
}