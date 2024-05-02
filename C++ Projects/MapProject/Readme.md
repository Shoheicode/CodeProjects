# Map Project

## Table of Contents:

<details>
  <summary>Project Overview</summary>
  
- [Project Description](#description)
- [Project Obstacles](#obstacles)
- [Test Cases](#test-cases)
- [Pseudocode](#pseudocode)
  
</details>

<details>
  <summary>Constructor/Destructor/Assignment Operator</summary>

- [Constructor](#constructor)
- [Copy Constructor](#copy-constructor)
- [Destructor](#destructor)
- [Assignment Operator](#assignment-operator)
  
</details>

<details>
  <summary>Inserting and Deleting Nodes</summary>

- [Size](#size)
- [Empty](#empty)
- [Insert](#insert)
- [Erase](#erase)
  
</details>

<details>
  <summary>Update Node and InsertOrUpdate</summary>

- [Update](#update)
- [Insert Or Update](#insert-or-update)
  
</details>

<details>
  <summary>Contains and Get</summary>

- [Contains](#constructor)
- [Get with key](#get-with-key)
- [Get with index](#get-with-index)
  
</details>

<details>
  <summary>Combine/Swap/Subtract</summary>

- [Swap](#swap)
- [Combine](#combine)
- [Subtract](#subtract)
  
</details>

---

## Description
The design I used for a map was through a binary tree with a struct root node within the class. The Struct Node had a KeyType and a ValueType variable with left and right nodes variables. These left and right nodes allowed for the ability to traverse the tree and be able to and used a binary tree. Finally, I have a constructor for the struct which allows me to create new Nodes if I needed to. For the Map Structure, I utilized a root node to store the first key and value of the binary tree which helped have a central root to then use to traverse the tree. I also use a variable m_size to store the size of the binary tree because it is important to know the size of the binary tree for functions like the get function and size function. The Nodes are ordered alphabetically where the left most node is the first word alphabetically and the rightmost node is the last word alphabetically.

Create a Map utilizing a data structure of your choosing and be able to complete the functions given and ensure proper deallocation and allocation of memory for the created data structure.

The data structure used in this project is a Binary Tree and it implements multiple different functions that help with management like inserting and updating nodes.

Each Node comes with a key and a data value and using a template, can implement multiple types of data types. 

## Obstacles:
Some of the obstacles I had to overcome was learning how to delete nodes in a deconstructor as I had to learn how to delete a node after I ran the recursive function. I figured out how to delete the node using a recursive function which helps transverse the node and wrote it so that after it transverse to the end of the binary tree, it would delete each node.  Another obstacle I had to overcome was the obstacle of using recursive functions more as I was a bit unfamiliar with utilizing them but through this project, I was able to utilize them and implement them into the binary tree. Finally, I think I had some obstacles with the copy constructor and using the constructor but I created a helper function which helped recursively copy each node. 

## Test cases: 
### Case 1:
```
Map m;

assert(m.empty()); //Asserts Map is empty
assert(m.insert("Fred", 1)); // Asserts you added Fred
assert(m.insert("Ethel", 4)); //Asserts you added Ethel

double d;
assert(m.get(“Fred”, d) && d == 1);
assert(m.get(“Ethel”, d) && d == 4);
assert(!m.insert("Ethel", 456)); //Asserts you can't add Ethel
assert(!m.empty()); // Asserts the map is empty.
```

### Case 2:
```
Map m;

assert(m.insert("James", 123)); // Asserts you added James
assert(m.insert("Johns", 456)); //Asserts you added Johns

Map m1(m); // Copy Constructor test

double d;
assert(m.size() == m1.size()); // Checked the size
assert(m1.get("James", d) && d == 123); // Checks if there is a node James and if it has the same value 
assert(m1.get("Johns", d) && d == 456); // Checks if there is a node Johns and if it has the same value 
```

### Case 3:
```
Map m;

assert(m.insert("Junior", 123)); // Asserts you added Junior
assert(m.insert("Abraham", 456)); //Asserts you added Abraham
assert(m.erase("Abraham")); //Assert you erased Abraham

Map m1;
m1 = m; // Equal Operator

double d;
assert(m.size() == m1.size()); // Check the size
assert(m1.insert(“whooo”, 12); // Assert that you inserted “whooo” with value 12.
assert(m.size() != m1.size()); // Check the size and they should not be equal.
assert(m1.get("Junior", d) && d == 123); // Checks if there is a node James and if it has the same value 
assert(!m1.get("Abraham", d) && d != 456); // Checks if there is not a node Abraham and if it does not have a value equal to 456 
assert(!m.get(“whooo”, d));
```

### Case 4:
```
Map m;

assert(m.insert("Junior", 123)); // Asserts you added Junior
assert(m.insert("Abraham", 456)); //Asserts you added Abraham
assert(m.erase("Abraham")); //Assert you erased Abraham
assert(m.erase("Junior")); //Asserts you erased Junior

assert(m.size() == 0);      // Asserts that the map size is 0
assert(m.empty());          // Asserts that the map is empty
assert(!m.erase("John"));  // Confirms that there is nothing that can be erased
```

### Case 5:
```
Map m;

assert(m.insert("Johnny", 123)); // Asserts you added Johnny
assert(m.insert("Rebecca", 456)); //Asserts you added Rebecca
assert(m.insert("D", 26)); //Asserts you added D
assert(m.insert("A", 46)); // Asserts you added A
assert(m.insert("C", 45)); // Asserts you added C

assert(m.update("Rebecca", 100)); // Updates value for Key Rebecca
assert(!m.update("James", 100)); // Asserts you can’t update James cause James is not part of the Map

double d;
assert(m.size() == 5);      // Asserts that the map size does not equal is 0
assert(m.get("Rebecca", d) && d == 100); // Asserts that you can get Rebecca and that d equals the new updated Value
```

### Case 6:
```
Map m;

assert(m.insert("Johnny", 123)); // Asserts you added Johnny
assert(m.insert("Rebecca", 456)); //Asserts you added Rebecca
assert(m.insert("Fully", 134)); //Asserts you added Fully

assert(m.insertOrUpdate("JAMES", 655)); // Insert or Update but in this case insert James

double d;
assert(m.size() == 4);      // Asserts that the map size does not equal is 0
assert(m.get("Fully", d) && d == 134); // Asserts nodes James Exists and that its value is 134
assert(m.get("JAMES", d) && d == 655); // Asserts that you can get JAMES and that d equals 655
```

### Case 7:
```
Map m;

assert(m.insert("Johnny", 123)); // Asserts you added Johnny
assert(m.insert("Rebel", 456)); //Asserts you added Rebel
assert(m.insert("Fully", 134)); // Asserts you added Fully
assert(m.insert("JustKen", 14)); // Asserts you added JustKen

assert(m.insertOrUpdate("Rebel", 544)); // Insert or Update but in this case updates Rebel to 544
assert(m.insertOrUpdate("JustKen", 165)); // Insert or Update but in this case updates JustKen to 165

double d;
assert(m.size() == 4);      // Asserts that the map size does not equal is 0
assert(m.get("Rebel", d) && d == 544); // Asserts nodes Rebel Exists and that its value is 544
assert(m.get("JustKen", d) && d == 165); // Asserts that you can get JustKen and that d equals the new updated Value
```

### Case 8:
```
Map m;

assert(m.insert("Curse", 1)); // Asserts you added Curse
assert(m.insert("you", 2));  // Asserts you added you
assert(m.insert("Perry", 3)); // Asserts you added Perry
assert(m.insert("the", 4)); //Asserts you added the
assert(m.insert("Platypus", 5)); // Asserts you added Platypus

assert(!m.contains("James")); // Checks if the map contains Hailey

//For loop that runs to get each individual node based on value i
string all;
double total = 0;
for (int n = 0; n < m.size(); n++)
{
    string k;
    double v;
    m.get(n, k, v);
    if (v == 5) {
        v = 10;
    }
    if (k == "Perry") {
        k = "you";
    }
    else if (k == "you") {
        k = "Platypus";
    }
    else if (k == "Platypus") {
        k = "Perry";
    }
    all += k + " ";
    total += v;
}
cout << all;

//Asserts that the statement and total value comes out to "Curse you Perry the Platypus " and 20.
assert(all == "Curse you Perry the Platypus ");
assert(total == 20);
```

### Case 9:
```
Map m;

assert(m.insert("June", 123)); // Asserts you added June
assert(m.insert("Quincy", 456)); //Asserts you added Quincy
assert(m.insert("Annie", 200)); //Assert you erased Annie

Map m1;
assert(m1.insert("Jae", 123)); // Asserts you added Jae
assert(m1.insert("Jona", 456)); //Asserts you added Jona
assert(m1.insert("Jameson", 100)); //Assert you added Jameson

m.swap(m1); //Runs Swap Function, exchanging elements

//Checks the first Map (m) to see if elements match the one in m1
double d;
assert(m.get("Jae", d) && d == 123);
assert(m.get("Jona", d) && d == 456);
assert(m.get("Jameson", d) && d == 100);
assert(!m.get("Junior", d));

//Checks the second Map (m1) to see if elements match the one in m
assert(m1.get("June", d) && d == 123);
assert(m1.get("Quincy", d) && d == 456);
assert(m1.get("Annie", d) && d == 200);
assert(!m1.get("Jae", d));
```

### Case 10:
```
Map m;

assert(m.insert("A", 123)); // Asserts you added A
assert(m.insert("B", 456)); //Asserts you added B
assert(m.insert("C", 200)); //Assert you erased C

Map m1;
assert(m1.insert("D", 123)); // Asserts you added D
assert(m1.insert("E", 456)); //Asserts you added E
assert(m1.insert("B", 456)); // Asserts you added B
assert(m1.insert("C", 111)); // Asserts you added C


Map result;

combine(m, m1, result); // Combine Function runs to combine the 2 maps

assert(result.contains("A")); // Asserts that the result of the combine contains A
assert(result.contains("B"));   // Asserts that the result of the combine contains B
assert(result.contains("D"));  // Asserts that the result of the combine contains D
assert(result.contains("E"));  // Asserts that the result of the combine contains E
assert(!result.contains("C"));  // Asserts that the result of the combine contains C

double d;
assert(result.get("A", d) && d == 123); //Asserts that result has node with key A and value 123
assert(result.get("B", d) && d == 456); //Asserts that result has node with key B and value 456
assert(result.get("D", d) && d == 123); //Asserts that result has node with key D and value 123
assert(result.get("E", d) && d == 456); //Asserts that result has node with key E and value 456
```

### Case 11:
```
Map m;

assert(m.insert("F", 123)); // Asserts you added F into map m
assert(m.insert("G", 456)); //Asserts you added G into map m
assert(m.insert("H", 200)); //Assert you added H into map m
assert(m.insert("L", 456)); //Assert you added L into map m

Map m1;
assert(m1.insert("P", 123)); // Assert you inserted P into map m1
assert(m1.insert("H", 456));  // Assert you inserted H into map m1
assert(m1.insert("G", 111)); // Assert you inserted G into map m1

Map result;

subtract(m, m1, result); //Subtracts m1 from m

assert(result.contains("F")); // Checks if results has node F
assert(result.contains("L")); // Checks if results has node L
assert(!result.contains("P")); // Checks if results does not has node P
assert(!result.contains("G")); // Checks if results does not has node G
assert(!result.contains("H")); // Checks if results does not has node H

double d;
assert(result.get("F", d) && d == 123); // Asserts node F exists and that its value is 123
assert(result.get("L", d) && d == 456); // Asserts node L exists and that its value is 456

```


## Pseudocode: 
```
Subtract function:
subtract function (Map1, Map2, resultMap)
	For each element in Map1
		Create KeyType variable A, ValueType variable B, and ValueType variable C
		Get values from Map1 and assign to A and B
		Get value from Map2 and assign it to C
		if Map2 does not contain the KeyType A
			Insert Node with KeyType A and ValueType B into resultMap

Erase function:
erase function (key)
	if the map contains the key
		Decrease the size of the map by 1
		Recursively check to delete node with the root and key as arguments
			Check if the root is non existent and if so, return false
			
			if the node key equals the key in the parameters
				if the node left does exist
					Create a temp that stores node data
					Set the node to the left node
					Delete temp that stores node data
					if the right node does not exist, return true;
					Otherwise, attach the right node to the rightmost node of node
					return true
			Else if right node does exist, 
Create a temp that stores node data
set the node to the right node 
				Delete temp that stores node data
return true
			Else if the node key is less than the current key, 
return the recursive function with the arguments the right node and the key
			Else if the node key is greater than the current key, 
return the recursive function with the arguments the left node and the key
			Otherwise, return false
			
	return false
```

---
---

## Constructor:

```
Map::Map() {
    this->root = nullptr; //sets root to nullptr
    m_size = 0;//sets size to 0;
};
```

## Copy Constructor

```
Map::Map(const Map& copy) {
    Map::Node* temp = copy.root;//Creates a temp to hold the copy root
    this->root = new Map::Node(temp->key, temp->value);
    //sets the current map root a new Node with the keys and values of the temp

    m_size = copy.m_size; // sets the size of the current map equal to the copy

    copyNode(temp->right, this->root->right); // recursively copys the right nodes of the copy
    copyNode(temp->left, this->root->left); // recursively copys the left nodes of the copy
}

//Helper function for Copy Constructor
void Map::copyNode(Node* original, Node*& root) {
    if (original != nullptr) { // checks if the original node is the there and if not, end

        root = new Node(original->key, original->value); // create a copy of the node and sets it to the root

        copyNode(original->right, root->right); // recursively copys the right nodes of the copy

        copyNode(original->left, root->left); // recursively copys the left nodes of the copy
    }
};
```

## Destructor 
```
Map::~Map() {
    deleteNodes(Map::root);//Rescursively Deletes Nodes from branch
}

//Helper Function for destructor
void Map::deleteNodes(Node* del) {
    if (del == nullptr) { //Checks is del is nullptr
        return; // return nothing and continues program.
    }
    else {
        deleteNodes(del->left); //Recursively Deletes the Nodes in the left branch

        deleteNodes(del->right); //Recursively Deletes the Nodes in the right branch

        delete del; // deletes node
    }
    m_size = 0;

};
```
## Assignment Operator
```
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
```

---
---

## Size

```
int Map::size() const {
    return m_size;
};
```

## Empty
```
bool Map::empty() const {
    return m_size == 0;
};
```

## Insert
```
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
```

## Erase
```
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
            Node* tem = node;
            Node* rightNode = node->right;
            node = node->left;
            delete tem;
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
            Node* tem = node;
            node = node->right;
            delete tem;
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
```

---
---

## Update
```
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

```

## Insert or Update
```
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (!this->contains(key)) { //Checks if the map contains the key 
        insertNode(root, key, value); //inserts node
    }
    else {
        updateNode(root, key, value); // update node
    }

    return true; // Always return true
}
```
---
--- 

## Contains
```
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
```

## Get with Key
```
bool Map::get(const KeyType& key, ValueType& value) const {
    if (!contains(key)) { // Checks if the key does not exist and return false when it does
        return false;
    }
    else {
        return getNode(root, key, value) != nullptr; // Recursively gets the node and checks if the node exists
    }
};

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
```


## Get with Index
```
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
```


---
---

## Swap
```
void Map::swap(Map& other) {
    Node* temp = root;// Create a temp to store the current root
    int size1 = m_size; //Create a int variable to store size

    root = other.root; // Set the current root to the other roo
    m_size = other.m_size; //set current map size to other map size

    other.root = temp; // Set other root to the temp
    other.m_size = size1; // Set the other map size to the current size

};
```

## Combine
```
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
```

## Subtract
```
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
```
