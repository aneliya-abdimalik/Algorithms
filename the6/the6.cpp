#include "the6.h"

// do not add extra libraries here

std::vector<std::vector<int>> calculateShortestPaths(const std::vector<std::vector<std::pair<int, int>>>& network) 
{
    int n = network.size();
    std::vector<std::vector<int>> distances(n, std::vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) 
    {
        for (const auto& edge : network[i]) 
        {
            distances[i][edge.first] = edge.second;
        }
    }

    for (int k = 0; k < n; ++k) 
    {
        for (int i = 0; i < n; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                if (distances[i][k] != INT_MAX && distances[k][j] != INT_MAX) 
                {
                    if (distances[i][j] > distances[i][k] + distances[k][j]) 
                    {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }
    }

    return distances;
}

std::vector<int> calculateSP1(const std::vector<std::vector<int>>& distances) 
{
    int n = distances.size();
    std::vector<int> SP1(n, 0);

    for (int i = 0; i < n; ++i) 
    {
        int min = distances[i][0];
        for (int j = 0; j < n; ++j) {
            if (distances[i][j] < min) {
                min = distances[i][j];
            }
        }
        SP1[i] = min;
    }

    return SP1;
}

std::vector<std::vector<float>> get_friendship_scores(const std::vector<std::vector<std::pair<int, int>>>& network) 
{
    int n = network.size();
    std::vector<std::vector<int>> distances = calculateShortestPaths(network);
    std::vector<int> SP1 = calculateSP1(distances);
    std::vector<std::vector<float>> friendship_scores(n, std::vector<float>(n, -1));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (i == j) 
            {
                if (distances[i][i] != INT_MAX) 
                {
                    friendship_scores[i][j] = (float)(SP1[i] * SP1[i]) / (distances[i][i] * distances[i][i]);
                } 
                else 
                {
                    friendship_scores[i][j] = -1;
                }
            } 
            else if (distances[i][j] == INT_MAX && distances[j][i] == INT_MAX) 
            {
                friendship_scores[i][j] = -1;
            } 
            else if (distances[i][j] == INT_MAX || distances[j][i] == INT_MAX) 
            {
                friendship_scores[i][j] = 0;
            } 
            else 
            {
                friendship_scores[i][j] = (float)(SP1[i] * SP1[j]) / (distances[i][j] * distances[j][i]);
            }
        }
    }

    return friendship_scores;
}
