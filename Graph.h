#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Stack.cpp"

class Graph
{
	int size;
	List<int> *adjency;
public:
	Graph(int size); // kurucu fonksiyon
	void addEdge(int v, int w); // edge ekleme fonksiyon
	void getPathByDFS(List<int> &path, int s, int e); // iki nokta arasindaki yolu path degiskenine yazan fonksiyon
};

#endif // GRAPH_H_INCLUDED
