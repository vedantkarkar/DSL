// Implement a priority queue for Hospital Emergency Room where:
// • Critical patients jump the queue
// • Regular patients follow FIFO

#include <iostream>

using namespace std;

constexpr int default_capacity = 16;

constexpr int line_width = 80;

void print_line(int l = line_width){
    cout << "\n";
    cout << string(l, '-');
    cout << "\n";
}

template<class T>
class Queue{
    private:
    T* arr;
    int total_size;
    int total_capacity;
    int front;
    int rear;

    public: 

    Queue(): total_size(0), total_capacity(default_capacity), front(-1), rear(-1) {
        arr = new T[total_capacity];
    }

    Queue(int initial_size): total_size(0), rear(-1), front(-1) {
        if(initial_size > 0){
            total_capacity = initial_size;
        }
        else{
            cerr << "Error: Size provided was negative\nFallback Protocol to default capacity: " << default_capacity << endl;
            total_capacity = default_capacity;
        }
        arr = new T[total_capacity];
    }

    ~Queue(){
        delete[] arr;
    }

    // Getter Setter

    void set_capacity(int new_capacity){
        if(new_capacity > 0){
            total_capacity = new_capacity;
        }
    }

    int capacity(){
        return total_capacity;
    }

    void set_size(int new_size){
        if(new_size > 0){
            total_size = new_size;
        }
    }

    int size(){
        return total_size;
    }

    int Front(){
        return front;
    }

    int Rear(){
        return rear;
    }

    // helper functions

    bool is_empty(){
        // rear == -1;
        return total_size == 0;
    }

    bool is_full(){
        // front == (rear + 1)%total_capacity;
        return total_size == total_capacity;
    }


    // Push Pop logic
    void push(T element){
        // try dynamic resize for queue
        if(is_full()){
            cerr << "Queue Overflow\n";
            return;
        }
        else if(is_empty()){
            arr[0] = element;
            front = 0;
            rear = 0;
            total_size++;
            return;
        }

        rear = (rear + 1)%total_capacity;
        total_size++; 
        arr[rear] = element;
    }
    
    void pop(){
        if(is_empty()){
            cerr << "Queue Underflow\n";
            return;
        }
        else if (total_size == 1){
            total_size = 0;
            front = -1;
            rear = -1;
            return;
        }

        front = (front + 1)%total_capacity;
        total_size--;
    }

    T& top(){
        try{
            if(is_empty()){
               throw std::out_of_range("Error: Index out of bound\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }

        return arr[front];
    }

    const T peek(){
        try{
            if(is_empty()){
               throw std::out_of_range("Error: Index out of bound\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }

        return arr[front];
    }

    // Handling display with at function to look at anything in the array which should be invalid actually
    T& at(int index){
        if(index >= total_capacity || index < 0){
            throw std::out_of_range("IndexError: Index Out of bounds");
        }
        return arr[index];
    }
    
    // try this display function in Queue class that needs << to be overloaded in T type class

};


class Hospital{
    public: 
    class Patient{
        public: 
        int id;
        string name;
        Patient() : id(-1), name("NOT INITIALIZED") {}
        Patient(int id_number, string patient_name): id(id_number), name(patient_name) {}

        // *** TRYING STATIC AS NO OTHER OBJECT SHOULD BE REQUIRED TO CALL THIS
        static Patient get_patient(){
            Patient temp;
            cout << "Enter the patient id: ";
            cin >> temp.id;
            cin.ignore();
            cout << "Enter the Patient Name: ";
            getline(cin, temp.name);
            return temp;
        }
    };

    Queue<Patient> Critical;
    Queue<Patient> Normal;
    
    // Work Here
    void display_menu(){
        cout << "1. Display queue\n";
        cout << "2. Insert Patient\n";
        cout << "3. Serve Patient\n";
        cout << "4. Exit\n";
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
                perform_serve();
            break;

            case 4:
                cout << "Please wait while program exits.\nExiting...\n";
                print_line();
            break;

            default: 
                cout << "Enter a Valid choice between 1 and 4.\n";
        }
    }

    void perform_display(){
        cout << "Displaying queue of total patient: " << Normal.size() + Critical.size() << endl;
        if(Critical.is_empty()){
            cout << "No Critical Patients in the queue.\n";
        }
        else{
            cout << "Total Critical Patients: " << Critical.size() << endl;
            int i = Critical.Front();
            for(int count = 0; count < Critical.size(); count++){
                cout << count + 1 << ". ID: \033[31m" << (Critical.at(i)).id << ".\033[0m " << (Critical.at(i)).name << endl;
                i = (i+1)%Critical.capacity();
            }
            print_line();
        }
        if(Normal.is_empty()){
            cout << "No Normal Patients in the queue.\n";
        }
        else{
            cout << "Total Normal Patients: " << Normal.size() << endl;
            int i = Normal.Front();
            for(int count = Critical.size(); count < Normal.size() + Critical.size(); count++){
                cout << count + 1 << ". ID: " << (Normal.at(i)).id << ". " << (Normal.at(i)).name << endl;
                i = (i+1)%Normal.capacity();
            }
        }
    }

    void perform_insert(){
        char choice; 
        cout << "Is the Patient Critical(Y/n)? ";
        cin >> choice;
        if(choice == 'Y' || choice == 'y'){

            // *** Can be a breakpoint
            Critical.push(Patient::get_patient());
        }
        else{
            Normal.push(Patient::get_patient());
        }
    }

    void perform_serve(){
        if(Critical.is_empty() && Normal.is_empty()){
            cout << "No Patient in the queue to be served\n";
            return;
        }
        else if(!Critical.is_empty()){
            cout << "Patient is ready to be served. \n";
            cout << "Critical patient with id \033[31m" << Critical.top().id << ".\033[0m " << Critical.top().name << " is taken in.\n";
            Critical.pop();
            // return;
        }
        else if(!Normal.is_empty()){
            cout << "No Critical Patient in the queue. \n";
            cout << "Normal patient with id \033[32m" << Normal.top().id << ".\033[0m " << Normal.top().name << " is taken in.\n";
            Normal.pop();
        }
    }

    void run(){
        int choice = 0;
        do{
            print_line();
            display_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        }while(choice != 4);
    }

    void default_init(){
        Normal.push(Patient(1279350, "Alice"));
        Normal.push(Patient(1279351, "Bob"));
        Critical.push(Patient(1279352, "Charlie"));
        Normal.push(Patient(1279353, "David"));
        Normal.push(Patient(1279354, "Eve"));
        Normal.push(Patient(1279355, "Frank"));
        Normal.push(Patient(1279356, "Grace"));
        Normal.push(Patient(1279357, "Heidi"));
        Normal.push(Patient(1279358, "Ivan"));
        Normal.push(Patient(1279359, "Judy"));
        Normal.push(Patient(1279360, "Karl"));
        Normal.push(Patient(1279361, "Leo"));
        Critical.push(Patient(1279362, "Mallory"));
        Normal.push(Patient(1279363, "Niaj"));
    }

};
// EOC ---

int main(){
    Hospital DMH;
    DMH.default_init();
    DMH.run();
    
    return 0;
}