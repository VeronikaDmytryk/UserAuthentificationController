/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A definition of StatisticsModule class for Autentication Controller
*/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <list>

using namespace std;

// a struct defined user statistic object
struct userStatistics{        
    string username;
    int passwordsCount;
    
    // constructor
    userStatistics(string _username = "EMPTY", int passwords = 0) {
        username = _username;
        passwordsCount = passwords;
    }

    // overriding operator==, for comparing userStatistics object only fy username
    friend bool operator==(const userStatistics &a, const userStatistics &b) {
        return a.username == b.username;
    }
};

class StatisticsModule {
    private:
        list<userStatistics> registrationStatistics;                // list to hold registered users data
    public: 
        // adds user to the statistics list
        void addUser(string username) {
            userStatistics newUser(username, 1);
            registrationStatistics.push_back(newUser);
        }

        // removes user from the statistics list
        void removeUser(string username) {
            userStatistics userToRemove(username);
            registrationStatistics.remove(userToRemove);
        }

        // user returns number of stored passwords, or 0 if user is not registered
        int getPasswords(string username) {
            userStatistics user(username);
            list<userStatistics>::iterator iter = find(registrationStatistics.begin(), registrationStatistics.end(), user);
            if (registrationStatistics.end() == iter ) {
                return 0;
            } else {
                return iter->passwordsCount;
            }
        }

        // increments the number of passwords for specific user
        int incrementPasswords(string username) {
            userStatistics user(username);
            list<userStatistics>::iterator iter = find(registrationStatistics.begin(), registrationStatistics.end(), user);
            if (registrationStatistics.end() == iter ) {
                return 0;
            } else {
                iter->passwordsCount = iter->passwordsCount + 1;
                return 1;
            }
        }

        // returns the number of registered users
        int getNumberOfRegisteredUsers() {
            return registrationStatistics.size();
        }

        // prints all user - passwords pairs
        void printAllUsers() {
            cout<<endl<<"Username - Passwords Statistics"<<endl;
            cout<<"---------------------------------"<<endl;
            for(list<userStatistics>::iterator it = registrationStatistics.begin(); it != registrationStatistics.end(); ++it){
                cout<<it->username<<": "<<it->passwordsCount<<endl;
            }
        }

        // Iterator functions for RegistrationModule
        list<userStatistics>::iterator begin() {
            return registrationStatistics.begin();
        }

        list<userStatistics>::iterator end() {
            return registrationStatistics.end();
        }
};

#endif