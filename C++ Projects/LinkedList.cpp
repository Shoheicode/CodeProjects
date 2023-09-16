#include <iostream>
#include <string>

//added vector
#include <vector>

#include <cassert>
 
// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
using namespace std;
        
using ItemType = string;
        
struct Node {
    ItemType value;
    Node *next;
    Node(ItemType a, Node* newNode = nullptr){
      value = a;
      next = newNode;
    }
};
        
class LinkedList {
            
private:
    Node *head;
    
public:
    
      // default constructor
    LinkedList() : head(nullptr) { }
    
      // copy constructor
    LinkedList(const LinkedList& rhs){
      this->head = nullptr;

      Node* temp = rhs.head;
      Node* copyHead = this->head;

      while(temp != nullptr){
        Node* newNode = new Node(temp->value);

        if(copyHead == nullptr){
          this->head = newNode;
          copyHead = this->head;
        }
        else{
          copyHead->next = newNode;
          copyHead = copyHead->next;
          
        }
        temp = temp->next;
      }
    }
    
      // Destroys all the dynamically allocated memory
      // in the list.
    ~LinkedList(){

    };
    
      // assignment operator
    const LinkedList& operator=(const LinkedList& rhs){
      LinkedList li(rhs);

      this->head = li.head;

      return *this;
    }
    
      // Inserts val at the front of the list
    void insertToFront(const ItemType &val){
        
        if(head != nullptr){
          Node* newHead = new Node(val, this->head);
          this->head = newHead;
          
        }
        else{
          this->head = new Node(val);
          
        }
    };
    
      // Prints the LinkedList
    void printList() const{
      //cout << "List" << endl;
      Node* current = head;
      while(current != nullptr){
        cout << current->value << endl;
        current = current->next;
      }
    }
    
      // Sets item to the value at position i in this
      // LinkedList and return true, returns false if 
      // there is no element i
    bool get(int i, ItemType& item) const{
      int c = 0;
      Node* current = head;
      while(current != nullptr){
        if(c == i){
          item = current->value;
          return true;
        }
        current = current->next;
        c++;
      }
      return false;

    }
    
      // Reverses the LinkedList
    void reverseList(){
      vector<ItemType> x;
      Node* current = head;
      while(current != nullptr){
        x.push_back(current->value);
        current = current->next;
      }
      this->head = new Node(x.at(0));
      for(int i = 1; i < x.size(); i++){
        Node* newHead = new Node(x.at(i), this->head);
        this->head = newHead;
      }
      //Taken
      
    }
    
      // Prints the LinkedList in reverse order
    void printReverse() const{
      vector<ItemType> x;
      Node* current = head;
      while(current != nullptr){
        x.push_back(current->value);
        current = current->next;
      }
      for(int i = x.size()-1; i >= 0; i-=1){
        cout << x.at(i) << endl;
      }

      //Recursion (Private member function)
    }
    
      // Appends the values of other onto the end of this
      // LinkedList.
    void append(const LinkedList &other){
      Node* current = this->head;
      while(current->next != nullptr){
        cout << current->value << endl;
        current = current->next;
      }
      cout << current->value << endl;
      Node* curr = other.head;
      //cout << curr->value << endl;
      int size = other.size();
      for(int i = 0; i < size; i++){
        current->next = new Node(curr->value);
        curr = curr->next;
        current = current->next;
      }
      
      //The Copy Swap Idiom
    }
    
      // Exchange the contents of this LinkedList with the other one.
    void swap(LinkedList &other){
      Node* temp = other.head;
      
      other.head = this->head;
      this->head = temp;

    }
    
      // Returns the number of items in the Linked List.
    int size() const{
      int i = 0;
      Node* current = head;
      while(current != nullptr){
        current = current->next;
        i++;
      }
      return i;
    }

};

int main(){
    // LinkedList ls;

    // ls.insertToFront("George");
    // ls.insertToFront("Louise");
    // ls.insertToFront("Lionel");
    // ls.insertToFront("Helen");

    // cout << "I AM RUNNING LIST" << endl;
    // for (int k = 0; k < ls.size(); k++)
    // {
    //     string x;
    //     ls.get(k, x);
    //     cout << x << endl;
    // }

    // cout <<"PRINTING LIST" << endl;
    // ls.printList();
    // cout <<"Reverse PRINTING LIST" << endl;
    // ls.printReverse();

    // LinkedList e1;
    // e1.insertToFront("bell");
    // e1.insertToFront("biv");
    // e1.insertToFront("devoe");
    // e1.printList();
    // LinkedList e2;
    // e2.insertToFront("Andre");
    // e2.insertToFront("Big Boi");
    // e2.printList();
    // e1.append(e2);  // adds contents of e2 to the end of e1
    // cout<<"Print new list" << endl;
    // e1.printList();
    // cout <<"RUNNING ASSERT" << endl;
    // string s;
    // assert(e1.size() == 5  &&  e1.get(3, s)  &&  s == "Big Boi");
    // assert(e2.size() == 2  &&  e2.get(1, s)  &&  s == "Andre");
    // cout << "CREATING THIRD LIST" << endl;
    // LinkedList e3;
    // e3.insertToFront("Rare Essence");
    // e3.insertToFront("JunkYard");
    // e3.insertToFront("Chuck Brown");
    // e3.append(e3);
    // e3.printList();
    // assert(e3.size() == 6  &&  e3.get(3, s)  &&  s == "Chuck Brown");

    // LinkedList e4;
    // e4.insertToFront("Sam");
    // e4.insertToFront("Carla");
    // e4.insertToFront("Cliff");
    // e4.insertToFront("Norm");

    // e4.reverseList();  // reverses the contents of e4
    // string s;
    // e4.printList();
    // assert(e4.size() == 4  &&  e4.get(0, s)  &&  s == "Sam");

    LinkedList e1;
    e1.insertToFront("A");
    e1.insertToFront("B");
    e1.insertToFront("C");
    e1.insertToFront("D");
    LinkedList e2;
    e2.insertToFront("X");
    e2.insertToFront("Y");
    e2.insertToFront("Z");
    //e1.swap(e2);  // exchange contents of e1 and e2
    cout << "HI" << endl;
    string s;
    // assert(e1.size() == 3  &&  e1.get(0, s)  &&  s == "Z");
    // assert(e2.size() == 4  &&  e2.get(2, s)  &&  s == "B");
    e1.printList();
    // e2.printList();

    // LinkedList e3(e2);
    // e2.insertToFront("HI");
    // cout << "First list" << endl;
    // e2.printList();
    // cout << "Second list" << endl;
    // e3.printList();
    // e2.printList();

    e1 = e2;
    e1.printList();

    float a = 5.51;
    int b = static_cast<int>(a);
    cout << b;

}