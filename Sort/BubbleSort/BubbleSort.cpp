#include <bits/stdc++.h>
using namespace std;

void BubbleSort(vector<int> &v) // time complexity wrost case O(n^2) , space complecity O(1)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }
    }
}
void Print(vector<int> vec)
{
    for (auto it : vec)
        cout << it << " ";
    cout << endl;
}
int main()
{
    vector<int> vec{1, 9, 0, 7, 4, 2};
    BubbleSort(vec);
    Print(vec);
    return 0;
}