#ifndef PRATE_H_INCLUDED
#define PRATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include "Graph.cpp"

#define maxRow 25
#define maxColumn 25

using namespace std;

string map[maxRow][maxColumn];
int END;


class Prate{
    string name;
    string priceType;
    int start;
    int end;
    int score = 0;
    int steps = -1;
    List<int> path;
public:
    void setParameters(string pname, string ppriceType, int s, int e); // oyuncuya parametreleri atayan fonksiyon
    void setPath(List<int> ppath); // oyuncunun yolunu olusturan fonksiyon

    void calculatePrice(); // oyuncunu toplayacagi odulleri hesaplayan fonksiyon

    void incScore(int inc); // oyuncuya puan ekleme fonksiyonu
    int getStepsValue(); // atilan adimlarin sayisini donduren fonksiyon
    int getScore(); // puani donduren fonkisyon
    string getName(); // oyuncun adini doduren fonksiyon

    void printPath(); // oyuncunun izledigi yolu yazdiran fonksiyon

    int getStart(); // baslangic noktasi donduren fonksiyon
};




#endif // PRATE_H_INCLUDED
