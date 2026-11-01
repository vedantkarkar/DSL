// A national electricity provider is tasked with building a power grid that
// connects all major substations across the country. Each potential connection
// (power line) between two substations has an associated installation cost
// based on distance, terrain, and material. To minimize infrastructure cost, the
// company needs to select a subset of connections such that all substations
// are connected, and the total cost is minimized, without forming any
// redundant loops. Solve the problem by using an appropriate algorithm.

#include <iostream>
using namespace std;

struct Edge
{
    int u, v, cost;
};

int parent[100];

int find(int x)
{
    while (parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void sortEdges(Edge e[], int m)
{
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - i - 1; j++)
        {
            if (e[j].cost > e[j + 1].cost)
            {
                Edge t = e[j];
                e[j] = e[j + 1];
                e[j + 1] = t;
            }
        }
    }
}

int main()
{
    Edge e[500];
    int n, m;

    cout << "Enter number of substations and connections: ";
    cin >> n >> m;

    if (n < 1 || n > 100 || m < 0 || m > 500)
    {
        cout << "Invalid input!\n";
        return 0;
    }

    cout << "Enter connections (u v cost), vertices 0 to "
         << n - 1 << ":\n";

    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].cost;

        if (e[i].u < 0 || e[i].u >= n ||
            e[i].v < 0 || e[i].v >= n)
        {
            cout << "Invalid vertex!\n";
            return 0;
        }
    }

    for (int i = 0; i < n; i++)
        parent[i] = i;

    sortEdges(e, m);

    int total = 0, count = 0;

    cout << "\nSelected power lines:\n";

    for (int i = 0; i < m && count < n - 1; i++)
    {
        int a = find(e[i].u);
        int b = find(e[i].v);

        if (a != b)
        {
            parent[a] = b;
            cout << e[i].u << " - " << e[i].v
                 << " : " << e[i].cost << "\n";

            total += e[i].cost;
            count++;
        }
    }

    if (count != n - 1)
        cout << "Graph is disconnected; MST does not exist.\n";
    else
        cout << "Minimum total cost = " << total << "\n";

    return 0;
}
