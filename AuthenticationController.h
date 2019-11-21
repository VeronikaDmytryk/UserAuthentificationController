#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <vector>

#define MAX_LOAD_FACTOR 0.65

using namespace std;

//a structure defines user entry
struct user{        
    string username;
    string password;
};

class AuthenticationController{
        vector<user> table1;            //a dynamic array that stores registered users
        vector<string> table2;          //a dynamic array that stores active users (logged in)

	int registeredTableSize;        //capacity of table1, registered users tabls
	int activeTableSize;            //capacity of table2, active users table
	int regCount;                   //current registered user count
	int activeCount;                //current active users counr

        //double hashing
	int hashFunction(std::string key, int tableSize, int i) {
		int length = key.length();
		int newK = 0;
		for (int j = 0; j < length; j++)
			newK += (int) key[j];
			// hash function 1 -> (newK % tableSize)
			// hash function 2 -> (newK * tableSize - 1) % tableSize)
		return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}
  public:
    //initialize the tables
    //Set entries of table 1 to < "EMPTY","EMPTY">
    //Set entries of table 2 to "EMPTY"
	AuthenticationController(int table1Size, int table2Size);


    //register the given user with username and password to 
    //registered users table if not registered
    //return 1 if successful, 0 if not.
	int addUser(string username, string pass);

    //delete all entries of that user
    //Put <"DELETED","DELETED"> as deleted entry
    //return 1 if the user is registered else just return 0
	int delUser(string username);

    //change the password of the given user if user is registered and 
    //oldpassword is equal the current password. While changing the password, 
    //keep the old entries <username,oldpassword> in the table and add 
    //new entry <username,newpassword> To the next empty cell that is 
    //found with the hash function. Last entry addes is the current 
    //password of that user. If operation is successful return 1, else return 0
	int changePass(string username, string oldpass, string newpass);

    //if the user is registered and password is the current 
    //password of given user, log the user in and return 1, 
    //if not do nothing and return 0.
	int login(string username, string pass);

    //if the given user is logged in, log that user out and retun 1, 
    //if not return 0
    //Put “DELETED” for logged out users. 
	int logout(string username);

    //print all logged in users 
    //print “DELETED” for deleted entries, “EMPTY” for empty entries
    //returns load factor.
	float printActiveUsers();

    //print all users and passwords, print “DELETED DELETERED” for deleted entries
    //print “EMPTY EMPTY” for empty entries
    //returns load factor. 
	float printPasswords();
	


};

#endif"