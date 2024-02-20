#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Kill_process
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;

    void DFS(vector<int> &res, int kill)
    {
        visited.insert(kill);
        res.push_back(kill);

        for (auto neighbor : graph[kill])
        {
            if (!visited.count(neighbor))
                DFS(res, neighbor);
        }
    }

public:
    vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill)
    {
        for (int i = 0; i < pid.size(); i++)
        {
            graph[ppid[i]].push_back(pid[i]);
        }
        vector<int> res;
        DFS(res, kill);

        return res;
    }
};

struct Employee
{
    int id;
    int importance;
    vector<int> subordinates;
};
class Employee_Importance
{
private:
    unordered_map<int, Employee *> graph;

public:
    int DFS(int id)
    {
        Employee *emp = graph[id];
        int res = graph[id]->importance;
        for (auto it : emp->subordinates)
        {
            res += DFS(it);
        }
        return res;
    }
    int getImportance(vector<Employee *> employees, int id)
    {
        for (auto it : employees)
        {
            graph[it->id] = it;
        }
        return DFS(id);
    }
};

class num_of_CC
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;

    void DFS(int node)
    {
        visited.insert(node);

        for (auto neighbor : graph[node])
        {
            if (!visited.count(neighbor))
            {
                DFS(neighbor);
            }
        }
    }

public:
    int countComponents(int n, vector<vector<int>> &edges)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];

            graph[from].push_back(to);
            graph[to].push_back(from);
        }

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visited.count(i))
            {
                cnt++;
                DFS(i);
            }
        }
        return cnt;
    }
};

class Flood_Fill
{
private:
    bool is_vaild(int r, int c, vector<vector<int>> &image)
    {
        if (r < 0 || r >= image.size())
            return false;
        if (c < 0 || c >= image[0].size())
            return false;
        return true;
    }
    int sr[4] = {-1, 1, 0, 0};
    int sc[4] = {0, 0, -1, 1};
    void DFS(vector<vector<int>> &image, vector<vector<bool>> &visited, int r, int c, int old_color, int new_color)
    {
        if (!is_vaild(r, c, image) || visited[r][c] || image[r][c] != old_color)
            return;
        visited[r][c] = true;
        image[r][c] = new_color;
        for (int i = 0; i < 4; i++)
            DFS(image, visited, r + sr[i], c + sc[i], old_color, new_color);
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size()));
        DFS(image, visited, sr, sc, image[sr][sc], color);
        return image;
    }
};

class Restore_the_Array
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;

    void DFS(vector<int> &res, int node)
    {
        visited.insert(node);
        res.push_back(node);
        for (auto neighbor : graph[node])
        {
            if (!visited.count(neighbor))
            {
                DFS(res, neighbor);
            }
        }
    }

public:
    vector<int> restoreArray(vector<vector<int>> &pairs)
    {
        for (int i = 0; i < pairs.size(); i++)
        {
            int from = pairs[i][0];
            int to = pairs[i][1];

            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        int start = 0;
        for (auto num : graph)
        {
            if (num.second.size() == 1)
            {
                start = num.first;
                break;
            }
        }
        vector<int> res;
        DFS(res, start);

        return res;
    }
};

class LongestConsecutiveSequence
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    int mx_len = 0;

    void DFS(int node, int cnt)
    {
        visited.insert(node);
        cnt++;

        for (auto neighbor : graph[node])
        {
            if (!visited.count(neighbor) && neighbor == node + 1)
            {
                DFS(neighbor, cnt);
            }
        }

        mx_len = max(mx_len, cnt);
    }

public:
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++)
        {
            int from = nums[i - 1], to = nums[i];
            graph[from].push_back(to);
        }

        for (auto num : nums)
        {
            if (!visited.count(num))
            {
                DFS(num, 0);
            }
        }
        return mx_len;
    }
};

class Cyclic_undirected
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    bool isCyclic(int node, int parent = -1)
    {
        visited.insert(node);

        for (auto neighbor : graph[node])
        {
            if (visited.count(neighbor) && neighbor != parent)
            {
                return true;
            }
            if (!visited.count(neighbor) && isCyclic(neighbor, node))
            {
                return true;
            }
        }
        return false;
    }

public:
    void Cyclic(vector<vector<int>> &edge)
    {
        for (int i = 0; i < edge.size(); i++)
        {
            int from = edge[i][0], to = edge[i][1];
            graph[from].push_back(to);
            graph[to].push_back(from);
        }

        for (auto nums : graph)
        {
            if (!visited.count(nums.first))
            {
                if (isCyclic(nums.first))
                {
                    cout << "Cyclic";
                    return;
                }
            }
        }
        cout << "Acyclic";
    }
};

class is_tree
{
private:
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    bool isCyclic(int node, int parent = -1)
    {
        visited.insert(node);

        for (auto neighbor : graph[node])
        {
            if (visited.count(neighbor) && neighbor != parent)
            {
                return true;
            }
            if (!visited.count(neighbor) && isCyclic(neighbor, node))
            {
                return true;
            }
        }
        return false;
    }
    void is_connected(int node)
    {
        visited.insert(node);

        for (auto neighbor : graph[node])
        {
            if (!visited.count(neighbor))
            {
                is_connected(neighbor);
            }
        }
    }

public:
    bool Is_tree(vector<vector<int>> edges)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];

            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        int cnt = 0;
        for (auto num : graph)
        {
            if (!visited.count(num.first))
            {
                cnt++;
                is_connected(num.first);
            }
        }

        bool cyclic = false;
        for (auto nums : graph)
        {
            if (!visited.count(nums.first))
            {
                if (isCyclic(nums.first))
                {
                    cyclic = true;
                    break;
                }
            }
        }

        if (!cyclic && cnt == 1)
            return true;
        else
            return false;
    }
};

class DAG
{
private:
    const int NOT_VISITED = 0, VISITED = 1, IN_PROGRESS = 2;
    unordered_map<int, vector<int>> graph;
    map<int, int> visited;

    bool Is_cyclic(int node)
    {
        visited[node] = IN_PROGRESS;

        for (auto neighbor : graph[node])
        {
            if (visited[neighbor] == NOT_VISITED && Is_cyclic(neighbor))
            {
                return true;
            }
            if (visited[neighbor] == IN_PROGRESS)
            {
                return true;
            }
        }
        visited[node] = VISITED;
        return false;
    }

public:
    void is_DAG(vector<vector<int>> &edges)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];

            graph[from].push_back(to);
        }

        for (auto num : graph)
        {
            if (visited[num.first] == NOT_VISITED)
            {
                if (Is_cyclic(num.first))
                {
                    cout << "Cyclic";
                    return;
                }
            }
        }
        cout << "Acyclic";
    }
};
int main()
{
    cout << "wow";
    return 0;
}