#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<ctime>
#include<cstdlib>
#include <unistd.h>
#include<set>
#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int tolls;
    int distance;
    int time;
};
struct edgemet{
    int v;
    int interchange;
    int distanc;
};
int counterroad=10;
int countmetro=10;

vector<vector<Edge>> Graph(15);
vector<vector<edgemet>>Graphm(15);
void typewriterEffect(const string& text, int delay = 10) {
    for (char c : text) {
        cout << c << flush;
        usleep(delay * 1000); // Convert milliseconds to microseconds
    }
    cout << endl;
}
string getPasswords(const string& prompt = "Enter password: ") {
    cout << prompt;
    string password;
    char ch;

    while ((ch = getchar()) != '\r') {  
        if (ch == '\b') {  
            if (!password.empty()) {
                cout << "\b \b"; 
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*';  
        }
    }
    cout << endl;  
    return password;
}

void displayRouteSaathiArt() {
    cout << "================================================================================================" << endl;
    typewriterEffect("RRRRRR    OOOOO   U   U   TTTTT  EEEEE      SSSS    AAAAA   AAAAA   RRRRR   TTTTT  H   H  III");
    typewriterEffect("R    R   O     O  U   U     T    E          S       A   A   A   A   R   R     T    H   H   I ");
    typewriterEffect("RRRRRR   O     O  U   U     T    EEEE        SSS    AAAAA   AAAAA   RRRRR     T    HHHHH   I ");
    typewriterEffect("R   R    O     O  U   U     T    E              S   A   A   A   A   R   R     T    H   H   I ");
    typewriterEffect("R    R    OOOO     UUU      T    EEEEE      SSSS    A   A   A   A   R    R    T    H   H  III");
    cout << "================================================================================================" << endl;
}

string getPassword(const string& prompt = "Enter password: ") {
    cout << prompt;
    string password;
    cin >> password; 
    return password;
}

void initializeGraph() {
    srand(time(0));
    for (int i = 0; i < 15; i++) {
        int u = rand() % 10;
        int v = rand() % 10;
        if (u == v) continue;

        Edge edges;
        edges.v = v;
        edges.tolls = rand() % 20 + 1;
        edges.distance = rand() % 100 + 1;
        edges.time = rand() % 60 + 1;

        Graph[u].push_back(edges);
        Graph[v].push_back({u, edges.tolls, edges.distance, edges.time});
    }
}

void initializeGraphMetro() {
    set<pair<int, int>> edgeset;
     srand(time(0));
    for (int i = 0; i < 15; i++) {
        int u = rand() % 10;
        int v = rand() % 10;
        if (u == v) continue;
        edgemet edges;
        edges.v = v;
        edges.distanc = rand() % 20 + 1;
        edges.interchange = 1; 
        if(edgeset.count({u, v}) == 0)
        {
        edgeset.insert({u, v});
        edgeset.insert({v, u});
        Graphm[u].push_back(edges);
        Graphm[v].push_back({u, 1, edges.distanc});

        }
    }
}


void newEdge() {
    int u, v, t, d, ti;
    cout << "Enter the vertex you want to add an edge from: ";
    cin >> u;
    cout << "Enter the vertex you want to add an edge to: ";
    cin >> v;
    cout << "Enter the toll amount from " << u << " to " << v << ": ";
    cin >> t;
    cout << "Enter the distance from " << u << " to " << v << ": ";
    cin >> d;
    cout << "Enter the time from " << u << " to " << v << ": ";
    cin >> ti;

    Edge edges;
    edges.v = v;
    edges.tolls = t;
    edges.distance = d;
    edges.time = ti;
    Graph[u].push_back(edges);
    Graph[v].push_back({u, t, d, ti});
    cout << "Your new path has been added successfully.\n";
}

void newVertex() {
    int u;
    cout << "Enter new destination code: ";
    cin >> u;
    int ec = 0;
    while (ec != 2) {
        int ch3;
        cout << "1. Enter new routes\n";
        cout << "2. Exit\n";
        cin >> ch3;
        if (ch3 == 1) {
            int v, t, d, ti;
            cout << "Enter the vertex you want to add an edge to: ";
            cin >> v;
            cout << "Enter the toll amount from " << u << " to " << v << ": ";
            cin >> t;
            cout << "Enter the distance from " << u << " to " << v << ": ";
            cin >> d;
            cout << "Enter the time from " << u << " to " << v << ": ";
            cin >> ti;
            Edge edges;
            edges.v = v;
            edges.tolls = t;
            edges.distance = d;
            edges.time = ti;
            Graph[u].push_back(edges);
            counterroad++;
            cout << "Your new path has been added successfully.\n";
        } else if (ch3 == 2) {
            ec = 2;
        }
    }
}

void printPath(int vertex, const vector<int>& previous) {
    if (vertex == -1) return;
    printPath(previous[vertex], previous);
    cout << vertex << " ";
}

void shortest_moneysaver() {
    cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> toll(counterroad, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(counterroad, -1);
    toll[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > toll[u]) continue;

        for (const auto& edge : Graph[u]) {
            int weight = edge.tolls;
            int next = edge.v;

            if (toll[u] + weight < toll[next]) {
                toll[next] = toll[u] + weight;
                pq.push({toll[next], next});
                previous[next] = u;
            }
        }
    }
    cout << "Your least required toll is: " << toll[v] << "\nPath: ";
    printPath(v, previous);
    cout << endl;
}

void shortest_fuelsaver() {
    cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> distance(counterroad, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(counterroad, -1);
    distance[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (const auto& edge : Graph[u]) {
            int weight = edge.distance;
            int next = edge.v;

            if (distance[u] + weight < distance[next]) {
                distance[next] = distance[u] + weight;
                pq.push({distance[next], next});
                previous[next] = u;
            }
        }
    }
    cout << "Your least required distance is: " << distance[v] << "\nPath: ";
    printPath(v, previous);
    cout << endl;
}

void shortest_timesaver() {
    cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> time(counterroad, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(counterroad, -1);
    time[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > time[u]) continue;

        for (const auto& edge : Graph[u]) {
            int weight = edge.time;
            int next = edge.v;

            if (time[u] + weight < time[next]) {
                time[next] = time[u] + weight;
                pq.push({time[next], next});
                previous[next] = u;
            }
        }
    }
    cout << "Your least required time is: " << time[v] << "\nPath: ";
    printPath(v, previous);
    cout << endl;
}
void minimumInterchange(){
      cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> interchanges(countmetro, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(countmetro, -1);
    interchanges[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > interchanges[u]) continue;

        for (const auto& edge : Graphm[u]) {
            int weight = edge.interchange;
            int next = edge.v;

            if (interchanges[u] + weight < interchanges[next]) {
                interchanges[next] = interchanges[u] + weight;
                pq.push({interchanges[next], next});
                previous[next] = u;
            }
        }
    }
    cout << "Your least required interchanged is: " << interchanges[v] << "\nPath: ";
    printPath(v, previous);
    cout << endl;
}
void minimumTime(){
    cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> distance(countmetro, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(countmetro, -1);
    distance[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (const auto& edge : Graphm[u]) {
            int weight = edge.distanc;
            int next = edge.v;

            if (distance[u] + weight < distance[next]) {
                distance[next] = distance[u] + weight;
                pq.push({distance[next], next});
                previous[next] = u;
            }
        }
    }
    cout << "Your least required distance is: " << distance[v] << "\nPath: ";
    printPath(v, previous);
}
void newstation(){
int u;
    cout << "Enter new destination code: ";
    cin >> u;
    int ec = 0;
    while (ec != 2) {
        int ch3;
        cout << "1. Enter new routes\n";
        cout << "2. Exit\n";
        cin >> ch3;
        if (ch3 == 1) {
            int v, d, intr;
            cout << "Enter the vertex you want to add an edge to: ";
            cin >> v;
            cout << "Enter the distance from " << u << " to " << v << ": ";
            cin >> d;
            cout << "Enter the interchange from " << u << " to " << v << ": ";
            cin >> intr;
            edgemet edges;
            edges.v = v;
            edges.distanc = d;
            edges.interchange = intr;
            Graphm[u].push_back(edges);
            countmetro++;
            cout << "Your new path has been added successfully.\n";
        } else if (ch3 == 2) {
            ec = 2;
        }
    }
}
void newroute(){
int u, v, d, intr;
    cout << "Enter the vertex you want to add an edge from: "<<endl;
    cin >> u;
    cout << "Enter the vertex you want to add an edge to: "<<endl;
    cin >> v;
    cout << "Enter the distance from " << u << " to " << v << ": "<<endl;
    cin >> d;
    cout << "Enter the interchange from " << u << " to " << v << ": "<<endl;
    cin >> intr;

    edgemet edges;
    edges.v = v;
    edges.distanc = d;
    edges.interchange = 1;
    Graphm[u].push_back(edges);
    Graphm[v].push_back({u,d,1});
    cout << "Your new path has been added successfully."<<endl;
}
void showRoadMap(const vector<vector<Edge>>& graph) {
    cout << "Road Graph Structure:\n";
    for (int i = 0; i < graph.size(); ++i) {
        if (!graph[i].empty()) {
            cout << "Node " << i << " is connected to:\n";
            for (const auto& edge : graph[i]) {
                cout << "  -> Node " << edge.v << " [Tolls: " << edge.tolls 
                     << ", Distance: " << edge.distance << " km, Time: " 
                     << edge.time << " mins]\n";
            }
        }
    }
}
void showMetroMap(const vector<vector<edgemet>>& graphm) {
    cout << "Metro Graph Structure:\n";
    for (int i = 0; i < graphm.size(); ++i) {
        if (!graphm[i].empty()) {
            cout << "Station " << i << " is connected to:\n";
            for (const auto& edge : graphm[i]) {
                cout << "  -> Station " << edge.v << " [Interchanges: " 
                     << edge.interchange << ", Distance: " << edge.distanc 
                     << " km]\n";
            }
        }
    }
}
double calculateFare(int distance) {
    const double baseFare = 10.0;
    const double perKmRate = 2.5;
    return baseFare + (distance * perKmRate);
}
void bookTicket() {
    
      cout << "Enter start and end of your journey: ";
    int u, v;
    cin >> u >> v;
    vector<int> distance(10, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> previous(10, -1);
    distance[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (const auto& edge : Graphm[u]) {
            int weight = edge.distanc;
            int next = edge.v;

            if (distance[u] + weight < distance[next]) {
                distance[next] = distance[u] + weight;
                pq.push({distance[next], next});
                previous[next] = u;
            }
        }
    }
    int distances = distance[v];
    if (distances == -1) {
        cout << "No path found between " << u << " and " << v << ".\n";
        return;
    }

    double fare = calculateFare(distances);

    cout << "\n--- Metro Ticket ---\n";
    cout << "From: " << u << "\n";
    cout << "To: " << v<< "\n";
    cout << "Distance: " << distances << " km\n";
    cout << "Fare: $" << fare << "\n";
    cout << "--------------------\n";
}
void display() {
    int ch;
    cout << "Welcome to RouteSaathi\n1. User Login\n2. Admin Login\n";
    cin >> ch;
    if (ch == 1) {
        int ch4;
        cout<<"1.RoadSaarthi"<<endl;
        cout<<"2.MetroSaarthi"<<endl;
        cin>>ch4;
        if(ch4==1){
           int ch1;
        cout << "1. MoneySaver Mode\n2. FuelSaver Mode\n3. TimeSaver Mode\n4. Show Complete Map\n";
        cin >> ch1;
        switch (ch1) {
            case 1: shortest_moneysaver(); break;
            case 2: shortest_fuelsaver(); break;
            case 3: shortest_timesaver(); break;
            case 4: showRoadMap(Graph); break;
            default: break;
        }
        }
        if(ch4==2){
            int ch5;
            cout<<"1.MinimumInterchange"<<endl;
            cout<<"2.MinimumTime"<<endl;
            cout<<"3.Show Complete Map"<<endl;
            cout<<"4.Book Ticket"<<endl;
            cin>>ch5;
            if(ch5==1)
            minimumInterchange();
            if(ch5==2)
            minimumTime();
            if(ch5==3)
            showMetroMap(Graphm);
            if(ch5==4)
            bookTicket();
        }
        
    } else if (ch == 2) {
        string username;
        string password;
        cout << "Enter username: ";
        cin >> username;
        password = getPassword();
        while (password != "admin") {
            cout << "Wrong username or password, re-enter."<<endl<< "Enter username: ";
            cin >> username;
            password = getPassword();
        }
        int ch6;
        cout<<"1.Metro Admin"<<endl;
        cout<<"2.Road Admin"<<endl;
        cin>>ch6;
        if(ch6==2){
           int ch2;
        cout << "1. Add a new destination on your map " <<endl ;
        cout<<"2. Add a new path in your existing destinations"<<endl;
        cout<<"3. Exit"<<endl;
        cin >> ch2;
        switch (ch2) {
            case 2: newEdge(); break;
            case 1: newVertex(); break;
            default: break;
        }
        }
        if(ch6==1){
            int ch7;
            cout<<"1.Enter route for an existing station"<<endl;
            cout<<"2.Add a new station to the system"<<endl;
            cin>>ch7;
            if(ch7==1){
                newroute();
            }
            if(ch7==2){
                newstation();
            }
        }
        
    }
}

int main() {
    displayRouteSaathiArt();
    initializeGraph();
    initializeGraphMetro();
    while (true) 
    {
        display();
        char userInput;
        cout << "Press any key to return to the main menu or '1' to exit: ";
        cin >> userInput;
        if (userInput == '1') {
            cout << "Exiting the program. Goodbye!\n";
            break;
        } else {
            cout << "Returning to the main menu...\n\n";
        }}
    
    
    
    return 0;
}
