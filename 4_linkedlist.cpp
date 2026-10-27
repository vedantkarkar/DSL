// Music players use linked lists to manage playlists dynamically. Build a
// Music Playlist Manager using linked list to:
// • Add songs
// • Remove songs
// • Display playlist
// Loop through songs forward/backward.

#include <iostream>

using namespace std;

constexpr int line_width = 75;

struct Node{
    string data;
    Node* next;
    Node* prev;

    // Node(): data("DATA NOT FOUND"), next(nullptr), back(nullptr) {}
    Node(string name): data(name), next(nullptr), prev(nullptr) {}
};

class Playlist{
    
    int length;
    
    public: 
    
    Node* head;
    Node* tail;

    Playlist(): length(0), head(nullptr), tail(nullptr) {}

    ~Playlist(){
        clear();
    }
    // Copy constructor, operator=
    
    // Helpers

    int get_length(){
        return length;
    }

    void set_length(int l){
        if(l < 0){
            return;
        }
        length = l;
    }

    bool isempty(){
        return length == 0;
    }

    void clear(){
        Node* current = head;

        while(current != nullptr){
            Node* temp = current->next;
            delete current;
            current = temp;
        }

        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void print_line(int l = line_width){
        cout << "\n";
        cout << string(l, '-');
        cout << "\n";
    }

    // Looping through
    void print_forward(){
        Node* current = head;
        if(current == nullptr){
            cout << "The playlist is empty.\n";
            return;
        }
        int count = 1;
        print_line();
        cout << "Printing Playlist of " << length << " length in forward order: \n";
        while(current != nullptr){
            cout << count << ". " << current->data << "\n";
            current = current->next;
            count ++;
        }
    }

    void print_backward(){
        Node* current = tail;
        if(current == nullptr){
            cout << "The playlist is empty.\n";
            return;
        }
        int count = 1;
        print_line();
        cout << "Printing Playlist of " << length << " length in backward order: \n";
        while(current != nullptr){
            cout << count << ". " << current->data << "\n";
            current = current->prev;
            count ++;
        }
    }

    // Insertion Operations:

    void push_back(string song){
        Node* temp = new Node(song);
        if(tail == nullptr){
            head = temp;
            tail = temp;
            length++;
            return;
        }
        tail->next = temp;
        temp->prev = tail;
        tail = tail->next;
        
        temp = nullptr; // just to be safe
        length++;
    }

    void push_front(string song){
        Node* temp = new Node(song);

        if(head == nullptr){
            head = temp;
            tail = temp;
            length++;
            return;
        }

        temp->next = head;
        head->prev = temp;

        head = temp; // caution
        temp = nullptr;
        length++;
    }

    void insert_at(int index, string song){
        if(index < 0 || index > length){
            cerr << "Error: Invalid Index!\n";
            return;
        }
        else if(index == 0){
            push_front(song);
            return;
        }
        else if(index == length){
            push_back(song);
            return;
        }
        Node* temp = new Node(song);
        Node* current = head;

        for(int i = 0; i < index; i++){
            current = current->next;
        }

        temp->prev = current->prev;
        temp->next = current;
        current->prev = temp;
        
        current = temp->prev;

        current->next = temp;

        temp = nullptr;
        current = nullptr;
        length++;
    }

    // Deletion Operations:
    void delete_back(){
        if(tail == nullptr){
            cerr << "Error: Delete called on Empty list.\n";
            return;
        }
        else if(tail->prev == nullptr){
            Node* temp = tail;
            delete temp;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }

        Node* temp = tail; // save current tail;

        tail = tail->prev;
        tail->next = nullptr;

        delete temp;
        temp = nullptr;
        length--;
    }

    void delete_front(){
        if(head == nullptr){
            cerr << "Error: Delete called on Empty list.\n";
            return;
        }
        else if(head->next == nullptr){
            Node* temp = head;
            delete temp;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }

        Node* temp = head;

        head = head->next;
        head->prev = nullptr;

        delete temp;
        temp = nullptr;
        length--;
    }

    void delete_at(int index){
        if(index < 0 || index >= length){
            cerr << "Error: Invalid Index!\n";
            return;
        }
        else if(index == 0){
            delete_front();
            return;
        }
        else if(index == length - 1){
            delete_back();
            return;
        }

        Node* current = head;

        for(int i = 0; i < index; i++){
            current = current->next;
        }

        Node* first = current->prev;
        Node* second = current->next;

        first->next = second;
        second->prev = first;

        delete current;
        current = nullptr;
        length--;
    }

    string pop_back(){
        if(tail == nullptr){
            return "Pop Called on Empty Playlist";
        }
        else if(tail->prev == nullptr){
            Node* temp = tail;
            string bin = temp->data;
            delete temp;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return bin;
        }

        Node* temp = tail; // save current tail;
        string bin = temp->data;

        tail = tail->prev;
        tail->next = nullptr;

        delete temp;
        temp = nullptr;
        length--;

        return bin;
    }

    string pop_front(){
        if(head == nullptr){
            return "Pop Called on Empty Playlist";
        }
        else if(head->next == nullptr){
            Node* temp = head;
            string bin = temp->data;
            delete temp;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return bin;
        }

        Node* temp = head;
        string bin = temp->data;

        head = head->next;
        head->prev = nullptr;

        delete temp;
        temp = nullptr;
        length--;
        
        return bin;
    }

    string pop_at(int index){
        if(index < 0 || index >= length){
            cerr << "Error: Invalid Index!\nIndex: " << index << endl;
            return "Pop Called on invalid index";
        }
        else if(index == 0){
            return pop_front();
        }
        else if(index == length - 1){
            return pop_back();
        }

        Node* current = head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        string bin = current->data;

        Node* first = current->prev;
        Node* second = current->next;

        first->next = second;
        second->prev = first;

        delete current;
        current = nullptr;
        length--;

        return bin;
    }

    // Searching a Song

    int search(string song){
        Node* current = head;
        int count = 0;
        while(current != nullptr){
            if(current->data == song){
                // cout << "Song entry found at: " << count + 1 << "\n";
                return count;
            }
            current = current->next;
            count ++;
        }
        // cout << "Song not found in the playlist\n";
        return -1;
        
    }

    // Menu driven program
    void show_menu(){
        cout << "1. Display Playlist\n"; // forward or backward
        cout << "2. Insert a song\n"; // ask index
        cout << "3. Remove a song\n"; // ask index
        cout << "4. Search a song\n"; // perform other operations on it
        cout << "5. Exit\n";
    }

    void perform(int ch){
        switch(ch){
            case 1:
                perform_display();
            break;
            
            case 2:
                perform_insert();
            break;

            case 3:
                perform_remove();
            break;

            case 4:
                perform_search();
            break;

            case 5:
                cout << "Please wait while program exits.\nExiting...\n";
                print_line();
            break;

            default: 
                cout << "Enter a Valid choice between 1 and 5.\n";
        }
    }

    void perform_display(){
        int choice = 0;
        while(true){
            cout << "1. Forward order\n";
            cout << "2. Reverse order\n";
            cout << "Choice: ";
            cin >> choice;
            if(choice == 1 || choice == 2){
                break;
            }
            cout << "Invalid choice! Enter number between 1 and 2\n";
            choice = 0;
        }
        switch(choice){
            case 1: 
                print_forward();
            break;

            case 2:
                print_backward();
            break;

            default:
                cerr << "Unexpected Error at perform_display() function";
        }
    }

    void perform_insert(){
        string song;
        cout << "Enter name of the song: ";
        cin.ignore();
        getline(cin, song);
        cout << endl;
        int choice = 0;
        while(true){
            cout << "1. Insert at front\n";
            cout << "2. Insert at back\n";
            cout << "3. Insert at a index\n";
            cout << "Choice: ";
            cin >> choice;
            if(choice <= 3 && choice >= 1){
                break;
            }
            cout << "Invalid choice! Enter number between 1 and 3\n";
            choice = 0;
        }
        switch(choice){
            case 1: 
                push_front(song);
            break;

            case 2:
                push_back(song);
            break;

            case 3:
                print_forward();
                int i;
                cout << "Enter the index at which song should be inserted: ";
                cin >> i;
                insert_at(i - 1, song);
            break;
            default:
                cerr << "Unexpected Error at perform_insert() function";
        }
    }

    void perform_remove(){
        if(isempty()){
            cout << "Playlist is empty, nothing to remove\n";
        }
        else{
            print_forward();
            int i;
            cout << "Enter the index at which song should be removed: ";
            cin >> i;
            string popped = pop_at(i - 1);
            cout << "Executed delete at entry: " << i << "\n";
            cout << "Following entry was popped: " << popped << "\n";
        }
    }

    void perform_search(){
        string song;
        cout << "Enter name of the song: ";
        cin.ignore();
        getline(cin, song);
        cout << endl;
        int found = search(song);
        if(found == -1){
            cout << "Song not found in the playlist\n";
        }
        else{
            cout << "Song found at entry: " << found + 1 << endl;
        }
    }

    void run(){
        int choice = 0;
        do{
            print_line(line_width);
            show_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        }while(choice != 5);
    }

    void default_init(){
        push_back("Iris - The Goo Goo Dolls");
        push_back("Human- Jon Bellion");
        push_back("Rambling Man- Waylon Jennings");
        push_back("Sunday Mornin' Comin Down- Kris Kristofferson");
        push_back("There is a Light that never goes out- The Smiths");
        push_back("Burn, Burn, Burn - Zach Bryan");
    }

};

int main(){
    Playlist p1;
    p1.default_init();
    p1.run();

    return 0;
}