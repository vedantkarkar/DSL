// Create a program that sorts elements by allowing users to choose between:
// • Linear search/Sentinel search
// • Binary search/Fibonacci search
// Compare time complexities for datasets of varying sizes

#include <iostream>
#include <chrono>

using namespace std;

constexpr int max_capacity = 1000;
constexpr int linewidth = 50;

class Array{
    private: 

    // private member functions
    int total_size;
    int capacity;
    int* arr;
    
    public: 

    Array(int size) : total_size(size) {
        arr = new int[max_capacity];
    }

    ~Array() {
        delete[] arr;
    }

    // getter setter functions 
    void set_size(int size){
        total_size = size;
    }
    int get_size(){
        return total_size;
    }

    // Helper Functions
    void drawline(int length = linewidth){
        cout << "\n";
        cout << string(length, '-');
        cout << "\n";
    }

    void swap(int& a, int& b){
        int temp = b;
        b = a;
        a = temp;
    }

    int partition(int low, int high){
        int pivot = arr[high];
        int i = low - 1;
        for(int j = low; j < high; j++){
            if(arr[j] < pivot){
                i++;
                swap(arr[j], arr[i]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quick_sort(int low, int high){
        if(low < high){
            int p = partition(low, high);
            quick_sort(low, p - 1);
            quick_sort(p + 1, high);
        }
    }

    // call this function for user initialization
    void user_init(){
        int n = 0;
        do{
            cout << "Enter the size of the array: ";
            cin >> n;
        }while(n < 0 || n > max_capacity);
        set_size(n);
        for(int i = 0; i < n; i++){
            cout << "Enter element" << i + 1 << ": ";
            cin >> arr[i];
        }
        cout << "Filled the array...\n";
        display_arr();
    }

    void display_arr(){
        cout << "Displaying array: \n";
        if(total_size > 0){
            for(int i = 0; i < total_size; i++){
                cout << "Index: " << i << " Element: " << arr[i] << endl;
            }
        }
        else{
            cout << "Array is empty ...\n";
        }
    }

    bool is_sorted(){
        for(int i = 0; i + 1 < total_size; i++){
            if(arr[i] > arr[i + 1]){
                return false;
            }
        }
        return true;
    }

    void show_menu(){
        cout << "0. Display array\n";
        cout << "1. Linear Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Fibonacci Search\n";
        cout << "4. Sentinel Search\n";
        cout << "5. Sort array\n";
        cout << "6. Benchmark\n";
        cout << "7. Exit\n";
    }


    // Algorithms 
    int linear_search(int item){
        for(int i = 0; i < total_size; i++){
            if(arr[i] == item){
                return i;
            }
        }
        return -1;
    }

    int binary_search(int item){
        int beg = 0;
        int end = total_size - 1;
        int mid;
        while(beg <= end){
            mid = (beg + end)/2;
            if(arr[mid] == item){
                return mid;
            }
            else if(arr[mid] > item){
                end = mid - 1;
            }
            else {
                beg = mid + 1;
            }
        }

        return -1;
    }

    int fib_search(int target){
        int n = total_size;
        int fibm2 = 0;
        int fibm1 = 1;
        int fibm = 1;

        while(fibm < n){
            fibm2 = fibm1;
            fibm1 = fibm;
            fibm = fibm1 + fibm2;
        }

        int offset = -1;

        while(fibm > 1){
            int i = (offset + fibm2 > n - 1)? n - 1 : offset + fibm2;

            if(arr[i] == target){
                return i;
            }
            else if(arr[i] < target){
                offset = i;
                fibm = fibm1;
                fibm1 = fibm2;
                fibm2 = fibm - fibm1;
            }
            else{
                fibm = fibm2;
                fibm1 = fibm1 - fibm2;
                fibm2 = fibm - fibm1;
            }
        }

        if(fibm1 && offset + 1 < n && arr[offset + 1] == target){
            return offset + 1;
        }

        return -1;
    }

    int sentinel_search(int target){
        int n = total_size;
        
        // CHECKING IF N IS ZERO OR GREATER THAN MAX_CAPACITY TO INSERT SENTINEL
        if(n < 1 || n >= max_capacity){
            return -1;
        }

        //INSERT THE SENTINEL
        arr[n] = target;
        int i = 0;
        while(arr[i] != target){
            i++;
        }
        arr[n] = 0;
        if(i == n){
            return -1;
        }
        else{
            return i;
        }
    }

    void perform_linear(){
        int key;
        cout << "Enter a number to search: ";
        cin >> key;
        auto start = chrono::high_resolution_clock::now();
        int found = linear_search(key);
        auto end = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::microseconds>(end - start);
        if(found == -1){
            cout << "\nElement not found\n";
        }
        else{
            cout << "\nElement found at " << found << " index\n";
        }
        cout << "Elapsed time in micro-seconds: " << ms.count() << endl;
    }

    void perform_binary(){
        if(!is_sorted()){
            cout << "Binary Search is not possible for unsorted array: \n";
            cout << "Do you want to perform a sort before searching? Y/n: ";
            char choice;
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                quick_sort(0, total_size - 1);
                display_arr();
            }
            else{
                cerr << "Exiting with array intrigrity as it was\n";
                return;
            }
        }
        int key;
        cout << "Enter a number to search: ";
        cin >> key;
        auto start = chrono::high_resolution_clock::now();
        int found = binary_search(key);
        auto end = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::microseconds>(end - start);
        if(found == -1){
            cout << "Element not found\n";
        }
        else{
            cout << "Element found at " << found << " index\n";
        }
        cout << "Elapsed time in micro-seconds: " << ms.count() << endl;
    }

    void perform_fib(){
        if(!is_sorted()){
            cout << "Fibonacci Search is not possible for unsorted array: \n";
            char choice;
            cout << "Do you want to perform a sort before searching? Y/n: ";
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                quick_sort(0, total_size - 1);
                display_arr();
            }
            else{
                cerr << "Exiting with array intrigrity as it was\n";
                return;
            }
        }
        int key;
        cout << "Enter a number to search: ";
        cin >> key;
        auto start = chrono::high_resolution_clock::now();
        int found = fib_search(key);
        auto end = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::microseconds>(end - start);
        if(found == -1){
            cout << "\nElement not found\n";
        }
        else{
            cout << "\nElement found at " << found << " index\n";
        }
        cout << "Elapsed time in micro-seconds: " << ms.count() << endl;
    }

    void perform_sentinel(){
        int key;
        cout << "Enter a number to search: ";
        cin >> key;
        auto start = chrono::high_resolution_clock::now();
        int found = sentinel_search(key);
        auto end = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::microseconds>(end - start);
        if(found == -1){
            cout << "\nElement not found\n";
        }
        else{
            cout << "\nElement found at " << found << " index\n";
        }
        cout << "Elapsed time in micro-seconds: " << ms.count() << endl;
    }

    void perform_benchmarking(){
        if(!is_sorted()){
            char choice;
            cout << "Binary & Fibonacci Search is not possible for unsorted array: \n";
            cout << "Do you want to perform a sort before searching? Y/n: ";
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                quick_sort(0, total_size - 1);
                display_arr();
            }
            else{
                cerr << "Exiting with array intrigrity as it was\n";
                return;
            }
        }
        int key;
        cout << "Enter a number to search: ";
        cin >> key;
        cout << "Performing benchmarking: \n";
        
        auto start2 = chrono::high_resolution_clock::now();
        int foundb = binary_search(key);
        auto end2 = chrono::high_resolution_clock::now();
        auto ms2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
        cout << "Time required for Binary search = " << ms2.count() << " micro seconds.\n";
        
        auto start3 = chrono::high_resolution_clock::now();
        int foundf = fib_search(key);
        auto end3 = chrono::high_resolution_clock::now();
        auto ms3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
        cout << "Time required for Fibonacci search = " << ms3.count() << " micro seconds.\n";
        
        auto start1 = chrono::high_resolution_clock::now();
        int foundl = linear_search(key);
        auto end1 = chrono::high_resolution_clock::now();
        auto ms1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
        cout << "Time required for Linear search = " << ms1.count() << " micro seconds.\n";

        auto start4 = chrono::high_resolution_clock::now();
        int founds = sentinel_search(key);
        auto end4 = chrono::high_resolution_clock::now();
        auto ms4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
        cout << "Time required for Sentinel search = " << ms4.count() << " micro seconds.\n";

        if(foundl == -1){
            cout << "\nElement not found\n";
        }
        else{
            cout << "\nElement found at " << foundl << " index\n";
        }
    }

    void perform(int ch){
        switch(ch){
            case 0:
            display_arr();
            break;
            
            case 1:
            perform_linear();
            break;

            case 2: 
            perform_binary();
            break;

            case 3:
            perform_fib();
            break;

            case 4:
            perform_sentinel();
            break;

            case 5:
            quick_sort(0, total_size - 1);
            display_arr();
            break;

            case 6: 
            perform_benchmarking();
            break;

            case 7:
            cout << "Please wait exiting Program ...\n";
            break;
            
            default:
            cout << "Enter a valid choice\n";
        }
    }

    // Final running function
    void run(){
        int choice = 0;
        do {

        drawline(linewidth);
        show_menu();
        cout << "Your Choice: ";
        cin >> choice;
        perform(choice);

        }while(choice != 7);
    }
};

int main() {
    Array obj(100);
    obj.user_init();
    obj.run();
    return 0;
}