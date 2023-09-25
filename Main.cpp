// Password Manager For Personal Use
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int abs(int num) {
    if (num > 0) {
        return num * -1;
    } else {
        return num;
    }
}

string binary(int num) {
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

void initialize() {    // Create a file to store passwords.
    ifstream password ("Passwords.pass");
    if (password.is_open()) {
        password.close();
    }
    else {
        ofstream password ("Passwords.pass");
        cout << "Created password storage file." << endl;
    }
    return;    
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
            part = part + to_string(index);
            if (part != "") {
                output = output + part;
            }
            part = "";
        } else {
            part = part + pass[i];
            index--;
        }
    }
    if (part != "") {
        output = output + part;
    }
    return output;
}

void export_password() {    // Output password to interface or file
    return;
}

void store_password(string pass, int num) {    // Put password into password file
    int size;
    size = pass.size();
    create_temp();
    remove("Passwords.pass");
    ofstream password ("Passwords.pass");  //Wipe the old password file
    ifstream temp ("temp.pass");
    string line;
    int count = 0;
    if (password && temp) {    //Create new password file
        while (getline(temp, line)) {
            if (count == num) {
                password << pass << "\n";
            } else {
                if (count == 5) {
                    password << line;
                } else {
                    password << line << "\n";
                }
            }
            count++;
        }
    }
    password.close();
    delete_temp();
    return;
}

int UI() {    // User interface
    delete_temp();
    initialize();
    int action;
    cout << "Action (0: Import password, 1: Export password):";
    cin >> action;
    if (action == 0) {
        string pass;
        int num = -1;
        cout << "Input your password:" << endl;
        cin >> pass;
        while (num < 1 or num > 6) {
            cout << "Choose password number (1-5):" << endl;
            cin >> num;
        }
        store_password(pass, num);
    } else {
        return 0;
    }
    return 0;
}

int main() {    // Temporary testing
    string pass;
    pass = "test";
    cout << endl << encrypt(pass) << endl << endl;
    cout << endl << decrypt(encrypt(pass)) << endl << endl;
}
