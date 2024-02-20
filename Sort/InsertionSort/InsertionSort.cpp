#include <bits/stdc++.h>
using namespace std;

void InsertionSort(vector<int> &v) // wrost cast time O(n^2) , best case O(n) if vector sorted ,avg case O(nlog), memeory complexity = O(1)
{
    for (int i = 1; i < v.size(); i++)
    {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
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
    InsertionSort(vec);
    Print(vec);
    return 0;
}