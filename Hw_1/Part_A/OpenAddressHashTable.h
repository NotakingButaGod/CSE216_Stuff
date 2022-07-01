#include <stdlib.h>
#include <ctime>
#include<string>
#include <sstream>
using namespace std;

template <class S>

class OpenAddressHashTable {
    class KeyValuePair {
        public:
            // INSTANCE VARIABLES
            string key;
            S* value;
            
            // CONSTRUCTOR
            KeyValuePair(string initKey, S* initValue) {
                key = initKey;
                value = initValue;
            }

            // DESTRUCTOR
            ~KeyValuePair() {}

            string toString() {
                stringstream ss;
                ss << "(" << this->key << "," << value->toString() << ")";
                return ss.str();
            }
    };

    private:
        KeyValuePair* *hashTable;
        int length;
        int size;
        int keyLength;

    public:
        OpenAddressHashTable(int initLength, int initKeyLength) {
            this->length = initLength;
            this->size = 0;
            keyLength = initKeyLength;
            hashTable = new KeyValuePair*[initLength];
            srand((unsigned) time(0));
        }
        int getSize() {
            return this->size;
        }
        int hashCode(string key) {
            int charsSum = 0;
            for (auto it = key.cbegin(); it != key.cend(); ++it) {
                int num = (int)(*it);
                charsSum += num;
            }
            return charsSum % length;
        }
        
        // @todo - YOU MUST UPDATE THIS METHOD SO A KEY ONLY HAS LOWERCASE LETTERS, NO NUMBERS
        string generateKey() {
            string key {""};
            for (int i = 0; i < this->keyLength; i++) {
                int randomNum = (rand() % 36);
                char randomChar;
                if (randomNum < 10) {
                    randomChar = (char)(randomNum + 48);
                }
                else {
                    randomChar = (char)(randomNum + 55);
                }
                key += randomChar;
            }
            return key;
        }

        // @todo - YOU MUST DEFINE THIS METHOD
        S* getValue(string key) {
            int index = hashCode(key); // THIS IS THE NATURAL INDEX
            int count = 0;
            while (count < length) {
                KeyValuePair *testKVP = hashTable[index];
                // IF IT'S nullptr, IT CAN'T BE IN THE HASH TABLE
                if (testKVP == nullptr) {
                    return nullptr;
                }
                // IF A KVP USES THIS KEY, RETURN ITS VALUE
                else if (testKVP->key.compare(key) == 0) {
                    return testKVP->value;
                }
                index++;
                // WE MAY NEED TO RESET index TO LOOK IN THE FRONT OF THE HASH TABLE
                if (index == length)
                    index = 0;
                count++;
            }
            // IT WAS NOT IN THE FULL HASH TABLE, SO RETURN nullptr
            return nullptr;
        }

        // @todo - YOU MUST DEFINE THIS METHOD
        void removeValue(string key) {
            int index = hashCode(key); // THIS IS THE NATURAL INDEX
            int count = 0;
            while (count < length) {
                KeyValuePair *testKVP = hashTable[index];
                // IF IT'S nullptr, IT CAN'T BE IN THE HASH TABLE
                if (testKVP == nullptr) {
                    return;
                }
                // IF A KVP USES THIS KEY, REMOVE IT
                else if (testKVP->key.compare(key) == 0) {
                    // DELETE THE KVP (but not the value)
                    delete testKVP;
                    
                    // EMPTY THAT LOCATION
                    hashTable[index] = nullptr;
                    
                    // DECREMENT THE SIZE
                    size--;
                    
                    // AND REHASH THE TABLE
                    KeyValuePair* *temp = new KeyValuePair*[length];
                    int counter = 0;
                    // FIRST GET ALL THE EXISTING VALUES AND PUT THEM
                    // WHERE WE CAN GET THEM WHILE EMPTYING THE HASH TABLE
                    for (int i = 0; i < length; i++) {
                        KeyValuePair *item = hashTable[i];
                        if (item != nullptr) {
                            temp[counter] = item;
                            counter++;
                        }
                        hashTable[i] = nullptr;
                    }
                    // RESET THE size
                    size = 0;
                    // AND NOW RE-PUT ALL THE VALUES
                    for (int i = 0; i < counter; i++) {
                        KeyValuePair *item = temp[i];
                        string keyToRehash = item->key;
                        S* valueToRehash = item->value;
                        putValue(keyToRehash, valueToRehash);
                        
                        // DELETE THE OLD KeyValuePair OBJECT SINCE putValue ADDS A NEW ONE
                        delete item;
                    }
                    // AND REMEMBER TO DELETE OUR TEMP ARRAY
                    delete temp;
                    return;
                }
                index++;
                // WE MAY NEED TO RESET index TO LOOK IN THE FRONT OF THE HASH TABLE
                if (index == length)
                    index = 0;
                count++;
            }            
        }

        // @todo - YOU MUST DEFINE THIS METHOD
        void putValue(string key, S* item) {
            int index = hashCode(key); // THIS IS THE NATURAL INDEX
            int count = 0;
            while (count < length) {
                KeyValuePair *testKVP = hashTable[index];
                // IF IT'S AVAILABLE, PUT IT HERE
                if (testKVP == nullptr) {
                    hashTable[index] = new KeyValuePair(key, item);
                    size++;
                    return;
                }
                // IF ANOTHER KVP ALREADY USES THIS KEY, REPLACE IT
                else if (testKVP->key.compare(key) == 0) {
                    hashTable[index]->value = item;
                    size++;
                    return;
                }
                index++;
                // WE MAY NEED TO RESET index TO LOOK IN THE FRONT OF THE HASH TABLE
                if (index == length)
                    index = 0;
                count++;
            }
            // WE DIDN'T FIND AN EMPTY SPOT OR AN ITEM WITH THE SAME
            // KEY SO WE NEED A BIGGER HASH TABLE. SO MAKE A BIGGER
            // ONE AND PUT ALL THE OLD VALUES IN THE NEW ONE
            KeyValuePair* *temp = hashTable;
            length = length*2;            
            this->hashTable = new KeyValuePair*[length];
            // FIRST CLEAR IT OUT
            for (int i = 0; i < length; i++) {
                this->hashTable[i] = nullptr;
            }
            // THEN MOVE ALL THE OLD VALUES OVER
            int numToCopy = size;
            size = 0;
            for (int i = 0; i < numToCopy; i++) {
                KeyValuePair *kvp = temp[i];
                string keyToMove = kvp->key;
                S* valueToMove = kvp->value;
                putValue(keyToMove, valueToMove);
                delete kvp;
            }
            delete temp;
            
            // AND REMEMBER TO ADD THE NEW ONE
            this->putValue(key, item);
        }
        
        // @todo - YOU MUST DEFINE THIS METHOD
        string toString() {
            stringstream ss;
            ss << "[" << endl;
            for (int i = 0; i < length; i++) {
                KeyValuePair *kvp = hashTable[i];
                string kvpDescription = "nullptr";
                if (kvp != nullptr)
                    kvpDescription = kvp->toString();
                ss << " " << i << ": " << kvpDescription << endl;
            }
            ss << "]" << endl;
            return ss.str();;
        }
};