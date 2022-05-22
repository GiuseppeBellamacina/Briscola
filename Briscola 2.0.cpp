#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
#define DIM 40
using namespace std;

class Carta{
	private:
		string seme;
		short valore;
		short punteggio;
		bool briscola;
		bool lanciata;
	public:
		Carta(string s, short v, short p, bool b, bool l): seme(s), valore(v), punteggio(p), briscola(b), lanciata(l){}
		
		string& getSeme(){return seme;}
		short& getValore(){return valore;}
		short& getPunteggio(){return punteggio;}
		bool& getBriscola(){return briscola;}
		bool& isLanciata(){return lanciata;}
		
		string name();
		
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

string Carta::name(){
	switch(this->getValore()){
		case 1: return "un asso";
		case 2: return "un 2";
		case 3: return "un 3";
		case 4: return "un 4";
		case 5: return "un 5";
		case 6: return "un 6";
		case 7: return "un 7";
		case 8: return "una donna";
		case 9: return "un cavallo";
		case 10: return "un re";
	}
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
			vec[10*i+j] = new Carta(a[i],j+1,setPunteggio(j+1),false,false);
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
	system("cls");
}

void noCartaTerra(){
	cout << "_______" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|_____|" << endl;;
}

void mostra(Carta** gioc, Carta** terra, bool vuoto){
	system("cls");
	cout << "Il seme di briscola e' " << br << endl;
	cout << "_________________________" << endl;
	cout << "Queste sono le tue carte" << endl;
	for(int i=0; i<3; i++){
		if(gioc[i]->isLanciata()) noCartaTerra();
		else cout << gioc[i];
	}
	cout << "_________________________" << endl;
	cout << "Carta a terra" << endl;
	if(vuoto) noCartaTerra();
	else cout << terra[0];
}

void lancio(Carta** orig, Carta** dest, int i){
	dest[0] = orig[i];
	orig[i]->isLanciata() = true;
}

void initPartita(Carta** mazzo, Carta** gioc, Carta** avv, Carta** terra, int& n1, int n2){
	init(mazzo);
	mischia(mazzo);
	distribuisci(mazzo,gioc,n1,n2);
	distribuisci(mazzo,avv,n1,n2);
	setBriscola(mazzo);
}

int match(Carta** vec, Carta** terra, int i){
	int ret = vec[i]->getPunteggio()+terra[0]->getPunteggio();
	if(terra[0]->getBriscola()){
		if(!vec[i]->getBriscola()) return -1;
		if(vec[i]->getBriscola()) return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -1;
	}
	if(!terra[0]->getBriscola()){
		if(vec[i]->getBriscola()) return ret;
		if(!vec[i]->getBriscola()){
			if(vec[i]->getSeme()==terra[0]->getSeme()) return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -1;
			else return -1;
		}
	}
}

// gioc sono le carte del giocatore
// avv sono le carte dell'avversario
// terra � la carta a terra (se c'�)
// g � il punteggio del giocatore
// a � il punteggio dell'avversario
// turno dice chi inizia il turno ogni volta (1->giocatore, 0->avversario)
// vuoto dice se a terra non c'� nessuna carta
// index � l'indice del mazzo
// z � l'indice della carta scelta dal giocatore
// q � l'indice della carta scelta dall'avversario

bool game(Carta** gioc, Carta** avv, Carta** terra, int& g, int& a, bool& turno, bool& vuoto, int& index, short& z, short& q){
	mostra(gioc,terra,vuoto);
	// comincio io
	if(turno){
		cout << endl << "Scegli la carta da lanciare (0) (1) (2)\t";
		cin >> z;
		while(cin.fail() || z>2 || z<0 ){
			cerr << endl << "Scrivi (1), (2) o (3)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Scegli la carta da lanciare (0) (1) (2)\t";
			cin >> z;
		}
		lancio(gioc,terra,z);
		vuoto = false;
		mostra(gioc,terra,vuoto);
		cout << endl << "Ora tocca all'avversario" << endl;
		system("pause");
		q = rand()%3;
		mostra(gioc,terra,vuoto);
		while(avv[q]->isLanciata()) q = rand()%3;
		cout << endl << "Il tuo avversario sta per lanciare " << avv[q]->name() << (avv[q]->getSeme()=="Oro" ? " d'" : " di ") << avv[q]->getSeme() << endl;
		system("pause");
		if(match(avv,terra,q)!=-1){
			a+=match(avv,terra,q);
			cout << endl << "Ha preso l'avversario" << endl;
			system("pause");
			vuoto = true;
			turno = false;
			return true;
		}
		else{
			g+=match(avv,terra,q);
			cout << endl << "Hai preso tu" << endl;
			system("pause");
			vuoto = true;
			turno = true;
			return true;
		}
	}
	// comincia l'avversario
	else{
		cout << endl << "Tocca all'avversario" << endl;
		q = rand()%3;
		while(avv[q]->isLanciata()) q = rand()%3;
		lancio(avv,terra,q);
		vuoto = false;
		system("pause");
		mostra(gioc,terra,vuoto);
		cout << endl << "Ora tocca a te" << endl;
		system("pause");
		mostra(gioc,terra,vuoto);
		cout << endl << "Scegli la carta da lanciare (0) (1) (2)\t";
		cin >> z;
		while(cin.fail() || z>2 || z<0 || gioc[z]->isLanciata()){
			cerr << endl << "Scrivi (1), (2) o (3)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Scegli la carta da lanciare (0) (1) (2)\t";
			cin >> z;
		}
		if(match(gioc,terra,z)!=-1){
			g+=match(gioc,terra,z);
			cout << endl << "Ha preso l'avversario" << endl;
			system("pause");
			vuoto = true;
			turno = false;
			return true;
		}
		else{
			a+=match(gioc,terra,z);
			cout << endl << "Hai preso tu" << endl;
			system("pause");
			vuoto = true;
			turno = true;
			return true;
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
	bool turno = true, vuoto = true, g = true;
	short z,q;
	
	initPartita(mazzo,gioc,avv,terra,index,3);
	cout << "Cominci tu, lancia una carta" << endl;
	
	while(g){
		g = game(gioc,avv,terra,punteggioGioc,punteggioAvv,turno,vuoto,index,z,q);
		pesca(mazzo,gioc,z,index);
		pesca(mazzo,avv,q,index);
		if(index>39){
			cout << endl << "ATTENZIONE: � appena finito il mazzo, giocatela bene ora" << endl;
			system("pause");
			g = false;
		}
	}
	
	for(int i=0; i<3; i++){
		game(gioc,avv,terra,punteggioGioc,punteggioAvv,turno,vuoto,index,z,q);
	}
	
	mostra(gioc,terra,vuoto);
	cout << endl << "La partita � giunta alla fine, ed il vincitore e'..." << endl;
	cout << (punteggioGioc>punteggioAvv ? "TU!!! Grandissimo, hai vinto con un bel punteggio di " : "Ehm, non sei tu, mi spiace ma hai perso, il tuo avversario ha totalizato un punteggio di ");
	cout << (punteggioGioc>punteggioAvv ? punteggioGioc : punteggioAvv) << endl;
	system("pause");
	
	return 0;
}
