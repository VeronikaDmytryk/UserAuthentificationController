
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A definition of LoginModule class for Autentication Controller
*/

#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <vector>
#include "RegistrationModule.h"
#include "HashingModule.h"

#define MAX_LOAD_FACTOR 0.65

using namespace std;

class LoginModule {
    private:
        int activeTableSize;                        // capacity of activeUsersTable, active users table
        int activeCount;                            // current active users count
        vector<string> activeUsersTable;            // a dynamic array that stores active users (logged in)
        RegistrationModule *regModule;

    public:
        // constructor
        LoginModule(int size, RegistrationModule * &rm) {
            activeCount = 0;
            activeTableSize = size;
            regModule = rm;
            activeUsersTable.resize(activeTableSize, "EMPTY");
        };

        // adds the user from the active users table 
        int loginUser(string username, string password) {
            int validCredentials = regModule->isRegistered(username, password);
            if (validCredentials == regModule->NOT_REGISTERED) {
                cout<<"User with username "<<username<<" is not registered yet"<<endl;
                return 0;
            } else if (validCredentials == regModule->CORRECT_PASSWORD) {
                if (addToTable(username)) {
                    cout<<"Welcome in "<<username<<"!"<<endl;
                    return 1;
                } else {
                    cout<<"Sorry "<<username<<", something went wrong :("<<endl;
                    return 0;
                }
            } else if (validCredentials == regModule->OLD_PASSWORD) {
                cout<<username<<" you cannot use old password"<<endl;
                return 0;
            } else {
                cout<<"Wrong password for "<<username<<endl;
                return 0;
            }
        };

        // removed the user from the active users table 
        int logoutUser(string username){
            if (deleteFromTable(username)){
                cout<<"Goodbye "<<username<<"!"<<endl;
                return 1;
            } else {
               cout<<"You are not logged in, "<<username<<endl;
                return 0; 
            }
        };

        // prints all active users and returns the load factor of the Active Users Table
        float printActiveUsers(){
            cout<<endl<<"List of active users"<<endl;
            cout<<"--------------------"<<endl;
            for(int i = 0; i < activeTableSize; i++){
                if(activeUsersTable[i] != "DELETED" && activeUsersTable[i] != "EMPTY"){
                    cout<<activeUsersTable[i]<<endl;
                }
            }
            return getLoadFactor();
        };

    private:
        int getNextAvailableIndex(string username) {
            for( int probe = 0; probe < activeTableSize; probe++) {
                int index = HashingModule::hashFunction(username, activeTableSize, probe);
                if (activeUsersTable[index] == "EMPTY" || activeUsersTable[index] == "DELETED") {
                    return index;
                }
            }
            return -1;
        };

        // adds the username to table if there is an available space
        int addToTable(string username) {
            int availableIndex = getNextAvailableIndex(username);
            if(availableIndex == -1) {
                return -1;
            } else {
                activeUsersTable[availableIndex] = username;
                activeCount++;
                // resizes and rehashes data in the active users table
                if (getLoadFactor() >= MAX_LOAD_FACTOR) {
                    rehash();
                }
                return 1;
            }
        };

        // deletes the user from active table if present
        int deleteFromTable(string username) {
            for (int probe = 0; probe < activeTableSize; probe++) {
                int index = HashingModule::hashFunction(username, activeTableSize, probe);
                if (activeUsersTable[index] == "EMPTY"){
                    return 0;
                } else if (activeUsersTable[index] == username) {
                    activeUsersTable[index] = "DELETED";
                    activeCount--;
                    return 1;
                } 
            }
            return 0;
        };

        void rehash() {
            int newActiveSize = HashingModule::nextPrime(2 * activeTableSize);
            vector<string> newTable(newActiveSize, "EMPTY");
            for (int i = 0; i < activeTableSize; i++) {
                if(activeUsersTable[i] != "EMPTY" && activeUsersTable[i] != "DELETED"){
                    for (int j = 0; j < newActiveSize; j++) {
                        int newIndex = HashingModule::hashFunction(activeUsersTable[i], newActiveSize, j);
                        if(newTable[newIndex] == "EMPTY"){
                            newTable[newIndex] = activeUsersTable[i];
                            break;
                        };
                    }
                }      
            }
            activeUsersTable = newTable;
            activeTableSize = newActiveSize;
        };

        float getLoadFactor(){
            return activeCount/activeTableSize;
        }
};

#endif
