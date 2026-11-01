// Create a program that sorts elements by allowing users to choose between:
// • Linear search/Sentinel searchCO2
// Page 13 of 48• Binary search/Fibonacci search
// Compare time complexities for datasets of varying sizes

// Sorting large sales data efficiently is crucial in e-commerce platforms. Write
// programs for merge sort and quicksort. Use large datasets to compare
// execution time and identify best/worst case scenarios.

#include <iostream>
using namespace std;

const int d_capacity = 1000;
const int line_width = 70;

class Array
{
public:
    int total_capacity;
    int total_size;
    int *arr;

    Array() : total_capacity(d_capacity), total_size(0)
    {
        arr = new int[d_capacity];
    }

    Array(int capacity) : total_size(0)
    {
        if (capacity > 0)
        {
            total_capacity = capacity;
            arr = new int[capacity];
        }
        else
        {
            total_capacity = d_capacity;
            arr = new int[d_capacity];
        }
    }

    ~Array()
    {
        delete[] arr;
    }

    void user_fill(int size)
    {
        if (size > 0 && size < total_capacity)
        {
            total_size = size;
        }
        else
        {
            total_size = 0;
        }
        cout << "Enter " << total_size << " elements: \n";
        for (int i = 0; i < total_size; i++)
        {
            cin >> arr[i];
        }
        cout << "Arrayy filled with " << total_size << " elements\n";
    }

    void random_fill(int size)
    {
        if (size > 0 && size <= total_capacity)
        {
            total_size = size;
        }
        else
        {
            total_size = 0;
        }
        cout << "Enter " << total_size << " elements: \n";
        for (int i = 0; i < total_size; i++)
        {
            arr[i] = rand() % 1000;
        }
        cout << "Arrayy filled with " << total_size << "elements\n";
    }

    bool empty()
    {
        return total_size == 0;
    }

    bool full()
    {
        return total_size == total_capacity;
    }

    int start()
    {
        return 0;
    }

    int end()
    {
        return (empty()) ? 0 : total_size - 1;
    }

    void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void show()
    {
        if (empty())
        {
            cout << "Array is empty\n";
            return;
        }
        cout << "Printing array of size " << total_size << "\n{";
        for (int i = 0; i < total_size - 1; i++)
        {
            cout << arr[i] << ", ";
        }
        cout << arr[total_size - 1] << "}\n";
    }

    int partition(int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        i++;
        swap(arr[high], arr[i]);

        return i;
    }

    void quick_sort(int low, int high)
    {
        if (low >= high)
        {
            return;
        }

        int p = partition(low, high);

        quick_sort(low, p - 1);
        quick_sort(p + 1, high);
    }

    void merge(int low, int mid, int high)
    {
        int *temp = new int[high - low + 1];
        int i = low;
        int j = mid + 1;
        int k = 0;

        while (i <= mid && j <= high)
        {
            if (arr[i] <= arr[j])
            {
                temp[k] = arr[i];
                i++;
            }
            else
            {
                temp[k] = arr[j];
                j++;
            }
            k++;
        }
        while (i <= mid)
        {
            temp[k] = arr[i];
            k++;
            i++;
        }
        while (j <= high)
        {
            temp[k] = arr[j];
            k++;
            j++;
        }
        k = 0;
        for (int i = low; i <= high; i++)
        {
            arr[i] = temp[k];
            k++;
        }

        delete[] temp;
    }

    void merge_sort(int low, int high)
    {
        if (low >= high)
            return;

        int mid = (low + high) / 2;

        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }

    int linear_search(int key)
    {
        for (int i = start(); i <= end(); i++)
        {
            if (arr[i] == key)
            {
                return i;
            }
        }
        return -1;
    }

    int sentinel_search(int key)
    {
        if (full())
        {
            cout << "Cannot perform sentinel on a full array\n";
            return -1;
        }
        else if (empty())
        {
            return -1;
        }
        arr[end() + 1] = key;
        int i = start();
        while (arr[i] != key)
        {
            i++;
        }
        return (i == end() + 1) ? -1 : i;
    }

    int binary_search(int key)
    {
        int l = start(), r = end();
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (key == arr[mid])
            {
                return mid;
            }
            else if (key < arr[mid])
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return -1;
    }

    // 0 1 1 2 3 5 8 13 21
    int fibonacci(int key)
    {
        int n = total_size;
        int fibm2 = 0, fibm1 = 1, fibm = 1;
        while (fibm < n)
        {
            fibm2 = fibm1;
            fibm1 = fibm;
            fibm = fibm1 + fibm2;
        }

        int offset = -1;

        while (fibm > 1)
        {
            int i = (offset + fibm2 < n) ? offset + fibm2 : n - 1;
            if (arr[i] == key)
            {
                return i;
            }
            else if (arr[i] < key)
            {
                offset = fibm2;
                fibm = fibm1;
                fibm1 = fibm2;
                fibm2 = fibm - fibm1;
            }
            else
            {
                fibm = fibm2;
                fibm1 = fibm1 - fibm2;
                fibm2 = fibm - fibm1;
            }
        }
        if (offset + 1 < n && fibm1 && arr[offset + 1] == key)
        {
            return offset + 1;
        }
        return -1;
    }
};
// EOC Array

int main()
{
    Array obj;
    obj.random_fill(10);
    obj.show();

    return 0;
}
