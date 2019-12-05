
/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A definition of HashingModule class for Autentication Controller
*/

#ifndef HASHING_H
#define HASHING_H

#include <iostream>
#include <vector>

using namespace std;

class HashingModule {
    public:
        //double hashing
        static int hashFunction(string key, int tableSize, int i) {
            int length = key.length();
            int newK = 0;
            for (int j = 0; j < length; j++)
                newK += (int) key[j];
                // hash function 1 -> (newK % tableSize)
                // hash function 2 -> (newK * tableSize - 1) % tableSize)
            return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
        }

        // returns the next available prime number greater than num
        static int nextPrime(int num) { 
            if (num <= 1) {
                return 2; 
            } 
            int prime = num; 
            bool found = 0; 
            while (!found) { 
                prime++; 
                if (isPrime(prime)) {
                    found = 1; 
                }       
            }
            return prime; 
        } 

        // returns true if the number is a prime
        static bool isPrime(int num) {  
            if (num <= 1)  return 0;  
            if (num <= 3)  return 1;  
            if (num%2 == 0 || num%3 == 0) return 0;  
            for (int i = 5; i*i <= num; i = i+6) {
                if (num%i == 0 || num%(i+2) == 0) {
                return 0;  
                } 
            }
            return 1;  
        } 
};

#endif