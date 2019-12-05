
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A client program to test AuthenticationController class
*/

#include <iostream>
#include "AuthenticationController.h"

using namespace std;

int main(){
    AuthenticationController controller(1, 7);

    // Testing adding users
    controller.addUser("Veronika", "Ruby");
    controller.addUser("Valerii", "Rainy");
    controller.addUser("Ruby", "Valerii");
    controller.addUser("Tom", "Jerry");
    controller.addUser("Jerry", "John");

    // Testing changing password
    controller.changePass("Veronika", "Ruby", "Mommy");
    controller.changePass("Tom", "Jerry", "TEST");

    // Testing logging in
    controller.login("smt", "stm");
    controller.login("Tom", "TEST");
    controller.login("Valerii", "Rainy");
    controller.login("Ruby", "Valerii");
    controller.login("Veronika", "Mommy");

    // Testing printing users
    controller.printActiveUsers();

    // Testing printing passwords
    controller.printPasswords();

    // Testing deleting a logged-in user with multiple passwords
    controller.delUser("Veronika");

    controller.printPasswords();
    controller.printActiveUsers();
    return 0;
}