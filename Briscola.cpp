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
		case 1: return "un gran bell'asso";
		case 2: return "un 2";
		case 3: return "un 3";
		case 4: return "un 4";
		case 5: return "un bel 5";
		case 6: return "un bel 6";
		case 7: return "un bel 7";
		case 8: return "una bella donna";
		case 9: return "un bel cavallo";
		case 10: return "un bel re";
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
	cout << "BRISCOLA" << endl << endl;
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

string setBriscola(Carta** vec){
	string br = vec[39]->getSeme();
	for(int i=0; i<DIM; i++)
		if(vec[i]->getSeme()==br) vec[i]->getBriscola()=true;
	cout << "Il seme di briscola e' " << br << endl;
	system("pause");
	system("cls");
	return br;
}

void noCartaTerra(){
	cout << "_______" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|     |" << endl
		 << "|_____|" << endl;;
}

void mostra(Carta** gioc, Carta** terra, bool vuoto, string br, int index, int g, int a){
	system("cls");
	cout << "Il seme di briscola e' " << br << setw(br=="Oro" ? 22 : 20) << "MAZZO" << endl;
	cout << "___________________________" << setw(33) << "Carte rimanenti: " << DIM-index << endl;
	cout << "Queste sono le tue carte" << endl;
	for(int i=0; i<3; i++){
		if(gioc[i]->isLanciata()) noCartaTerra();
		else cout << gioc[i];
	}
	cout << "___________________________" << endl;
	cout << "Carta a terra" << endl;
	if(vuoto) noCartaTerra();
	else cout << terra[0];
}

void lancio(Carta** orig, Carta** dest, int i){
	dest[0] = orig[i];
	orig[i]->isLanciata() = true;
}

string initPartita(Carta** mazzo, Carta** gioc, Carta** avv, Carta** terra, int& n1, int n2){
	init(mazzo);
	mischia(mazzo);
	distribuisci(mazzo,gioc,n1,n2);
	distribuisci(mazzo,avv,n1,n2);
	string br = setBriscola(mazzo);
	return br;
}

int match(Carta** vec, Carta** terra, int i){
	int ret = vec[i]->getPunteggio()+terra[0]->getPunteggio();
	if(terra[0]->getBriscola()){
		if(vec[i]->getBriscola()){
			if(vec[i]->getPunteggio()==0 && terra[0]->getPunteggio()==0)
				return vec[i]->getValore()>terra[0]->getValore() ? ret : -ret;
			return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -ret;
		}
		else return -ret;
	}
	else{
		if(vec[i]->getBriscola()) return ret;
		else{
			if(vec[i]->getSeme()==terra[0]->getSeme()){
				if(vec[i]->getPunteggio()==0 && terra[0]->getPunteggio()==0)
					return vec[i]->getValore()>terra[0]->getValore() ? ret : -ret;
				return vec[i]->getPunteggio()>terra[0]->getPunteggio() ? ret : -ret;
			}
			else return -ret;
		}
	}
}

bool matchL(Carta** vec, Carta** terra, int i){
	if(terra[0]->getBriscola()){
		if(vec[i]->getBriscola()){
			return terra[0]->getValore()>vec[i]->getValore() ? false : true;
		}
	}
	else{
		if(vec[i]->getBriscola()) return true;
		else return terra[0]->getValore()>vec[i]->getValore() ? false : true;
	}
}

void occhiata(Carta** avv){
	system("cls");
	cout << "Minchia mbare, belle carte..." << endl;
	cout << "___________________________" << endl;
	cout << "Queste NON sono le tue carte" << endl;
	for(int i=0; i<3; i++){
		if(avv[i]->isLanciata()) noCartaTerra();
		else cout << avv[i];
	}
	cout << endl;
	system("pause");
}

// gioc sono le carte del giocatore
// avv sono le carte dell'avversario
// terra è la carta a terra (se c'è)
// g è il punteggio del giocatore
// a è il punteggio dell'avversario
// turno dice chi inizia il turno ogni volta (1->giocatore, 0->avversario)
// vuoto dice se a terra non c'è nessuna carta
// index è l'indice del mazzo
// z è l'indice della carta scelta dal giocatore
// q è l'indice della carta scelta dall'avversario
// br è la briscola

bool game(Carta** gioc, Carta** avv, Carta** terra, int& g, int& a, bool& turno, bool& vuoto, int& index, short& z, short& q, string br){
	mostra(gioc,terra,vuoto,br,index,g,a);
	// comincio io
	if(turno){
		cout << endl << "Scegli la carta da lanciare (1) (2) (3) --> ";
		cin >> z;
		if(z==1234){
			occhiata(avv);
			mostra(gioc,terra,vuoto,br,index,g,a);
		}
		while(cin.fail() || z>3 || z<1 || gioc[z-1]->isLanciata()){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Scegli la carta da lanciare (1) (2) (3) --> ";
			cin >> z;
		}
		z--;
		lancio(gioc,terra,z);
		vuoto = false;
		mostra(gioc,terra,vuoto,br,index,g,a);
		cout << endl << "Ora tocca all'avversario" << endl;
		system("pause");
		q = rand()%3;
		mostra(gioc,terra,vuoto,br,index,g,a);
		while(avv[q]->isLanciata()) q = rand()%3;
		if(avv[q]->getPunteggio()==0){
			cout << endl << "Il tuo avversario ci va di liscio con " << avv[q]->name() << (avv[q]->getSeme()=="Oro" ? " d'" : " di ") << avv[q]->getSeme() << endl;
			if(avv[q]->getBriscola()) cout << "Ma tena accura, ittau na briscola" << endl;
		}
		else
			cout << endl << "Il tuo avversario sta per lanciare " << avv[q]->name() << (avv[q]->getSeme()=="Oro" ? " d'" : " di ") << avv[q]->getSeme() << endl;
		avv[q]->isLanciata() = true;
		system("pause");
		if(match(avv,terra,q)>0){
			a+=match(avv,terra,q);
			cout << endl << "Ha preso l'avversario" << endl;
			system("pause");
			vuoto = true;
			turno = false;
			return true;
		}
		else if(match(avv,terra,q)<0){
			g-=match(avv,terra,q);
			cout << endl << "Hai preso tu" << endl;
			system("pause");
			vuoto = true;
			turno = true;
			return true;
		}
		else{
			if(matchL(avv,terra,q)){
				cout << endl << "Ha preso l'avversario" << endl;
				system("pause");
				vuoto = true;
				turno = false;
				return true;
			}
			else{
				cout << endl << "Hai preso tu" << endl;
				system("pause");
				vuoto = true;
				turno = true;
				return true;
			}
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
		mostra(gioc,terra,vuoto,br,index,g,a);
		if(avv[q]->getPunteggio()==0) cout << endl << "Ci va di liscio" << endl;
		else if(avv[q]->getPunteggio()>=10) cout << endl << "Mizzica, ittau nu bellu caricu" << endl;
		cout << endl << "Ora tocca a te" << endl;
		system("pause");
		mostra(gioc,terra,vuoto,br,index,g,a);
		cout << endl << "Scegli la carta da lanciare (1) (2) (3) --> ";
		cin >> z;
		while(cin.fail() || z>3 || z<1 || gioc[z-1]->isLanciata()){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Scegli la carta da lanciare (1) (2) (3) --> ";
			cin >> z;
		}
		z--;
		gioc[z]->isLanciata() = true;
		if(match(gioc,terra,z)>0){
			g+=match(gioc,terra,z);
			cout << endl << "Hai preso tu" << endl;
			system("pause");
			vuoto = true;
			turno = true;
			return true;
		}
		else if(match(gioc,terra,z)<0){
			a-=match(gioc,terra,z);
			cout << endl << "Ha preso l'avversario" << endl;
			system("pause");
			vuoto = true;
			turno = false;
			return true;
		}
		else{
			if(matchL(gioc,terra,z)){
				cout << endl << "Hai preso tu" << endl;
				system("pause");
				vuoto = true;
				turno = true;
				return true;
			}
			else{
				cout << endl << "Ha preso l'avversario" << endl;
				system("pause");
				vuoto = true;
				turno = false;
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
	bool turno = true, vuoto = true, g = true;
	short z,q;
	
	string br = initPartita(mazzo,gioc,avv,terra,index,3);
	
	while(g){
		g = game(gioc,avv,terra,punteggioGioc,punteggioAvv,turno,vuoto,index,z,q,br);
		pesca(mazzo,gioc,z,index);
		pesca(mazzo,avv,q,index);
		if(index>39){
			cout << endl << "ATTENZIONE: e' appena finito il mazzo, giocatela bene ora" << endl;
			system("pause");
			g = false;
		}
	}
	
	for(int i=0; i<3; i++){
		game(gioc,avv,terra,punteggioGioc,punteggioAvv,turno,vuoto,index,z,q,br);
	}
	
	mostra(gioc,terra,vuoto,br,index,punteggioGioc,punteggioAvv);
	cout << endl << "La partita e' giunta alla fine, ed il vincitore e'..." << endl;
	if(punteggioGioc==punteggioAvv) cout << "Wow, non me l'aspettavo, questo e' un bel pareggio" << endl;
	else{
		cout << (punteggioGioc>punteggioAvv ? "TU!!! Grandissimo, hai vinto con un bel punteggio di " : "Ehm, non sei tu, mi spiace ma hai perso, il tuo avversario ha totalizato un punteggio di ");
		cout << (punteggioGioc>punteggioAvv ? punteggioGioc : punteggioAvv) << " punti" << endl;
	}
	system("pause");
	
	return 0;
}
