#include "function_insert_user.h"
using namespace std;
void insertPatientProfileInfo();
void selectAllergy(int patientid);
void allergyPlatForm();
void insertEmergencyContact();
void insertDoctorProfileInfo();
void addMedicalRecords();
void publicSignin();
bool checkUserName(string username);
bool contains(string username);
bool checkIc(string ic);
bool checkPhoneNumber(string phonenumber);
void signIn();
void logIn();
void signIn()
{
    while (true)
    {
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
    User *u = new User();
    string input;
    bool flag;
    while (true)
    {
        cout << "Please enter username:\n";
        cin >> input;
        u->set_username(input);
        if (!checkUserName(u->username1()) || contains(u->username1()))
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
        cin >> input;
        u->set_password(input);
        cout << "Confirm password\n";
        cin >> confirmpassword;
        if (u->password1() == confirmpassword)
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
        cin >> input;
        u->set_ic(input);
        flag = checkIc(u->ic1());
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
        cin >> input;
        u->set_phonenumber(input);
        flag = checkPhoneNumber(u->phonenumber1());
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
    InsertUserInfo(u);
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
bool contains(string username)
{
    return userMap.find(username) != userMap.end();
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
    Patient *p = new Patient();
    string cpassword;
    string cusername;
    string username;
    string password;
    int choice;
    bool flag = true;
    while (flag)
    {
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
    User *user = new User();
    Doctor *d = new Doctor();
    cout << "please enter username:\n";
    cin >> username;
    cout << "Please enter password\n";
    cin >> password;
    if (userMap.find(username) != userMap.end())
    {
        user = userMap[username];
        if (user->password1() == password && choice == 3)
        {
            cout << "Patient login success!\n";
            p->patientPlatForm();
        }
        else if (user->password1() == password && choice == 2)
        {
            cout << "Doctor login success!\n";
            d->showDoctorDashboard();
        }
        else if (user->password1() == password && choice == 1)
        {
            cout << "Admin login success!\n";
        }
    }
    else
    {
        cout << "username or password incorrect\n";
    }
}

void Patient ::patientPlatForm()
{
    int choice;
    while (true)
    {
        cout << "-----Welcome to patient service platform!-----\n"
             << "---------Please select your service.----------\n";
        cout << "1. Me \n2. Booking appointment \n3. Check appointment status\n4. Medical Record\n5. Exit";
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
            break;
        case 3:
            break;
        }
    }
}
void Patient ::information()
{
    int choice;
    while (true)
    {
        cout << "-----------------Your profile page------------------\n"
             << "--------------Please select your service.-----------\n";
        cout << "1. Personal info\n2. Allergies\n3. Emergency Contact\n4. Exit\n";
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
        }
    }
}
void insertPatientProfileInfo()
{
    int count = 0;
    string username;
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
        Patient *p = new Patient();
        int NumberInput;
        string StringInput;
        cout << "Fill in your basic information.\n";
        cout << "Name:\n";
        cin >> StringInput;
        p->setName(StringInput);
        cout << "gender:\n";
        cin >> StringInput;
        p->setGender(StringInput);
        cout << "age:\n";
        cin >> NumberInput;
        p->setAge(NumberInput);
        cout << "Enter the username to associate with the patient: ";
        cin >> username;
        if (username.empty())
        {
            cerr << "Username cannot be empty.\n";
            return;
        }
        InsertPatientInfo(p, username);
        count = 1;
    }
    int id;
    cout << "Please enter your Patient ID to get your information: ";
    cin >> id;
    getPatientInfo(id);
}
void selectAllergy(int patientid)
{
    int allergyid;
    while (true)
    {
        cout << "Enter the ID of the allergy you want to select: ";
        cin >> allergyid;
        auto it = allergyMap.find(allergyid);
        if (it != allergyMap.end())
        {
            Allergy *selected = it->second;
            cout << "您选择了: " << selected->getName() << " (Severity: " << selected->getSeverity() << ")\n";
            InsertAllergyPatient(patientid, allergyid);
            break;
        }
        else
        {
            cout << "Invalid ID. Please try again.\n"
                 << endl;
            continue;
        }
    }
}
void allergyPlatForm()
{
    int patientid;
    while (true)
    {
        bool flag = false;
        cout << "Please enter your patient ID: ";
        cin >> patientid;
        for (const auto &entry : patientMap)
        {
            if (entry.first == patientid)
            {
                flag = true;
                break;
            }
            else
            {
                flag = false;
            }
        }
        if (flag)
        {
            cout << "Patient ID is valid. Proceeding to allergy selection." << endl;
            break;
        }
        else
        {
            cout << "Invalid Patient ID. Please try again." << endl;
            break;
        }
    }
    if (allergyMap.empty())
    {
        cout << "No allergies found in the database." << endl;
    }
    displayAllergies();
    selectAllergy(patientid);
    for (auto &[id, allergy] : allergyMap)
    {
        delete allergy;
    }
}
void insertEmergencyContact()
{
    int choice = 0;
    int patientid;
    while (choice == 0)
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
        if (choice != 0)
        {
            break;
        }
        EmergencyContact *ec = new EmergencyContact();
        string stringInput;
        cout << "Please enter your Patient ID: ";
        cin >> patientid;
        auto it = patientMap.find(patientid);

        if (it != patientMap.end())
        {
            cout << "Patient found: \n";
            getPatientInfo(patientid);
        }
        cout << "Please enter Contact name: ";
        cin >> stringInput;
        ec->setContactName(stringInput);
        cout << "Please enter phone number: ";
        cin >> stringInput;
        ec->setPhoneNumber(stringInput);
        cout << "Please enter Relationship: ";
        cin >> stringInput;
        ec->setRelationShip(stringInput);
        InsertEmergencyInfo(patientid, ec);
        choice = 1;
    }
    int id;
    cout << "Please enter contact ID to get emergency contact Info: ";
    cin >> id;
    getEmergencyContactInfo(id);
}
void Doctor ::showDoctorDashboard()
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
    }
}
void Doctor ::displayDoctorInfo()
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
        }
    }
}
void insertDoctorProfileInfo()
{
    int count = 0;
    string username;
    int id;
    Doctor *d = new Doctor();
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
        string stringInput;
        int intInput;
        cout << "Fill in your basic information.\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, stringInput);
        d->setName(stringInput);
        cout << "Age: ";
        cin >> intInput;
        d->setAge(intInput);
        cout << "Gender: ";
        cin.ignore();
        getline(cin, stringInput);
        d->setGender(stringInput);
        cout << "Specialty: ";
        getline(cin, stringInput);
        d->setSpecialty(stringInput);
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
    cin >> id;
    getDoctorInfo(id);
}
void Doctor ::medicalRecordsPlatForm()
{
    vector<MedicalRecordsNode *> Records;
    int choice;
    while (true)
    {
        cout << "-----Medical Records here! Do anything you want!-----\n"
             << "---------Please select your choice.----------\n";
        cout << "1. Add medical records \n2. Check Medical Records \n3. Check appointment status\n4. Medical Record\n5. Exitln";
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
            break;
        }
    }
}
void addMedicalRecords()
{
    int choice;
    int patientid;
    int doctorid;
    string details;
    string date;
    bool flag = false;
    while (true)
    {
        cout << "Please enter doctor ID: ";
        cin >> choice;
        flag = getDoctorInfo(choice);
        if (flag)
        {
            cout << "---------------------------\n";
            cout << "---------------------------\n";
            doctorid = choice;

            displayPatientInfo();
            while (true)
            {
                cout << "Please select Patient (ID): ";
                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number.\n";
                }
                flag = getPatientInfo(choice);
                if (flag)
                {
                    patientid = choice;
                    cout << "Enter records: ";
                    cin.ignore();
                    getline(cin, details);
                    time_t now = time(0);
                    struct tm tstruct;
                    localtime_s(&tstruct, &now);
                    char buf[11];
                    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
                    date = buf;
                    MedicalRecordsNode *record = new MedicalRecordsNode(date, details, patientid, doctorid);
                    recordList.addRecords(*record);
                    InsertMedicalRecords(record);
                    cout << "Records insert successfully!\n";
                }
                else
                {
                    cout << "Invalid patient ID, please try again\n";
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid Doctor ID, Please try again.";
            break;
        }
    }
}