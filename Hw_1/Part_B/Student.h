#pragma once

#include<string>
#include <sstream>
using namespace std;
#include "Person.h"

class Student : public Person {
    private:
        double gpa;
    
    public:
        Student(string initKey, string firstName, string lastName, double initGPA)
            : Person(initKey, firstName, lastName) {
            this->gpa = initGPA;
        }
        
        double getGpa() {
            return this->gpa;
        }
        
        void setGpa(double initGpa) {
            this->gpa = initGpa;
        }
        
        string toString() {
            stringstream ss;
            ss << this->getKey() << ": " << this->getFirstName() << " " << this->getLastName() << " (" << this->gpa << ")";
            return ss.str();
        }
};