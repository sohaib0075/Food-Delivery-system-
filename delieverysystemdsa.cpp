#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

#define INF numeric_limits<int>::max()

struct node {
    int id;
    int N;
    int air;
    node* next;

    node() {
        N = 0;
        id = 0;
        air = 0;
        next = nullptr;
    }

    node(int i, int a) {
        N = 0;
        id = i;
        air = a;
        next = nullptr;
    }

    ~node() {}
};

struct Queue {
    node* head;

    Queue() {
        head = nullptr;
    }

    void push(int e) {
        node* use = new node(e, 0);
        node* curr = head;
        if (curr == nullptr) {
            head = use;
        }
        else {
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = use;
        }
    }

    void pop() {
        if (!isempty()) {
            node* use = head;
            head = head->next;
            delete use;
        }
    }

    int peek() {
        if (!isempty()) {
            return head->id;
        }
        return -1;
    }

    bool isempty() {
        return head == nullptr;
    }

    ~Queue() {
        while (!isempty()) {
            pop();
        }
    }
};

void reverse_queue(Queue& result) {
    if (result.isempty()) {
        return;
    }
    int use = result.peek();
    result.pop();
    reverse_queue(result);
    result.push(use);
}

struct Order {
    string name;
    int node_loc;
    int div_time;
    Order() {
        name = "";
        node_loc = 0;
        div_time = 0;
    }

    Order(string n, int nl, int dt) {
        name = n;
        node_loc = nl;
        div_time = dt;
    }
};

struct Restaurant {
    string name;
    Order* orders;
    int node_loc;
    int N;
    int num_orders;

    Restaurant() {
        name = "";
        orders = nullptr;
        node_loc = 0;
        N = 0;
        num_orders = 0;
    }

    Restaurant(string nam, int nl, int no, int n) {
        name = nam;
        node_loc = nl;
        N = n;
        num_orders = no;
        orders = new Order[num_orders];
    }

    void output() {
        cout << "Restaurant node value: " << node_loc << endl;
        for (int i = 0; i < num_orders; i++) {
            cout << "Order " << i + 1 << " node value: " << orders[i].node_loc << endl;
        }
    }
};

struct Graph {
    int N;
    node** grid;

    Graph() {
        N = 0;
        grid = nullptr;
    }

    Graph(int n) {
        N = n;
        grid = new node * [N];
        for (int i = 0; i < N; ++i) {
            grid[i] = nullptr;
        }
    }

    void add_edge(int from, int to, int a) {
        node* use = new node(to, a);
        use->next = grid[from];
        grid[from] = use;
    }

    int minDistance(int dist[], bool visited[], int V) {
        int minDist = INF, minIndex = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    int dijkstra(int source, int target, int* deliveryTimes) {
        bool* visited = new bool[N];
        int* dist = new int[N];

        for (int i = 0; i < N; ++i) {
            visited[i] = false;
            dist[i] = INF;
        }

        dist[source] = 0;

        for (int count = 0; count < N - 1; ++count) {
            int u = minDistance(dist, visited, N);

            if (u == -1)
                break;

            visited[u] = true;

            for (node* v = grid[u]; v != nullptr; v = v->next) {
                if (!visited[v->id] && dist[u] != INF && dist[u] + 1 < dist[v->id]) {
                    if (dist[u] + 1 <= deliveryTimes[v->id]) {
                        dist[v->id] = dist[u] + 1;
                    }
                }
            }
        }

        int result = dist[target];
        delete[] visited;
        delete[] dist;
        return result;
    }

    void PrintGraph() {
        int count = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << setw(3) << count++ << " ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        for (int i = 0; i < N; ++i) {
            node* current = grid[i];
            while (current) {
                node* use = current;
                current = current->next;
                delete use;
            }
        }
        delete[] grid;
    }
};

void processFile(const string& testfile) {
    ifstream file(testfile);
    if (!file.is_open()) {
        cout << "File " << testfile << " is not opening or not opened " << endl;
        return;
    }

    int tests;
    file >> tests;

    for (int t = 0; t < tests; t++) {
        cout << "Test Case " << t + 1 << ":" << endl;

        int N, num_riders, num_rest;
        file >> N >> num_riders >> num_rest;
        Graph g(N);

        cout << "\nRiders: " << num_riders << "\nRestaurants: " << num_rest << endl;

        for (int i = 0; i < N - 1; ++i) {
            int from, to, a;
            file >> from >> to >> a;
            g.add_edge(from - 1, to - 1, a);
        }

        Restaurant* rest;
        rest = new Restaurant[num_rest];
        for (int i = 0; i < num_rest; ++i) {
            string rest_name;
            int rest_loc, num_orders;
            file >> rest_name >> rest_loc >> num_orders;
            cout << "Restaurant " << i + 1 << ": " << rest_name << "\nLocation: " << rest_loc << "\nNumber of Orders: " << num_orders << endl;

            rest[i] = Restaurant(rest_name, rest_loc, num_orders, N);

            for (int j = 0; j < num_orders; j++) {
                string order_name;
                int order_location, div_time;
                file >> order_name >> order_location >> div_time;
                cout << "Order " << j + 1 << ": " << order_name << "\nLocation: " << order_location << "\nDelivery Time: " << div_time << endl;

                rest[i].orders[j] = Order(order_name, order_location, div_time);
            }
            rest[i].output();
        }

        int* deliveryTimes = new int[N];
        for (int i = 0; i < N; ++i) {
            file >> deliveryTimes[i];
        }

        int shortestPathLength = g.dijkstra(0, N - 1, deliveryTimes);
        if (shortestPathLength == INF)
            cout << "Shortest Path Length: " << "No path exists." << endl;
        else
            cout << "Shortest Path Length: " << shortestPathLength << endl;

        delete[] deliveryTimes;
    }

    file.close();
}

int main() {
    processFile("test.txt");
    return 0;
}

