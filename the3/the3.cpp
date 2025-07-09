#include "the3.h"
#include <vector>
#include <limits>

// Define constants for plant types
const int F1 = 0, F2 = 1, B1 = 2, B2 = 3, T1 = 4, T2 = 5;
const int INF = std::numeric_limits<int>::max();

// Function to check if transition from plant p to s is allowed
bool allowed(int p, int s) {
    // No two bushes adjacent
    if ((p == B1 || p == B2) && (s == B1 || s == B2)) return false;
    // No two trees adjacent
    if ((p == T1 || p == T2) && (s == T1 || s == T2)) return false;
    // Adjacent flowers must be of the same species
    if ((p == F1 && s == F2) || (p == F2 && s == F1)) return false;
    return true;
}

// Function to check if starting plant s0 and ending plant s' are compatible
bool is_compatible(int s0, int s) {
    // No two bushes adjacent
    if ((s0 == B1 || s0 == B2) && (s == B1 || s == B2)) return false;
    // No two trees adjacent
    if ((s0 == T1 || s0 == T2) && (s == T1 || s == T2)) return false;
    // Adjacent flowers must be of the same species
    if ((s0 == F1 && s == F2) || (s0 == F2 && s == F1)) return false;
    return true;
}

int find_min_cost(const std::vector<std::vector<int>>& costs, int N) {
    int min_cost = INF;
    int num_plants = 6;
    int num_positions = N - 1; // Number of plantable spots

    // For each possible starting plant
    for (int s0 = 0; s0 < num_plants; ++s0) {
        // Initialize DP arrays
        std::vector<int> prev_dp(num_plants, INF);
        std::vector<int> curr_dp(num_plants, INF);

        // Set the cost for the starting plant
        prev_dp[s0] = costs[0][s0];

        // Fill DP array
        for (int i = 1; i < num_positions; ++i) {
            for (int s = 0; s < num_plants; ++s) {
                curr_dp[s] = INF;
                for (int p = 0; p < num_plants; ++p) {
                    if (prev_dp[p] != INF && allowed(p, s)) {
                        int cost = prev_dp[p] + costs[i][s];
                        if (cost < curr_dp[s]) {
                            curr_dp[s] = cost;
                        }
                    }
                }
            }
            prev_dp.swap(curr_dp);
        }

        // Check compatibility between starting and ending plants
        for (int s = 0; s < num_plants; ++s) {
            if (prev_dp[s] != INF && is_compatible(s0, s)) {
                if (prev_dp[s] < min_cost) {
                    min_cost = prev_dp[s];
                }
            }
        }
    }

    return (min_cost == INF) ? 0 : min_cost;
}
