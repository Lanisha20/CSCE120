#include <iostream>
#include <sstream>
#include <limits>
#include "functions.h"
#include <stdexcept>

using std::cout, std::cin, std::endl, std::exception, std::invalid_argument; 
using std::getline, std::string;

int mapping (string loc) {
            int num = 0;
            if (loc == "Boston") num = 1;
            else if (loc == "Hartford") num = 2;
            else if (loc == "NewYork") num = 3;
            else if (loc == "Philadelphia") num = 4;
            else if (loc == "Baltimore") num = 5;
            else if (loc == "WashingtonDC") num = 6;
            else if (loc == "Pittsburgh") num = 7;
            else if (loc == "Cleveland") num = 8;
            else if (loc == "Detroit") num = 9;
            else if (loc == "Chicago") num = 10;
            else if (loc == "Indianapolis") num = 11;
            else if (loc == "Nashville") num = 12;
            else if (loc == "Atlanta") num = 13;
            else if (loc == "Houston") num = 14;
            else if (loc == "Austin") num = 15;
            else if (loc == "Dallas") num = 16;
            else if (loc == "Denver") num = 17;
            else if (loc == "Albuquerque") num = 18;
            else if (loc == "Phoenix") num = 19;
            else if (loc == "Sacramento") num = 20;
            else {
                try { throw invalid_argument("Undefined location"); } 
                catch (std::invalid_argument const& e) { cout << e.what() << endl; } 
            }
            return num;
}

string rev_mapping (int num) {
            string loc;
            switch (num)
            {
            case 1: { loc = "Boston"; break; }
            case 2: { loc = "Hartford"; break; }
            case 3: { loc = "NewYork"; break; }
            case 4: { loc = "Philadelphia"; break; } 
            case 5: { loc = "Baltimore"; break; }
            case 6: { loc = "WashingtonDC"; break; }
            case 7: { loc = "Pittsburgh"; break; }
            case 8: { loc = "Cleveland"; break ; }
            case 9: { loc = "Detroit"; break; }
            case 10: { loc = "Chicago"; break; }
            case 11: { loc = "Indianapolis"; break; }
            case 12: { loc = "Nashville"; break; }
            case 13: { loc = "Atlanta"; break; }
            case 14: { loc = "Houston"; break; }
            case 15: { loc = "Austin"; break; }
            case 16: { loc = "Dallas"; break; }
            case 17: { loc = "Denver"; break; }
            case 18: { loc = "Albuquerque"; break; }
            case 19: { loc = "Phoenix"; break; }
            case 20: { loc = "Sacramento"; break; }
            default: { loc = "undefined"; break;}
            }            
            if (loc == "undefined") {
                try { throw invalid_argument("Undefined location"); } 
                catch (std::invalid_argument const& e) { cout << e.what() << endl; } 
            }
            return loc;
}

void get_op(const string& line, string* operation) {
    std::istringstream sin(line);
    sin >> *operation;
    if (sin.fail()) {
        sin.clear();
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        *operation = "ignore";
    }
}

void get_loc(const string& line, string* location) {
    std::istringstream sin(line);
    sin >> *location;
    if (sin.fail()) {
        sin.clear();
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void print_inst_1() {
    cout << "*** enter operation: push <location> | insert <location> | pop | clear | print | locations | quit" << endl;
    cout << "*** enter location from above list on next line" << endl;
    cout << "*** enter an empty line to end input" << endl;
    cout << "***" << endl;
    cout << "*** WARNING: push operation pushes location in push order without any location ordering" << endl;
    cout << "***" << endl;
}

void print_inst_2() {
    cout << "*** Locations: Boston | Hartford | NewYork | Philadelphia | Baltimore | WashingtonDC | Pittsburgh | Cleveland | Detroit | Chicago | " << endl;
    cout << "*** Indianapolis | Nashville | Atlanta | Houston | Dallas | Austin | Denver | Albuquerque | Phoenix | Sacramento" << endl;
    cout << "*** .... you can repeat this list anytime at prompt by typing locations ...." << endl;
    cout << "***" << endl;   
}

void print_inst_3() {
    cout << endl;
    cout << "next" << endl;
}

// HOMEWORK TODO, update value and ptr members of node with arguments from the called function
node::node (int arg_val, node *ptr = nullptr) {
    this->value = arg_val;
    this->ptr = ptr;
}

// getters, gets value, gets ptr
// HOMEWORK TODO getvalue returns the value of the node
int node::getvalue () {
        return value; // This return has to be updated
}
// HOMEWORK TODO getptr returns the ptr from the node
node *node::getptr () {
        return ptr; // This return has to be updated
}


// setter
// HOMEWORK TODO setptr sets the node member ptr
void node::setptr (node *ptr) {
    this->ptr = ptr;
}

// HOMEWORK TODO setptr sets the node member value
void node::setvalue (int value) {
    this->value = value;
}

//LinkedList constructor
// HOMEWORK TODO initialize the headptr to nullptr at the start
LinkedList::LinkedList () : headptr(nullptr) {
    // already initializes headptr to nullptr
    // might need to manually initialize fi this doesn't work
    headptr = nullptr;
}

// LinkedList destructor
// HOMEWORK TODO pop (remove) all nodes until the LinkedList is empty
LinkedList::~LinkedList () {
    while (headptr != nullptr) {
        pop();
    }
}

//LinkedList copy constructor
// HOMEWORK TODO Follow the Rule of 3 and create a copy of the object
LinkedList::LinkedList (const LinkedList& object) : headptr(nullptr) {
    node* curNode = object.headptr;
    while (curNode != nullptr) {
        push(curNode->getvalue()); // add each node to new list
        curNode = curNode->getptr();
    }
}

//LinkedList assignment operator overload
// HOMEWORK TODO Follow the Rule of 3 and create an overload for assignment
LinkedList& LinkedList::operator=(const LinkedList &object) {
    if (this == &object) {
        return *this;
    }
    this->~LinkedList();    
    LinkedList temporary(object);
    headptr = temporary.headptr;
    temporary.headptr = nullptr;
    return *this; // This return has to be updated
}

// add a node, push a node
// HOMEWORK TODO add a new node at the head of the LinkedList
void LinkedList::push (int value) {
    //node* newNode = new node(value, headptr); // node points to current head
    //headptr = newNode;
    node* newNode = new node(value, nullptr);
    node* temporaryNode = headptr;
    headptr = newNode;
    newNode->setptr(temporaryNode);
}

// remove node, pop a node
// HOMEWORK TODO removes the node at the head of the LinkedList
int LinkedList::pop () {
            int value_to_remove;      
            // TODO Here...
            if (link_list_empty()) { // error if list emtpty
                cout << "Cannot remove elements from empty link list" << endl;
                return -1; // returning an error value
            }
            value_to_remove = headptr->getvalue();
            node* curNode = headptr;
            headptr = headptr->getptr();
            delete curNode;
            // 
            return value_to_remove;
}

// print linked list
// Do not touch
void LinkedList::printLinkedList () {
    node *curNode = headptr;
    int reference;
        while (curNode != nullptr) {
            reference = curNode->getvalue();
            cout << rev_mapping(reference) << " -> ";
            curNode = curNode->getptr();
        }
    cout << endl;
}

// inserts a node in a sepcific location
// HOMEWORK TODO Insert a node at the reference_value
// reference_value is obtained from the get_closest_less_than function
void LinkedList::insertNode(int value, int reference_value) {
    node* curNode = headptr;
    if (curNode == nullptr) {
        throw std::runtime_error("Cannot remove elements from empty link list");
    }
    while (curNode != nullptr) {
        if (curNode->getvalue() == reference_value) {
            node* newNode = new node(value, curNode->getptr());
            curNode->setptr(newNode);
            return; 
        }
        curNode = curNode->getptr();
    }        
} // end insertNode

// HOMEWORK TODO
// To find the last value in the linked list which is less than the new node’s value. 
// i.e. find the node which is closest to the end (among those with value less than the given value) 
//  i.e. where in the linked list should you insert. It approximates the correct driving order for the driver.
// In other words given a new node to insert, with a specific value, find where
// in the linkedlist is a node that is less than the new node's value and there
// aren't any other nodes in the linkedlist which are less than and closer to the
// new value. Eg given nodes with values 3, 8, 11, 15, 17. Insert 14 after 11. 
// Insert 9 after 8. Insert 19 after 17. Insert 2 at the head. 
int LinkedList::find_closest_less_than(int value) {
    int closest_less_than = 0;   
    // TODO here
    node* curNode = headptr;
    while (curNode) {
        if (curNode->getvalue() < value) {
            closest_less_than = curNode->getvalue();
        }
        curNode = curNode->getptr();
    }
    //
    return closest_less_than;
}
// Is the link list empty?
// HOMEWORK TODO return true if the linkedlist is empty, has no nodes 
bool LinkedList::link_list_empty() {
    if (headptr == nullptr){
        return true;
    }
    else {
        return false; // This return has to be updated
    }
}

// do not touch, is used for unit testing
int LinkedList::obtain_value_head () {
    node *curNode = headptr;
    return curNode->getvalue();
}
// end of public methods for LinkedList
