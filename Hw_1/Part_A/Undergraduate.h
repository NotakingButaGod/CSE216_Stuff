#pragma once

#include<string>
#include <sstream>
using namespace std;
#include "Student.h"

class Undergraduate : public Student {
    private:
        string standing;
    
    public:
        Undergraduate(string initKey, string firstName, string lastName, double initGPA, string initStanding)
            : Student(initKey, firstName, lastName, initGPA) {
            this->standing = initStanding;
        }
        
        string getStanding() {
            return this->standing;
        }
        
        void setStanding(string initStanding) {
            this->standing = initStanding;
        }
        
        string toString() {
            stringstream ss;
            ss << this->getFirstName() << " " << this->getLastName() << " (" << this->standing << " " << this->getGpa() << ")";
            return ss.str();
        }
};