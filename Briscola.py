from os import system
from random import randint


DIM = 40
# Classe delle carte
class Carta:
    def __init__(self, seme, valore, punteggio, briscola, lanciata):
        self.seme = seme
        self.valore = valore
        self.punteggio = punteggio
        self.briscola = briscola
        self.lanciata = lanciata
    def name(self):
        match self.valore:
            case 1: return "un gran bell'asso"
            case 2: return "un 2"
            case 3: return "un 3"
            case 4: return "un 4"
            case 5: return "un bel 5"
            case 6: return "un bel 6"
            case 7: return "un bel 7"
            case 8: return "una bella donna"
            case 9: return "un bel cavallo"
            case 10: return "un bel re"

# funzione per stamapre le carte
def print_carta(obj :Carta) -> None:
    print("_________")
    if obj.seme == "Oro":
        print("|" + obj.seme + "    |")
    else:
        print("|" + obj.seme + "  |")
    match obj.valore:
        case 1:
            print("|Asso   |")
        case 8:
            print("|Donna  |")
        case 9:
            print("|Cavallo|")
        case 10:
           print("|Re     |") 
        case _:
            print("|" + str(obj.valore) + "      |")
    print("|       |")
    print("|       |")
    print("|_______|")

# funzione per assegnare il punteggio
def setPunteggio(n: int) -> int:
    match n:
        case 1: return 11
        case 2,4,5,6,7: return 0
        case 8: return 2
        case 9: return 3
        case 10: return 4
        case 3: return 10

# funzione per inizializzare il mazzo
def init(list: Carta) -> None:
    a = ["Oro","Spade","Coppe","Mazze"]
    for i in range(4):
        for j in range(10):
            list.append(Carta(a[i],j+1,setPunteggio(j+1),False,False))
    print("BRISCOLA")
    print("Benvenuto, il mazziere ha preso il mazzo e lo sta mischiando")

# funzione per lo swap
def swap(list: Carta, i: int) -> None:
    pos = randint(0,DIM-1)
    aux = list[i]
    list[i] = list[pos]
    list[pos] = aux

# funzione per mischiare il mazzo
def mischia(list: Carta) -> None:
    for i in range(DIM):
        swap(list,i)

# DA QUI INIZIA L'ESECUZIONE
def main() -> None:
    mazzo, gioc, avv, terra = [], [], [], []
    init(mazzo)
    mischia(mazzo)
    for carta in mazzo:
        print_carta(carta)
    system("pause")

main()