// Password Manager For Personal Use
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int abs(int num) {    // Abslute value of a number
    if (num > 0) {
        return num * -1;
    } else {
        return num;
    }
}

string binary(int num) {    // Convert number into binary
    if (num != 0) {    
        int quotient = abs(num);
        char temp;
        string new_num = "";
        int test;
        int remainder, length = 0;
        while (quotient != 0) {
            remainder = (quotient % 2) * - 1;
            quotient = quotient / 2;
            temp = remainder + 48;
            new_num = new_num + temp;	
        }
        reverse(new_num.begin(), new_num.end());
        if (num < 0) {
            return "-" + new_num;
        } else {
            return new_num;
        }
    } else {
        return "0";
    }
}

int decimal(string num) {    // Convert number into decimal
    int size = num.length();
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (num[i] == '1') {
            total += pow(2 , (size - i - 1));
        }
    }
    return total;
}

void create_temp() {    // Clone the passwords to a temp file.
    char ch;
    ofstream temp ("temp.pass");
    ifstream password ("Passwords.pass");
    while (password && password.get(ch)) 
        temp.put(ch);
    password.close();
    temp.close();
    return;
}

void delete_temp() {    // Delete the temp file.
    ifstream temp ("temp.pass");
    remove("temp.pass");
    return;
}

string encrypt(string pass) {    //Encrypt password
    string output = "";
    int length = pass.length();
    for (int i = 0; i < length; i++) {
        char temp;
        string lenC;
        temp = pass[i];
        lenC = binary(temp+0);
        output = output + to_string(lenC.length());
        output = output + lenC;
    }
    return output;
}

string decrypt(string pass) {    //Decrypt password
    int length = pass.length();
    int index = 0;
    string output;
    string part = "";
    char temp;
    int current;
    for (int i = 0; i < length; i++) {
        if (index == 0) {
            index = pass[i] - '0';
            if (part != "") {
                temp = decimal(part);
                output = output + temp;
            }
            part = "";
        } else {
            if (pass[i] == '/')
                part = part + '1';
            else {
                part = part + '0';
            }
            index--;
        }
    }
    if (part != "") {
        temp = decimal(part);
        output = output + temp;
    }
    return output;
}

void export_password() {    // Output password to interface or file
    string pass;
    ifstream password ("Passwords.pass");
    int current = 1;
    getline(password, pass);
    while (!password.eof() and current != 6) {
        getline(password, pass);
        cout << current << ": " <<  decrypt(pass) << endl;
        current++;
    }
    return;
}

void store_password(string pass, int num) {    // Put password into password file
    int size;
    pass = encrypt(pass);
    size = pass.size();
    create_temp();
    remove("Passwords.pass");
    ofstream password ("Passwords.pass");  //Wipe the old password file
    ifstream temp ("temp.pass");
    string line;
    int count = 0;        //Create new password file
    bool end = false;
    while (getline(temp, line)) {
        if (count == num) {
            password << pass << "\n";
        } else {
            if (count == 6) {
                password << line;
            } else {
                password << line << "\n";
            }
        }
        count++;
    }
    password.close();
    delete_temp();
    return;
}

bool check_passcode(string pass) {
    ifstream password ("Passwords.pass");
    string temp;
    getline(password, temp);
    if (encrypt(pass) == temp) {
        return true;
    }
    return false;
}

void passfile() {
    ofstream password ("Passwords.pass");
    for (int i = 0; i < 6; i++) {
        password << "\n";
    }
}

void initialize() {    // If user is first time using
    ifstream password ("Passwords.pass");
    if (password.is_open()) {
        password.close();
    }
    else {
        ofstream password ("Passwords.pass");
        password.close();
        passfile();
        cout << "Created password storage file." << endl;
        cout << "Please create a password for your program." << endl;
        string pass;
        cin >> pass;
        store_password(pass, 0);
    }
    return;    
}

int main() {    // User interface
    initialize();
    int action;
    cout << "Action (0: Import password, 1: Export password, 2: Set password):";
    cin >> action;
    if (action == 0) {
        string pass;
        int num = -1;
        cout << "Input your current password:" << endl;
        cin >> pass;
        if (check_passcode(pass)) {
            cout << "Input your password:" << endl;
            cin >> pass;
            while (num < 1 or num > 5) {
                cout << "Choose password number (1-5):" << endl;
                cin >> num;
            }
            store_password(pass, num);
        } else {
            cout << "Invalid password bro." << endl;
            return 0;
        }
    } else if (action == 2) {
        cout << "Input your old password:" << endl;
        string pass;
        cin >> pass;
        if (check_passcode(pass)) {
            cout << "Input your new password:" << endl;
            cin >> pass;
            store_password(pass, 0);
        } else {
            cout << "Invalid password." << endl;
            return 0;
        }
        
    } else {
        cout << "Input your current password:" << endl;
        string pass;
        cin >> pass;
        if (check_passcode(pass)) {
            export_password();
        } else {
            cout << "Invalid password bro." << endl;
            return 0;
        }
    }
    return 0;
}
