# Map Project

## Description

Create a Map utilizing a data structure of your choosing and be able to complete the functions given and ensure proper deallocation and allocation of memory for the created data structure.

The data structure used in this project is a Binary Tree and it implements multiple different functions that help with management like inserting and updating nodes.

Each Node comes with a key and a data value and using a template, can implement multiple types of data types. 

## Table of Contents:

- [Contribution guidelines for this project](#constructor)
- [Copy Constructor](#copy-constructor)

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
        deleteNodes(del->left);//Recursively Deletes the Nodes in the left branch

        deleteNodes(del->right);//Recursively Deletes the Nodes in the right branch

        delete del; // deletes node
    }
    m_size = 0;

};
```
