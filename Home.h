#include "function_insert_user.h"
using namespace std;

void publicSignin();
bool checkUserName(string username);
bool checkIc(string ic);
bool checkPhoneNumber(string phonenumber);
void signIn();
void logIn();
void patientPlatForm();
void information();
void checkMedicalRecord();
void bookingAppointment();
void appointmentStatus();
void insertPatientProfileInfo();
string getValidatedStringInput(const string &errorMessage);
int getValidatedNumericInput(const string &errorMessage);
void selectAllergy(int patientid);
bool allergyContains(int choice, int PatientID);
void allergyPlatForm();
void checkAllergyInfo(int PatientID);
void addAllergy();
void insertEmergencyContact();
void insurancePlatForm();
void checkInsuranceInfo(int PatientID);
void insertInsurance();
bool insuranceExists(int choice);
bool insuranceRepeat(int choice, int PatientID);
void addressPlatForm();
void insertAddress();
bool isValidTime(const string &time);
bool isValidDate(const string &date);
void paymentFunction();
void paymentProcess(int id);
double insuranceProcess(int PatientID, int InsuranceID, sqlite3 *db, double price);
string paymentMethod();
void giveFeedback();
bool serviceExists(int ServiceID);
void showDoctorDashboard();
void displayDoctorInfo();
void medicalRecordsPlatForm();
void insertDoctorProfileInfo();
void addMedicalRecords();

void signIn()
{
    while (true)
    {
        cout << "---------------------Register Platform-----------------------------\n";
        cout << "Please select account type: 1. Admin 2. Doctor 3. Patient 4. Exit\n";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            publicSignin();
            break;
        case 2:
            publicSignin();
            break;
        case 3:
            publicSignin();
            break;
        case 4:
            cout << "Exit\n";
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}
void publicSignin()
{
    UserNode *user;
    string input;
    bool flag;
    while (true)
    {
        cout << "Please enter username:\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        user->username = input;
        if (!checkUserName(user->username) || UserList.isDuplicate(user->username))
        {
            cout << "Username format wrong or duplicate username, please try again\n";
            continue;
        }
        else
        {
            cout << "Username correct.\n";
            break;
        }
    }
    while (true)
    {
        string confirmpassword;
        cout << "Please enter your password:\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        user->password = input;
        cout << "Confirm password\n";
        getline(cin, confirmpassword);
        if (user->password == confirmpassword)
        {
            cout << "valid password\n";
            break;
        }
        else
        {
            cout << "Password different, please try again.\n";
        }
    }
    while (true)
    {
        cout << "Please enter your IC:\n";
        getline(cin, input);
        user->ic = input;
        flag = checkIc(user->ic);
        if (flag)
        {
            cout << "Valid IC\n";
            break;
        }
        else
        {
            cout << "Invalid IC, please try again.\n";
        }
    }
    while (true)
    {
        cout << "Please enter your phone number:\n";
        getline(cin, input);
        user->phonenumber = input;
        flag = checkPhoneNumber(user->phonenumber);
        if (flag)
        {
            cout << "Valid phone number.\n";
            break;
        }
        else
        {
            cout << "Invalid phone number, please try again.\n";
        }
    }
    InsertUserInfo(user);
}
bool checkUserName(string username)
{
    int len = username.length();
    if (len < 3 || len > 15)
    {
        cout << "Username too short or too long, please try again.\n";
        return false;
    }
    for (int i = 0; i < username.length(); i++)
    {
        char c = username.at(i);
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
        {
            cout << "Invalid character, please try again.\n";
            return false;
        }
    }
    int count = 0;
    for (int i = 0; i < username.length(); i++)
    {
        char c = username.at(i);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            count++;
            break;
        }
    }
    return count > 0;
}
bool checkIc(string ic)
{
    int len = ic.length();
    if (len != 12)
    {
        cout << "Invalid IC number(Must be 12-digit), please try again\n";
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        char c = ic.at(i);
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }
    return true;
}
bool checkPhoneNumber(string phonenumber)
{
    int len = phonenumber.length();
    if (len < 10)
    {
        return false;
    }
    for (int i = 0; i < len; i++)
    {
        char c = phonenumber.at(i);
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }
    return true;
}
void logIn()
{
    string username;
    string password;
    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "-----------------------Login Platform-------------------------\n";
        cout << "Please select acc type: 1. admin 2. doctor 3. patient 4. exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            flag = false;
            break;
        case 2:
            flag = false;
            break;
        case 3:
            flag = false;
            break;
        case 4:
            return;
        default:
            cout << "Invalid choose.\n";
        }
    }
    cout << "please enter username:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    username = getValidatedStringInput("Invalid input, please try again: ");
    cout << "Please enter password\n";
    password = getValidatedStringInput("Invalid input, please try again: ");
    if (UserList.loginAuth(username, password) && choice == 3)
    {
        cout << "Patient login success!\n";
        patientPlatForm();
    }
    else if (UserList.loginAuth(username, password) && choice == 2)
    {
        cout << "Doctor login success!\n";
        showDoctorDashboard();
    }
    else if (UserList.loginAuth(username, password) && choice == 1)
    {
        cout << "Admin login success!\n";
    }
    else
    {
        cout << "username or password incorrect\n";
    }
}
// Patient Platform
void patientPlatForm()
{
    int choice;
    while (true)
    {
        cout << "-----Welcome to patient service platform!-----\n"
             << "---------Please select your service.----------\n";
        cout << "1. Me \n2. Medical Records \n3. Booking appointment \n4. appointment status \n5. Exit";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            information();
            break;
        case 2:
            checkMedicalRecord();
            break;
        case 3:
            bookingAppointment();
            break;
        case 4:
            appointmentStatus();
            break;
        }
        if (choice == 5)
            break;
    }
}
// Patient profile page, and the function
void information()
{
    int choice;
    while (true)
    {
        cout << "-----------------Your profile page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Personal info\n2. Allergies\n3. Emergency Contact\n4. Insurance\n5. Address\n6. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            insertPatientProfileInfo();
            break;
        case 2:
            allergyPlatForm();
            break;
        case 3:
            insertEmergencyContact();
            break;
        case 4:
            insurancePlatForm();
            break;
        case 5:
            addressPlatForm();
            break;
        case 6:
            return;
        }
    }
}
// Insert Personal details
void insertPatientProfileInfo()
{
    PatientNode *patient;
    int count;

    while (true)
    {
        cout << "First time login(0 for first time)? (0/1):\n";
        cin >> count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (0 or 1).\n";
            continue;
        }

        if (count == 1)
        {
            break;
        }
        else if (count == 0)
        {
        cout << "Fill in your basic information.\n";

        cout << "Name:\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        patient->name = getValidatedStringInput("Name cannot be empty. Please re-enter:");

        cout << "Gender:\n";
        patient->gender = getValidatedStringInput("Name cannot be empty. Please re-enter:");
        while (true)
        {
            cout << "Age:\n";
            int age = getValidatedNumericInput("Invalid input. Please enter a valid age (1-150):");
            if (age > 0 && age < 150)
            {
                patient->age = age;
                break;
            }
            cout << "Invalid Age, please try again!\n";
        }
        cout << "Enter the username to associate with the patient: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string username = getValidatedStringInput("Username cannot be empty. Please re-enter:");
        InsertPatientInfo(patient, username);
        break;
        }
        else
        {
            cout << "Invalid input, Please try again!\n";
            return;
        }
    }
    while (true)
    {
        cout << "Please enter your Patient ID to get your information (0 for exit): ";
        int id = getValidatedNumericInput("Invalid input. Please enter a valid numeric Patient ID:");
        if (id == 0)
        {
            cout << "Exiting...\n";
            return;
        }
        PatientList.findPatient(id);
        break;
    }
}
// Check the string input is null or not
string getValidatedStringInput(const string &errorMessage)
{
    string input;
    while (true)
    {
        getline(cin, input);
        if (!input.empty())
        {
            return input;
        }
        cerr << errorMessage << endl;
    }
}
// Check number input valid or not
int getValidatedNumericInput(const string &errorMessage)
{
    int input;
    while (true)
    {
        cin >> input;
        if (!cin.fail())
        {
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << errorMessage << endl;
    }
}
// Allergy platform, check and add
void allergyPlatForm()
{
    int PatientID;
    int choice;
    while (true)
    {
        cout << "----------Here is allergy PlatForm!----------\n"
             << "---------Please select your service.----------\n";
        cout << "1. View Allergy \n2. Add allergy \n3. allergy details\n4. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            cout << "Please enter your Patient ID: ";
            PatientID = getValidatedNumericInput("Invalid input, Please try again!\n");
            checkAllergyInfo(PatientID);
            break;
        case 2:
            addAllergy();
            break;
        case 3:
            AllergyList.displayAllergy();
            break;
        case 4:
            return;
        }
    }
}
void checkAllergyInfo(int PatientID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL query to fetch patient's allergies
    const char *sql = R"(
        SELECT a.Allergy_id, a.Allergy_Name, a.Severity
        FROM allergies a
        INNER JOIN Allergies_Patient ap ON a.Allergy_id = ap.Allergyid
        INNER JOIN Patient p ON ap.Patientid = p.id
        WHERE p.id = ?;
    )";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the PatientID parameter
    sqlite3_bind_int(stmt, 1, PatientID);

    // Execute the query and display the results
    cout << "Allergy information for PatientID: " << PatientID << "\n";
    cout << "-------------------------------------\n";

    bool hasAllergies = false;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int AllergyID = sqlite3_column_int(stmt, 0);
        const unsigned char *AllergyName = sqlite3_column_text(stmt, 1);
        const unsigned char *Severity = sqlite3_column_text(stmt, 2);

        cout << "AllergyID: " << AllergyID << "\n";
        cout << "AllergyName: " << AllergyName << "\n";
        cout << "Severity: " << Severity << "\n";
        cout << "-------------------------------------\n";

        hasAllergies = true;
    }

    if (!hasAllergies)
    {
        cout << "No allergies found for this patient.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void addAllergy()
{
    int patientid;
    while (true)
    {
        cout << "Please enter your patient ID: ";
        patientid = getValidatedNumericInput("Invalid Input, please try again!\n");
        if (PatientList.findPatient(patientid))
        {
            break;
        }
        else
        {
            return;
        }
    }
    AllergyList.displayAllergy();
    selectAllergy(patientid);
    return;
}
void selectAllergy(int patientid)
{
    int allergyid;
    while (true)
    {
        cout << "Enter the ID of the allergy you want to select: ";
        allergyid = getValidatedNumericInput("Invalid input, please try again!\n");
        if (AllergyList.findAllergy(allergyid) && !(allergyContains(allergyid, patientid)))
        {
            InsertAllergyPatient(patientid, allergyid);
            break;
        }
        else
        {
            cout << "Invalid ID or duplicate. Please try again.\n"
                 << endl;
            continue;
        }
    }
    return;
}
bool allergyContains(int allergyid, int PatientID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    bool flag = false;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Now, check if the patient already has the insurance ID
    const char *sql = "SELECT COUNT(*) FROM Allergies_Patient WHERE Allergyid = ? AND Patientid = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, allergyid);
        sqlite3_bind_int(stmt, 2, PatientID);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0)
            {
                flag = true; // InsuranceID already exists for this patient
            }
        }
    }
    else
    {
        cerr << "Error preparing statement for Allergies_patient table: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return flag;
}
// Insert emergency contact function
void insertEmergencyContact()
{
    EmergencyContactNode *ec;
    int choice;
    while (true)
    {
        cout << "First Time insert emergency contact info?(0/1)(0 for first time): ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice == 1)
        {
            break;
        }
        else if (choice == 0)
        {
            cout << "Please enter your Patient ID: ";
            ec->patientid = getValidatedNumericInput("Invalid input, Please enter a valid ID: ");
            if (!PatientList.findPatient(ec->patientid))
            {
                return;
            }
            cout << "Please enter Contact name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ec->contactName = getValidatedStringInput("Invalid input, please try again!\n");
            cout << "Please enter phone number: ";
            ec->phoneNumber = getValidatedStringInput("Invalid input, please try again!\n");
            cout << "Please enter Relationship: ";
            ec->relationShip = getValidatedStringInput("Invalid input, please try again!\n");
            InsertEmergencyInfo(ec);
            break;
        }
        else
        {
            cout << "Invalid input, please try again!\n";
            continue;
        }
    }
    while (true)
    {
        int id;
        cout << "Please enter contact ID to get emergency contact Info (0 for exit): ";
        id = getValidatedNumericInput("Invalid input. Please enter a valid numeric Patient ID:");
        if (id == 0)
        {
            cout << "Exiting...\n";
            return;
        }
        EmergencyContactList.findEmergencyContact(id);
        return;
    }
}
// Insurance platform
void insurancePlatForm()
{
    int choice;
    int PatientID;
    while (true)
    {
        cout << "-----------------Insurance page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Your insurance\n2. add insurance\n3. insurance details\n4. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            cout << "Please enter your Patient ID: ";
            PatientID = getValidatedNumericInput("Please enter valid ID: ");
            checkInsuranceInfo(PatientID);
            break;
        case 2:
            insertInsurance();
            break;
        case 3:
            InsuranceList.displayProviders();
            break;
        case 4:
            return;
        }
    }
}
void checkInsuranceInfo(int PatientID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // SQL query to fetch patient's insurance
    const char *sql = R"(
        SELECT i.InsuranceID, i.Provider_Name, i.Coverage_Percentage
        FROM Insurance i
        INNER JOIN Insurance_Patient ip ON i.InsuranceID = ip.InsuranceID
        INNER JOIN Patient p ON ip.PatientID = p.id
        WHERE p.id = ?;
    )";

    bool hasInsurance;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, PatientID);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int InsuranceID = sqlite3_column_int(stmt, 0);
        const unsigned char *ProviderName = sqlite3_column_text(stmt, 1);
        double Coverage = sqlite3_column_double(stmt, 2);
        cout << "-------------------------------------\n";
        cout << "InsuranceID: " << InsuranceID << "\n";
        cout << "ProviderName: " << ProviderName << "\n";
        cout << "Coverage: " << Coverage << "%\n";
        cout << "-------------------------------------\n";

        hasInsurance = true;
    }

    if (!hasInsurance)
    {
        cout << "No insurance found for this patient.\n";
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void insertInsurance()
{
    int PatientID;
    int choice;
    while (true)
    {
        cout << "Please enter your patient ID: ";
        PatientID = getValidatedNumericInput("Invalid input, Please try again: ");
        if (PatientList.findPatient(PatientID))
        {
            InsuranceList.displayProviders();
            cout << "Please select your insurance provider (ID): ";
            choice = getValidatedNumericInput("Invalid input, please enter a valid Input: ");
            bool contains = insuranceExists(choice);
            if (contains)
            {
                contains = insuranceRepeat(choice, PatientID);
                if (!contains)
                {
                    InsertPatientInsurance(PatientID, choice);
                    return;
                }
                else
                {
                    cout << "Record already exists, please try again.\n";
                    return;
                }
            }
            else
            {
                cout << "Insurance not found, please try again!\n";
                return;
            }
        }
        else
        {
            cout << "Patient Not found, please try again!\n";
            return;
        }
    }
}
bool insuranceExists(int choice)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // First, check if the insurance ID exists in the Insurance table
    string sql = "SELECT COUNT(*) FROM Insurance WHERE InsuranceID = ?;";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, choice);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count == 0)
            {
                cerr << "The selected InsuranceID does not exist in the Insurance table." << endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return false; // InsuranceID does not exist
            }
        }
    }
    else
    {
        cerr << "Error preparing statement for Insurance table: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}
bool insuranceRepeat(int choice, int PatientID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Now, check if the patient already has the insurance ID
    string sql = "SELECT COUNT(*) FROM Insurance_Patient WHERE PatientID = ? AND InsuranceID = ?;";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, PatientID);
        sqlite3_bind_int(stmt, 2, choice);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0)
            {
                return true; // InsuranceID already exists for this patient
            }
        }
    }
    else
    {
        cerr << "Error preparing statement for Insurance_Patient table: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return false;
}
// Insert patient address function
void addressPlatForm()
{
    int choice;
    int PatientID;
    while (true)
    {
        cout << "-------------------Address page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Your Address\n2. add address\n3. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            cout << "Please enter your Patient ID: ";
            PatientID = getValidatedNumericInput("Please enter valid ID: ");
            AddressList.findAddress(PatientID);
            break;
        case 2:
            insertAddress();
            break;
        case 3:
            return;
        }
    }
}
void insertAddress()
{
    int PatientID;
    string country, city, street, postcode;
    cout << "Please enter your patient ID: ";
    PatientID = getValidatedNumericInput("Please enter valid ID: ");
    if (PatientList.findPatient(PatientID))
    {
        cout << "Please enter Country: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        country = getValidatedStringInput("Please enter valid input: ");
        cout << "Please enter city: ";
        city = getValidatedStringInput("Please enter valid input: ");
        cout << "Please enter street: ";
        street = getValidatedStringInput("Please enter valid input: ");
        cout << "Please enter postal code: ";
        postcode = getValidatedStringInput("Please enter valid input: ");
        AddressNode *address = new AddressNode(PatientID, country, city, street, postcode);
        AddressList.addAddress(*address);
        InsertPatientAddress(address);
    }
}
// Checking medical records function
void checkMedicalRecord()
{
    int PatientID;
    vector<MedicalRecordsNode *> Records;
    while (true)
    {
        cout << "Please enter your Patient ID: ";
        PatientID = getValidatedNumericInput("Please enter valid ID: ");
        if (PatientList.findPatient(PatientID))
        {
            Records = recordList.findRecords(PatientID);
            if (!Records.empty())
            {
                cout << "Found Records for Patient ID " << PatientID << ":\n";
                for (const auto &record : Records)
                {
                    cout << "------------------------------------------\n";
                    cout << "Record ID: " << record->recordID << "\n"
                         << "Date: " << record->date << "\n"
                         << "Details: " << record->details << "\n"
                         << "Doctor ID: " << record->doctorID << "\n"
                         << "Patient ID: " << record->patientID << "\n";
                    cout << "------------------------------------------\n";
                    return;
                }
            }
            else
            {
                cout << "No records found for Patient ID " << PatientID << "\n";
            }
        }
        return;
    }
}
// Booking medical records function
void bookingAppointment()
{
    int choice, PatientID, DoctorID, ServiceID;
    string date, time;

    while (true)
    {
        cout << "Please enter your Patient ID: ";
        PatientID = getValidatedNumericInput("Please enter valid ID: ");
        ;

        if (!PatientList.findPatient(PatientID))
        {
            cout << "Invalid Patient ID. Please try again.\n";
            return; // No need for further actions if patient ID is invalid
        }

        cout << "Doctor sort by Age or general display?(0/1): ";
        choice = getValidatedNumericInput("Please enter valid choice: ");

        if (choice == 1)
        {
            DoctorList.displayDoctors();
        }
        else if (choice == 0)
        {
            // Display doctors sorted by age
            DoctorList.bubbleSorting();
            DoctorList.displayDoctors();
        }
        else
        {
            cout << "Invalid input. Please try again.\n";
            continue; // Skip the rest of the loop and ask for input again
        }

        cout << "Please select doctor ID you want to book (0 to return): ";
        DoctorID = getValidatedNumericInput("Please enter valid ID: ");
        if (!DoctorList.findDoctor(DoctorID))
        {
            return;
        }
        else if (DoctorID == 0)
        {
            return;
        }

        ServiceList.displayService();

        cout << "Please select service you want (0 to return): ";
        ServiceID = getValidatedNumericInput("Please enter valid ID: ");
        if (!serviceExists(ServiceID))
        {
            return;
        }
        if (ServiceID == 0)
        {
            return;
        }
        // Get appointment date and time
        cout << "Enter appointment date (YYYY-MM-DD): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        date = getValidatedStringInput("Please enter valid date: ");
        if (!isValidDate(date))
        {
            cout << "Date format wrong!\n";
            return;
        }
        do
        {
            cout << "Enter appointment time (HH:MM AM/PM): ";
            time = getValidatedStringInput("Please enter valid time: ");
            if (isValidTime(time))
            {
                // Add appointment info to the appointment list
                AppointmentNode *app = new AppointmentNode(date, time, "Pending", PatientID, DoctorID, ServiceID);
                AppointmentList.addAppointment(*app);
                InsertAppointmentInfo(app);
                cout << "Appointment booked successfully.\n";
                break; // Exit loop after successful booking
            }
            cout << "Invalid time format. Try again.\n";
        } while (true);

        return; // End function after booking appointment
    }
}
bool serviceExists(int ServiceID)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int exit = sqlite3_open("medical_appointment_system.db", &db);

    if (exit != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // First, check if the insurance ID exists in the Insurance table
    string sql = "SELECT COUNT(*) FROM Health_Service WHERE ServiceID = ?;";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, ServiceID);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            if (count == 0)
            {
                cerr << "The selected ServiceID does not exist in the Service table." << endl;
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return false; // InsuranceID does not exist
            }
        }
    }
    else
    {
        cerr << "Error preparing statement for Insurance table: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}
bool isValidDate(const string &date)
{
    // Regular expression to match the format YYYY-MM-DD
    regex dateRegex("^(\\d{4})-(\\d{2})-(\\d{2})$");
    smatch match;

    if (!std::regex_match(date, match, dateRegex))
    {
        return false; // Date doesn't match the required format
    }

    // Extract year, month, and day from the matched groups
    int year = stoi(match[1].str());
    int month = stoi(match[2].str());
    int day = stoi(match[3].str());

    // Check if the month is valid
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Days in each month (non-leap year)
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap year in February
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        daysInMonth[1] = 29;
    }

    // Check if the day is valid for the given month
    if (day < 1 || day > daysInMonth[month - 1])
    {
        return false;
    }

    return true; // The date is valid
}
bool isValidTime(const string &time)
{
    if (time.length() < 7 || time.length() > 8)
        return false;
    string hourStr = time.substr(0, 2);
    string minuteStr = time.substr(3, 2);
    string period = time.substr(6, 2);
    if (time[2] != ':' || (period != "AM" && period != "PM"))
        return false;
    int hour = stoi(hourStr), minute = stoi(minuteStr);
    return (hour >= 1 && hour <= 12) && (minute >= 0 && minute < 60);
}
// Checking appointment status, cancel, making payment and give feedback
void appointmentStatus()
{
    int choice;
    while (true)
    {
        cout << "---------Appointment Platform here!-----------\n"
             << "---------Please select your service.----------\n";
        cout << "1. My appointment \n2. Cancel appointment \n3. Payment \n4. Feedback\n5. Exit";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            int id;
            cout << "Please enter Patient ID: ";
            cin >> id;
            AppointmentList.findAppointment(id);
            break;
        case 2:
            int PatientID;
            int choice;
            cout << "Please enter your patient ID: ";
            cin >> PatientID;
            AppointmentList.findAppointment(PatientID);
            cout << "Please enter the appointment ID you want to delete: ";
            cin >> choice;
            deleteAppointment(choice);
            break;
        case 3:
            paymentFunction();
            break;
        case 4:
            break;
        case 5:
            return;
        }
        if (choice == 5)
            break;
    }
}
void paymentFunction()
{
    int PatientID;
    int AppointmentID;
    cout << "Please enter your patient ID to get your appointment list: ";
    cin >> PatientID;
    AppointmentList.findAppointment(PatientID);
    cout << "Please enter an appointment you want to pay: ";
    cin >> AppointmentID;
    paymentProcess(AppointmentID);
}
void paymentProcess(int ID)
{
    sqlite3 *db = nullptr;
    sqlite3_stmt *stmt = nullptr;
    string date, times;
    char choice;

    if (sqlite3_open("medical_appointment_system.db", &db) != SQLITE_OK)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return;
    }

    const char *query = R"(
        SELECT A.ServiceID, H.Price , A.PatientID
        FROM Appointment A 
        JOIN Health_Service H ON A.ServiceID = H.ServiceID 
        WHERE A.AppointmentID = ?;
    )";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_bind_int(stmt, 1, ID);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int serviceID = sqlite3_column_int(stmt, 0);
        double price = sqlite3_column_double(stmt, 1);
        int patientID = sqlite3_column_int(stmt, 2);

        cout << "Appointment ID: " << ID << "\n";
        cout << "Service ID: " << serviceID << "\n";
        cout << fixed << setprecision(2) << "Price: RM" << price << "\n";

        cout << "Do you have insurance?(Y/N): ";
        cin >> choice;

        if (toupper(choice) == 'Y')
        {
            int insuranceID;
            cout << "Enter your insurance ID: ";
            cin >> insuranceID;
            price = insuranceProcess(patientID, insuranceID, db, price);
        }
        else if (toupper(choice) != 'N')
        {
            cout << "Invalid choice. Please try again.\n";
            sqlite3_close(db);
            sqlite3_finalize(stmt);
            return;
        }

        string method = paymentMethod();
        time_t now = time(0);
        struct tm tstruct;
        localtime_s(&tstruct, &now);

        char dateBuf[11];
        char timeBuf[9];

        strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", &tstruct);
        strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &tstruct);

        date = dateBuf;
        times = timeBuf;

        if (updateAppointmentStatus(db, ID))
        {
            sqlite3_close(db);
            sqlite3_finalize(stmt);
            PaymentNode *payment = new PaymentNode(price, date, times, method, ID);
            InsertPaymentInfo(payment);
        }
    }
    else
    {
        cerr << "No matching appointment found.\n";
    }
}
double insuranceProcess(int PatientID, int InsuranceID, sqlite3 *db, double price)
{
    sqlite3_stmt *stmt;
    const char *sql = R"(
        SELECT Coverage_Percentage
        FROM Insurance_Patient IP
        JOIN Insurance I ON IP.InsuranceID = I.InsuranceID
        WHERE IP.PatientID = ? AND IP.InsuranceID = ?;
    )";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return price; // Return original price if there's an error
    }

    // Bind parameters
    sqlite3_bind_int(stmt, 1, PatientID);
    sqlite3_bind_int(stmt, 2, InsuranceID);

    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double coverage = sqlite3_column_double(stmt, 0);
        cout << "Insurance coverage: " << coverage << "%\n";
        price = price * ((100.0 - coverage) / 100);
        cout << "Price after insurance coverage: RM " << fixed << setprecision(2) << price << "\n";
    }
    else
    {
        cout << "Invalid Insurance ID or not associated with this patient. Full price applies.\n";
        cout << "You need to pay: RM " << fixed << setprecision(2) << price << "\n";
    }

    // Finalize and close resources
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return price;
}
// Select payment method
string paymentMethod()
{
    string m;
    while (true)
    {
        cout << "\nSelect your payment method:\n";
        cout << "1. Online Banking\n";
        cout << "2. E-Wallet\n";
        cout << "3. Credit/Debit Card\n";

        int method;
        cout << "Enter your choice: ";
        cin >> method;

        switch (method)
        {
        case 1:
            m = "Online Banking";
            cout << "Processing payment via Online Banking...\n";
            break;
        case 2:
            m = "E-Wallet";
            cout << "Processing payment via E-Wallet...\n";
            break;
        case 3:
            m = "Credit Card";
            cout << "Processing payment via Credit/Debit Card...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            continue;
        }
        cout << "Payment successful! Thank you.\n";
        break;
    }
    return m;
}
void giveFeedback()
{
    int PatientID;
    int AppointmentID;
    while (true)
    {
        cout << "Please enter your Patient ID: ";
        cin >> PatientID;
        if (PatientList.findPatient(PatientID))
        {
            AppointmentList.findAppointment(PatientID);
            cout << "Please select appointment ID that you want to evaluate: ";
            cin >> AppointmentID;
        }
    }
}
void showDoctorDashboard()
{
    int choice;
    while (true)
    {
        cout << "-----Welcome to Doctor service platform!-----\n"
             << "---------Please select your service.----------\n";
        cout << "1. Me \n2. Medical Records \n3. Check appointment status\n4. Medical Record\n5. Exit";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            displayDoctorInfo();
            break;
        case 2:
            medicalRecordsPlatForm();
            break;
        case 3:
            break;
        }
        if (choice == 5)
            break;
    }
}
void displayDoctorInfo()
{
    int choice;
    while (true)
    {
        cout << "-----------------Your profile page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Personal info\n2. Department Info\n3. Hospital Info\n4. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            insertDoctorProfileInfo();
            break;
        case 2:
            cout << "Department Info: \n";
            DepartmentList.printDepartment();
            break;
        case 3:
            selectHospitalInfo();
            break;
        case 4:
            return;
        }
    }
}
void insertDoctorProfileInfo()
{
    int count = 0;
    string username;
    int id;
    DoctorNode *d;
    while (count == 0)
    {
        cout << "First time login(0 for first time)?(0/1):\n";
        cin >> count;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (count == 1)
        {
            break;
        }
        string department;
        int intInput;
        cout << "Fill in your basic information.\n";
        cout << "Name: ";
        cin.ignore();
        d->name = getValidatedStringInput("Please enter valid input: ");
        cout << "Age: ";
        d->age = getValidatedNumericInput("Please enter valid input: ");
        cout << "Gender: ";
        cin.ignore();
        d->gender = getValidatedStringInput("Please enter valid input: ");
        cout << "Specialty: ";
        d->specialty = getValidatedStringInput("Please enter valid input: ");
        cout << "Enter the username to associate with the Doctor: ";
        getline(cin, username);
        if (username.empty())
        {
            cerr << "Username cannot be empty.\n";
            delete d;
            continue;
        }
        while (true)
        {
            DepartmentList.printDepartment();
            cout << "Enter the department to associate with the Doctor: ";
            getline(cin, department);

            if (DepartmentList.exists(department))
            {
                cout << "department valid.";
                break;
            }
            else
            {
                cout << "Invalid Department, try again!";
            }
        }
        InsertDoctorInfo(d, username, department);
        count = 1;
        delete d;
    }
    cout << "Please enter your ID to get your information: ";
    id = getValidatedNumericInput("Please enter valid ID: ");
    DoctorList.findDoctor(id);
    return;
}
void medicalRecordsPlatForm()
{
    vector<MedicalRecordsNode *> Records;
    int choice;
    while (true)
    {
        cout << "-----Medical Records here! Do anything you want!-----\n"
             << "---------Please select your choice.----------\n";
        cout << "1. Add medical records \n2. Check Medical Records \n3. Exit\n";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            addMedicalRecords();
            break;
        case 2:
            int id;
            cout << "Please enter patient ID: ";
            cin >> id;
            Records = recordList.findRecords(id);
            if (!Records.empty())
            {
                cout << "Found Records for Patient ID " << id << ":\n";
                for (const auto &record : Records)
                {
                    cout << "------------------------------------------\n";
                    cout << "Record ID: " << record->recordID << "\n"
                         << "Date: " << record->date << "\n"
                         << "Details: " << record->details << "\n"
                         << "Doctor ID: " << record->doctorID << "\n"
                         << "Patient ID: " << record->patientID << "\n";
                    cout << "------------------------------------------\n";
                }
            }
            else
            {
                cout << "No records found for Patient ID " << id << "\n";
            }
            break;
        case 3:
            return;
        }
    }
}
void addMedicalRecords()
{
    MedicalRecordsNode *record;
    int DoctorID;
    int PatientID;
    while (true)
    {
        cout << "Please enter doctor ID: ";
        DoctorID = getValidatedNumericInput("Please enter valid ID: ");
        if (DoctorList.findDoctor(DoctorID))
        {
            record->doctorID = DoctorID;
            PatientList.displayPatients();
            while (true)
            {
                cout << "Please select Patient (ID): ";
                PatientID = getValidatedNumericInput("Please enter valid ID: ");
                if (PatientList.findPatient(PatientID))
                {
                    record->patientID = PatientID;
                    cout << "Enter records: ";
                    cin.ignore();
                    record->details = getValidatedStringInput("Please enter valid input: ");
                    time_t now = time(0);
                    struct tm tstruct;
                    localtime_s(&tstruct, &now);
                    char buf[11];
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
                    record->date = buf;

                    recordList.addRecords(*record);
                    InsertMedicalRecords(record);
                    cout << "Records insert successfully!\n";
                }
                else
                {
                    cout << "Invalid patient ID, please try again\n";
                    return;
                }
            }
        }
        else
        {
            cout << "Invalid Doctor ID, Please try again.\n";
            return;
        }
    }
}