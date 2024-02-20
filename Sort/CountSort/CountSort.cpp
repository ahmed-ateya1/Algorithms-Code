#include <bits/stdc++.h>
using namespace std;

void counting_sort(vector<int> &v)
{
	int mx = *max_element(v.begin(), v.end());
	vector<int> count(mx + 1);
	vector<int> output(v.size());
	for (int i = 0; i < v.size(); i++)
	{
		count[v[i]]++;
	}
	for (int i = 1; i <= mx; i++)
	{
		count[i] += count[i - 1];
	}
	for (int i = v.size() - 1; i >= 0; i--)
	{
		output[count[v[i]] - 1] = v[i];
		count[v[i]]--;
	}
	v = output;
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
	counting_sort(vec);
	Print(vec);
	return 0;
}