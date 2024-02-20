#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void print_triangle_v1(int n)
{
    if (n == 0)
        return;
    for (int i = 0; i < n; i++)
        cout << "*";
    cout << endl;
    print_triangle_v1(n - 1);
}
void print_triangle_v2(int n)
{
    if (n == 0)
        return;
    print_triangle_v2(n - 1);
    for (int i = 0; i < n; i++)
        cout << "*";
    cout << endl;
}
void print_3n(int n)
{
    cout << n << " ";
    if (n == 1)
        return;
    if (n % 2 == 0)
        print_3n(n / 2);
    else
    {
        print_3n(3 * n + 1);
    }
}
int count_3n_plus_one(int n)
{
    if (n == 1)
        return 1;
    if (n % 2 == 0)
        return 1 + count_3n_plus_one(n / 2);
    else
    {
        return 1 + count_3n_plus_one(3 * n + 1);
    }
}
int power_fun(int n, int p)
{
    if (p == 0)
        return 1;
    return n * power_fun(n, p - 1);
}
int array_sum(vector<int> v, int idx = 0)
{
    if (idx == v.size())
        return 0;
    return v[idx] + array_sum(v, idx + 1);
}
void array_inc(vector<int> &v, int idx = 0)
{
    if (idx == v.size())
        return;
    v[idx] += idx;
    array_inc(v, idx + 1);
}

int max_num_v2(vector<int> v, int start, int end)
{
    if (start == end)
        return INT_MIN;
    int res = v[start];
    return max(res, max_num_v2(v, start + 1, end));
}
void array_acc(vector<int> &v, int idx = 1)
{
    if (idx == v.size())
        return;
    v[idx] += v[idx - 1];
    array_acc(v, idx + 1);
}
void left_max(vector<int> &v, int len)
{
    if (len == 1)
        return;
    left_max(v, len - 1);
    v[len - 1] = max(v[len - 1], v[len - 2]);
}
int suffix_sum(vector<int> v, int k, int count)
{
    if (count == 0)
        return 0;
    return v[k - 1] + suffix_sum(v, k + 1, count - 1);
}
int prefix_sum(vector<int> v, int k)
{
    if (k == 0)
        return 0;
    return v[k - 1] + prefix_sum(v, k - 1);
}
bool is_palindrom(vector<long long> v, int idx = 0)
{
    if (idx == v.size())
        return true;
    if (v[idx] != v[v.size() - idx - 1])
        return false;
    return is_palindrom(v, idx + 1);
}
bool is_prefix(string main, string prefix, int idx = 0)
{
    if (idx == prefix.size())
        return true;
    if (prefix[idx] != main[idx])
        return false;
    return is_prefix(main, prefix, idx + 1);
}
int fibonacci(int n)
{
    if (n <= 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
int main()
{
    return 0;
}