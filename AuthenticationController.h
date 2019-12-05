
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A definition of AuthenticationController class
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "RegistrationModule.h"
#include "LoginModule.h"

using namespace std;

class AuthenticationController {
    RegistrationModule *registrationModule;
    LoginModule *loginModule;

  public:
    //initialize the tables
    //Set entries of table 1 to < "EMPTY","EMPTY">
    //Set entries of table 2 to "EMPTY"
	AuthenticationController(int table1Size, int table2Size) {
        registrationModule = new RegistrationModule(table1Size);
        loginModule = new LoginModule(table2Size, registrationModule);
    }


    //register the given user with username and password to 
    //registered users table if not registered
    //return 1 if successful, 0 if not.
	int addUser(string username, string pass) {
        return registrationModule->registerUser(username, pass);
    }

    //delete all entries of that user
    //Put <"DELETED","DELETED"> as deleted entry
    //return 1 if the user is registered else just return 0
	int delUser(string username) {
        loginModule->logoutUser(username);
        return registrationModule->delUser(username);
    }

    //change the password of the given user if user is registered and 
    //oldpassword is equal the current password. While changing the password, 
    //keep the old entries <username,oldpassword> in the table and add 
    //new entry <username,newpassword> To the next empty cell that is 
    //found with the hash function. Last entry addes is the current 
    //password of that user. If operation is successful return 1, else return 0
	int changePass(string username, string oldpass, string newpass) {
        return registrationModule->changePassword(username, oldpass, newpass);
    }

    //if the user is registered and password is the current 
    //password of given user, log the user in and return 1, 
    //if not do nothing and return 0.
	int login(string username, string pass) {
        return loginModule->loginUser(username, pass);
    }

    //if the given user is logged in, log that user out and retun 1, 
    //if not return 0
    //Put “DELETED” for logged out users. 
	int logout(string username) {
        return loginModule->logoutUser(username);
    }

    //print all logged in users 
    //print “DELETED” for deleted entries, “EMPTY” for empty entries
    //returns load factor.
	float printActiveUsers() {
        return loginModule->printActiveUsers();
    }

    //print all users and passwords, print “DELETED DELETERED” for deleted entries
    //print “EMPTY EMPTY” for empty entries
    //returns load factor. 
	float printPasswords() {
        return registrationModule->printPasswords();
    }

    ~AuthenticationController(){
        delete loginModule;
        delete registrationModule;
    }
};

#endif