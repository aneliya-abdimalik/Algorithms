#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// You may implement helper functions below

unsigned int min_waste_calculate(int w, int h, bool **perfect_cuts, int **dp) {
    if (dp[w][h] != -1) 
        return dp[w][h];
    if (perfect_cuts[w][h]) 
    {
        dp[w][h] = 0;
        return 0;
    }

    int min_waste = w * h;

    for (int i = 1; i < h; i++) 
    {
        int waste = min_waste_calculate(w, i, perfect_cuts, dp) + min_waste_calculate(w, h - i, perfect_cuts, dp);
        min_waste = (min_waste < waste) ? min_waste : waste;
    }

    for (int i = 1; i < w; i++) 
    {
        int waste = min_waste_calculate(i, h, perfect_cuts, dp) + min_waste_calculate(w - i, h, perfect_cuts, dp);
        min_waste = (min_waste < waste) ? min_waste : waste;
    }

    dp[w][h] = min_waste;
    return min_waste;
}

unsigned int alice_cutting_cake(const unsigned short cake_width, const unsigned short cake_height, bool **perfect_cuts) {
    int **dp = new int *[cake_width + 1];
    for (int i = 0; i <= cake_width; i++) 
    {
        dp[i] = new int[cake_height + 1];
        for (int j = 0; j <= cake_height; j++) 
            dp[i][j] = -1;
    }

    unsigned int result = min_waste_calculate(cake_width, cake_height, perfect_cuts, dp);

    for (int i = 0; i <= cake_width; i++)
        delete[] dp[i];
    delete[] dp;

    return result;
}
