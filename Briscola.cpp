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

void mostra(Carta** gioc){
	system("cls");
	cout << "_________________________" << endl;
	cout << "Queste sono le tue carte" << endl;
	for(int i=0; i<3; i++) cout << gioc[i];
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

void noCartaTerra(){
	cout << "_______" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|_____|" << endl;;
}

int match(Carta** vec, Carta** terra, int i){
	int ret = vec[i]->getPunteggio()+terra[0]->getPunteggio();
	if(vec[i]->getBriscola()){
		if(!terra[0]->getBriscola()) return ret;
		if(terra[0]->getBriscola()) return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -1;
	}
	if(!vec[i]->getBriscola()){
		if(terra[0]->getBriscola()) return -1;
		if(!terra[0]->getBriscola()) return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -1;
	}
}

bool game(Carta** gioc, Carta** avv, Carta** terra, int& g, int& a, bool& turno, bool vuoto, int index, short& z, short& q){
	if(vuoto) noCartaTerra();
	else cout << terra[0];
	if(turno){
		if(vuoto){
			cout << "\nScegli la carta da lanciare (0) (1) (2)";
			cin >> z;
			vuoto = false;
			turno = false;
			return true;
		}
		else{
			cout << "\nScegli la carta da lanciare (0) (1) (2)";
			cin >> z;
			if(match(gioc,terra,z)!=-1){
				g+=match(avv,terra,z);
				vuoto = true;
				turno = false;
				return true;
			}
			else{
				a+=match(avv,terra,z);
				vuoto = true;
				turno = false;
				return true;
			}
		}
	}
	else{
		q = rand()%3;
		if(vuoto){
			terra[0] = avv[q];
			vuoto = false;
			turno = true;
			return true;
		}
		else{
			if(match(gioc,terra,q)!=-1){
				a+=match(avv,terra,q);
				cout << "Ha preso l'avversario" << endl;
				vuoto = true;
				turno = true;
				return true;
			}
			else{
				g+=match(avv,terra,q);
				cout << "Hai preso tu" << endl;
				vuoto = true;
				turno = true;
				return true;
			}
		}
	}
}

void pesca(Carta** mazzo, Carta** vec, short n, int& index){
	vec[n] = mazzo[index++];
}


int main(){
	srand(time(0));
	Carta* mazzo[DIM];
	Carta* gioc[3];
	Carta* avv[3];
	Carta* terra[1];
	int index = 0, punteggioGioc = 0, punteggioAvv = 0;
	bool turno = 1, vuoto = 0; // 1->gioc; 0->avv
	short z,q;
	
	initPartita(mazzo,gioc,avv,terra,index,3);
	while(game(gioc,avv,terra,punteggioGioc,punteggioAvv,turno,vuoto,index,z,q)){
		pesca(mazzo,gioc,z,index);
		pesca(mazzo,avv,q,index);
	};
	return 0;
}
