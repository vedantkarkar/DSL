#include <iostream>
using namespace std;

class Playlist
{
private:
    class Node
    {
    public:
        char song[50];
        Node *prev;
        Node *next;

        Node(char name[])
        {
            int i = 0;

            while (name[i] != '\0')
            {
                song[i] = name[i];
                i++;
            }

            song[i] = '\0';

            prev = NULL;
            next = NULL;
        }
    };

    Node *head;
    Node *tail;

public:
    Playlist()
    {
        head = NULL;
        tail = NULL;
    }

    // Add song at the end
    void addSong(char name[])
    {

        Node *newNode = new Node(name);

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

        cout << "Song added.\n";
    }

    // Remove song by name
    void removeSong(char name[])
    {

        Node *current = head;

        while (current != NULL)
        {

            int i = 0;
            bool same = true;

            while (name[i] != '\0' || current->song[i] != '\0')
            {

                if (name[i] != current->song[i])
                {
                    same = false;
                    break;
                }

                i++;
            }

            if (same)
            {

                // Only node
                if (current == head && current == tail)
                {
                    head = NULL;
                    tail = NULL;
                }

                // First node
                else if (current == head)
                {
                    head = current->next;
                    head->prev = NULL;
                }

                // Last node
                else if (current == tail)
                {
                    tail = current->prev;
                    tail->next = NULL;
                }

                // Middle node
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;

                cout << "Song removed.\n";
                return;
            }

            current = current->next;
        }

        cout << "Song not found.\n";
    }

    // Display from beginning to end
    void displayForward()
    {

        if (head == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        Node *current = head;

        cout << "\nPlaylist (Forward):\n";

        while (current != NULL)
        {
            cout << current->song << endl;
            current = current->next;
        }
    }

    // Display from end to beginning
    void displayBackward()
    {

        if (tail == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        Node *current = tail;

        cout << "\nPlaylist (Backward):\n";

        while (current != NULL)
        {
            cout << current->song << endl;
            current = current->prev;
        }
    }

    ~Playlist()
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

    Playlist playlist;

    int choice;
    char song[50];

    do
    {

        cout << "\n===== MUSIC PLAYLIST =====\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Display Forward\n";
        cout << "4. Display Backward\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            cout << "Enter song name: ";
            cin >> song;
            playlist.addSong(song);
            break;

        case 2:
            cout << "Enter song name to remove: ";
            cin >> song;
            playlist.removeSong(song);
            break;

        case 3:
            playlist.displayForward();
            break;

        case 4:
            playlist.displayBackward();
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
