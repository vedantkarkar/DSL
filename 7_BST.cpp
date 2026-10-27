// A smartphone app stores contacts using a Binary Search Tree (BST), where 
// each  node  holds  a  contact  name  (as  key)  and  phone  number  (as  value)  to 
// enable  efficient  insertion,  deletion,  and  lookup.  Implement  the  following 
// using BST: 
// • Add Contact [x]
// • Delete Contact 
// • Update Contact [x]
// • Display Contacts [x]
// • Search Analysis [x]

#include <iostream>

using namespace std;

constexpr int line_width = 70;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

void draw_line(int length = line_width){
    cout << string(length, '-') << "\n";
}

class BST{
    public:

    class Node{
        public:

        // Data Members
        string name;
        string number;

        // Pointers
        Node* left;
        Node* right;

        Node(): name("Not Initialized"), number("Not Initialized"), left(nullptr), right(nullptr) {}

        Node(string NUM): name("Not Initialized"), number(NUM), left(nullptr), right(nullptr) {}
        
        Node(string NAME, string NUM): name(NAME), number(NUM), left(nullptr), right(nullptr) {}

        Node(const Node& NODE){
            name = NODE.name;
            number = NODE.number;
            left = NODE.left;
            right = NODE.right;
        }

        // to return a address of node, works as Node* smth = get_node() instead of Node* smth = new node() 
        static Node* get_node(){
            Node* temp = new Node();
            cout << "Enter the name of the contact\n";
            cin.ignore();
            getline(cin, temp->name);
            cout << "Enter the phone number of the contact\n";
            getline(cin, temp->number);

            return temp;
        }

        void display(){
            cout << "Name: " << name << endl;
            cout << "Number: " << number << endl;
        }
    };
    // EOF Node Class

    Node* root;
    int total_size;

    BST(): root(nullptr), total_size(0) {}

    BST(Node* ROOT): root(ROOT), total_size(1) {}

    ~BST(){
        clear();
    }
    
    bool is_empty(){
        return root == nullptr;
    }

    int size(){
        return total_size;
    }
    
    void clear(){
        recurse_delete(root);
        root = nullptr;
        total_size = 0;
    }

    void recurse_delete(Node* current){
        if(current == nullptr){
            return;
        }

        recurse_delete(current->left);
        recurse_delete(current->right);
        delete current;
    }

    // Overloaded function to accept a lvalue reference of a child instead of an address 
    void insert(const Node& child){
        if(is_empty()){
            root = new Node(child);
            total_size++;
            return;
        }

        Node* temp = root;
        while(true){
            if(temp->number == child.number){
                cout << "Number already exists\nNo insertion is made\n";
                return;
            }
            else if(temp->number < child.number){
                if(temp->right == nullptr){
                    temp->right = new Node(child);
                    total_size++;
                    return;
                }
                else{
                    temp = temp->right;
                }
            }
            else{
                // child is less than temp.
                if(temp->left == nullptr){
                    temp->left = new Node(child);
                    total_size++;
                    return;
                }
                else{
                    temp = temp->left;
                }
            }
        }
    }

    // Overloaded function to accept an address of a child to insert directly
    void insert(Node* child){
        if(is_empty()){
            root = child;
            total_size++;
            return;
        }

        Node* temp = root;
        while(true){
            if(temp->number == child->number){
                cout << "Number already exists\nNo insertion is made\n";
                return;
            }
            else if(temp->number < child->number){
                if(temp->right == nullptr){
                    temp->right = child;
                    total_size++;
                    return;
                }
                else{
                    temp = temp->right;
                }
            }
            else{
                // child is less than temp.
                if(temp->left == nullptr){
                    temp->left = child;
                    total_size++;
                    return;
                }
                else{
                    temp = temp->left;
                }
            }
        }
    }

    // in order traversal to display tree in ascending order
    void recurse_display(Node* current, int& counter){
        if(current == nullptr){
            return;
        }

        recurse_display(current->left, counter);
        cout << "Contact " << counter << ":\n";
        current->display();
        counter++;
        recurse_display(current->right, counter);
    }

    // public api to display the whole tree
    void display(){
        int start = 1;
        recurse_display(root, start);
    }

    // returns address to the node of number and nullptr if number not present
    Node* get_number(string number, int& count){
        count = 0;
        if(is_empty()){
            return nullptr;
        }
        Node* temp = root;

        while(temp != nullptr){
            ++count;
            if(temp->number == number) {
                return temp;
            }
            else if(temp->number < number){
                temp = temp->right;
            }
            else{
                temp=temp->left;
            }
        }
        return nullptr;
    }

    // returns address to the node of name and nullptr if name not present

    // will not work as key is number and comparisons are valid on keys only
    // Node* get_name(string name, int& count){
    //     count = 0;
    //     if(is_empty()){
    //         count = 0;
    //         return nullptr;
    //     }

    //     Node* temp = root;

    //     while(temp != nullptr){
    //         ++count;
    //         if(temp->name == name) {
    //             return temp;
    //         }
    //         else if(temp->name < name){
    //             temp = temp->right;
    //         }
    //         else{
    //             temp = temp->left;
    //         }
    //     }

    //     return nullptr;
    // }

    void update_name(string number, string new_name){
        int count;
        Node* temp = get_number(number, count);
        if(temp == nullptr){
            cout << "No contact with number [" << number << "] not found\n"<< RED << "No contact updated\n" << RESET;
            return;
        }

        cout << "Contact found after " << count << " searches\n";
        cout << RED << temp->name << RESET << " -> ";
        temp->name = new_name;
        cout << GREEN << temp->name << RESET << endl;
    }

    void update_number(string number, string new_number){
        int count;
        Node* temp = get_number(number, count);
        if(temp == nullptr){
            cout << "No contact with number [" << number << "] not found\n"<< RED << "No contact updated\n" << RESET;
            return;
        }

        cout << "Contact found after " << count << " searches\n";
        cout << RED << temp->number << RESET << " -> ";
        temp->number = new_number;
        cout << GREEN << temp->number << RESET << endl;
    }

    void show_menu(){
        cout << BLUE << "\t\t\tContacts menu" << RESET << endl;
        cout << "1. Display Contacts\n";
        cout << "2. Add Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Search Analysis\n";
        cout << "6. Exit\n";
    }

    void run(){
        int choice = 0;
        do{
            draw_line();
            show_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        }while(choice != 6);
    }

    void perform(int ch){
        switch(ch){
            case 1:
                perform_display();
            break;
            
            case 2:
                insert(BST::Node::get_node());
            break;

            case 3:
                perform_delete();
            break;

            case 4: 
                perform_update();
            break;

            case 5: 
                perform_search();
            break;

            case 6:
                cout << "Please wait while program exits.\nExiting...\n";
                draw_line();
            break;

            default: 
                cout << "Enter a Valid choice between 1 to 6.\n";
        }
    }

    void perform_display(){
        if(is_empty()) {
            cout << "Contact list is empty.\n";
            return;
        }

        cout << "Displaying Contact list of " << total_size << " size: \n";
        display();
    }

    Node* delete_node(Node* current, const string& key){
        if(current == nullptr){
            return nullptr;
        }

        if(key < current->number){
            current->left = delete_node(current->left, key);
            return current;
        }
        if(key > current->number){
            current->right = delete_node(current->right, key);
            return current;
        }

        if(current->left == nullptr){
            Node* right = current->right;
            delete current;
            return right;
        }
        if(current->right == nullptr){
            Node* left = current->left;
            delete current;
            return left;
        }

        Node* successor = current->right;
        while(successor->left != nullptr){
            successor = successor->left;
        }

        current->number = successor->number;
        current->name = successor->name;
        current->right = delete_node(current->right, successor->number);
        return current;
    }

    void perform_delete(){
        if(is_empty()){
            cout << "Contact list is empty.\n";
            return;
        }

        string key;
        int count = 0;
        cout << "Enter the number to delete: ";
        cin >> key;

        Node* found = get_number(key, count);
        if(found == nullptr){
            cout << key << " not found in the contact list\n";
            return;
        }

        root = delete_node(root, key);
        total_size--;
        cout << key << " deleted successfully.\n";
    }

    void perform_update(){
        string temp_num;
        int choice, count; 
        cout << "Enter the number you want to change: ";
        cin >> temp_num;
        if(get_number(temp_num, count) == nullptr){
            cout << temp_num << " not found in the contact list\n";
            return;
        }
        while(true){
            cout << "Enter 1 to update name, or 2 to update number\n";
            cin >> choice;
            if(choice == 1 || choice == 2) break;
        }
        if(choice == 1){
            string new_name; 
            cout << "Enter the new name for contact: ";
            cin.ignore();
            getline(cin, new_name);
            update_name(temp_num, new_name);
        }
        else{
            string new_num; 
            cout << "Enter the new number for contact: ";
            cin.ignore();
            getline(cin, new_num);
            update_number(temp_num, new_num);
        }
    }

    void perform_search(){
        int count;
        string temp_num;
        cout << "Enter the number you want to search: ";
        cin.ignore();
        getline(cin, temp_num);
        Node* temp = get_number(temp_num, count);
        if(temp == nullptr){
            cout << temp_num << " not found in the contact list\n";
            cout << count << " comparisons checked.\n";
        }
        else{
            cout << temp_num << " Found after " << count << " path search\n";
            temp->display();
        }
    }

};

int main(){
    BST Tree;

    // Tree.insert(*BST::Node::get_node());
    // Tree.insert(*BST::Node::get_node());
    // Tree.display();

    Tree.run();

    return 0;
}