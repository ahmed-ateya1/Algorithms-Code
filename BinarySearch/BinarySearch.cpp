#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int left(vector<int> &v, int target)
    {
        int l = 0, r = v.size() - 1, partion = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (v[mid] > target)
            {
                r = mid - 1;
            }
            else if (v[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                partion = mid;
                r = mid - 1;
            }
        }
        return partion;
    }
    int right(vector<int> &v, int target)
    {
        int l = 0, r = v.size() - 1, partion = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (v[mid] > target)
            {
                r = mid - 1;
            }
            else if (v[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                partion = mid;
                l = mid + 1;
            }
        }
        return partion;
    }
    vector<int> searchRange(vector<int> &v, int target)
    {
        int l = left(v, target);
        int r = right(v, target);
        return {l, r};
    }
    int coins(int n)
    {
        int l = 0, r = n;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            int equ = mid * (mid + 1) / 2;
            if (equ == n)
                return mid;
            else if (equ > n)
                r = mid - 1;
            else
                l = mid + 1;
        }
        return l - 1;
    }
};

class Solution
{
public:
    int compare(vector<long long> &houses, vector<long long> &heaters, int mid)
    {
        long long mn = abs(houses[mid] - heaters[0]);
        for (int i = 1; i < heaters.size(); i++)
            mn = min(mn, abs(houses[mid] - heaters[i]));
        return mn;
    }
    long long findRadius(vector<long long> &houses, vector<long long> &heaters)
    {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        long long mx = INT_MIN, l = 0, r = houses.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (compare(houses, heaters, mid) >= mx)
            {
                mx = compare(houses, heaters, mid);
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return mx;
    }
};
class Solution
{
public:
    int mySqrt(int x)
    {
        if (x == 0)
            return x;
        int first = 1, last = x;
        while (first <= last)
        {
            int mid = first + (last - first) / 2;
            if (mid == x / mid)
                return mid;
            else if (mid > x / mid)
            {
                last = mid - 1;
            }
            else
            {
                first = mid + 1;
            }
        }
        return last;
    }
};

int main()
{
    vector<int> v{1, 3, 5, 5, 5, 7};
    vector<int>::iterator it = upper_bound(v.begin(), v.end(), 5);
    cout << it - v.begin();
    return 0;
}