#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int OO = 0x3f3f3f3f;

class shortest_path
{
private:
    const int OO = 0x3f3f3f3f;

public:
    vector<int> BFS(unordered_map<int, vector<int>> &graph, int src)
    {
        vector<int> distance(graph.size(), OO);
        queue<int> q;
        q.push(src);
        distance[src] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto neighbor : graph[node])
            {
                if (distance[neighbor] == OO)
                {
                    q.push(neighbor);
                    distance[neighbor] = distance[node] + 1;
                }
            }
        }
        return distance;
    }
    vector<int> BFS_V2(unordered_map<int, vector<int>> &graph, int src)
    {
        vector<int> len(graph.size(), OO);
        queue<int> q;
        len[src] = 0;
        q.push(src);

        for (int sz = 1, level = 0; !q.empty(); ++level, sz = q.size())
        {
            int node = q.front();
            q.pop();
            while (sz--)
            {
                for (auto neighbor : graph[node])
                {
                    if (len[neighbor] == OO)
                    {
                        len[neighbor] = level + 1;
                        q.push(neighbor);
                    }
                }
            }
        }
        return len;
    }
};

class Cyclic_using_BFS
{
private:
public:
    bool is_cyclic(unordered_map<int, vector<int>> &graph, vector<bool> &visited, int src)
    {
        unordered_map<int, int> parent;

        queue<int> q;
        q.push(src);
        visited[src] = 1;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto neighbor : graph[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    parent[neighbor] = node;
                    q.push(neighbor);
                }
                else if (parent[node] != neighbor)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

class BipartiteGraph // Biportatie = Bicolorable
{
private:
public:
    bool Coloring(unordered_map<int, vector<int>> &graph, vector<char> &visited, int src)
    {

        visited[src] = 'R';

        queue<pair<int, char>> q;
        q.push({src, 'R'});

        while (!q.empty())
        {
            int node = q.front().first;
            int color = q.front().second;
            q.pop();
            for (auto neighbor : graph[node])
            {
                if (visited[neighbor] == '0')
                {
                    if (color == 'R')
                    {
                        q.push({neighbor, 'B'});
                        visited[neighbor] = 'B';
                    }
                    else
                    {
                        q.push({neighbor, 'R'});
                        visited[neighbor] = 'R';
                    }
                }
                else if (visited[neighbor] == color)
                {
                    return false;
                }
            }
        }
        return true;
    }
};
void test_Bipartite()
{
    int node, edge;
    cin >> node >> edge;
    unordered_map<int, vector<int>> graph;
    BipartiteGraph a;
    for (int i = 0; i < edge; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    vector<char> visited(node, '0');
    cout << a.Coloring(graph, visited, 0);
}

class Mouse_Cat
{
private:
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool is_vaild(int r, int c, vector<vector<char>> &grid)
    {
        if (r < 0 || r >= grid.size())
            return false;
        if (c < 0 || c >= grid[0].size())
            return false;
        return true;
    }

public:
    void BFSCAT(vector<vector<char>> &grid, vector<vector<int>> &disCAT)
    {
        queue<pair<int, int>> catPlace;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 'C')
                {
                    disCAT[i][j] = 0;
                    catPlace.push({i, j});
                }
            }
        }

        while (!catPlace.empty())
        {
            pair<int, int> cat = catPlace.front();
            catPlace.pop();

            for (int k = 0; k < 4; k++)
            {
                int nR = cat.first + dr[k];
                int nC = cat.second + dc[k];

                if (is_vaild(nR, nC, grid) && disCAT[nR][nC] == OO && grid[nR][nC] != '#')
                {
                    disCAT[nR][nC] = disCAT[cat.first][cat.second] + 1;
                    catPlace.push({nR, nC});
                }
            }
        }
    }

    bool BFSMouse(vector<vector<char>> &grid, vector<vector<int>> &disM, vector<vector<int>> &catDis, int mr, int mc)
    {
        queue<pair<int, int>> mousePlace;

        mousePlace.push({mr, mc});
        disM[mr][mc] = 0;

        while (!mousePlace.empty())
        {
            pair<int, int> mouse = mousePlace.front();
            mousePlace.pop();
            for (int k = 0; k < 4; k++)
            {
                int nR = mouse.first + dr[k];
                int nC = mouse.second + dc[k];

                if (is_vaild(nR, nC, grid) && disM[nR][nC] == OO && grid[nR][nC] != '#' && catDis[nR][nC] > disM[nR][nC])
                {
                    if (grid[nR][nC] == 'E')
                    {
                        return true;
                    }
                    disM[nR][nC] = disM[mouse.first][mouse.second] + 1;
                    mousePlace.push({nR, nC});
                }
            }
        }
        return false;
    }
};
void test_cat_mouse()
{
    int row, col;
    cin >> row >> col;

    int mr, mc;
    Mouse_Cat a;
    vector<vector<char>> grid(row, vector<char>(col));
    vector<vector<int>> disC(row, vector<int>(col, OO));
    vector<vector<int>> disM(row, vector<int>(col, OO));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> grid[i][j];

            if (grid[i][j] == 'M')
            {
                mr = i;
                mc = j;
            }
        }
    }

    a.BFSCAT(grid, disC);

    cout << a.BFSMouse(grid, disM, disC, mr, mc);
}

class correct_path
{
private:
    void print(vector<int> &parent, int cur_node)
    {
        if (parent[cur_node] == -1)
            return;
        print(parent, parent[cur_node]);
        cout << cur_node << " ";
    }

public:
    void print_path(unordered_map<int, vector<int>> &graph, vector<bool> &visited, int src, int dist)
    {
        queue<int> q;
        q.push(src);
        vector<int> parent(graph.size(), -1);
        visited[src] = true;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto neighbour : graph[node])
            {
                if (visited[neighbour] == false)
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                    parent[neighbour] = node;
                }
                if (neighbour == dist)
                {
                    if (parent[neighbour] == -1)
                    {
                        cout << "No path from " << src << " to " << dist << endl;
                    }
                    else
                    {
                        cout << " path from " << src << " to " << dist << " is : ";
                        print(parent, dist);
                        cout << endl;
                    }
                    return;
                }
            }
        }

        cout << "No path from " << src << " to " << dist << endl;
    }
};
void test_path()
{
    int node, edge;
    cin >> node >> edge;
    unordered_map<int, vector<int>> graph;
    vector<bool> visited(node, false);
    correct_path a;

    for (int i = 0; i < edge; i++)
    {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }

    int src, dist;
    cout << "Enter source and destination: ";
    cin >> src >> dist;

    a.print_path(graph, visited, src, dist);
}

class ShortestPathtoGetFood
{

private:
    int dr[4] = {0, 1, -1, 0};
    int dc[4] = {1, 0, 0, -1};
    bool is_vaild(vector<vector<char>> &grade, int r, int c)
    {
        if (r < 0 || r >= grade.size())
            return false;
        if (c < 0 || c >= grade[0].size())
            return false;
        return true;
    }
    int BFS(vector<vector<char>> &grid, int mr, int mc)
    {
        queue<pair<int, int>> q;
        vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), OO));
        q.push({mr, mc});
        dist[mr][mc] = 0;

        while (!q.empty())
        {
            int MR = q.front().first;
            int MC = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nr = dr[i] + MR, nc = dc[i] + MC;
                if (is_vaild(grid, nr, nc) && grid[nr][nc] != 'X' && dist[nr][nc] == OO)
                {
                    q.push({nr, nc});
                    dist[nr][nc] = dist[MR][MC] + 1;
                    if (grid[nr][nc] == '#')
                        return dist[nr][nc];
                }
            }
        }
        return -1;
    }

public:
    int getFood(vector<vector<char>> &matrix)
    {
        int mr, mc;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] == '*')
                {
                    mr = i, mc = j;
                    break;
                }
            }
        }
        return BFS(matrix, mr, mc);
    }
};

void test_food()
{
    ShortestPathtoGetFood s;

    vector<vector<char>> grid{{'X', 'X', 'X', 'X', 'X', 'X'}, {'X', '*', 'O', 'O', 'O', 'X'}, {'X', 'O', 'O', '#', 'O', 'X'}, {'X', 'X', 'X', 'X', 'X', 'X'}};
    // vector<vector<char>>grid{{'X', '*'}, { '#','X' }};
    cout << s.getFood(grid);
}

class MinimumOperationstoConvertNumber
{
private:
    const int OO = 0x3f3f3f3f;
    bool is_vaild(int equ, int goal, queue<int> &q, vector<int> &len, int front)
    {
        if (equ == goal)
            return true;
        if (equ >= 0 && equ <= 1000 && len[equ] == OO)
        {
            q.push(equ);
            len[equ] = len[front] + 1;
        }
        return false;
    }

public:
    int minimumOperations(vector<int> &nums, int start, int goal)
    {
        queue<int> q;
        q.push(start);
        vector<int> len(10000, OO);
        len[start] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (int i = 0; i < nums.size(); i++)
            {
                if (is_vaild(node + nums[i], goal, q, len, node) || is_vaild(node - nums[i], goal, q, len, node) || is_vaild(node ^ nums[i], goal, q, len, node))
                {
                    return len[node] + 1;
                }
            }
        }
        return -1;
    }
};

class openTheLock
{
private:
    string front(string &lock, int idx)
    {
        string temp = lock;
        int value = temp[idx] - '0';

        if (value == 9)
            value = 0;
        else
            value += 1;

        temp[idx] = value + '0';
        return temp;
    }

    string back(string &lock, int idx)
    {
        string temp = lock;
        int value = temp[idx] - '0';

        if (value == 0)
            value = 9;
        else
            value -= 1;

        temp[idx] = value + '0';
        return temp;
    }

public:
    int openLock(vector<string> &deadends, string target)
    {

        queue<string> q;
        unordered_set<string> visited{deadends.begin(), deadends.end()};
        string start = "0000";
        if (visited.count(start))
            return -1;
        int moves = 0;
        if (start == target)
            return moves;
        q.push(start);
        visited.insert(start);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                string key = q.front();
                q.pop();

                for (int j = 0; j < 4; j++)
                {
                    string temp = front(key, j);
                    if (!visited.count(temp))
                    {
                        if (temp == target)
                            return moves + 1;
                        q.push(temp);
                        visited.insert(temp);
                    }

                    string temp2 = back(key, j);
                    if (!visited.count(temp2))
                    {
                        if (temp2 == target)
                            return moves + 1;
                        q.push(temp2);
                        visited.insert(temp2);
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};
class CanReach_0
{

private:
    bool is_vaild(queue<int> &q, vector<int> &arr, vector<bool> &visited, int num_idx)
    {
        if (num_idx < 0 || num_idx >= visited.size() || visited[num_idx])
            return false;

        if (arr[num_idx] == 0)
            return true;
        visited[num_idx] = true;
        q.push(num_idx);
        return false;
    }

public:
    bool canReach(vector<int> &arr, int start)
    {
        if (arr[start] == 0)
            return true;

        queue<int> q;
        q.push(start);
        vector<bool> visited(arr.size());
        visited[start] = true;

        for (int sz = 1, level = 0; !q.empty(); ++level, sz = q.size())
        {
            while (sz--)
            {
                int num = q.front();
                q.pop();

                if (is_vaild(q, arr, visited, num + arr[num]) || is_vaild(q, arr, visited, num - arr[num]))
                    return true;
            }
        }
        return false;
    }
};

class WallsandGates
{
private:
    int dr[4] = {0, 1, -1, 0};
    int dc[4] = {1, 0, 0, -1};
    const int INF = 2147483647;

    bool isValid(vector<vector<int>> &rooms, int r, int c)
    {
        if (r < 0 || r >= rooms.size() || c < 0 || c >= rooms[0].size())
            return false;
        return true;
    }

public:
    void wallsAndGates(vector<vector<int>> &rooms)
    {
        queue<pair<int, int>> gates;
        // vector<vector<bool>>visited(rooms.size(), vector<bool>(rooms[0].size()));

        for (int i = 0; i < rooms.size(); i++)
        {
            for (int j = 0; j < rooms[0].size(); j++)
            {
                if (rooms[i][j] == 0)
                {
                    gates.push({i, j});
                }
            }
        }
        while (!gates.empty())
        {
            pair<int, int> gate = gates.front();
            gates.pop();
            queue<pair<int, int>> q;
            q.push(gate);

            while (!q.empty())
            {
                int MR = q.front().first, MC = q.front().second;
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int nr = dr[i] + MR, nc = dc[i] + MC;

                    if (isValid(rooms, nr, nc) && rooms[nr][nc] != -1 && rooms[nr][nc] != 0)
                    {
                        if (rooms[nr][nc] == INF)
                        {
                            rooms[nr][nc] = rooms[MR][MC] + 1;
                            q.push({nr, nc});
                        }
                        else if (rooms[nr][nc] > rooms[MR][MC] + 1)
                        {
                            rooms[nr][nc] = rooms[MR][MC] + 1;
                            q.push({nr, nc});
                        }
                    }
                }
            }
        }
    }
    void wallsAndGates_V2(vector<vector<int>> &rooms)
    {
        int rows = rooms.size();
        if (rows == 0)
            return;
        int cols = rooms[0].size();

        queue<pair<int, int>> q;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (rooms[i][j] == 0)
                {
                    q.push({i, j});
                }
            }
        }

        while (!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (isValid(rooms, nr, nc) && rooms[nr][nc] == INF)
                {
                    rooms[nr][nc] = rooms[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
};

typedef long long LL;
class SteppingNumbers
{
private:
    bool inRange(LL num, LL low, LL high)
    {
        return num >= low && num <= high;
    }
    bool is_vaild(queue<LL> &q, vector<int> &res, int num, LL low, LL high)
    {
        if (num > high)
            return false;
        if (inRange(num, low, high))
            res.push_back(num);

        q.push(num);
        return true;
    }

public:
    vector<int> countSteppingNumbers(LL low, LL high)
    {
        queue<LL> q;
        vector<int> res;

        if (inRange(0, low, high))
            res.push_back(0);

        for (int i = 1; i <= 9; i++)
        {
            if (inRange(i, low, high))
                res.push_back(i);
            q.push(i);
        }

        for (int sz = q.size(), level = 0; !q.empty(); ++level, sz = q.size())
        {
            int num = q.front();
            q.pop();
            int last_digit = num % 10;

            if (last_digit != 0 && !is_vaild(q, res, num * 10 + last_digit - 1, low, high))
                break;
            if (last_digit != 9 && !is_vaild(q, res, num * 10 + last_digit + 1, low, high))
                break;
        }
        return res;
    }
};

class ShortestPathwithAlternatingColors
{
private:
    unordered_map<int, vector<pair<int, int>>> graph;
    const int OO = 0x3f3f3f3f;
    const int B = 1, R = 0;
    // 0 -> red , 1 -> Blue
    void BFS(int start, int n, vector<int> &res)
    {
        queue<pair<int, int>> q;
        vector<vector<int>> len(n, vector<int>(2, OO));
        q.push({start, R});
        q.push({start, B});

        len[start][R] = len[start][B] = 0;
        res[start] = 0;

        while (!q.empty())
        {
            int node_p = q.front().first, color_p = q.front().second;
            q.pop();

            for (auto neighbor : graph[node_p])
            {
                int node_c = neighbor.first, color_c = neighbor.second;

                if (color_c != color_p && len[node_c][color_c] == OO)
                {
                    q.push({node_c, color_c});
                    len[node_c][color_c] = len[node_p][color_p] + 1;

                    if (res[node_c] == -1)
                        res[node_c] = len[node_c][color_c];
                }
            }
        }
    }

public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
    {
        for (int i = 0; i < redEdges.size(); i++)
        {
            int from = redEdges[i][0], to = redEdges[i][1];
            graph[from].push_back({to, R});
        }

        for (int i = 0; i < blueEdges.size(); i++)
        {
            int from = blueEdges[i][0], to = blueEdges[i][1];
            graph[from].push_back({to, B});
        }
        vector<int> res(n, -1);

        BFS(0, n, res);

        return res;
    }
};

class Puzzle
{
private:
    string goal = "123450";

    vector<vector<int>> dir{{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {3, 5, 1}, {4, 2}};

public:
    int slidingPuzzle(vector<vector<int>> &board)
    {
        string start = "";
        for (int i = 0; i < (int)board.size(); i++)
            for (int j = 0; j < (int)board[0].size(); j++)
                start += board[i][j] + '0';

        if (goal == start)
            return 0;

        unordered_set<string> visited;
        queue<string> q;
        q.push(start);
        visited.insert(start);

        for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size())
        {
            while (sz--)
            {
                string cur = q.front();
                q.pop();
                int idx1 = (int)cur.find('0');

                for (int idx2 : dir[idx1])
                {
                    swap(cur[idx1], cur[idx2]);

                    if (cur == goal)
                        return level + 1;

                    if (visited.insert(cur).second)
                        q.push(cur);
                    swap(cur[idx1], cur[idx2]);
                }
            }
        }
        return -1;
    }
};

int main()
{
    return 0;
}