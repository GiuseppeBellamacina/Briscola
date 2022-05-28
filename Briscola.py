class Carta:
    def __init__(self, seme, valore, punteggio, briscola, lanciata):
        self.seme = seme
        self.valore = valore
        self.punteggio = punteggio
        self.briscola = briscola
        self.lanciata = lanciata

def setPunteggio(n: int) -> int:
    match n:
        case 1:
            return 11
        case 2,4,5,6,7:
            return 0
        case 8:
            return 2
        case 9:
            return 3
        case 10:
            return 4
        case 3:
            return 10

def init(list) -> None:
    a = ["Oro","Spade","Coppe","Mazze"]
    for i in range(4):
        for j in range(10):
            list.append(Carta(a[i],j+1,setPunteggio(j+1),False,False))
    print("BRISCOLA")
    print("Benvenuto, il mazziere ha preso il mazzo e lo sta mischiando")

def print_carta(obj :Carta) -> None:
    print("_______")
    print("|     |")
    print("|     |")
    print("|     |")
    print("|_____|")

arr = []
init(arr)