#include <bits/stdc++.h>
using namespace std;

void SelectionSort(vector<int> &v) // wrost cast time O(n^2) , memeory complexity = O(1)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] < v[min_idx])
                min_idx = j;
        }
        swap(v[i], v[min_idx]);
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
    SelectionSort(vec);
    Print(vec);
    return 0;
}