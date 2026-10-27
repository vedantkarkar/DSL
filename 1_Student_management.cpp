// A college wants to maintain a static list of student record (roll number, name) implement basic operation on arrays like insertion, deletion, and merging of two student sections. 
// write a program for static student record management using arrays and stimulate merging of two section.

#include <iostream>

using namespace std;

constexpr int max_students = 100;
constexpr int div_capacity = 10;
constexpr int initial_divisions = 2;

constexpr int line_length = 50;
int total_div = initial_divisions;
class Section {
    public:

    struct Student
    {
        int rollno;
        string name;
    };
    
    
    string secname;
    int total;
    Student s[100];

    Section(){
        for(int i = 0; i < 100; i++){
            s[i].rollno = -1;
            s[i].name = "NO DATA FOUND";
        }
        secname = "NOT INITIALISED";
    }

    void settotal(int t) {
        try
        {
            if(t > max_students) {
                throw std::out_of_range("\aTotal number of students exceeds maximum capacity");
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        total = t;
    }

    void set_secname(string secn = "Default"){
        secname = secn;
    }

    void read(){
        int t;
        cout << "Enter a name to allocate for this section: " << endl;
        getline(cin, secname);
        cout << "Enter total number of students in this section" << endl;
        cin >> t;
        settotal(t);
        cout << endl;
    }

    // check if entry works for parameter
    void getstudent(Student& entry){
        cout << "\nEnter Student's roll number: ";
        cin >> entry.rollno;
        cin.ignore();
        cout << "Enter Student name: ";
        getline(cin, entry.name);
        cout << endl;
    }

    void takelist(){
        for(int i = 0; i < total; i++){
            cout << "Entry for Student " << i + 1 << " :" << endl;
            getstudent(s[i]);
        }
        cout << "Entry Complete.\n";
    }

    // call this function right after creation of a section
    void init() {
        read();
        takelist();
    }

    void insert(int index){
        if(index > 100 || total + 1 > 100) {
            cerr << "Insertion not possible. Index out of bounds or maximum capacity reached." << endl;
            return;
        }
        if(index < 0 || index > total) {
            cerr << "Invalid index. Please enter a valid index between 0 and " << total << "." << endl;
            return;
        }
        for(int i = total - 1; i >= index; i--){
            s[i + 1] = s[i];
        }
        getstudent(s[index]);
        settotal(total + 1);
    }

    void delete_s(int index){
        if(index < 0 || index >= total) {
            cerr << "Invalid index. Please enter a valid index between 0 and " << total - 1 << "." << endl;
            return;
        }
        for(int i = index; i < total - 1; i++){
            s[i] = s[i + 1];
        }
        settotal(total - 1);
    }

    void displaystudent(const Student s){
        cout << "Roll Number: " << s.rollno << 
        ". " << s.name << endl;
    }

    void display(){
        cout << "\nDisplaying list of Section: " << secname << " with total "<< total << " students" << endl;
        for(int i = 0; i < total; i++){
            displaystudent(s[i]);
        }
        cout << endl;
    }
}division[div_capacity];
// END OF CLASS

void drawline(int length = line_length){
    cout << "\n";
    cout << string(length, '-');
    cout << "\n";
}

void merge(const Section& A, const Section& B, Section& C, string sec = "Merged") {
    if(A.total + B.total > 100){
        cerr << "Cannot merge sections. Total number of students exceeds maximum capacity." << endl;
        return;
    }

    C.settotal(A.total + B.total);
    C.secname = sec;

    for(int i = 0; i < A.total; i++) {
        C.s[i] = A.s[i];
    }
    for(int i = A.total; i < A.total + B.total; i++) {
        C.s[i] = B.s[i - A.total];
    }

}

void display_menu(){
    drawline();
    cout << "\033[1;34mStudent Management System\033[0m\n";
    cout << "1. Insert Student\n";
    cout << "2. Delete Student\n";
    cout << "3. Display Student list\n";
    cout << "4. Merge Section\n";
    cout << "5. Exit\n" ;
}

Section& choose_Division(){
    int ch = 0;
    cout << "Select a Division: " << endl;
    do{ 
        for(int i = 0; i < total_div; i++){
            cout << i + 1 << ". " << division[i].secname << endl;
        }
        cout << "Enter your choice: ";
        cin >> ch;
        if(ch > total_div) {
            cerr << "\aNo such division exists\nChoose again or ctrl+c to exit" << endl;
        }
    }while(ch <= 0 || ch > total_div);

    return division[ch - 1];
}

void perform_insert(Section &div){
    cout << "Inserting a student in section: " << div.secname << " with total " << div.total << " students" << endl;
    int index;
    cout << "Enter the index to insert student at: ";
    cin >> index;
    div.insert(index);
}

void perform_delete(Section &div){
    cout << "Deleting a student in section: " << div.secname << " with total " << div.total << " students" << endl;
    int index;
    cout << "Enter the index to delete student at: ";
    cin >> index;
    div.delete_s(index);
}

void perform_merge(){
    Section* A = &choose_Division();
    Section* B = &choose_Division();
    string newsecname;
    cout << "Enter a name for the new merged section: ";
    cin.ignore();
    getline(cin, newsecname);
    merge(*A, *B, division[total_div], newsecname);
    cout << "Merged section created with name: " << division[total_div].secname << endl;
    division[total_div].display();
    ++total_div;
    A = nullptr;
    B = nullptr;
}

// WORK HERE: 
void perform(int choice){
    Section* temp = nullptr;
    switch(choice){
        case 1:
        temp = &choose_Division();
        perform_insert(*temp);
        break;
        case 2:
        temp = &choose_Division();
        perform_delete(*temp);
        break;
        case 3:
        temp = &choose_Division();
        temp->display();
        break;
        case 4:
        if(total_div < 2){
            cerr << "Not enough divisions to merge" << endl;
            break;
        }
        else if(total_div >= div_capacity){
            cerr << "Maximum number of divisions reached" << endl;
            break;
        }
        perform_merge();
        break;
        case 5:
        cout << "Exiting...\nThank you for using the program!" << endl;
        drawline();
        break;
        default:
        cerr << "Invalid choice" << endl;
    }
    temp = nullptr;
}

void default_init(){
    division[0].set_secname("Division A");
    division[0].settotal(5);
    division[0].s[0] = {1, "Alice"};
    division[0].s[1] = {2, "Bob"};
    division[0].s[2] = {3, "Charlie"};
    division[0].s[3] = {4, "David"};
    division[0].s[4] = {5, "Eve"};

    division[1].set_secname("Division B");
    division[1].settotal(9);
    division[1].s[0] = {6, "Frank"};
    division[1].s[1] = {7, "Grace"};
    division[1].s[2] = {8, "Heidi"};
    division[1].s[3] = {9, "Ivan"};
    division[1].s[4] = {10, "Judy"};
    division[1].s[5] = {11, "Karl"};
    division[1].s[6] = {12, "Leo"};
    division[1].s[7] = {13, "Mallory"};
    division[1].s[8] = {14, "Niaj"};
}

void initial_init(){
    try{
        if(initial_divisions > div_capacity) {
            throw std::out_of_range("\aInitial number of divisions exceeds maximum capacity");
        }
        else if(initial_divisions < 1) {
            throw std::out_of_range("\aInitial number of divisions must be at least 1");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    for(int i = 0; i < initial_divisions; i++){
        division[i].init();
    }
}

int main(){
    // Initialise for every div
    // initial_init();

    // Default initialisation for testing
    default_init();


    int choice;
    do{
        choice = 0;
        display_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        perform(choice);
    } while(choice != 5);

    return 0;
}