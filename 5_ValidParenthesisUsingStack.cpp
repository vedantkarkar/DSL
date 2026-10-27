// Code editors need to validate expressions for syntax correctness using
// parentheses. Develop a stack-based Multi-Bracket Validator tool to check
// nested brackets ((), [], {}) in code/text files.
// Extension: Highlight erroneous lines and suggest fixes.

#include <iostream>

using namespace std;

constexpr int default_capacity = 8;

constexpr int line_width = 80;
const string quit_phrase = "q";

void draw_line(int length = line_width){
    cout << string(length, '-') << "\n";
}

template<typename T>
class Stack{
    using type_name = T;

    private: 
    type_name* arr;
    int total_size;
    int total_capacity;

    public:

    // Constructor, Destructors

    Stack(): total_size(0), total_capacity(default_capacity) {
        arr = new type_name[total_capacity];
    }

    // Work here
    Stack(int initial_size): total_size(0) {
        if(initial_size > 0){
            total_capacity = initial_size;
            arr = new type_name[total_capacity];
        }
        else{
            total_capacity = default_capacity;
            arr = new type_name[total_capacity];
        }
    }

    ~Stack(){
        delete[] arr;
    }

    // helper functions

    bool is_empty(){
        return total_size == 0;
    }

    bool is_full(){
        return total_size == total_capacity;
    }

    // getter setter functions

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

    // resize function to dynamically change the capacity of the stack

    void resize(int new_size){
        if(new_size <= total_size){
            cerr << "Error: New Size is less than the current size of the stack\nResize Failed.";
            return;
        }
        type_name* temp = new type_name[new_size];
        for(int i = 0; i < total_size; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        set_capacity(new_size);

    }

    void resize(){
        type_name* temp = new type_name[total_capacity * 2];
        for(int i = 0; i < total_size; i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        set_capacity(total_capacity * 2);
    }

    // actually pushing elements.

    void push(type_name element){
        if(is_full()){
            resize();
        }
        arr[total_size] = element;
        total_size++;
    }

    type_name pop(){
        try{
            if(is_empty()){
               throw std::out_of_range("Error: Stack is empty, pop failed\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }
        total_size--;
        return arr[total_size];
    }

    // You can change a element by top
    type_name& top(){
        try{
            if(is_empty()){
               throw std::out_of_range("Error: Index out of bound\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }
        return arr[total_size - 1];
    }

    // Peek is a read only value of top element
    const type_name peek(){
        try{
            if(is_empty()){
               throw std::out_of_range("Error: Index out of bound\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }
        return arr[total_size - 1];
    }

    // this function should not exist but exists for debugging the code 
    type_name& get(int index){
        try{
            if(index < 0 || index >= total_size){
               throw std::out_of_range("Error: Index out of bound\n");
            }
        }
        catch (std::out_of_range e){
            cerr << e.what();
        }
        return arr[index];
    }

};
// End of class

// To clearly resolve the type of error in struct Error
enum class Error_type{
    OPEN, 
    CLOSED, 
    GOOD
};

// structure to hold the properties of error found.
struct Error{
    int index;
    Error_type bracket;
};

// Function that returns true if string passed has valid parenthesis, and false otherwise
// At the same time updates struct Error passed as a parameter in place.
bool valid_parenthesis(const string& str, Error& error){
    Stack<char> st;
    
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '(' || str[i] == '{' || str[i] == '['){
            st.push(str[i]);
            error.index = i;
        }
        else if(str[i] == ')' || str[i] == '}' || str[i] == ']'){
            if(st.is_empty()){
                error.index = i;
                error.bracket = Error_type::CLOSED;
                return false;
            }
            else if((st.top() == '(' && str[i] != ')') || (st.top() == '{' && str[i] != '}') || (st.top() == '[' && str[i] != ']')){
                error.index = i;
                error.bracket = Error_type::CLOSED;
                return false;
            }
            st.pop();
        }
    }
    if(!st.is_empty()){
        error.bracket = Error_type::OPEN;
        return false;
    }
    error.bracket = Error_type::GOOD;
    error.index = -1;
    return true;
}


void process_error(const string& str, const Error& error){
    if(str == quit_phrase){
        cout << "\nPlease wait while program exits...\n";
        draw_line();
    }
    else if(error.bracket != Error_type::GOOD){
        cout << "\033[31mInvalid Expression: \033[0m \n";
        cout << "Error type: invalid " <<(error.bracket == Error_type::CLOSED? "Closed" : "Open")<< " bracket found at index: " << error.index << endl;
        for(int i = 0; i < error.index; i++){
            cout << str[i];
        }   
        cout << "\033[31m" << str[error.index] << "\033[0m";
        for(int i = error.index + 1; i < str.length(); i++){
            cout << str[i];
        } 
        cout << "\n";
    }
    else{
        cout << "Valid Expression: \n";
        cout << "\033[32m" << str << "\033[0m\n";
    }
}

int main(){
    string input;
    Error error;
    do{
        draw_line();
        cout << "Enter a Expression (or press 'q' to quit the program): \n";
        getline(cin, input);
        valid_parenthesis(input, error);
        process_error(input, error);

    }while(input != "q");

    return 0;
}