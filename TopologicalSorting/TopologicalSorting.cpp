#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class khan_Algorithm
{
private:
    unordered_map<int, vector<int>> graph;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> in_degree(numCourses, 0);

        for (auto &pre : prerequisites)
        {
            int to = pre[0], from = pre[1];
            graph[from].push_back(to);
            in_degree[to]++;
        }

        queue<int> ready; // is handle diconnected graph because every node with in_degree =0 add to queue

        for (int i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
                ready.push(i);
        }

        vector<int> res;

        while (!ready.empty())
        {
            int node = ready.front();
            ready.pop();
            res.push_back(node);

            for (auto neighbor : graph[node])
            {
                if (--in_degree[neighbor] == 0)
                    ready.push(neighbor);
            }
        }

        if (res.size() != numCourses) // check if found cycle because not visited all the node
            res.clear();

        return res;
    }
};

class Course_schedule
{
private:
    unordered_map<int, vector<int>> graph;

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> in_degree(numCourses, 0);

        for (int i = 0; i < prerequisites.size(); i++)
        {
            int from = prerequisites[i][0], to = prerequisites[i][1];

            graph[from].push_back(to);
            in_degree[to]++;
        }

        queue<int> ready;

        for (int i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
                ready.push(i);
        }

        vector<int> res;
        while (!ready.empty())
        {
            int node = ready.front();
            ready.pop();
            res.push_back(node);

            for (auto neighbor : graph[node])
            {
                if (--in_degree[neighbor] == 0)
                    ready.push(neighbor);
            }
        }
        return res.size() == graph.size();
    }
};

class ParallelCourses
{
private:
    unordered_map<int, vector<int>> graph;

public:
    int longestPath(int n, vector<vector<int>> &relations)
    {
        unordered_map<int, int> in_degree;

        for (int i = 0; i < relations.size(); i++)
        {
            int from = relations[i][0], to = relations[i][1];
            graph[from].push_back(to);

            in_degree[to]++;
        }

        queue<int> ready;

        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] == 0)
            {
                ready.push(i);
            }
        }

        int l = 1;
        for (int sz = ready.size(), level = 1; !ready.empty(); ++level, sz = ready.size())
        {
            while (sz--)
            {
                int node = ready.front();
                ready.pop();

                for (auto neighbor : graph[node])
                {
                    if (--in_degree[neighbor] == 0)
                    {
                        ready.push(neighbor);
                        l = level + 1;
                    }
                }
            }
        }

        for (auto it : in_degree)
        {
            if (it.second > 0)
                return -1;
        }
        return l;
    }

    int longestPathV2(int n, vector<vector<int>> &edge)
    {
        vector<int> in_degree(n, 0);

        for (int i = 0; i < edge.size(); i++)
        {
            int from = edge[i][0], to = edge[i][1];

            graph[from].push_back(to);
            in_degree[to]++;
        }

        queue<int> ready;

        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] == 0)
                ready.push(i);
        }

        int levels = 0, ready_node = 0;
        while (!ready.empty())
        {
            int level_sz = ready.size();

            while (level_sz--)
            {
                int node = ready.front();
                ready.pop();
                ready_node++;

                for (auto neighbor : graph[node])
                {
                    if (--in_degree[neighbor] == 0)
                    {
                        ready.push(neighbor);
                    }
                }
            }
            levels++;
        }

        if (ready_node != n)
            return -1;
        return levels;
    }
};

class Thelexicographicalorder
{
private:
    unordered_map<int, vector<int>> graph;

public:
    vector<int> TopSort(int n, vector<vector<int>> &relations) // O(VlogV+E)
    {
        vector<int> in_degree(n, 0);

        for (int i = 0; i < relations.size(); i++)
        {
            int from = relations[i][0], to = relations[i][1];
            graph[from].push_back(to);

            in_degree[to]++;
        }

        priority_queue<int, vector<int>, greater<int>> ready;

        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] == 0)
            {
                ready.push(i);
            }
        }
        vector<int> res;
        while (!ready.empty())
        {
            int node = ready.top();
            ready.pop();
            res.push_back(node);

            for (auto neighbor : graph[node])
            {
                if (--in_degree[neighbor] == 0)
                {
                    ready.push(neighbor);
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (in_degree[i] > 0)
                return {};
        }
        return res;
    }
};

typedef vector<vector<int>> GRAPH;

class MinimumHeightTree
{
private:
    vector<int> tree_centroids(const GRAPH &adjList)
    { // O(V)
        int sz = adjList.size();

        if (sz == 1) // special case
            return {0};

        vector<int> indegree(sz, 0);
        for (int i = 0; i < sz; ++i)
            for (int j : adjList[i])
                indegree[j]++;

        queue<int> ready;
        for (int i = 0; i < sz; ++i)
            if (indegree[i] == 1) // leaves
                ready.push(i);

        // keep shrinking leaves: level by level
        while (sz > 2)
        {
            int level_sz = ready.size(); // how many leaves NOW
            sz -= level_sz;
            while (level_sz--)
            { // level by level like BFS
                int i = ready.front();
                ready.pop();

                for (int j : adjList[i])
                    if (--indegree[j] == 1)
                        ready.push(j);
            }
        }
        vector<int> res;
        while (!ready.empty())
        {
            res.push_back(ready.front());
            ready.pop();
        }
        return res;
    }
    void add_undirected_edge(GRAPH &graph, int from, int to)
    {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        GRAPH graph(edges.size() + 1);

        for (auto &edge : edges)
            add_undirected_edge(graph, edge[0], edge[1]);

        return tree_centroids(graph);
    }
};

int main()
{
    return 0;
}