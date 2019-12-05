
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A definition of RegistrationModule class for Autentication Controller
*/

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <iostream>
#include <vector>
#include "HashingModule.h"
#include "StatisticsModule.h"

using namespace std;

#define MAX_LOAD_FACTOR 0.65

// a structure defines user entry
struct user{        
    string username;
    string password;
    user(string _username = "EMPTY", string _password = "EMPTY"){
        username = _username;
        password = _password;
    }
};

class RegistrationModule {
    private:
        int registeredTableSize;                        // capacity of registered Users Table
        int regCount;                                   // current registered user count
        vector<user> registeredUsersTable;              // a dynamic array that stores registered users
        StatisticsModule statModule;

        int getNextAvailableIndex(string username) {
            for( int probe = 0; probe < registeredTableSize; probe++) {
                int index = HashingModule::hashFunction(username, registeredTableSize, probe);
                if (registeredUsersTable[index].username == "EMPTY" || registeredUsersTable[index].username == "DELETED") {
                    return index;
                }
            }
            return -1;
        };

        // inserts <username, password> to the registeredUsersTable table
        int insertUser(string username, string password) {
            int index = getNextAvailableIndex(username);
            if (index >= 0) {
                user user(username, password);
                registeredUsersTable[index] = user;
                regCount++;
                // resizes and rehashes data in the registration table
                if (getLoadFactor() >= MAX_LOAD_FACTOR) {
                    rehash();
                }
                return 1;
            } else {
               return 0;
            }
        };
        
        // rehashes the Registered User's table
        void rehash(){
            int newRegisterSize = HashingModule::nextPrime(2 * registeredTableSize);
            vector<user> newTable(newRegisterSize, {"EMPTY", "EMPTY"});
            for (list<userStatistics>::iterator it = statModule.begin(); it != statModule.end(); ++it){
                // gets first registered user from statistics table
                userStatistics user = *it;    
                int passwordsToCopy = user.passwordsCount;

                int probesToGet = 0;
                while (passwordsToCopy > 0){
                    int oldIndex = HashingModule::hashFunction(user.username, registeredTableSize, probesToGet);
                    if (registeredUsersTable[oldIndex].username == user.username){   
                        // if correct user entry is found, insert it to new table
                        for (int probeToInsert = 0; probeToInsert < newRegisterSize; probeToInsert++) {
                            int newIndex = HashingModule::hashFunction(user.username, newRegisterSize, probeToInsert);
                            // copy if available spot in new table is found
                            if(newTable[newIndex].username == "EMPTY"){
                                newTable[newIndex] = {registeredUsersTable[oldIndex].username, registeredUsersTable[oldIndex].password};
                                break;
                            }
                        }
                        passwordsToCopy--;  
                    }
                    probesToGet++;
                } ; // continue doing so until all passwords of the user are copied
            }
            registeredUsersTable = newTable;
            registeredTableSize = newRegisterSize;
        }

        float getLoadFactor(){
            return regCount/registeredTableSize;
        }

    public:
        // constants to use for user credentials validation
        const int NOT_REGISTERED = -1;
        const int WRONG_PASSWORD = 0;
        const int CORRECT_PASSWORD = 1;
        const int OLD_PASSWORD = 2;

        RegistrationModule(int size){
            registeredTableSize = size;
            regCount = 0;
            registeredUsersTable.resize(registeredTableSize, {"EMPTY", "EMPTY"});
            statModule = StatisticsModule();
        };

        int registerUser(string username, string password){
            if(isRegistered(username, password) == NOT_REGISTERED){
                statModule.addUser(username);
                return insertUser(username, password);
            } else {
                cout<<"This user is already registered"<<endl;
                return 0;
            }
        };

        int delUser(string username){
            int quantityOfPasswords = statModule.getPasswords(username);
            if(quantityOfPasswords == 0){
                return 0;
            }
            int i = 0;
            while(quantityOfPasswords > 0) {
                int index = HashingModule::hashFunction(username, registeredTableSize, i);   
                if(registeredUsersTable[index].username == "EMPTY"){
                    return 0;
                } else if (registeredUsersTable[index].username == username){
                    registeredUsersTable[index].username = "DELETED";
                    registeredUsersTable[index].password = "DELETED";
                    quantityOfPasswords--;
                }
                i++;
            }
            statModule.removeUser(username);
            regCount--;
            return 1;
        };

        int changePassword(string username, string oldpass, string newpass){
            int result = isRegistered(username, oldpass);
            if(result == NOT_REGISTERED){
                cout<<"No user found with this username"<<endl;
            } else if(result == WRONG_PASSWORD){
                cout<<"Wrong password"<<endl;
            } else if( result == CORRECT_PASSWORD){
                return statModule.incrementPasswords(username) && insertUser(username, newpass);
            } else if (result == OLD_PASSWORD) {
                cout<<"You cannot use your old password"<<endl;
            }
            return 0;
        };

        int isRegistered(string username, string password){
            int quantityOfPasswords = statModule.getPasswords(username);
            if(quantityOfPasswords == 0){
                return NOT_REGISTERED;                     
            }
            for (int i = 0; (i < registeredTableSize || quantityOfPasswords > 0); i++){
                int index = HashingModule::hashFunction(username, registeredTableSize, i);   
                if (registeredUsersTable[index].username == username){
                    if (password == registeredUsersTable[index].password){
                        if(quantityOfPasswords > 1){
                            return OLD_PASSWORD;                  
                        }
                        return CORRECT_PASSWORD;                      
                    }
                    quantityOfPasswords--;
                }
            };
            return WRONG_PASSWORD;                                   
        };

        float printPasswords(){
            cout<<endl;
            cout<<"Registered users"<<endl;
            cout<<"-----------------"<<endl;
            int count = 0;
            for(int i = 0; i < registeredTableSize; i++){
                cout<<registeredUsersTable[i].username<<": "<<registeredUsersTable[i].password<<endl;
            }
            cout<<endl;
            return getLoadFactor();
        }
};

#endif