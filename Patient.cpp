#include "Patient.h"

int Patient :: patientPlatForm()
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
        }
    }
}

 void Patient :: information(){
    int count = 0;
    while(count == 0){
    cout << "First time login(0 for first time)?(0/1):\n";
    cin >> count;
    if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue; 
        }
    if(count == 1){
        break;
    }
    Patient* p = new Patient();
    int age;
    string name;
    string gender;
    string username;
    cout << "Fill in your basic information.\n";
    cout << "Name:\n";
    cin >> name;
    p->setName(name);
    cout << "gender:\n";
    cin >> gender;
    p->setGender(gender);
    cout << "age:\n";
    cin >> age;
    p->setAge(age);
    cout << "Enter the username to associate with the patient: ";
    cin >> username;
        if (username.empty()) {
        std::cerr << "Username cannot be empty.\n";
        return;
    }
    InsertPatientInfo(p,username);
    count = 1;
    }
    string username;
    cout << "Please enter your username to get your information: ";
    cin >> username;
    getPatientInfo(username);
}