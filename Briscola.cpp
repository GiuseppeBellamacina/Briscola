#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#define DIM 40
using namespace std;

class Carta{
	private:
		string seme;
		short valore;
		short punteggio;
		bool briscola;
	public:
		Carta(string s, short v, short p, bool b): seme(s), valore(v), punteggio(p), briscola(b){}
		
		string& getSeme(){return seme;}
		short& getValore(){return valore;}
		short& getPunteggio(){return punteggio;}
		bool& getBriscola(){return briscola;}
		
		ostream& print(ostream& os){
			int i=1,j=4;
			if(this->valore<10) j=5;
			if(this->seme=="Oro") i=3;
			os << "_______" << endl;
			os << "|" << seme <<  setw(i) << "|" << endl;
			os << "|" << valore << setw(j) << "|" << endl;
			os << "|     |" << endl;
			os << "|_____|" << endl;
			return os;
		}
		
};

ostream& operator<<(ostream& os, Carta* c){
	return c->print(os);
}

short setPunteggio(short n){
			switch(n){
				case 1: return 11;
				case 2:
				case 4:
				case 5:
				case 6:
				case 7: return 0;
				case 8: return 2;
				case 3: return 10;
				case 9: return 3;
				case 10: return 4;
			}
		}

void init(Carta** vec){
	string a[4]={"Oro","Spade","Coppe","Mazze"};
	for(int i=0; i<4; i++){
		for(int j=0; j<10; j++){
			vec[10*i+j] = new Carta(a[i],j+1,setPunteggio(j+1),false);
		}
	}
	cout << "BRISCOLA" << endl;
	cout << "Benvenuto, il mazziere ha preso il mazzo e lo sta mischiando" << endl;
}

void swap(Carta** vec, int i){
	int pos = rand()%DIM;
	Carta aux = *vec[i];
	*vec[i] = *vec[pos];
	*vec[pos] = aux;
}

void mischia(Carta** vec){
	for(int i=0; i<DIM; i++) swap(vec,i);
}

void distribuisci(Carta** vec1, Carta** vec2, int& n1, int n2){
	for(int i=0; i<n2; i++)
		vec2[i] = vec1[i+n1];
	n1+=n2;
}

void setBriscola(Carta** vec){
	string br = vec[39]->getSeme();
	for(int i=0; i<DIM; i++)
		if(vec[i]->getSeme()==br) vec[i]->getBriscola()=true;
	cout << "Il seme di briscola e' " << br << endl;
	system("pause");
}

void mostra(Carta** vec){
	system("cls");
	cout << "_________________________" << endl;
	cout << "Queste sono le tue carte" << endl;
	for(int i=0; i<3; i++) cout << vec[i];
	cout << "_________________________" << endl;
	cout << "Carta a terra" << endl;
}

void lancio(Carta** orig, Carta** dest, int i){
	dest[0] = orig[i];
}

void initPartita(Carta** mazzo, Carta** gioc, Carta** avv, Carta** terra, int& n1, int n2){
	init(mazzo);
	mischia(mazzo);
	distribuisci(mazzo,gioc,n1,n2);
	distribuisci(mazzo,avv,n1,n2);
	setBriscola(mazzo);
	mostra(gioc);
	lancio(avv,terra,rand()%3);
}


int main(){
	srand(time(0));
	Carta* mazzo[DIM];
	Carta* gioc[3];
	Carta* avv[3];
	Carta* terra[1];
	int index = 0, punteggioGioc = 0, punteggioAvv = 0;
	
	initPartita(mazzo,gioc,avv,terra,index,3);
	cout << terra[0];
	return 0;
}
