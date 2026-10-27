// Evaluate expressions like 3 4 + 5 * using a stack.
// Extension: Add an "undo" feature using a secondary stack.

#include <iostream>

using namespace std;

constexpr int default_capacity = 8;

constexpr int line_width = 80;

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
        }
        else{
            total_capacity = default_capacity;
        }
        arr = new type_name[total_capacity];
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

// 3 4 + 5 *
// 4 5 7 2 + - *
int postfix(string expression){
    Stack<int> st;
    for(int i = 0; i < expression.length(); i++){
        if(expression[i] >= '0' && expression[i] <= '9'){
            // try without casting
            st.push((int)expression[i] - '0');
        }
        else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%'){
            if(st.size() < 2){
                cout << "Operator limit exceeded for given operands: \033[31mInvalid Expression- " << expression << " \033[0m\nError: ";
                return -1;
            }
            int b = st.pop();
            int a = st.pop();
            switch(expression[i]){
                case '+':
                st.push(a+b);
                break;

                case '-':
                st.push(a-b);
                break;

                case '*':
                st.push(a*b);
                break;

                case '/':
                st.push(a/b);
                break;

                case '%':
                st.push(a%b);
                break;
            }
        }
    }
    int ans = st.pop();
    if(!st.is_empty()){
        cout << "Operand limit exceeded for given operators: \033[31mInvalid Expression- " << expression << " \033[0m\nError: ";
        return -1;
    }
    return ans;
}

int main(){
    string input;
    while(true){
        draw_line();
        cout << "Enter a Postfix Expression (or press 'q' to quit the program): \n";
        getline(cin, input);

        if(input == "q"){
            cout << "Wait while exiting the program...\n";
            draw_line();
            break;
        }

        cout << "Evaluation: " << postfix(input) << endl;
    }
    return 0;
}