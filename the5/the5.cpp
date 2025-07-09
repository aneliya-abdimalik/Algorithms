#include "the5.h"
#include <stack>
#include <algorithm>

void dfs(int node, const std::vector<std::vector<bool>> &dependencies, std::vector<bool> &visited, std::vector<int> &component) {
    visited[node] = true;
    component.push_back(node);
    for (int i = 0; i < dependencies.size(); ++i) {
        if (dependencies[node][i] && !visited[i]) {
            dfs(i, dependencies, visited, component);
        }
    }
}

void fillOrder(int node, const std::vector<std::vector<bool>> &dependencies, std::vector<bool> &visited, std::stack<int> &order) {
    visited[node] = true;
    for (int i = 0; i < dependencies.size(); ++i) {
        if (dependencies[node][i] && !visited[i]) {
            fillOrder(i, dependencies, visited, order);
        }
    }
    order.push(node);
}

std::vector<std::vector<bool>> transposeGraph(const std::vector<std::vector<bool>> &dependencies) {
    int n = dependencies.size();
    std::vector<std::vector<bool>> transposed(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dependencies[i][j]) {
                transposed[j][i] = true;
            }
        }
    }
    return transposed;
}

std::vector<std::vector<int>> find_work_order(const std::vector<std::vector<bool>> &dependencies) {
    int n = dependencies.size();

    // Step 1: Fill the order of nodes using DFS
    std::stack<int> order;
    std::vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            fillOrder(i, dependencies, visited, order);
        }
    }

    // Step 2: Transpose the graph
    std::vector<std::vector<bool>> transposed = transposeGraph(dependencies);

    // Step 3: Find SCCs using the transposed graph
    std::fill(visited.begin(), visited.end(), false);
    std::vector<std::vector<int>> sccs;
    while (!order.empty()) {
        int node = order.top();
        order.pop();

        if (!visited[node]) {
            std::vector<int> component;
            dfs(node, transposed, visited, component);
            std::sort(component.begin(), component.end()); // Sort to maintain order within SCC
            sccs.push_back(component);
        }
    }

    // Step 4: Build the result
    std::vector<std::vector<int>> result;
    for (const auto &scc : sccs) {
        result.push_back(scc);
    }
    return result;
}
