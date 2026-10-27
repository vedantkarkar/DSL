// Sorting large sales data efficiently is crucial in e-commerce platforms. Write
// programs for merge sort and quicksort. Use large datasets to compare
// execution time and identify best/worst case scenarios.

#include <iostream>
#include <chrono>
#include <random>

using namespace std;

constexpr int max_capacity = 10000;
constexpr int linewidth = 50;
constexpr int def_size = 500; // default size for random initialization

random_device rd;
mt19937 rng(rd());
uniform_int_distribution dist(-100000, 100000);

class Array{
    private: 
    
    int total_size;
    int capacity;
    int* arr;

    public: 

    Array(){
        arr = new int[max_capacity];
        choose_init();
    }

    Array(int size) : total_size(size) {
        arr = new int[max_capacity];
        default_init(size);
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

    int begin(){
        return 0;
    }

    int end(){
        return total_size - 1;
    }

    void set(int index, int data){
        if(index < max_capacity && index >= 0){
            arr[index] = data;
        }
        else{
            cerr << "IndexError: Out of bound\n";
        }
    }

    int& get(int index){
        try{
            if(index > max_capacity || index < 0){
                throw index;
            }
            return arr[index];
        }
        catch(int e){
            cerr << "IndexError: index " << e << "out of bound\nMax Capacity of array: "
            << max_capacity << "\nExiting safely...";
        }
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

    // call this function for user initialization
    void user_init(){
        int n = choose_size();
        set_size(n);
        for(int i = 0; i < n; i++){
            cout << "Enter element " << i + 1 << ": ";
            cin >> arr[i];
        }
        cout << "Filled the array...\n";
        display_arr();
    }

    void default_init(int size){
        set_size(size);
        for(int i = 0; i < size; i++){
            arr[i] = dist(rng);
        }
        display_arr();
        cout << "Filled the array of size " << size << " with random values\n";
    }

    int choose_size(){
        int n;

        while(true){
            cout << "Enter the size of the array (max "
                << max_capacity << "): ";

            cin >> n;

            if(n < 0 || n > max_capacity){
                cout << "Size must be between 0 and "
                    << max_capacity << ".\n";
                continue;
            }

            return n;
        }
    }

    void choose_init(){
        int choice = 0;
        cout << "Choose initialization method:\n";
        cout << "1. User Input\n";
        cout << "2. Random Initialization\n";
        cin >> choice;
        switch(choice){
            case 1:
            user_init();
            break;

            case 2:
            default_init(choose_size());
            break;

            default:
            cout << "Invalid choice, using random initialization by default with size " << def_size << "\n";
            default_init(def_size);
        }
    }

    void display_arr(){
        drawline(linewidth);
        cout << "Displaying array: \n";
        if(total_size > 0){
            for(int i = 0; i < total_size; i++){
                cout << "Index: " << i << ", Element: " << arr[i] << endl;
            }
        }
        else{
            cout << "Array is empty ...\n";
        }
        drawline(linewidth);
    }

    bool is_sorted(){
        for(int i = 0; i + 1 < total_size; i++){
            if(arr[i] > arr[i + 1]){
                return false;
            }
        }
        return true;
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

    void merge(int low, int mid, int high){
        int i = low;
        int j = mid + 1;
        int k = 0;
        int* temp = new int[high - low + 1];
        
        while(i <= mid && j <= high){
            if(arr[i] < arr[j]){
                // try k++ and i++ inside []
                temp[k] = arr[i];
                i++;
            }
            else{
                temp[k] = arr[j];
                j++;
            }
            k++;
        }

        while(i <= mid){
            temp[k] = arr[i];
            i++;
            k++;
        }

        while(j <= high){
            temp[k] = arr[j];
            j++;
            k++;
        }

        j = 0;
        for(int i = low; i <= high; i++){
            arr[i] = temp[j];
            j++;
        }

        delete[] temp;
    }

    void merge_sort(int low, int high){
        if(low >= high){
            return;
        }
        int mid = low + (high - low)/2 ;

        merge_sort(low, mid);
        merge_sort(mid + 1, high);

        merge(low, mid, high);
    }

    // Menu Driven Code

    void show_menu(){
        cout << "0. Display array\n";
        cout << "1. New array\n";
        cout << "2. Merge Sort\n";
        cout << "3. Quick Sort\n";
        cout << "4. Benchmark\n";
        cout << "5. Exit\n";
    }

    void perform_merge_sort(){
        auto start = chrono::high_resolution_clock::now();
        merge_sort(begin(), end());
        auto end = chrono::high_resolution_clock::now();
        display_arr();
        cout << "Is array sorted after Merge Sort? " << (is_sorted() ? "Yes" : "No") << "\n";
        cout << "Merge Sort completed in: " 
        << chrono::duration_cast<chrono::microseconds>(end - start).count() 
        << " microseconds\n\n";
    }

    void perform_quick_sort(){
        auto start = chrono::high_resolution_clock::now();
        quick_sort(begin(), end());
        auto end = chrono::high_resolution_clock::now();
        display_arr();
        cout << "Is array sorted after Quick Sort? " << (is_sorted() ? "Yes" : "No") << "\n";
        cout << "Quick Sort completed in: " 
        << chrono::duration_cast<chrono::microseconds>(end - start).count() 
        << " microseconds\n\n";
    }

    void perform_benchmark(){
        cout << "Benchmarking Merge Sort and Quick Sort with array size: " << total_size << "\n";
        
        // initialize the array with random values for benchmarking and take a backup for supplying same dataset for all sorting algorithms
        // default_init(total_size);
        int* temp_arr = new int[total_size];
        for(int i = 0; i < total_size; i++){
            temp_arr[i] = arr[i];
        }
        
        // Benchmark Merge Sort
        auto start_merge = chrono::high_resolution_clock::now();
        merge_sort(begin(), end());
        auto end_merge = chrono::high_resolution_clock::now();
        display_arr();
        cout << "Is array sorted after Merge Sort? " << (is_sorted() ? "Yes" : "No") << "\n";
        cout << "Merge Sort Time: " 
        << chrono::duration_cast<chrono::microseconds>(end_merge - start_merge).count() 
        << " microseconds\n\n";

        // Benchmark Quick Sort
        for(int i = 0; i < total_size; i++){
            arr[i] = temp_arr[i];
        }
        auto start_quick = chrono::high_resolution_clock::now();
        quick_sort(begin(), end());
        auto end_quick = chrono::high_resolution_clock::now();
        cout << "Is array sorted after Quick Sort? " << (is_sorted() ? "Yes" : "No") << "\n";
        cout << "Quick Sort Time: " 
        << chrono::duration_cast<chrono::microseconds>(end_quick - start_quick).count() 
        << " microseconds\n\n";

        delete[] temp_arr;
    }

    void perform(int ch){
        switch(ch){
            case 0:
            display_arr();
            cout << "Is array sorted? " << (is_sorted() ? "Yes" : "No") << "\n";
            break;
            
            case 1:
            choose_init();
            break;

            case 2: 
            perform_merge_sort();
            break;

            case 3:
            perform_quick_sort();
            break;

            case 4:
            perform_benchmark();
            break;

            case 5:
            cout << "Please wait exiting Program ...\n";
            break;
            
            default:
            cout << "Enter a valid choice\n";
        }
    }

    void run(){
        int choice = 0;
        do{
            drawline(linewidth);
            show_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        }while(choice != 5);
    }
};

int main(){
    Array arr;
    arr.run();
    
    return 0;
}