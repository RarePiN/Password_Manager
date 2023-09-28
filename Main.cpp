// Password Manager For Personal Use
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

bool first_time = false;

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
    cout << "█▀█ ▄▀█ █▀ █▀ █░█░█ █▀█ █▀█ █▀▄ █▀" << endl;
    cout << "█▀▀ █▀█ ▄█ ▄█ ▀▄▀▄▀ █▄█ █▀▄ █▄▀ ▄█" << endl << endl << endl;
    getline(password, pass);
    while (!password.eof() and current != 6) {
        getline(password, pass);
        cout << current << ": " <<  decrypt(pass) << endl << endl;
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

void line() {       // Draw a line
    for (int i = 0; i < 72; i++) {
        cout << '=';
    }
    cout << endl;
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

bool check_overwrite(int num) {
    ifstream password ("Passwords.pass");
    string line;
    int current = 0;
    getline(password, line);
    while (!password.eof() and current != 6) {
        getline(password, line);
        current++;
        if (current == num) {
            if (line == "") {
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

void passfile() {
    ofstream password ("Passwords.pass");
    for (int i = 0; i < 6; i++) {
        password << "\n";
    }
}

void data_wipe() {
    string temp;
    ifstream password ("Passwords.pass");
    getline(password, temp);
    remove("Passwords.pass");
    ofstream newpass ("Passwords.pass");
    newpass << temp;
    for (int i = 0; i < 6; i++) {
        newpass << "\n";
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
        cout << endl;
        line();
        cout << endl;
        cout << "Thank you for using this program." << endl << endl;;
        cout << "Please set a password to access your stored passwords." << endl << endl << ": ";
        string pass;
        cin >> pass;
        store_password(pass, 0);
        first_time = true;
    }
    return;    
}

void logo() {    //Draw the logo
    cout << "██████╗░░█████╗░░██████╗░██████╗░██╗░░░░░░░██╗░█████╗░██████╗░██████╗░" << endl;
    cout << "██╔══██╗██╔══██╗██╔════╝██╔════╝░██║░░██╗░░██║██╔══██╗██╔══██╗██╔══██╗" << endl;
    cout << "██████╔╝███████║╚█████╗░╚█████╗░░╚██╗████╗██╔╝██║░░██║██████╔╝██║░░██║" << endl;
    cout << "██╔═══╝░██╔══██║░╚═══██╗░╚═══██╗░░████╔═████║░██║░░██║██╔══██╗██║░░██║" << endl;
    cout << "██║░░░░░██║░░██║██████╔╝██████╔╝░░╚██╔╝░╚██╔╝░╚█████╔╝██║░░██║██████╔╝" << endl;
    cout << "╚═╝░░░░░╚═╝░░╚═╝╚═════╝░╚═════╝░░░░╚═╝░░░╚═╝░░░╚════╝░╚═╝░░╚═╝╚═════╝░" << endl << endl;
    cout << "███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗██████╗░" << endl;
    cout << "████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝██╔══██╗" << endl;
    cout << "██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██████╔╝" << endl;
    cout << "██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██╔══██╗" << endl;
    cout << "██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░░██║" << endl;
    cout << "╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░╚═╝" << endl;
}

int main() {    // User interface
    logo();
    cout << endl;
    initialize();
    cout << endl;
    line();
    string login = "";
    int tries = 4;
    if (!first_time) {    // Login
        while (check_passcode(login) == false and tries > 0) {
            cout << endl;
            cout << "Please enter your access password." << endl << endl << ": ";
            cin >> login;
            cout << endl;
            line();
            if (check_passcode(login) == false) {
                cout << endl << "Invalid acces password, you have " << tries << " try(s) left." << endl;
                tries--;
            }
        }
        if (tries == 0) {
            return 0;
        }
    }

    int action = 0;
    while (action >= 0 and action < 4) {    // Main Interface
        cout << "┏━┓┏━┓" << endl;
        cout << "┃┃┗┛┃┃" << endl;
        cout << "┃┏┓┏┓┣━━┳━┓┏┓┏┓" << endl;
        cout << "┃┃┃┃┃┃┃━┫┏┓┫┃┃┃" << endl;
        cout << "┃┃┃┃┃┃┃━┫┃┃┃┗┛┃" << endl;
        cout << "┗┛┗┛┗┻━━┻┛┗┻━━┛" << endl << endl;
        cout << "0: Import password." << endl;
        cout << "1: Export password." << endl;
        cout << "2: Reset access password." << endl;
        cout << "3: Clear stored password." << endl;
        cout << "4: Exit." << endl << endl << ": ";
        cin >> action;
        cout << endl;
        line();
        cout << endl;
        if (action == 0) {
            string pass;
            int storage;
            cout << "Please enter the password you want to import." << endl << endl << ": ";
            cin >> pass;
            cout << endl << "Please choose a storage space. (1-5)" << endl << endl << ": ";
            cin >> storage;
            if (storage > 0 and storage < 6) {
                if (check_overwrite(storage)) {
                    cout << endl << "Storage already contains a password." << endl << "Overwrite password? (Y/N)" << endl << endl << ": ";
                    char temp;
                    cin >> temp;
                    if (temp == 'Y') {
                        store_password(pass, storage);
                        cout << endl << "Success." << endl << endl;
                        line();                        
                    } else {
                        cout << endl;
                        line();
                    }
                } else {
                    store_password(pass, storage);
                    cout << endl << "Success." << endl << endl;
                    line();
                }
            } else {
                cout << endl << "Invalid storage number." << endl << endl;
                line();
            }
        } else if (action == 1) {
            export_password();
            cout << endl;
            line();
        } else if (action == 2) {
            cout << "Please enter a new access password." << endl << endl << ": ";
            string new_pass, confrim;
            cin >> new_pass;
            cout << endl << endl << "Please enter your new password again to confrim." << endl << endl << ": ";
            cin >> confrim;
            if (confrim == new_pass) {
                store_password(new_pass, 0);
                cout << endl << "Success." << endl;
            } else {
                cout << endl << "New passwords do not match. Reset failed." << endl;
            }
            cout << endl;
            line();
        } else if (action == 3) {
            cout << "Do you wish to clear all stored passwords?" << endl;
            cout << "This action cannot be reversed." << endl << endl;
            cout << "Please enter your curretn access password." << endl << endl << ": ";
            string pass;
            cin >> pass;
            if (check_passcode(pass)) {
                data_wipe();
                cout << endl << "Success." << endl << endl;
                line();             
            } else {
                cout << endl << "Invalid password. Action failed." << endl << endl;
                line();
            }
        }
    }
    return 0;
}
