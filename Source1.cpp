#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

void print(vector<int> array) {
    for (int i = 0; i < array.size(); i++) cout << array[i] << "->";
    cout << "\n";
}
void print2(vector<vector<int>> array) {
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < array[i].size(); j++)
            cout << array[i][j] << "->";
        cout << "\n";
    }
}
void print3(map<int, set<int>> myMap) {
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) {
        cout << it->first << " ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            cout << *it2 << " ";
        cout << "\n";
    }
}
vector<int> split(string string) {
    stringstream iss(string);
    int number;
    vector<int> ans;
    while (iss >> number)
        ans.push_back(number);
    return ans;
}
vector<vector<int>> getData(string fileName) {
    string temp;
    vector<vector<int>> data;
    ifstream MyReadFile(fileName);
    int counter = 0;
    while (getline(MyReadFile, temp)) {
        if (counter > 3) data.push_back(split(temp));
        counter += 1;
    }
    MyReadFile.close();
    return data;
}

class Stack {
public:
    vector<int> array;
    void push(int value) {
        array.push_back(value);
    }
    int pop() {
        int ans = array.back();
        array.pop_back();
        return ans;
    }
    int top() {
        return array.back();
    }
    bool is_empty() {
        return array.size() == 0;
    }
};
class Queue {
public:
    vector<int> array;
    void push(int value) {
        array.push_back(value);
    }
    int pop() {
        int ans = *array.begin();
        array.erase(array.begin());
        return ans;
    }
    int top() {
        return *array.begin();
    }
    bool is_empty() {
        return array.size() == 0;
    }
};
class Graph {
public:
    map<int, set<int>> graph;
    void addEdge(int u, int v) {
        graph[u].insert(v);
    }
    vector<int> BFS(int start) {
        Queue queue;
        queue.push(start);
        vector<int> ans;
        while (!queue.is_empty()) {
            int vertex = queue.pop();
            if (count(ans.begin(), ans.end(), vertex)) continue;
            ans.push_back(vertex);
            for (auto it = graph.cbegin(); it != graph.cend(); ++it) {
                if (it->first == vertex) {
                    for (auto neighbor = it->second.begin(); neighbor != it->second.end(); ++neighbor) {
                        queue.push(*neighbor);
                    }
                }
            }
        }
        return ans;
    }
    vector<int> DFS(int start) {
        Stack stack;
        stack.push(start);
        vector<int> ans;
        while (!stack.is_empty()) {
            int vertex = stack.pop();
            if (count(ans.begin(), ans.end(), vertex)) continue;
            ans.push_back(vertex);
            for (auto it = graph.cbegin(); it != graph.cend(); ++it) {
                if (it->first == vertex) {
                    for (auto neighbor = it->second.begin(); neighbor != it->second.end(); ++neighbor) {
                        stack.push(*neighbor);
                    }
                }
            }
        }
        return ans;
    }
    vector<vector<int>> connectedComponents() {
        vector<int> visited;
        vector<vector<int>> ans;
        for (auto it = graph.begin(); it != graph.end(); it++) {
            if (!count(visited.begin(), visited.end(), it->first)) {
                vector<int> temp = DFS(it->first);
                visited.insert(visited.end(), temp.begin(), temp.end());
                ans.push_back(temp);
            }
        }
        return ans;
    }
};

int main() {
    int a = clock();
    cout << "Hello World!";
    Graph graph;
    vector<vector<int>> data = getData("roadNet-PA.txt");
    for (int i = 0; i < data.size(); i++) graph.addEdge(data[i][0], data[i][1]);
    cout << "DFS: \n";
    print(graph.DFS(0));
    cout << "BFS: \n";
    print(graph.BFS(0));
    cout << "ConnectedComponents: \n";
    print2(graph.connectedComponents());
    cout << "Runtime: " << clock() - a;
    return 0;

}