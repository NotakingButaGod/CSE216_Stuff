template <class T>

class BinarySearchTree {

    // THIS INNER CLASS IS FOR OUR TREE NODES
    class Node {
        public:
            string key;
            T* data;
            Node *parent;
            Node *left;
            Node *right;
            
            Node(string initKey, T* initData, Node *initParent, Node *initLeft, Node *initRight) {
                key = initKey;
                data = initData;
                parent = initParent;
                left = initLeft;
                right = initRight;
            }
    };

    private:
        Node *root;
        int size;
        int keyLength;

    public:
        BinarySearchTree(int initKeyLength) {
            root = nullptr;
            size = 0;
            this->keyLength = initKeyLength;
        }

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

        int getSize() { 
            return this->size;
        }

        void putValueRecursively(string key, T* value, Node *testNode) {
            // DOES IT GO ON THE LEFT?
            if (key.compare(testNode->key) < 0) {
                if (testNode->left == nullptr) {
                    testNode->left = new Node(key, value, testNode, nullptr, nullptr);
                    size++;
                    return;
                }
                else {
                    putValueRecursively(key, value, testNode->left);
                }
            }
            else if (key.compare(testNode->key) == 0) {
                testNode->data = value;
                return;
            }
            else {
                if (testNode->right == nullptr) {
                    testNode->right = new Node(key, value, testNode, nullptr, nullptr);
                    size++;
                    return;
                }
                else {
                    putValueRecursively(key, value, testNode->right);
                }
            }
        }

        void putValue(string key, T* value) {
            // IF IT'S THE FIRST ONE MAKE IT THE ROOT
            if (root == nullptr) {
                root = new Node(key, value, nullptr, nullptr, nullptr);
                size++;
                return;
            }
            // ADD IT TO THE EXISTING TREE
            putValueRecursively(key, value, root);
        }

        T* getValueRecursively(string key, Node *testNode) {
            if (key.compare(testNode->key) < 0) {
                if (testNode->left == nullptr) {
                    return nullptr;
                }
                else {
                    return getValueRecursively(key, testNode->left);
                }
            }
            else if (key.compare(testNode->key) == 0) {
                return testNode->data;
            }
            else {
                if (testNode->right == nullptr) {
                    return nullptr;
                }
                else {
                    return getValueRecursively(key, testNode->right);
                }
            }
        }

        T* getValue(string key) {
            if (root == nullptr) {
                return nullptr;
            }
            else {
                return getValueRecursively(key, root);
            }
        }

        void removeValue(string key) {
            Node *traveller = root;
            bool found = false;
            while (!found) {
                cout << "key: " << key << ", traveller->key: " << traveller->key << endl;
                if (key.compare(traveller->key) == 0) {
                    // GET THE LARGEST ON THE LEFT, IS THERE IS A LEFT
                    if (traveller->left != nullptr) {
                        // FIND THE LARGEST
                        Node *largest = traveller->left;
                        while (largest->right != nullptr) {
                            largest = largest->right;
                        }
                        // AT THIS POINT largest MUST
                        // BE THE LARGEST ON THE LEFT
                        // BUT IT MIGHT BE ITS PARENT LEFT
                        // OR RIGHT NODE
                        
                        // FIRST MOVE THE key AND THE data
                        traveller->key = largest->key;
                        traveller->data = largest->data;
                        
                        // THEN FIX THE TREE, NOTE largest HAS NO RIGHT
                        // IF IT'S A LEAF WE DON'T CARE ABOUT ITS CHILDREN
                        // SO WE CAN JUST KEEP ITS LEFT
                        if (largest == largest->parent->left) {
                            largest->parent->left = largest->left;
                        }
                        else {
                            largest->parent->right = largest->left;
                        }
                        delete largest;
                    }
                    // OR THE SMALLEST ON THE RIGHT
                    else if (traveller->right != nullptr) {
                        // FIND THE SMALLEST
                        Node *smallest = traveller->right;
                        while (smallest->left != nullptr) {
                            smallest = smallest->left;
                        }
                        // AT THIS POINT Smallest MUST
                        // BE THE SMALLEST ON THE RIGHT
                        // BUT IT MIGHT BE ITS PARENT RIGHT
                        // OR LEFT NODE
                        
                        // FIRST MOVE THE key AND THE data
                        traveller->key = smallest->key;
                        traveller->data = smallest->data;
                        
                        // THEN FIX THE TREE
                        if (smallest == smallest->parent->right) {
                            smallest->parent->right = smallest->right;
                        }
                        else {
                            smallest->parent->left = smallest->right;
                        }
                        delete smallest;
                    }
                    // IT'S A LEAF
                    else {
                        // IT MIGHT BE THE ROOT (i.e. THE ONLY NODE)
                        if (traveller == root) {
                            delete root;
                            root = nullptr;
                        }
                        // IT MIGHT BE ON ITS PARENT'S LEFT
                        else if (traveller == traveller->parent->left) {
                            traveller->parent->left = nullptr;
                            delete traveller;
                        }
                        // OR ITS RIGHT
                        else {
                            traveller->parent->right = nullptr;
                            delete traveller;
                        }
                    }
                    size--;
                    found = true;
                }
                else if (key.compare(traveller->key) < 0) {
                    if (traveller->left == nullptr) {
                        return;
                    }
                    else {
                        traveller = traveller->left;
                    }
                }
                else {
                    if (traveller->right == nullptr) {
                        return;
                    }
                    else {
                        traveller = traveller->right;
                    }
                }
            }
        }

        void toStringRecursively(stringstream& ss, Node *traveller, int level) {
            if (traveller->left != nullptr) {
                toStringRecursively(ss, traveller->left, level+1);
            }
            for (int i = 0; i < level; i++) {
                ss << " ";
            }
            ss << traveller->data->toString() << endl;
            if (traveller->right != nullptr) {
                toStringRecursively(ss, traveller->right, level+1);
            }
        }

        // @todo - YOU MUST DEFINE THIS METHOD
        string toString() {
            stringstream ss;
            ss << endl << "Current Binary Search Tree:" << endl;
            toStringRecursively(ss, root, 0);
            return ss.str();
        }
};