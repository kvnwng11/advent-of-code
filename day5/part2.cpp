#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

unordered_map<int, unordered_set<int>> adj;

bool containsCycle(vector<int> &nodes) {

    // construct new adj list
    unordered_map<int, unordered_set<int>> adjList;
    for (int i=0; i<nodes.size(); ++i) {
        for (int j=i+1; j<nodes.size(); ++j) {
            int node1 = nodes[i];
            int node2 = nodes[j];

            if (!adjList.count(node1)) adjList[node1] = {};
            if (!adjList.count(node2)) adjList[node2] = {};

            adjList[node1].insert(node2);
        }
    }

    // add original edges to graph
    for (auto [node, neighbors] : adj) {
        for (int neighbor : neighbors) {
            // these are nodes in the graph
            if (adjList.count(node) && adjList.count(neighbor)) {
                adjList[node].insert(neighbor);
            }
        }
    }

    // topological sort
    unordered_map<int, int> indegree;
    for (int node : nodes) {

        // initialize
        if (indegree.find(node) == indegree.end())
            indegree[node] = 0;

        // compute indegree
        for (auto [node2, neighbors] : adjList) {
            if (node == node2) continue;

            if (neighbors.count(node))
                indegree[node]++;
        }
    }

    queue<int> q;
    for (int node : nodes)
        if (indegree[node] == 0)
            q.push(node);

    int numVisited = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        numVisited++;

        for (int neighbor : adjList[node]) {
            indegree[neighbor]--;

            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return numVisited != nodes.size();
}

vector<int> topoSort(vector<int> &nodes) {
    unordered_map<int, unordered_set<int>> adjList;
    unordered_map<int, int> indegree;

    // construct adjList and indegree
    for (int node : nodes) {
        adjList[node] = {};
        indegree[node] = 0;
    }
    for (auto [node, neighbors] : adj) {
        for (int neighbor : neighbors) {
            // these are nodes in the graph
            if (adjList.count(node) && adjList.count(neighbor)) {
                adjList[node].insert(neighbor);
                indegree[neighbor]++;
            }
        }
    }

    // kahns algo
    queue<int> q;
    for (int node : nodes)
        if (indegree[node] == 0)
            q.push(node);

    vector<int> sortedNodes;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        sortedNodes.push_back(node);

        for (int neighbor : adjList[node]) {
            indegree[neighbor]--;

            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return sortedNodes;
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string line;
    while (fin >> line) {
        size_t delimit = line.find('|');
        if (delimit == string::npos) break;

        int num1 = stoi(line.substr(0, delimit));
        int num2 = stoi(line.substr(delimit+1));

        if (!adj.count(num1)) adj[num1] = {};
        if (!adj.count(num2)) adj[num2] = {};

        adj[num1].insert(num2);
    }

    int ans = 0;
    do {
        // delimit by commas
        vector<int> nodes;
        stringstream ss(line);
        string numStr = "";
        while (getline(ss, numStr, ',')) {
            nodes.push_back(stoi(numStr));
        }   

        if (containsCycle(nodes)) {
           vector<int> correctOrdering = topoSort(nodes);
           ans += correctOrdering[correctOrdering.size() / 2];
        }


    } while (fin >> line);

    cout << ans << endl;

	return 0;
}
