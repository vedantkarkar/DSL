#include <iostream>
using namespace std;

struct Node {
    int roll;
    char name[30];
    Node *left, *right;
    bool lthread, rthread;
};

Node* create(int roll, char name[]) {
    Node* n = new Node;
    n->roll = roll;

    int i = 0;
    while (name[i] != '\0') {
        n->name[i] = name[i];
        i++;
    }
    n->name[i] = '\0';

    n->left = n->right = NULL;
    n->lthread = n->rthread = true;
    return n;
}

Node* insert(Node* root, int roll, char name[]) {
    Node *p = root, *parent = NULL;

    while (p != NULL) {
        if (roll == p->roll) {
            cout << "Duplicate roll number!\n";
            return root;
        }

        parent = p;

        if (roll < p->roll) {
            if (!p->lthread)
                p = p->left;
            else
                break;
        } else {
            if (!p->rthread)
                p = p->right;
            else
                break;
        }
    }

    Node* n = create(roll, name);

    if (parent == NULL)
        return n;

    if (roll < parent->roll) {
        n->left = parent->left;
        n->right = parent;
        parent->lthread = false;
        parent->left = n;
    } else {
        n->right = parent->right;
        n->left = parent;
        parent->rthread = false;
        parent->right = n;
    }

    return root;
}

Node* leftmost(Node* p) {
    if (p == NULL)
        return NULL;

    while (!p->lthread)
        p = p->left;

    return p;
}

void inorder(Node* root) {
    Node* p = leftmost(root);

    while (p != NULL) {
        cout << p->roll << " " << p->name << "\n";

        if (p->rthread)
            p = p->right;
        else
            p = leftmost(p->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, roll;
    char name[30];

    do {
        cout << "\n1.Insert Student\n2.Display Inorder\n3.Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter roll number and name: ";
            cin >> roll >> name;
            root = insert(root, roll, name);
        } else if (choice == 2) {
            cout << "Roll No.  Name\n";
            inorder(root);
        } else if (choice != 3) {
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
