#include "Graph.h"


Graph::Graph(int size)
{
	this->size = size;
	adjency = new List<int>[size]; // komsuluk listesi
}

void Graph::addEdge(int v, int w)
{
	adjency[v].push_back(w); // komsuluk listesine ekleniyor
}

void Graph::getPathByDFS(List<int> &path, int s, int e)
{
    bool visited[size] = {false}; // ziyaret bilgisini tutan dizi
	Stack<int> stack; // yol uzerinde dfs mantigi ile gezmek icin yigin yapisi
	stack.push(s); // ilk ziyaret edilen dugum yigina ekleniyor
	while (!stack.isEmpty())
	{
		int s = stack.topAndPop(); // yiginin basindaki elemani alip siliyor
		if (!visited[s]){ // ziyaret edilememis ise yigina ekleyip ziyaret edildi diye isaretliyor
			path.push_back(s);
			visited[s] = true;
		}
		if(s == e){ // eger varilmak istenilen noktaya varidiysa gezme dongusu kiriliyor
            break;
		}
		bool test = false; // derinlemesine gidildigi icin en derine gittikten sonra en son yol ayrimina dondugunu anlamak icin konulan degisken
		for (Node<int>* i = adjency[s].begin(); i != adjency[s].end(); i = i->next){ // her dugumden derinlemsine gidebildigi kadar gidiyor
            if (!visited[i->data]){
                stack.push(i->data);
                test = true;
            }
        }
        if(!test){ // en derine gittikten sonra en son yol ayrimine dondugunu anlamak icin yola bir -1 kordinatoru ekleniyor
            path.push_back(-1);
        }
	}
}

