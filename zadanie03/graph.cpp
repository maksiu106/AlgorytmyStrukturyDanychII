#include <iostream>

#include "graph.hpp"

int main() {
	//wczytanie ilości przystanków
	int n;
	std::string str;
	std::cin >> n;
	Graph city = Graph(n);

	//wczytanie przystanków
	for (int i=0; i<n; ++i) {
		std::cin >> str;
		city.add_vertex(str);
	}

	//wczytanie liczby linii
	std::cin >> n;
	std::cin.ignore();

	//wczytanie tras linii
	for(int i=0; i<n; ++i) {
		std::getline (std::cin, str);
		city.add_route(str);
	}

	//przystanek początkowy i końcowy
	std::string start;
	std::string end;
	std::cin >> start;
	std::cin >> end;

	std::cout << city.bfs(start, end) << std::endl;
}
