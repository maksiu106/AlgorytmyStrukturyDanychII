#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <string>
#include <set>
#include <queue>
#include <sstream>

struct Vertex {
	std::string name;
	std::set<int> neighbours;
	Vertex(std::string stop) {name = stop;}
};

class Graph {
	int no_vertex;
	std::vector<Vertex> vertex;
public:
	Graph(int number) {no_vertex = number;}

	void add_vertex(std::string name) {
		Vertex stop = Vertex(name);
		vertex.push_back(stop);
	}

	int find_vertex(std::string name) {
		for (int i=0; i<vertex.size(); ++i) {
			if (vertex[i].name == name) return i;
		}
		return -1;
	}

	void add_edge(std::string f, std::string s) {
		int first = find_vertex(f);
		int second = find_vertex(s);
		if (first == -1 || second == -1) return;
		vertex[first].neighbours.insert(second);
		vertex[second].neighbours.insert(first);
	}

	//funkcja służąca dodawaniu krawędzi na podstawie trasy
	void add_route(std::string route) {
		std::stringstream ss(route);
		std::string stop;
		std::vector<std::string> stops;
		while (std::getline(ss, stop, ' ')) {
			stops.push_back(stop);
		}
		//pierwszy element to nazwa linii - można pominąć
		//ponadto idzie się do przedostatniego przystanku
		for (int i=1; i<stops.size()-1; ++i) {
			add_edge(stops[i], stops[i+1]);
		}
	}

	std::string bfs(std::string start, std::string end) {
		bool seen[no_vertex];
		int distance[no_vertex]; //wszystko ustawione na 0; w drugim wierszu jest zapamiętany poprzedni wierzchołek
		int previous[no_vertex];
		for (int i=0; i<no_vertex; ++i) {
			seen[i] = 0;
			distance[i] = 0;
			previous[i] = 0;
		}
		std::queue<int> q;
		int start_index = find_vertex(start);
		int end_index = find_vertex(end);
		seen[start_index] = 1;
		distance[start_index] = 0;
		previous[start_index] = -1;
		q.push(start_index);
		//dopóki nie znalazło się szukanego końcowego przystanku
		while (!q.empty() && !seen[end_index]) {
			int current = q.front();
			q.pop();
			for (int u : vertex[current].neighbours) {
				if (seen[u] == 0) {
					distance[u] = distance[current]+1;
					seen[u] = 1;
					previous[u] = current;
					q.push(u);
				}
			}
		}
		if (seen[end_index] == 0) return "NO ROUTE"; //jeśli nie udało się znaleźć ścieżki
		else {
			std::vector<std::string> result;
			int index = end_index;
			while (index != start_index) {
				result.push_back(vertex[index].name);
				index = previous[index];
			}
			result.push_back(vertex[start_index].name);
			std::string to_return;
			for (int i = result.size()-1; i>=0; --i) {
				to_return += result[i] + " ";
			}
			return to_return;
		}
	}
};
#endif /* GRAPH_HPP_ */
