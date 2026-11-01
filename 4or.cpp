// In embedded systems and digital circuit simulators, binary numbers are
// handled at the bit level, requiring explicit bitwise operations for various
// tasks. To simulate this behaviour, implement a binary number system using
// a doubly linked list, where each node represents a single bit (0 or 1). Compute
// the following:
// a) To compute 1’s and 2’s complement
// b) Add two binary numbers

#include <iostream>
using namespace std;

class Binary
{
private:
    class Node
    {
    public:
        int bit;
        Node *prev;
        Node *next;

        Node(int b)
        {
            bit = b;
            prev = NULL;
            next = NULL;
        }
    };

    Node *head;
    Node *tail;

public:
    Binary()
    {
        head = NULL;
        tail = NULL;
    }

    // Insert bit at the end
    void insertBit(int bit)
    {

        Node *newNode = new Node(bit);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Create binary number from user input
    void input()
    {

        char bit;

        cout << "Enter binary number: ";
        cin >> bit;

        while (bit != '\0')
        {

            if (bit == '0' || bit == '1')
            {
                insertBit(bit - '0');
            }
            else
            {
                cout << "Invalid binary number.\n";
                return;
            }

            cin.get(bit);

            if (bit == '\n')
                break;
        }
    }

    // Display binary number
    void display()
    {

        Node *current = head;

        while (current != NULL)
        {
            cout << current->bit;
            current = current->next;
        }

        cout << endl;
    }

    // Compute 1's complement
    Binary onesComplement()
    {

        Binary result;

        Node *current = head;

        while (current != NULL)
        {

            if (current->bit == 0)
                result.insertBit(1);
            else
                result.insertBit(0);

            current = current->next;
        }

        return result;
    }

    // Compute 2's complement
    Binary twosComplement()
    {

        Binary result = onesComplement();

        int carry = 1;

        Node *current = result.tail;

        while (current != NULL && carry == 1)
        {

            if (current->bit == 0)
            {
                current->bit = 1;
                carry = 0;
            }
            else
            {
                current->bit = 0;
                carry = 1;
            }

            current = current->prev;
        }

        if(carry == 1)
        {
            result.insertFront(1);
        }

        return result;
    }

    // Add two binary numbers
    Binary add(Binary &other)
    {

        Binary result;

        Node *p = tail;
        Node *q = other.tail;

        int carry = 0;

        while (p != NULL || q != NULL || carry != 0)
        {

            int sum = carry;

            if (p != NULL)
            {
                sum = sum + p->bit;
                p = p->prev;
            }

            if (q != NULL)
            {
                sum = sum + q->bit;
                q = q->prev;
            }

            result.insertFront(sum % 2);

            carry = sum / 2;
        }

        return result;
    }

    // Insert at beginning
    void insertFront(int bit)
    {

        Node *newNode = new Node(bit);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    ~Binary()
    {

        Node *current = head;

        while (current != NULL)
        {

            Node *next = current->next;

            delete current;

            current = next;
        }
    }
};

int main()
{

    Binary A, B;

    cout << "Enter first binary number:\n";
    A.input();

    cout << "Enter second binary number:\n";
    B.input();

    cout << "\nFirst number: ";
    A.display();

    cout << "Second number: ";
    B.display();

    Binary one = A.onesComplement();
    Binary two = A.twosComplement();

    cout << "\n1's Complement: ";
    one.display();

    cout << "2's Complement: ";
    two.display();

    Binary sum = A.add(B);

    cout << "\nBinary Addition: ";
    sum.display();

    return 0;
}
