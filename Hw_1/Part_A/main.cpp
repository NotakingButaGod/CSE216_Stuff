// FIRST WE INCLUDE ALL THE THINGS WE PLAN TO USE HERE

// FOR printf
#include <stdio.h>

// FOR cout
#include <iostream>
#include<string>
#include <sstream>
using namespace std;

// OUR STUFF
#include "Person.h"
#include "Student.h"
#include "Employee.h"
#include "Undergraduate.h"
#include "OpenAddressHashTable.h"

const int NUM_BINS = 5;
const int KEY_LENGTH = 8;

void printHashTable(string header, OpenAddressHashTable<Person> *hashTable);
void addPersonToHashTable(Person *person, OpenAddressHashTable<Person> *hashTable);

// EXECUTION OF OUR PROGRAM STARTS HERE
int main() {
    OpenAddressHashTable<Person> *hashTable = new OpenAddressHashTable<Person>(NUM_BINS, KEY_LENGTH);

    // DEMONSTRATE ADDING VALUES TO THE HASH TABLE, WHICH INCLUDES THE NEED TO MAKE THE HASH TABLE BIGGER
    string georgeHarrisonKey = hashTable->generateKey();
    addPersonToHashTable(new Student(georgeHarrisonKey, "George", "Harrison", 4.0), hashTable);
    addPersonToHashTable(new Employee(hashTable->generateKey(), "Paul", "McCartney", 80000), hashTable);
    addPersonToHashTable(new Employee(hashTable->generateKey(), "Ringo", "Starr", 40000), hashTable);
    addPersonToHashTable(new Person(hashTable->generateKey(), "Chuck", "Berry"), hashTable);
    addPersonToHashTable(new Student(hashTable->generateKey(), "Mick", "Jagger", 3.5), hashTable);
    addPersonToHashTable(new Student(hashTable->generateKey(), "Jimi", "Hendrix", 3.6), hashTable);
    addPersonToHashTable(new Person(hashTable->generateKey(), "Roger", "Waters"), hashTable);

    // DEMONSTRATE MAKING KEYS AND ADDING VALUES TO THE HASH TABLE    
    string jlKey = hashTable->generateKey();
    hashTable->putValue(jlKey, new Student(jlKey, "John", "Lennon", 3.8));
    string cwKey = hashTable->generateKey();
    hashTable->putValue(cwKey, new Student(cwKey, "Charlie", "Watts", 3.1));
    string dgKey = hashTable->generateKey();
    hashTable->putValue(dgKey, new Employee(dgKey, "David", "Gilmour", 120000));
    printHashTable("\nAfter Changing 3 Items", hashTable);
    
    // DEMONSTRATE GETTING VALUES FROM THE HASH TABLE
    Person *p = hashTable->getValue(jlKey);
    cout << endl << "get " << jlKey << ": " << p->toString() << endl;
    p = hashTable->getValue(cwKey);
    cout << "get " << cwKey << ": " << p->toString() << endl;
    p = hashTable->getValue(dgKey);
    cout << "get " << dgKey << ": " << p->toString() << endl;
    
    // NOW LET'S TRY REPLACING THE DATA IN THE ABOVE THREE
    hashTable->putValue(jlKey, new Student(jlKey, "Otis", "Redding", 3.5));
    hashTable->putValue(cwKey, new Student(cwKey, "Keith", "Richards", 3.1));
    hashTable->putValue(dgKey, new Student(dgKey, "Bill", "Withers", 3.4));
    printHashTable("\nAfter Changing 3 Items", hashTable);
    
    // AND DEMONSTRATE REMOVING ITEMS FROM THE HASH TABLE
    hashTable->removeValue(georgeHarrisonKey);
    printHashTable("\nAfter Removing George Harrison", hashTable);
    
    hashTable->removeValue(jlKey);
    printHashTable("\nAfter Removing Otis Redding", hashTable);

    hashTable->removeValue(cwKey);
    printHashTable("\nAfter Removing Keith Richards", hashTable);
    
    hashTable->removeValue(dgKey);
    printHashTable("\nAfter Removing Bill Withers", hashTable);
    
    // NOW LET'S MAKE USE OF UNDERGRADUATE OBJECTS
    string jimMorrisonKey = hashTable->generateKey();
    addPersonToHashTable(new Undergraduate(jimMorrisonKey, "Jim", "Morrison", 2.7, "U3"), hashTable);
    Undergraduate *jim = (Undergraduate*)hashTable->getValue(jimMorrisonKey);
    cout << "Before Changing Undergraduate: " << jim->toString() << endl;
    jim->setStanding("U4");
    cout << "After Changing Undergraduate: " << jim->toString() << endl;

    return 0;
}

void addPersonToHashTable(Person *person, OpenAddressHashTable<Person> *hashTable) {
    hashTable->putValue(person->getKey(), person);
    cout << hashTable->toString();
}

void printHashTable(string header, OpenAddressHashTable<Person> *hashTable) {
    string text = hashTable->toString();
    cout << header << endl;
    cout << text;
}