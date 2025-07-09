#include "the7.h"


bool isDAGUtil(int node, std::vector<bool>& visited, std::vector<bool>& recursionStack, const std::vector<std::vector<std::pair<int, int>>>& graph) {
    visited[node] = true;
    recursionStack[node] = true;

    for (const auto& neighbor : graph[node]) {
        int nextNode = neighbor.first;
        if (!visited[nextNode] && isDAGUtil(nextNode, visited, recursionStack, graph)) {
            return true;
        } else if (recursionStack[nextNode]) {
            return true;
        }
    }

    recursionStack[node] = false;
    return false;
}

bool isDAG(const std::vector<std::vector<std::pair<int, int>>>& graph) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<bool> recursionStack(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && isDAGUtil(i, visited, recursionStack, graph)) {
            return false;
        }
    }
    return true;
}

void topologicalSort(int node, std::vector<bool>& visited, std::stack<int>& topoStack, const std::vector<std::vector<std::pair<int, int>>>& graph) {
    visited[node] = true;

    for (const auto& neighbor : graph[node]) {
        int nextNode = neighbor.first;
        if (!visited[nextNode]) {
            topologicalSort(nextNode, visited, topoStack, graph);
        }
    }

    topoStack.push(node);
}

std::vector<int> findLongestPathDAG(const std::vector<std::vector<std::pair<int, int>>>& graph, int starting_node, int destination_node, long& length_of_longest_path) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> topoStack;

    // Topological sort
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            topologicalSort(i, visited, topoStack, graph);
        }
    }

    // Initialize distances and predecessors
    std::vector<long> distances(n, LONG_MIN);
    std::vector<int> predecessor(n, -1);
    distances[starting_node] = 0;

    // Process nodes in topological order
    while (!topoStack.empty()) {
        int node = topoStack.top();
        topoStack.pop();

        if (distances[node] != LONG_MIN) {
            for (const auto& neighbor : graph[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;
                if (distances[node] + weight > distances[nextNode]) {
                    distances[nextNode] = distances[node] + weight;
                    predecessor[nextNode] = node;
                }
            }
        }
    }

    // Backtrack to find the path
    std::vector<int> path;
    if (distances[destination_node] != LONG_MIN) {
        for (int at = destination_node; at != -1; at = predecessor[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
    }

    length_of_longest_path = distances[destination_node];
    return path;
}

void exhaustiveSearch(const std::vector<std::vector<std::pair<int, int>>>& graph, int node, int destination_node, std::vector<bool>& visited, long current_length, std::vector<int>& current_path, std::vector<int>& best_path, long& max_length) {
    if (node == destination_node) {
        if (current_length > max_length) {
            max_length = current_length;
            best_path = current_path;
        }
        return;
    }

    visited[node] = true;

    for (const auto& neighbor : graph[node]) {
        int nextNode = neighbor.first;
        int weight = neighbor.second;

        if (!visited[nextNode]) {
            current_path.push_back(nextNode);
            exhaustiveSearch(graph, nextNode, destination_node, visited, current_length + weight, current_path, best_path, max_length);
            current_path.pop_back();
        }
    }

    visited[node] = false;
}

std::vector<int> find_longest_path(const std::vector<std::vector<std::pair<int, int>>>& graph, int starting_node, int destination_node, long& length_of_longest_path) {
    if (isDAG(graph)) {
        return findLongestPathDAG(graph, starting_node, destination_node, length_of_longest_path);
    } else {
        std::vector<int> best_path;
        std::vector<int> current_path = {starting_node};
        std::vector<bool> visited(graph.size(), false);
        long max_length = 0;

        exhaustiveSearch(graph, starting_node, destination_node, visited, 0, current_path, best_path, max_length);

        length_of_longest_path = max_length;
        return best_path;
    }
}
