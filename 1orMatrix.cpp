// You are building a backend module for a financial reporting system used by
// multinational corporations. Each department in each country generates a
// matrix of financial figures representing revenues and expenses over a period
// (e.g., months vs. categories). These matrices are used for global analysis,
// budgeting, and projections. You are tasked with writing a code for the
// following operations:
// a) Addition of two matrices
// b) Subtraction of two matrices
// c) Multiplication of two matrices
// d) Transpose of a matrix

#include <iostream>
using namespace std;

// Constants for the program:
const int default_degree = 3;
const int line_width = 70;

void drawline(int length = line_width)
{
    for (int i = 0; i < length; i++)
    {
        cout << '-';
    }
    cout << endl;
}

class Program
{
public:
    class Matrix
    {
    public:
        int **arr;
        int n;

        Matrix() : n(default_degree)
        {
            arr = new int *[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = new int[n];
            }
        }
        Matrix(int degree) : n(degree)
        {
            arr = new int *[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = new int[n];
            }
        }
        ~Matrix()
        {
            for (int i = 0; i < n; i++)
            {
                delete[] arr[i];
            }
            delete[] arr;
        }

        // Overloading [] operator to allow Matrix[i][j]
        int *operator[](int i)
        {
            return arr[i];
        }

        // Get a matrix from user input:
        void fill()
        {
            cout << "Enter the matrix with degree " << n << ": " << endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cin >> arr[i][j];
                }
            }
        }

        // Swap two elements
        void swap(int &a, int &b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        void transpose()
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    swap(arr[i][j], arr[j][i]);
                }
            }
        }

        void show()
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << arr[i][j] << " ";
                }
                cout << "\n";
            }
        }
    };
    // EOC Matrix

    int n;
    Matrix A;
    Matrix B;
    Matrix result;

    Program(int degree) : n(degree), A(degree), B(degree), result(degree) {}

    Program() : n(default_degree), A(n), B(n), result(n) {}

    void addition()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = A[i][j] + B[i][j];
            }
        }
    }

    void AsubsB()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = A[i][j] - B[i][j];
            }
        }
    }

    void BsubsA()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = B[i][j] - A[i][j];
            }
        }
    }

    void multiply()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = 0;
                for (int k = 0; k < n; k++)
                {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    void show_menu()
    {
        cout << "\t\t\tMENU\n";
        cout << "0. Change matrices\n";
        cout << "1. Show Matrix\n";
        cout << "2. Addition of two matrices\n";
        cout << "3. Substraction of two matrices\n";
        cout << "4. Multiplication of two matrices\n";
        cout << "5. Transpose of a matrix\n";
        cout << "6. Exit\n";
    }

    void perform(int ch)
    {
        switch (ch)
        {
        case 0:
            cout << "Enter Matrix A: \n";
            A.fill();
            cout << "\nEnter Matrix B: \n";
            B.fill();
            cout << "Both matrices filled.\n";
            break;

        case 1:
            cout << "Enter 1 to choose A and 2 for B: \n";
            int choice3;
            while (true)
            {
                cin >> choice3;
                if (choice3 == 1 || choice3 == 2)
                {
                    break;
                }
                cout << "Enter a valid choice of 1 or 2\n";
            }
            if (choice3 == 1)
            {
                cout << "A = \n";
                A.show();
            }
            else
            {
                cout << "B = \n";
                B.show();
            }
            break;

        case 2:
            addition();
            cout << "Result of addition: \n";
            result.show();
            break;

        case 3:
            cout << "Enter 1 to do A - B and 2 for B - A: \n";
            int choice;
            while (true)
            {
                cin >> choice;
                if (choice == 1 || choice == 2)
                {
                    break;
                }
                cout << "Enter a valid choice of 1 or 2\n";
            }
            if (choice == 1)
            {
                cout << "A - B = \n";
                AsubsB();
                result.show();
            }
            else
            {
                cout << "B - A = \n";
                BsubsA();
                result.show();
            }
            break;

        case 4:
            multiply();
            cout << "Result of Multiplication: \n";
            result.show();
            break;

        case 5:
            cout << "Enter 1 to do A transpose and 2 for B transpose: \n";
            int choice1;
            while (true)
            {
                cin >> choice1;
                if (choice1 == 1 || choice1 == 2)
                {
                    break;
                }
                cout << "Enter a valid choice of 1 or 2\n";
            }
            if (choice1 == 1)
            {
                cout << "A transpose = \n";
                A.transpose();
                A.show();
            }
            else
            {
                cout << "B transpose = \n";
                B.transpose();
                B.show();
            }
            break;

        case 6:
            cout << "Exiting the program\n";
            break;

        default:
            cout << "Enter a valid output." << endl;
            break;
        }
    }

    void run()
    {
        int choice;
        A.fill();
        B.fill();
        do
        {
            drawline();
            show_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        } while (choice != 6);
    }
};
// EOC Program

int main()
{
    // place the degree of matrix you want:
    Program object(3);
    object.run();
    return 0;
}
