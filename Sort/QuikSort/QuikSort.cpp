#include <bits/stdc++.h>
using namespace std;

int partion(vector<int> &v, int l, int r)
{
    int pivot = v[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(v[j], v[i]);
        }
    }
    swap(v[i + 1], v[r]);
    return (i + 1);
}
void quicksort(vector<int> &v, int l, int r)
{
    if (l < r)
    {
        int q = partion(v, l, r);
        quicksort(v, l, q - 1);
        quicksort(v, q, r);
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
    quicksort(vec, 0, vec.size());
    Print(vec);
    return 0;
}