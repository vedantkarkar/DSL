// A social network stores friends/followers as a graph. Write a program to
// represent users as nodes using adjacency matrix or adjacency list.
// • Find mutual friends (common neighbors)
// • Identify influencers (nodes with highest degree)

#include <iostream>
using namespace std;

const int line_width = 70;
const int default_cap = 50;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

const string BOLD = "\033[1m";

void drawline(int length = line_width){
    for(int i = 0; i < length; i++){
        cout << "-";
    }
    cout << endl;
}

class Graph{
    public:

    int total_capacity;
    int vertices;
    
    string* name;

    // 2D adjacency matrix
    bool** adj;

    Graph(): vertices(0), total_capacity(default_cap){
        name = new string[default_cap];
        adj = new bool*[default_cap];

        for(int i = 0; i < total_capacity; i++){
            adj[i] = new bool[total_capacity];
            for(int j = 0; j < total_capacity; j++){
                adj[i][j] = false;
            }
        }

    }

    Graph(int cap): vertices(0), total_capacity(cap){
        name = new string[cap];
        adj = new bool*[cap];

        for(int i = 0; i < total_capacity; i++){
            adj[i] = new bool[total_capacity];
            for(int j = 0; j < total_capacity; j++){
                adj[i][j] = false;
            }
        }

    }

    ~Graph(){
        for(int i = 0; i < total_capacity; i++){
            delete[] adj[i];
        }
        delete[] adj;

        delete[] name;
    } 

    bool empty(){
        return vertices == 0;
    }

    bool full(){
        return vertices == total_capacity;
    }

    void init(int v){
        if(v < 0){
            cerr << "Negative number of vertices not allowed.\nAborted.\n";
            return;
        }
        else if(v > total_capacity){
            cerr << "Memory overflow detected, try a smaller number than " << total_capacity << ".\nAborted\n";
            return;
        }

        // set vertices to appropriate v
        vertices = v;

        // taking names of v friends
        cout << "Enter " << v << " friends in the group\n";
        cin.ignore();
        for(int i = 0; i < v; i++){
            cout << "Friend "<< i+1 << " : ";
            getline(cin, name[i]);
        }

        // asking for their connections
        display_friendlist();
        for(int i = 0; i < v - 1; i++){
            int count = 0;
            while(count < v - i - 1){
                cout << "Who " << name[i] << " is friends with?\n"   
                    << "Press their number or press -1 to terminate the process: \n";
                for(int j = i+1; j < v; j++){
                    cout << j+1 << ". " << name[j] << endl;
                }
                int ch;
                cout << "Choice: ";
                cin >> ch;
                ch--;
                // since pressing -1 and doing ch-- will make it -2
                if(ch == -2){
                    break;
                }
                else if(ch > i && ch < v){
                    adj[i][ch] = adj[ch][i] = true;
                    cout << name[i] << " is friends with " << name[ch] << endl; 
                    count++;
                }
            }
        }

    }

    void display_friendlist(){
        if(empty()){
            cout << "Network is empty.\n";
            return;
        }
        cout << "Displaying friendlist of " << vertices << " length\n";
        for(int i = 0; i < vertices; i++){
            cout << i+1 << ". " << name[i] << endl;
        }
    }

    void display_matrix(){
        if(empty()){
            cout << "No vertices to show the matrix\n";
            return;
        }

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(j != vertices - 1){
                    if(adj[i][j]){
                        cout << GREEN << adj[i][j] << RESET << " | ";
                    }
                    else{
                        cout << adj[i][j] << " | ";
                    }
                }
                else{
                    if(adj[i][j]){
                        cout << GREEN << adj[i][j] << RESET << endl;
                    }
                    else{
                        cout << adj[i][j] << endl;
                    }
                    
                }
            }
            // print line
            if(i != vertices - 1){
                for(int k = 0; k < vertices; k++){
                    if(k == 0){
                        cout << "--+";
                    }
                    else if(k != vertices - 1){
                        cout << "---+";
                    }
                    else{
                        cout << "---\n";
                    }
                }
            }
        }
    }

    void describe(){
        cout << "Graph Description: \n";
        cout << "Total Capacity = " << total_capacity << endl;
        cout << "Total Vertices = " << vertices << endl;
        cout << "List of vertices: \n";
        display_friendlist();
        cout << "Graph with adjacency matrix: \n";
        display_matrix();
    }

    // Returns out degree of a vertex i, and -1 if vertex not found
    int degree(int i){
        if(i < vertices){
            int deg = 0;
            for(int j = 0; j < vertices; j++){
                if(adj[i][j]) deg++;
            }
            return deg;
        }
        return -1;
    }

    void mutual_friends(){
        int check = 0;
        for(int i = 0; i < vertices; i++){
            int deg = degree(i);
            if(deg > 1){
                drawline();
                check++;
                cout << name[i] << " is mutual friend of: \n";
                int count = 0;
                for(int j = 0; j < vertices; j++){
                    if(adj[i][j]){
                        count++;
                        cout << count << ". " << name[j] << endl;
                    }
                }
            }
        }
        if(!check){
            cout << "No mutual friendship found in current network\n";
        }
    }

    // returns the vertex with maximum degree
    int influencer(){
        int inf = -1;
        int max = -1;
        for(int i = 0; i < vertices; i++){
            if(degree(i) > max){
                max = degree(i);
                inf = i;
            }
        }
        return inf;
    }


    // init
    // update a friendship
    // Display candidates in the network
    // • Find mutual friends (common neighbors)
    // • Identify influencers (nodes with highest degree)
    // Describe the network
    // exit
    void show_menu(){
        cout << BLUE << "\t\t\tSocial Network" << RESET << endl;
        cout << "1. " << BOLD << "Initialize" << RESET << " new network\n";
        cout << "2. " << BOLD << "Display" << RESET << " Candidates in the Network\n";
        cout << "3. Find " << BOLD << "Mutual friends\n" << RESET;
        cout << "4. Identify most " << BOLD << "influential" << RESET << " friend\n";
        cout << "5. " << BOLD << "Describe" << RESET << " Network using Data Structures\n";
        cout << "6. " << BOLD << "Exit\n" << RESET;
    }

    void perform(int ch){
        switch(ch){
            case 1:
                int v;
                cout << "Enter the number of friends you want to add: ";
                cin >> v;
                init(v);
            break;
            
            case 2:
                display_friendlist();
            break;

            case 3:
                cout << "Finding mutual friendships in the network: \n";
                mutual_friends();
            break;

            case 4: 
                if(!empty()){
                    cout << "Most influential friend in the network is " << name[influencer()] << "!\n";
                    cout << "With most " << degree(influencer()) << " Friends\n";
                }
                else{
                    cout << "Network has no candidates!\n";
                }
                break;

            case 5: 
                describe();
            break;

            case 6:
                cout << "Please wait while program exits.\nExiting...\n";
                drawline();
            break;

            default: 
                cout << "Enter a Valid choice between 1 to 6.\n";
        }
    }

    void run(){
        int choice = 0;
        do{
            drawline();
            show_menu();
            cout << "Enter your choice: ";
            cin >> choice;
            perform(choice);
        }while(choice != 6);
    }

};

int main(){
    Graph SocialNetwork;
    SocialNetwork.run();

    return 0;
}