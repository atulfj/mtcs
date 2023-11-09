#include <bits/stdc++.h>

using namespace std;

pair<int, int> getMinMax(int N, vector<int> &Y)
{
    int yMin = INT_MAX, yMax = INT_MIN;
    for (int i = 0; i < N; i++)
    {
        yMin = min(yMin, Y[i]);
        yMax = max(yMax, Y[i]);
    }

    return {yMin, yMax};
}

int findIntersections(float mid, int N, vector<int> &Y)
{
    int intersections = 0;
    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
        {
            if (Y[i] <= mid)
                intersections++;

            continue;
        }
        if (Y[i] < mid && Y[i + 1] > mid || Y[i] > mid && Y[i + 1] < mid)
            intersections++;

        if (Y[i] == mid)
            intersections++;
    }
    return intersections;
}

int solution(vector<int> &Y)
{
    int N = Y.size();
    pair<int, int> pair = getMinMax(N, Y);
    int yMin = pair.first, yMax = pair.second;

    float low = (float)yMin, high = (float)yMax;

    int maxIntersections = 0;
    float mid = (low + high) / 2;
    float maxMid = 0;
    while (mid >= low && mid <= high)
    {

        int currAns = findIntersections(mid, N, Y);
        //cout << mid;
        if (currAns > maxIntersections)
        {
            maxMid = mid;
            mid = mid + 0.5;
        }
        else
            mid = mid - 0.5;

        maxIntersections = max(maxIntersections, currAns);
    }

    return maxIntersections;
}
int main()
{
    vector<int> nums = {10000000, 2, 1, 2, 1, 3, 20000000};
    cout << solution(nums) << endl;
}
