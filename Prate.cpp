#include "Prate.h"

void Prate::setParameters(string pname, string ppriceType, int s, int e){
        name = pname;
        priceType = ppriceType;
        start = s;
        end = e;
}

void Prate::setPath(List<int> ppath){
            path = ppath;
            steps = path.size();
        }

void Prate::calculatePrice(){
        for(Node<int>* i = path.begin(); i != path.end(); i = i->next){
            if(map[i->data / 25][i->data % 25] == priceType){
                incScore(10);
            }
        }
    }

void Prate::incScore(int inc){
        score += inc;
    }

int Prate::getStepsValue(){
        return steps;
    }

int Prate::getScore(){
        return score;
    }

string Prate::getName(){
        return name;
    }

void Prate::printPath(){
        fstream file;
        string filename = name + "adim" + ".txt";
        file.open(filename, ios::out);
        file << name << ".adim = " << steps << endl;
        file << name << ".puani = " << score << endl;
        file << "\n" << name << " path : \n" << endl;
        file << "(" << start / maxRow << ", " << start % maxColumn << ")" << "=>";
        for(Node<int>* i = path.begin(); i != path.end(); i = i->next){
            if(i->data == -1){
                file << "\nGeldigi en son yol ayirmina donuyor" << endl;
            }
            else{
                file << "(" << i->data / maxRow << ", " << i->data % maxColumn << ")" << "=>";
            }

        }
        file << "(" << END / maxRow << ", " << END % maxColumn << ")" << endl;
        file << "Cikisa vardi..." << endl;
        file << endl;
        cout << name << ".txt dosyasi olusturup oyuncunu adimlari topladigi puanlari yazdirlidi."  << endl;
    }

int Prate::getStart(){
        return start;
    }
