#include <iostream>
#include <string>
#include "Map.h"

//added vector
#include <vector>

#include <cassert>

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
using namespace std;

using KeyType = std::string;
using ValueType = double;

#define COUNT 10


Map::Map() {
    this->root = nullptr;
};

Map::Map(const Map& copy) {
    Map::Node* temp = copy.root;
    this->root = new Map::Node(temp->key, temp->value);

    m_size = copy.m_size;

    copyNode(temp->right, this->root->right);
    copyNode(temp->left, this->root->left);
}

void Map::copyNode(Node* original, Node*& root) {
    if (original != nullptr) {
        root = new Node(original->key, original->value);
        copyNode(original->right, root->right);
        copyNode(original->left, root->left);
    }
};

Map::~Map() {
    deleteNodes(Map::root);
}

void Map::deleteNodes(Node* del) {
    if (del == nullptr) {
        return;
    }
    else {
        deleteNodes(del->left);
        deleteNodes(del->right);
        delete del;
    }

};

const Map& Map::operator=(const Map& rhs) {

    Map copy(rhs);

    return copy;
}

int Map::size() const {
    return m_size;
};

bool Map::empty() const {
    return m_size == 0;
};

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (this->contains(key)) {
        return false;
    }
    else if (root == nullptr) {
        root = new Node(key, value);
        this->m_size++;
        return true;
    }

    if (insertNode(root, key, value) != nullptr) {
        this->m_size++;
        return true;
    }
    return false;
}

Map::Node* Map::insertNode(Map::Node* root, const KeyType& key, const ValueType& value) {
    if (root == nullptr) return nullptr;

    if (root->key < key) {
        if (root->right == nullptr) {
            root->right = new Node(key, value);
            return root->right;
        }
        return insertNode(root->right, key, value);
    }
    if (root->key > key) {
        if (root->left == nullptr) {
            root->left = new Node(key, value);
            return root->left;
        }
        return insertNode(root->left, key, value);
    }
    else {
        return nullptr;
    }
};

bool Map::update(const KeyType& key, const ValueType& value) {
    if (!this->contains(key)) {
        return false;
    }

    return updateNode(this->root, key, value) != nullptr;
};

Map::Node* Map::updateNode(Map::Node* root, const KeyType& key, const ValueType& value) {
    if (root == nullptr) return nullptr;

    if (root->key == key) {
        root->value = value;
        return root;
    }
    else if (root->key < key) {
        return updateNode(root->right, key, value);
    }
    else if (root->key > key) {
        return updateNode(root->left, key, value);
    }
    else {
        return nullptr;
    }
    return nullptr;

};

bool Map::erase(const KeyType& key) {
    if (contains(key)) {
        Node* prevNode = nullptr;
        this->m_size--;
        return eraseNode(root, prevNode, key);
    }

    return false;
}

bool Map::eraseNode(Map::Node*& node, Map::Node*& prevNode, const KeyType& key) const {
    if (node == nullptr) return false;

    if (node->key == key) {
        if (node->left != nullptr) {
            Node* rightNode = node->right;
            node = node->left;
            if (rightNode == nullptr) {
                return true;
            }
            else {
                Node* temp = node;
                while (temp->right != nullptr) {
                    temp = temp->right;
                }
                temp->right = rightNode;
                return true;
            }
        }
        else if (node->right != nullptr) {
            node = node->right;
            return true;
        }
        node = nullptr;
        return true;

    }
    else if (node->key < key) {
        return eraseNode(node->right, node, key);
    }
    else if (node->key > key) {
        return eraseNode(node->left, node, key);
    }
    else {
        return false;
    }

    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (!this->contains(key)) {
        insertNode(root, key, value);
    }
    else {
        updateNode(root, key, value);
    }

    return true;
}

bool Map::contains(const KeyType& key) const {
    if (findNodeInTree(root, key) != nullptr) {
        return true;
    }
    else {
        return false;
    }
};

Map::Node* Map::findNodeInTree(Map::Node* node, const KeyType& key) const {
    if (node == nullptr) return nullptr;

    if (node->key < key) {
        return findNodeInTree(node->right, key);
    }
    else if (node->key > key) {
        return findNodeInTree(node->left, key);
    }
    else {
        return node;
    }
};

bool Map::get(const KeyType& key, ValueType& value) const {
    if (!contains(key)) {
        return false;
    }
    else {
        return getNode(root, key, value) != nullptr;
    }
}

Map::Node* Map::getNode(Node* root, const KeyType& key, ValueType& value) const {
    if (root == nullptr) return nullptr;

    if (root->key == key) {
        value = root->value;
        return root;
    }
    else if (root->key < key) {
        return getNode(root->right, key, value);
    }
    else if (root->key > key) {
        return getNode(root->left, key, value);
    }
    else {
        return nullptr;
    }


};

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i >= 0 && i < size()) {
        int iteration = 0;
        return getNode(i, iteration, root, key, value);
    }
    return false;
}

bool Map::getNode(int i, int& iteration, Node* root, KeyType& key, ValueType& value) const {
    if (root == nullptr) return false;

    if (getNode(i, iteration, root->left, key, value)) {
        return true;
    }

    if (i == iteration) {
        key = root->key;
        value = root->value;
        iteration++;
        return true;
    }
    iteration++;

    return getNode(i, iteration, root->right, key, value);

};

void Map::swap(Map& other) {
    Node* temp = root;
    int size1 = m_size;

    root = other.root;
    m_size = other.m_size;

    other.root = temp;
    other.m_size = size1;

};

bool combine(const Map& m1, const Map& m2, Map& result) {
    for (int n = 0; n < m1.size(); n++)
    {
        KeyType k;
        ValueType v;
        ValueType z;
        m1.get(n, k, v);
        m2.get(k, z);
        if (!(m2.contains(k) && z != v)) {
            result.insert(k, v);
        }
    }
    for (int n = 0; n < m2.size(); n++)
    {
        KeyType k;
        ValueType v;
        ValueType z;
        m2.get(n, k, v);
        m1.get(k, z);
        if (!(m1.contains(k) && z != v)) {
            result.insert(k, v);
        }
    }
    return true;
};

void subtract(const Map& m1, const Map& m2, Map& result) {
    for (int n = 0; n < m1.size(); n++)
    {
        KeyType k;
        ValueType v;
        ValueType z;
        m1.get(n, k, v);
        m2.get(k, z);
        if (!(m2.contains(k))) {
            result.insert(k, v);
        }
    }

};


int main() {
    Map m;
    m.insert("A", 10);
    m.insert("B", 44);
    m.insert("C", 10);
    string all;
    double total = 0;
    for (int n = 0; n < m.size(); n++)
    {
        string k;
        double v;
        m.get(n, k, v);
        all += k;
        total += v;
    }
    cout << all << total << endl;

    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v;
    string k1;
    assert(gpas.get(1, k1, v) && (k1 == "Fred" || k1 == "Ethel"));
    string k2;
    assert(gpas.get(1, k2, v) && k2 == k1);

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
        m2.size() == 1 && m2.contains("Fred"));

    Map gpas1;
    gpas1.insert("Fred", 2.956);
    assert(!gpas1.contains(""));
    gpas1.insert("Ethel", 3.538);
    gpas1.insert("", 4.000);
    gpas1.insert("Lucy", 2.956);
    assert(gpas1.contains(""));
    gpas1.erase("Fred");
    assert(gpas1.size() == 3 && gpas1.contains("Lucy") && gpas1.contains("Ethel") &&
        gpas1.contains(""));

    Map m3;
    assert(m3.insert("Fred", 123));
    assert(m3.insert("Ethel", 456));
    assert(m3.size() == 2);
    double d = 42;
    assert(m3.get("Fred", d) && d == 123);
    d = 42;
    string s1;
    assert(m3.get(0, s1, d) &&
        ((s1 == "Fred" && d == 123) || (s1 == "Ethel" && d == 456)));
    string s2;
    assert(m3.get(1, s2, d) && s1 != s2 &&
        ((s2 == "Fred" && d == 123) || (s2 == "Ethel" && d == 456)));
}

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
    "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
    "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=, Map & (Map::*)(const Map&));
    CHECKTYPE(&Map::empty, bool (Map::*)() const);
    CHECKTYPE(&Map::size, int  (Map::*)() const);
    CHECKTYPE(&Map::insert, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase, bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains, bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get, bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get, bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap, void (Map::*)(Map&));

    CHECKTYPE(combine, bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}