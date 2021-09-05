#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

//features for now: create account, login

//will ask for username and password, then update the list
void makeAccount(unordered_set <string>*, ofstream&);
//create a user's txt file
void createPasswordFile(string);

//have the user login
bool login(unordered_set <string>*, string);

//features when logged in: change password
void changePassword(string);
 
int main() {
	bool running = true, loggedIn = false;
	int choice = -1;
	unordered_set <string> *userList = new unordered_set <string>;
	unordered_set<string> :: iterator itr;
	string userName, temp;
	ofstream writeUsers("users.txt", ios_base::app);
	ifstream readUsers("users.txt");

	while (getline(readUsers, temp)) {
		userList->insert(temp);
	}

	readUsers.close();
	while (running) {
		if (!loggedIn) {
			//prompt for logged out users
			cout << "\nWhat would you like to do:\n"
				 << "(1) Create a new account\n"
				 << "(2) Login into an account\n"
				 << "(3) Quit\n";
			cin >> choice;
			cin.ignore();

			switch (choice) {
			case 1:
				makeAccount(userList, writeUsers);
				break;
			case 2:
				cout << "Enter your username: ";
				getline(cin, userName);
				loggedIn = login(userList, userName);
				break;
			case 3:
				running = false;
				break;
			default:
				break;
			}
		}
		else {
			//prompt for logged in users
			cout << "\nHello " << userName << ", what would you like to do:\n"
				 << "(1) Change password\n"
				 << "(2) Logout\n"
				 << "(3) Quit\n";
			cin >> choice;
			cin.ignore();

			switch (choice) {
			case 1:
				changePassword(userName);
				break;

			case 2:
				loggedIn = false;
				break;
				
			case 3:
				running = false;
				cout << "Goodbye, " << userName;
				break;

			default:
				break;
			}
		}
	}

	writeUsers.close();
	return 0;
}

void makeAccount(unordered_set <string> *userList, ofstream &users) {
	string name;
	cout << "Enter a new username: ";
	getline(cin, name);

	if (userList->find(name) != userList->end()) {
		cout << "User name already exists.\n";
		return;
	}


	createPasswordFile(name);
	userList->insert(name);

	//append the new username to the users file
	users << name << endl;

	cout << "User created successfully.\n";
}

void createPasswordFile(string name) {
	string password;
	cout << "Enter a password: ";
	getline(cin, password);
	ofstream newPasswordFile("passwords\\" + name);
	newPasswordFile << password;
	newPasswordFile.close();
}

bool login(unordered_set <string> *userList, string userName) {
	string password;
	string passwordInput;

	if (userList->find(userName) == userList->end()) {
		cout << "This user does not exist.\n";
		return false;
	}

	ifstream passwordFile("passwords\\" + userName);
	if (!passwordFile.is_open()) {
		cout << "This user does not have a password!\n"
			 << "Logging in, but please create a password.";
		return true;
	}

	getline(passwordFile, password);
	cout << "Please enter your password: ";
	getline(cin, passwordInput);

	if (passwordInput != password) {
		cout << "Incorrect password.\n";
		return false;
	}

	cout << "Login successful.\n";
	return true;
}

void changePassword(string userName) {;
	createPasswordFile(userName);
	cout << "Password changed.\n";
}