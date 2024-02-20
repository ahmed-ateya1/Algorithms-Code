#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<map>
#include<set>
using namespace std;


typedef vector<vector<int>> Graph1;
class Adjacency_Matrix
{
public:
	void undirected_Graph(Graph1& graph, int from, int to)
	{
		graph[from][to]++;
		graph[to][from]++;
	}
	void directed_Graph(Graph1& graph, int from, int to)
	{
		graph[from][to]++;
	}
	void print_matrix(Graph1& graph)
	{
		int sz = (int)graph.size();
		for (int from = 0; from < sz; from++)
		{
			for (int to = 0; to < sz; to++)
			{
				if (graph[from][to] > 0)
					cout << "From " << from << " to " << to << " there are " << graph[from][to] << " edges\n";

			}
		}
	}
};
void test1()
{
	Adjacency_Matrix a;
	int node, edge;
	cin >> node >> edge;
	Graph1 graph(node, vector<int>(node));

	for (int i = 0; i < edge; i++)
	{
		int from, to; cin >> from >> to;
		a.directed_Graph(graph, from, to);
	}
	a.print_matrix(graph);
}


struct Edge
{
	int to, cost;
};
typedef vector<vector<Edge>> Graph2;
class Adjacency_List
{
private:

public:

	void undirected_Graph(Graph2& graph, int from, int to, int cost)
	{

		graph[from].push_back({ to , cost });
		graph[to].push_back({ from,cost });
	}
	void directed_Graph(Graph2& graph, int from, int to, int cost)
	{

		graph[from].push_back({ to , cost });

	}
	void print_List(Graph2& graph)
	{
		int sz = (int)graph.size();
		for (int from = 0; from < sz; from++)
		{
			cout << " Node " << from << " has Neighbour : ";
			for (int edge = 0; edge < (int)graph[from].size(); edge++)
			{
				cout << "(to " << graph[from][edge].to << " cost " << graph[from][edge].cost << ") ";
			}
			cout << endl;
		}
	}
};
void test2()
{
	int node, edge;
	cin >> node >> edge;
	Graph2 graph(node);
	Adjacency_List a;
	for (int i = 0; i < edge; i++)
	{
		int from, to, cost;
		cin >> from >> to >> cost;
		a.directed_Graph(graph, from, to, cost);
	}
	a.print_List(graph);
}



struct edge
{
	int from, to, cost;
	edge(int from, int to, int cost) :from(from), to(to), cost(cost) { }
	bool operator<(edge& r)
	{
		return cost < r.cost;
	}
	void print()
	{
		cout << " From Node : " << from << " to Node " << to << " cost is " << cost << endl;
	}
};
typedef vector<edge> Graph3;
class Edge_List
{
public:
	void add_edge(Graph3& graph, int from, int to, int cost)
	{
		graph.push_back({ from , to , cost });
	}
	void print(Graph3& graph)
	{
		int sz = (int)graph.size();
		for (int i = 0; i < sz; i++)
		{
			graph[i].print();
		}
	}
};
void test3()
{
	Edge_List e;
	int node, edge;
	cin >> node >> edge;
	Graph3 graph;
	for (int i = 0; i < edge; i++)
	{
		int from, to, cost; cin >> from >> to >> cost;
		e.add_edge(graph, from, to, cost);
	}
	sort(graph.begin(), graph.end());
	e.print(graph);
}

typedef vector<unordered_set<int>> Graph4;
class Adjacency_Hashset
{
public:
	void directed_Graph(Graph4& graph, int from, int to)
	{
		graph[from].insert(to);
	}
	void undirected_Graph(Graph4& graph, int from, int to)
	{
		graph[from].insert(to);
		graph[to].insert(from);
	}
	void print(Graph4& graph)
	{
		int sz = (int)graph.size();
		for (int i = 0; i < sz; i++)
		{
			cout << "Adjacent vertices of vertex " << i << ": ";
			for (auto it : graph[i])
				cout << it << " ";
			cout << endl;
		}
	}
};
void test4()
{
	Adjacency_Hashset a;
	int node, edge;
	cin >> node >> edge;
	Graph4 graph(node);
	for (int i = 0; i < edge; i++)
	{
		int from, to; cin >> from >> to;
		a.directed_Graph(graph, from, to);
	}
	a.print(graph);
}


typedef vector<vector<vector<int>>> Graph5;
class Adjacency_matrix_with_multiple_edges
{
public:
	void add_edge(Graph5& graph, int from, int to, int cost)
	{
		graph[from][to].push_back(cost);
	}
	void print(Graph5& graph)
	{
		for (int i = 0; i < graph.size(); i++)
		{
			for (int j = 0; j < graph[i].size(); j++)
			{
				for (auto k : graph[i][j])
				{
					cout << "From " << i << " to " << j << " cost is " << k << endl;
				}
			}
		}
	}
};
void test5()
{
	Adjacency_matrix_with_multiple_edges a;
	int node, edge;
	cin >> node >> edge;
	Graph5 graph(node, vector<vector<int>>(node));
	for (int i = 0; i < edge; i++)
	{
		int from, to, cost; cin >> from >> to >> cost;
		a.add_edge(graph, from, to, cost);
	}
	a.print(graph);
}



struct Edgee
{
	string to;
	int cost;
	bool operator < (const Edgee& e) const {
		if (to != e.to)
			return to < e.to;
		return cost < e.cost;
	}
};
typedef map<string, multiset<Edgee>> Graph6;
class Adjacency_flight_v1
{
public:
	void add_flight(Graph6& graph, string from, string to, int cost)
	{
		graph[from].insert({ to , cost });
	}
	void print(Graph6& graph)
	{
		for (auto from : graph)
		{
			cout << " Flight from " << from.first << " : " << endl;
			for (auto to : from.second)
			{
				cout << "    to " << to.to << " with Cost " << to.cost << endl;
			}
			cout << endl;
		}
	}
};
void test6()
{
	Adjacency_flight_v1 a;
	int node, edge; cin >> node >> edge;
	Graph6 graph;
	for (int i = 0; i < edge; i++)
	{
		string from, to;
		int cost;
		cin >> from >> to >> cost;
		a.add_flight(graph, from, to, cost);
	}
	a.print(graph);
}

class Image_Graph
{
public:
	void add_edge(Graph1& graph, int from, int to)
	{
		graph[from].push_back(to);
	}
	void print(Graph1& graph)
	{
		for (int i = 0; i < graph.size(); i++)
		{
			cout << "Node " << i << " has neighbors: ";
			for (int j = 0; j < graph[i].size(); j++)
			{
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}

};
void test7()
{
	int row, col;
	cin >> row >> col;
	Graph1 graph(row * col);
	Image_Graph a;
	int r, c, to;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int from = i * col + j;

			r = i + 1, c = j, to = r * col + c;
			if (r < row)
			{
				a.add_edge(graph, from, to);
			}
			r = i - 1, c = j, to = r * col + c;
			if (r >= 0)
			{
				a.add_edge(graph, from, to);
			}
			r = i, c = j + 1, to = r * col + c;
			if (c < col)
			{
				a.add_edge(graph, from, to);
			}
			r = i, c = j - 1, to = r * col + c;
			if (c >= 0)
			{
				a.add_edge(graph, from, to);
			}
		}
	}
	a.print(graph);
}

class Print_Chain
{
public:
	void add_edge(Graph1& graph, int from, int to)
	{
		graph[from].push_back(to);
	}

	void print_chain(Graph1& graph, int from)
	{
		cout << from << "-> ";
		if (graph[from].size() > 0)
		{
			print_chain(graph, graph[from][0]);
		}
	}
};
void test_print_chain()
{
	Print_Chain p;
	int node, edge;
	cin >> node >> edge;
	Graph1 graph(node);
	for (int i = 0; i < edge; i++)
	{
		int from, to;
		cin >> from >> to;
		p.add_edge(graph, from, to);
	}
	int q;
	cin >> q;
	while (q--)
	{
		int temp; cin >> temp;
		p.print_chain(graph, temp);
	}
}


class Print_path2
{
public:
	void add_edge(Graph1& graph, int from, int to)
	{
		graph[from].push_back(to);
	}
	void print_path_of_len2(Graph1& graph)
	{
		for (int i = 0; i < graph.size(); i++)
		{
			for (int j = 0; j < graph[i].size(); j++)
			{
				int to = graph[i][j];
				for (int k = 0; k < graph[to].size(); k++)
					cout << i << " " << to << " " << graph[to][k] << endl;

			}
		}
	}
};
void test_print_len2()
{
	Print_path2 a;
	int node, edge;
	cin >> node >> edge;
	Graph1 graph(node);
	for (int i = 0; i < edge; i++)
	{
		int from, to;
		cin >> from >> to;
		a.add_edge(graph, from, to);
	}
	a.print_path_of_len2(graph);
}



class ObjectIdMapper {
private:
	map<string, int> str_to_id;
	map<int, string> id_to_str;
public:
	int getId(string& str) {
		if (str_to_id.count(str))
			return str_to_id[str];

		int id = str_to_id.size();
		str_to_id[str] = id;
		id_to_str[id] = str;
		return id;
	}
	string getStr(int id) {
		return id_to_str[id];
	}
};

struct edgew {
	int to;
	int cost;
};

typedef vector<vector<edgew>> GRAPH;

void add_directed_edge(GRAPH& graph, int from, int to, int cost) {
	graph[from].push_back({ to, cost });
}
void add_undirected_edge(GRAPH& graph, int from, int to, int cost) {
	graph[from].push_back({ to, cost });
	graph[to].push_back({ from, cost });
}
void print_adjaceny_matrix(GRAPH& graph, ObjectIdMapper& mapper) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << mapper.getStr(from) << " has neighbors: \n";
		for (int edge = 0; edge < (int)graph[from].size(); ++edge)
			cout << "\t(to " << mapper.getStr(graph[from][edge].to)
			<< " cost " << graph[from][edge].cost << ")\n";
	}
}
void test_flight_v2()
{
	int nodes, edges;
	cin >> nodes >> edges;

	GRAPH graph(nodes);
	ObjectIdMapper mapper;

	for (int e = 0; e < edges; ++e) {
		string from, to;
		int cost;
		cin >> from >> to >> cost;
		int from_idx = mapper.getId(from);
		int to_idx = mapper.getId(to);
		add_directed_edge(graph, from_idx, to_idx, cost);
	}
	print_adjaceny_matrix(graph, mapper);
}


int main()
{
	return 0;
}