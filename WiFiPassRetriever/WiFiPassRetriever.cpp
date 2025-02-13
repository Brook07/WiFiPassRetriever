#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void retrievePassword() {
    system("color A");  // Set console color to yellow
    cout << "\nAvailable Wi-Fi Networks:\n";
    system("netsh wlan show profile"); // List saved Wi-Fi networks

    cout << "\nEnter the Wi-Fi name (or type 'exit' to quit): ";
    string networkName;
    getline(cin, networkName);

    if (networkName == "exit") {
        cout << "Exiting program...\n";
        exit(0);
    }

    // Execute command to retrieve Wi-Fi password and store output in a temp file
    string command = "netsh wlan show profile \"" + networkName + "\" key=clear > temp.txt";
    system(command.c_str());

    ifstream file("temp.txt");
    if (!file) {
        cout << "Error retrieving Wi-Fi profile. Make sure the name is correct.\n";
        return;
    }

    string line, password;
    
    while (getline(file, line)) {
        if (line.find("Key Content") != string::npos) {  // Look for password line
            size_t pos = line.find(":");
            if (pos != string::npos) {
                password = line.substr(pos + 2);  // Extract password
            }
            break;
        }
    }

    file.close();
    remove("temp.txt"); // Clean up temp file

    if (!password.empty()) {
        cout << "\nYour Wi-Fi password is: \033[1;32m" << password << "\033[0m\n"; // Green text output
    } else {
        cout << "\nPassword not found or network does not exist.\n";
    }

    cout << "\nPress Enter to check another Wi-Fi network...";
    cin.get();
    system("cls"); // Clear screen for better readability
}

int main() {
    while (true) {
        retrievePassword();
    }
    return 0;
}
