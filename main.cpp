#include "Prate.cpp"

/*
    Bu projede ilk once ada.txt dosyasindan harita okunuyor, ada.txt dosyasinda oyuncularin kordinatlarini
    bulunup oyuncular olusturuluyor, ondan sonra END yani cikis noktasinin bulunup oyunculara aktariliyor.
    Harita okunduktan sonra matrisin her bir elemani edge olarak grapha ekleniyor. Graphta yazmis oldugum
    matris uzerindeki her hangi iki nokta arasinda ki yolu DFS mantigi ile donduryor boylece her oyuncu kendi
    yolunu bulmasi icin graph sinifin icinde ki bu fonksiyonu kullanarak buluyor.
*/

Graph graph(maxRow * maxColumn);
List<Prate> prates;

int readMap(); //Haritayi okuyup map degiskenine atiyor
void buildGraph(); // Grapha edgeleri yukleyen fonksiyon
void findEnd(); // END cikis noktasini bulan fonksiyon
void initializePrates(); // oyunculari insa eden fonksiyon
void runPrates(); // oyunculari oyunatan fonksiyon
void conclusion(); // sonucu hesaplayip sonuc dosyasina yazdiran fonksiyon

int main()
{
    if(readMap() == -1){
        cout << "Ada.txt dosyasi acilamadi" << endl;
        return -1;
    }
    cout << "############################\n" << endl;
    findEnd();
    initializePrates();
    buildGraph();
    runPrates();
    conclusion();
    cout << "\n############################" << endl;
	return 0;
}

void conclusion(){
    // sonuc.txt dosyasi aciliyor
    fstream file;
    file.open("sonuc.txt", ios::out);
    int pratesSize;
    pratesSize = prates.size();
    Prate tmpPrates[pratesSize];
    // oyunculari siralamak icin gecici bir diziye atiliyor
    for(int i = 0; i < pratesSize; i++){
        tmpPrates[i] = prates.getBack();
        prates.pop_back();
    }
    // adim sayisina gore oyuncular siralaniyor.
    for(int i = 0; i < pratesSize; i++){
        for(int j = i + 1; j < pratesSize; j++){
            if(tmpPrates[j].getStepsValue() < tmpPrates[i].getStepsValue()){
                Prate tmp;
                tmp = tmpPrates[j];
                tmpPrates[j] = tmpPrates[i];
                tmpPrates[i] = tmp;
            }
        }
    }
    file << "## Sonuc dosyasi ##\n\n" << endl;
    file << "Adim sayisina gore siralama : " << endl;
    // oyuncularin adimlari dosyaya yazdirliyor
    for(int i = 0; i < pratesSize; i++){
        file << tmpPrates[i].getName() << ".adim = " << tmpPrates[i].getStepsValue() << endl;
    }

    file << "\n\nBuna gore " << tmpPrates[0].getName() << "'e 15 puan eklenecek. \n" << endl;
    tmpPrates[0].incScore(15);
    //puana gore oyuncular siralaniyor
    for(int i = 0; i < pratesSize; i++){
        for(int j = i + 1; j < pratesSize; j++){
            if(tmpPrates[j].getScore() > tmpPrates[i].getScore()){
                Prate tmp;
                tmp = tmpPrates[j];
                tmpPrates[j] = tmpPrates[i];
                tmpPrates[i] = tmp;
            }
        }
    }
    file << "Toplam puan : " << endl;
    // oyuncularin puanlari yazdiriliyor
    for(int i = 0; i < pratesSize; i++){
        file << tmpPrates[i].getName() << ".adim = " << tmpPrates[i].getScore() << endl;
    }
    file << "\n######################" << endl;
    file << "\nBuna gore kazanan " << tmpPrates[0].getName() << " :) " << endl;
    file << "\n######################" << endl;
    cout << "Sonuc hesaplanip sonuc.txt dosyasina yazdirildi." << endl;
}

void runPrates(){
    // oyunculari once yol bulma fonksiyonu sonra odulu hesaplama sonra sonucu yazdirmak icin gerekli fonksiyonlar cagirliyor.
    for(Node<Prate>* i = prates.begin(); i != prates.end(); i = i->next){
        List<int> path;
        graph.getPathByDFS(path, i->data.getStart() + 1, END-1);// yolu bulan foksiyon
        i->data.setPath(path); // bulunan yol oyuncuya atayan fonksiyon
        i->data.calculatePrice(); // oyucunu toplayacagi odulu hesaplayan
        i->data.printPath(); // oyucunu gectigi yolu dosyaya yazdiran fonksiyon
    }
}

void initializePrates(){
    //Karakterlerin baslangic noktalri bulunup olusturlumasi ve hartiadan kalidirilmasi
    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxColumn; j++){
            if(map[i][j] == "P1"){
                Prate p;
                p.setParameters("P1", "Y", ((i*maxRow) + j), END);
                prates.push_back(p);
                map[i][j] = "0";
            }
            if(map[i][j] == "P2"){
                Prate p;
                p.setParameters("P2", "Z", ((i*maxRow) + j), END);
                prates.push_back(p);
                map[i][j] = "0";
            }
            if(map[i][j] == "P3"){
                Prate p;
                p.setParameters("P3", "S", ((i*maxRow) + j), END);
                prates.push_back(p);
                map[i][j] = "0";
            }
            if(map[i][j] == "P4"){
                Prate p;
                p.setParameters("P4", "P", ((i*maxRow) + j), END);
                prates.push_back(p);
                map[i][j] = "0";
            }
        }
    }

}

void findEnd(){
    //Hazinenin kordinatoru bulunmasi
    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxColumn; j++){
            if(map[i][j] == "E"){
                END = (i*maxRow) + j;
            }
        }
    }
}

void buildGraph(){
    // edgler grapha ekleniyor
    // formul matris uzerindeki dugumun degerini bulmak icin {{edgeValue = i*maxRow + j*maxColumn}}
    // her nokta icin ust, sol, sag, alt bakip yol varsa edge olarak grapha ekleniyor.
    for(int i = 1; i < maxRow-1; i++){
        for(int j = 1; j < maxColumn-1; j++){
            if(map[i][j] != "0"){
                if(map[i-1][j] != "0"){
                    graph.addEdge(((i*maxRow) + j), (((i-1)*maxRow) + j));
                }
                if(map[i][j+1] != "0") {
                    graph.addEdge(((i*maxRow) + j), ((i*maxRow) + j+1));
                }
                if(map[i+1][j] != "0"){
                    graph.addEdge(((i*maxRow) + j), (((i+1)*maxRow) + j));
                }
                if(map[i][j-1] != "0") {
                    graph.addEdge(((i*maxRow) + j), ((i*maxRow) + j-1));
                }
            }
        }
    }
}

int readMap(){
    // ada.txt dosyasi okunup map dizisine ataniyor.
    char word;
    List<string> s;
    string ss = "";
    fstream file;
    file.open("Ada.txt", ios::in);
    if(!file.is_open()){
        return -1;
    }
    while(file >> word){
        if(word != ','){
            if(word == 'P'){
                ss = "";
                char c;
                c = word;
                file >> word;
                if(word == ','){
                    ss += c;
                    s.push_back(ss);
                }
                else{
                    ss += c;
                    ss += word;
                    s.push_back(ss);
                }
            }
            else{
                string sss;
                sss = word;
                s.push_back(sss);
            }
        }

    }

    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxColumn; j++){
            map[i][j] = s.front();
            s.pop_front();
        }
    }
    return 1;
}
