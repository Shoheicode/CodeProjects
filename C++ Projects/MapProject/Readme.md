# Map Project

## Table of Contents:

<details>
  <summary>Project Overview</summary>
  
- [Project Description](#description)
- [Project Obstacles](#obstacles)
  
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

## Insert or Update

---
--- 

## Contains

## Get with Key

## Get with Index

---
---

## Swap

## Combine

## Subtract
