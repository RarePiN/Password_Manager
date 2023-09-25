// Password Manager For Personal Use
#include <iostream>
#include <fstream>
using namespace std;

void create_temp() {
    ofstream temp ("temp.txt");
    ifstream password ("Passwords.txt");
    password.open ("Passwords.txt");
    temp.open ("temp.txt");
    return;
}

void delete_temp() {
    return;
}

void initialize() {
    ifstream password ("Passwords.txt");
    if (password.is_open()) {
        password.close();
    }
    else {
        ofstream password ("Passwords.txt");
        cout << "Created password storage file.";
    }
    return;    
}

void export_password() {
    return;
}

void store_password(string pass, int num) {
    int size;
    size = pass.size();
    ofstream password;
    password.open ("Passwords.txt");
    password << pass;
    password.close();
    return;
}

void read_password() {
    return;
}

int main() {  
    initialize();
    int action;
    cout << "Action (0: Import password, 1: Export password):";
    cin >> action;
    if (action == 0) {
        string pass;
        int num;
        cout << "Input your password:" << endl;
        cin >> pass;
        cout << "Choose password number (1-5):" << endl;
        cin >> num;
        store_password(pass, num);
    }
    return 0;
}
