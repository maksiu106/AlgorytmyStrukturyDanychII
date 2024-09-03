#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <set>
#include <utility>

class Graph {
	struct Vertice {
		int id; //identyfikator metalu
		int price; //wartość metalu
		//lista sąsiedztwa - krawędzie wychodzące z wierzchołka
		//pierwszy element to id, drugi to koszt
		std::set<std::pair<int, int>> neighbours;
		Vertice() : id(0), price(0) {}
		void setVertice(int i, int p) {
			id = i;
			price = p;
		}
	};

	int n_v;
	Vertice* vertices;
public:
	Graph(int size) { //konstruktor
		n_v = size;
		vertices = new Vertice[n_v];
	}

	~Graph() {delete[] vertices;} //destruktor

	void addVertice(int i, int p) {
		vertices[i].setVertice(i, p);
	}

	void addEdge(int start, int end, int price) {
		vertices[start].neighbours.insert(std::make_pair(end, price));
	}

	bool hasEdge(int start, int end) {
		std::pair<int, int> target(end, 0);
		auto it = vertices[start].neighbours.find(target);
		if (it != vertices[start].neighbours.end()) return true;
		else return false;
	}

	std::set<std::pair<int, int>> outConnections(int v) {
		return vertices[v].neighbours;
	}

	int size() {return n_v;}

	int getPrice(int i) {
		return vertices[i].price;
	}

	void printVertices() {
		for (int i=0; i<n_v; ++i) {
			std::cout << vertices[i].id << " " << vertices[i].price << std::endl;
		}
	}

	void printEdges() {
		for (int i=0; i<n_v; ++i) {
			for (std::pair<int, int> p : outConnections(i)) {
				std::cout << i << " " << p.first << " " << p.second << std::endl;
			}
		}
	}
};

#endif /* GRAPH_HPP_ */
