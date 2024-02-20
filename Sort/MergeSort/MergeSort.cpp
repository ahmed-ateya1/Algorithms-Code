#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& v, int l, int m, int r)//m = l + (r - l) / 2;       
{
	int i, j, k;
	int n1 = m - l + 1;// First subarray is arr[l..m]                    
	int n2 = r - m;// Second subarray is arr[m+1..r]                     
	vector<int>L(n1), R(n2);
	for (i = 0; i < n1; i++)
		L[i] = v[l + i];
	for (j = 0; j < n2; j++)
		R[j] = v[m + 1 + j];

	i = j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			v[k] = L[i];
			i++;
		}
		else
		{
			v[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		v[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		v[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(vector<int>& v, int l, int r)//time complexity O(nlog) , space complexity O(n)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		mergeSort(v, l, m);
		mergeSort(v, m + 1, r);

		merge(v, l, m, r);
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
    mergeSort(vec , 0 , vec.size());
    Print(vec);
    return 0;
}