#include "Map.h"

//Constructor
Map::Map() {
    this->root = nullptr; //sets root to nullptr
    m_size = 0;//sets size to 0;
};

//Copy Constructor
Map::Map(const Map& copy) {
    Map::Node* temp = copy.root;//Creates a temp to hold the copy root
    this->root = new Map::Node(temp->key, temp->value);
    //sets the current map root a new Node with the keys and values of the temp

    m_size = copy.m_size; // sets the size of the current map equal to the copy

    copyNode(temp->right, this->root->right); // recursively copys the right nodes of the copy
    copyNode(temp->left, this->root->left); // recursively copys the left nodes of the copy
}

//Helper Function of Copy Constructor
void Map::copyNode(Node* original, Node*& root) {
    if (original != nullptr) { // checks if the original node is the there and if not, end

        root = new Node(original->key, original->value); // create a copy of the node and sets it to the root

        copyNode(original->right, root->right); // recursively copys the right nodes of the copy

        copyNode(original->left, root->left); // recursively copys the left nodes of the copy
    }
};

//Destructor
Map::~Map() {
    deleteNodes(Map::root);//Rescursively Deletes Nodes from branch
}

void Map::deleteNodes(Node* del) {
    if (del == nullptr) { //Checks is del is nullptr
        return; // return nothing and continues program.
    }
    else {
        deleteNodes(del->left);//Recursively Deletes the Nodes in the left branch

        deleteNodes(del->right);//Recursively Deletes the Nodes in the right branch

        delete del; // deletes node
    }
    m_size = 0;

};


//Operator = 
const Map& Map::operator=(const Map& rhs) {

    if (this->root != nullptr) { // Checks if root is exists and if it does, delete the nodes and 
        deleteNodes(this->root);
        copyNode(rhs.root, this->root);
        this->m_size = rhs.m_size;
        return *this;
    }

    copyNode(rhs.root, this->root);
    this->m_size = rhs.m_size;

    return *this;
}

//Returns the size of the Map
int Map::size() const {
    return m_size;
};

//Returns if the map is empty
bool Map::empty() const {
    return m_size == 0;
};

//Inserts Node
bool Map::insert(const KeyType& key, const ValueType& value) {
    if (this->contains(key)) { // Checks if the map contains the key and if so, return false
        return false;
    }
    else if (root == nullptr) { //Checks if root is nullprt and creates a new node and sets to root and increases size
        root = new Node(key, value);
        this->m_size++;
        return true;
    }

    if (insertNode(root, key, value) != nullptr) { // Inserts Node and checks if the addition does not equal nullptr and if so, incrase size and return true;
        this->m_size++;
        return true;
    }
    return false;
}

//Recursively insert Node
Map::Node* Map::insertNode(Map::Node* node, const KeyType& key, const ValueType& value) {
    if (node == nullptr) return nullptr;

    if (node->key < key) { // Moves down the right of the tree
        if (node->right == nullptr) { // checks if right it null and if so, add node
            node->right = new Node(key, value);
            return node->right;
        }
        return insertNode(node->right, key, value); //other wise continuing adding
    }
    else if (node->key > key) { // Moves down the left of the tree
        if (node->left == nullptr) { // checks if right it null and if so, add node
            node->left = new Node(key, value);
            return node->left;
        }
        return insertNode(node->left, key, value);//other wise continue inserting
    }
    else {
        return nullptr; // other wise, return nullptr
    }
};

//Updates the Value
bool Map::update(const KeyType& key, const ValueType& value) {
    if (!this->contains(key)) { //Checks if key exists in map and if not, return false;
        return false;
    }

    return updateNode(this->root, key, value) != nullptr; // recursively update and returns true when updated node returns
};

//Recursively Update Function
Map::Node* Map::updateNode(Map::Node* root, const KeyType& key, const ValueType& value) {
    if (root == nullptr) return nullptr; // if root is null, return nullptr;

    if (root->key == key) { // if the key is equal to the key you are searching for, set node value to value;
        root->value = value;
        return root;
    }
    else if (root->key < key) { // Move Right Recursively
        return updateNode(root->right, key, value);
    }
    else if (root->key > key) { // Move Left Recursively
        return updateNode(root->left, key, value);
    }
    else {
        return nullptr; // Otherwise, return nullptr
    }
    return nullptr;

};

//Erase function
bool Map::erase(const KeyType& key) {
    if (contains(key)) { // Checks if the key is in the Map and if so, recursively erase from map
        this->m_size--;
        return eraseNode(root, key);
    }

    return false;
}

//Recursively Erase Function
bool Map::eraseNode(Map::Node*& node, const KeyType& key) const {
    if (node == nullptr) return false; // Checks if node is there and return nullptr if it does not

    if (node->key == key) { // if the node key equals the key, point all nodes back correctly
        if (node->left != nullptr) { // if node left exists, move left node to node
            Node* rightNode = node->right;
            node = node->left;
            if (rightNode == nullptr) { // if right node does not exist, return true;
                return true;
            }
            else {
                Node* temp = node;
                while (temp->right != nullptr) { // check where the right most node is for temp and set the right to the rightNode
                    temp = temp->right;
                }
                temp->right = rightNode;
                return true;
            }
        }
        else if (node->right != nullptr) { // Check if right node exists and if so, set the current node to the right node
            node = node->right;
            return true;
        }
        node = nullptr;
        return true;

    }
    else if (node->key < key) { //recursively check the right branch to erase
        return eraseNode(node->right, key);
    }
    else if (node->key > key) { //recursively check the left branch to erase
        return eraseNode(node->left, key);
    }
    else {
        return false; //Otherwise return false;
    }

    return false;
}

//Insert or Update
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (!this->contains(key)) { //Checks if the map contains the key 
        insertNode(root, key, value); //inserts node
    }
    else {
        updateNode(root, key, value); // update node
    }

    return true; // Always return true
}

//Checks if map contains
bool Map::contains(const KeyType& key) const {
    if (findNodeInTree(root, key) != nullptr) { // Checks if the recursive findNodeInTree function gives back node with same key
        return true;
    }
    else {
        return false;
    }
};

//Recursively FindNodeInTree
Map::Node* Map::findNodeInTree(Map::Node* node, const KeyType& key) const {
    if (node == nullptr) return nullptr; // Checks if node is there and return nullptr if it does not

    if (node->key < key) { //Recursively Check to find node right
        return findNodeInTree(node->right, key);
    }
    else if (node->key > key) { // Recursively Check to find node left
        return findNodeInTree(node->left, key);
    }
    else { // Otherwise, return the node that exists as it only returns node when node->key == key
        return node;
    }

    return nullptr;
};

//Get Function
bool Map::get(const KeyType& key, ValueType& value) const {
    if (!contains(key)) { // Checks if the key does not exist and return false when it does
        return false;
    }
    else {
        return getNode(root, key, value) != nullptr; // Recursively gets the node and checks if the node exists
    }
}

Map::Node* Map::getNode(Node* node, const KeyType& key, ValueType& value) const {
    if (node == nullptr) return nullptr; // Checks if node is there and return nullptr if it does not

    if (node->key == key) { // Checks if the node key equals the key we are looking for
        value = node->value; // sets the value to the node value
        return node;
    }
    else if (node->key < key) { // Goes down the right branch and tries to get node down the branch
        return getNode(node->right, key, value);
    }
    else if (node->key > key) { // Goes down the left branch and tries to get node down the branch
        return getNode(node->left, key, value);
    }
    else {
        return nullptr; //Otherwise, return nullptr
    }


};

//Get Function with i
bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i >= 0 && i < size()) { // Checks if i is within the size of the map
        int iteration = 0; //sets iteration equal to zero
        return getNode(i, iteration, root, key, value); // Recursively checks if the node is there
    }
    return false;
}

//Recursive Get Function with i
bool Map::getNode(int i, int& iteration, Node* node, KeyType& key, ValueType& value) const {
    if (node == nullptr) return false; // Checks if node is there and return nullptr if it does not

    if (getNode(i, iteration, node->left, key, value)) { // Go down left branch until reach hits the i value for the iteration
        return true;
    }

    if (i == iteration) { // Checks if the iteration equals the i value
        key = node->key; //Sets key reference in function to node key 
        value = node->value; //Sets value reference in function to node value
        return true;
    }
    iteration++;

    //increase iteration

    return getNode(i, iteration, node->right, key, value); //Look down the right branch recursively

};

//Swap Function
void Map::swap(Map& other) {
    Node* temp = root;// Create a temp to store the current root
    int size1 = m_size; //Create a int variable to store size

    root = other.root; // Set the current root to the other roo
    m_size = other.m_size; //set current map size to other map size

    other.root = temp; // Set other root to the temp
    other.m_size = size1; // Set the other map size to the current size

};

//Combine Function
bool combine(const Map& m1, const Map& m2, Map& result) {
    for (int n = 0; n < m1.size(); n++) // Loop through Map 1
    {
        //Create variables to store keytypes and valuetypes
        KeyType k;
        ValueType v;
        ValueType z;

        m1.get(n, k, v);//Get the values for each member in Map 1
        m2.get(k, z); // Get the value for member with same key from Map 1 in Map 2
        if (!(m2.contains(k) && z != v)) { // Checks if there does not exist a key in Map 2 and the values do not equal each other 
            result.insert(k, v); // insert key and values from Map 1 in result
        }
    }
    for (int n = 0; n < m2.size(); n++) //Loop through Map 2
    {
        //Create variables to store keytypes and valuetypes
        KeyType k;
        ValueType v;
        ValueType z;

        m2.get(n, k, v);//Get the values for each member in Map 2
        m1.get(k, z);// Get the value for member with same key from Map 2 in Map 1

        if (!(m1.contains(k) && z != v)) {// Checks if there does not exist a key in Map 1 and the values do not equal each other 

            result.insert(k, v);// insert key and values from Map 2 in result
        }
    }
    return true; // return true
};

//Subtract Function
void subtract(const Map& m1, const Map& m2, Map& result) {
    for (int n = 0; n < m1.size(); n++) // Loops through Map 1
    {
        //Create variables to store keytypes and valuetypes
        KeyType k;
        ValueType v;
        ValueType z;

        m1.get(n, k, v); //Get values and key for each member in Map 1
        m2.get(k, z); // Gets value for each member Map 2

        if (!(m2.contains(k))) { //Check if the key does not exists in Map 2
            result.insert(k, v); // Inserts key and values from Map 1
        }
    }

};

int main() {

}