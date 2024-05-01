# Map Project

## Description

Create a Map utilizing a data structure of your choosing and be able to complete the functions given and ensure proper deallocation and allocation of memory for the created data structure.

The data structure used in this project is a Binary Tree and it implements multiple different functions that help with management like inserting and updating nodes.

Each Node comes with a key and a data value and using a template, can implement multiple types of data types. 

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
- [Destructor](#Destructor)
- [Copy Constructor](#Assignment-Operator)
  
</details>


---

## Description
The design I used for a map was through a binary tree with a struct root node within the class. The Struct Node had a KeyType and a ValueType variable with left and right nodes variables. These left and right nodes allowed for the ability to traverse the tree and be able to and used a binary tree. Finally, I have a constructor for the struct which allows me to create new Nodes if I needed to. For the Map Structure, I utilized a root node to store the first key and value of the binary tree which helped have a central root to then use to traverse the tree. I also use a variable m_size to store the size of the binary tree because it is important to know the size of the binary tree for functions like the get function and size function. The Nodes are ordered alphabetically where the left most node is the first word alphabetically and the rightmost node is the last word alphabetically. 

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

