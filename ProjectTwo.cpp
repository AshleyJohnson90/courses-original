// Ashley Johnson
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// initialize Course and Node structs
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prereq;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};

// Creating the BST
class BinarySearchTree {

private:
    void Destructor(Node* node);

public:
    Node* root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Search(string courseNumber);
    void Insert(BinarySearchTree* tree, Node* node);
    void Print(Node* node);
};

// default constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    Destructor(root);
}

// deletes from left and right nodes
void BinarySearchTree::Destructor(Node* node) {
    if (node != nullptr) {
        Destructor(node->left);
        node->left = nullptr;
        Destructor(node->right);
        node->right = nullptr;
        delete node;
    }
}

// search the file for a specific course
void BinarySearchTree::Search(string courseNumber) {
    Node* currentNode = root;

    // prints the searched course and prerequesites if not null
    while (currentNode != nullptr) {
        if (currentNode->course.courseNumber == courseNumber) {
            cout << "Course Number: " << currentNode->course.courseNumber << endl;
            cout << "Course Title: " << currentNode->course.courseTitle << endl;
            cout << "Prerequisites: ";
            for (string prereq : currentNode->course.prereq) {
                if (prereq == currentNode->course.prereq.back()) {
                    cout << prereq << endl;
                }
                else
                {
                    cout << prereq << ", ";
                }
            }

            return;
        }
        else if (courseNumber < currentNode->course.courseNumber) {
            if (currentNode->left != nullptr) {
                currentNode = currentNode->left;
            }
        }
        else
        {
            currentNode = currentNode->right;
        }
    }
    cout << "That course was not found in the list of courses." << endl;
}

// Insert function for loading courses
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {
    if (tree->root == nullptr) {
        tree->root = node;
    }
    else
    {
        Node* current = tree->root;
        // sorting the courses numerically, left if smaller, right if larger
        while (current != nullptr) {
            if (node->course.courseNumber < current->course.courseNumber) {
                if (current->left == nullptr) {
                    current->left = node;
                    current = nullptr;
                }
                else {
                    current = current->left;
                }
            }
            else {
                if (current->right == nullptr) {
                    current->right = node;
                    current = nullptr;
                }
                else {
                    current = current->right;
                }
            }
        }
    }
}

// printing all the courses
void BinarySearchTree::Print(Node* node) {
    if (node == nullptr) {
        return;
    }
    Print(node->left);
    cout << node->course.courseNumber << " ";
    cout << node->course.courseTitle << endl;
    Print(node->right);
}

// loading the file to be read
void loadFile(string courseFile, BinarySearchTree* search) {
    ifstream file(courseFile);
    if (file.is_open()) {
        cout << "Courses loaded successfully." << endl;

        int number;
        string line;
        string word;

        while (getline(file, line)) {

            number = 0;
            Node* node = new Node();
            stringstream strst(line);

            while (number < 2) {
                getline(strst, word, ',');
                if (number == 0) {
                    node->course.courseNumber = word;
                }
                else {
                    node->course.courseTitle = word;
                }
                number++;
            }
            while (getline(strst, word, ',')) {
                node->course.prereq.push_back(word);
            }

            search->Insert(search, node);
        }
    }
    else {
        cout << "Courses failed to load. Please try to load them again." << endl;
        return;
    }
}

// displays the menu
void Menu() {
    cout << "Please Choose an Option" << endl;
    cout << endl;
    cout << "1 Load Courses" << endl;
    cout << "2 Show All Courses" << endl;
    cout << "3 Show Specific Course Information" << endl;
    cout << "4 Exit" << endl;
    cout << endl;
}

void main()
{
    BinarySearchTree* sTree = new BinarySearchTree();

    string userCourse;
    string file;
    int userChoice = 0;

    while (userChoice != 4) {
        Menu();
        cin >> userChoice;

        switch (userChoice) {

        case 1:
            cout << endl;
            file = "CourseFile.txt";
            loadFile(file, sTree);
            cout << endl;
            break;

        case 2:
            cout << endl;
            sTree->Print(sTree->root);
            cout << endl;
            break;

        case 3:
            cout << endl;
            cout << "Enter the course number you'd like to find" << endl;
            cin >> userCourse;
            cout << endl;
            sTree->Search(userCourse);
            cout << endl;
            break;
            
        case 4:
            break;

        default:
            cout << "Sorry, that's not a valid option, try a different number." << endl;
            cout << endl;
            break;
        }
    }
}


