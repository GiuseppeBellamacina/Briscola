from os import system
from random import randint
from pyfiglet import figlet_format
from termcolor import colored
import colorama

# variable definitions area:
# arrays
deck, player, opponent, ground = [], [], [], [0]
# int
index, player_points, opponent_points, ind1, ind2 = 0, 0, 0, 0, 0
# booleans
turn, no_ground, game = True, True, True

# constant value
DIM = 40

# class: it is the class which defines a card
class Card:
    # constructor
    def __init__(self, seed: str, value: int, points: int, briscola: bool, launched: bool):
        self.seed = seed
        self.value = value
        self.points = points
        self.briscola = briscola
        self.launched = launched
    # function: gives to each card a name
    def name(self) -> str:
        match self.value:
            case 1: return "un gran bell'\33[1masso\33[0m"
            case 2: return "un 2"
            case 3: return "un 3"
            case 4: return "un 4"
            case 5: return "un bel 5"
            case 6: return "un bel 6"
            case 7: return "un bel 7"
            case 8: return "una bella \33[1mdonna\33[0m"
            case 9: return "un bel \33[1mcavallo\33[0m"
            case 10: return "un bel \33[1mre\33[0m"

# function: defines the way to print the cards
def print_card(obj :Card) -> None:
    print("_________")
    if obj.seed == "\33[1;33mOro\33[0m":
        print("|" + obj.seed + "    |")
    else:
        print("|" + obj.seed + "  |")
    match obj.value:
        case 1:
            print("|\33[1mAsso\33[0m   |")
        case 8:
            print("|\33[1mDonna\33[0m  |")
        case 9:
            print("|\33[1mCavallo\33[0m|")
        case 10:
           print("|\33[1mRe\33[0m     |") 
        case _:
            print("|" + str(obj.value) + "      |")
    print("|       |")
    print("|       |")
    print("|_______|")

# function: sets the amount of points for each card
def setPoints(n: int) -> int:
    match n:
        case 1: return 11
        case 2,4,5,6,7: return 0
        case 8: return 2
        case 9: return 3
        case 10: return 4
        case 3: return 10

#ASCII art
def ascii_art() -> None:
    colors = ["red","yellow","green","cyan","blue","magenta"]
    str = "BRISCOLA\nLGBT Edition\n\n"
    print(colored(figlet_format(str, font="slant"), colors[randint(0,5)], 'on_black', ['bold', 'blink']), end='')

# function: initializes the deck
def init(list: Card) -> None:
    a = ["\33[1;33mOro\33[0m","\33[1;34mSpade\33[0m","\33[1;31mCoppe\33[0m","\33[1;32mMazze\33[0m"]
    for i in range(4):
        for j in range(10):
            list.append(Card(a[i],j+1,setPoints(j+1),False,False))
    ascii_art()
    print("Benvenuto, il mazziere ha preso il mazzo e lo sta mischiando")

# function: swap two cards position
def swap(list: Card, i: int) -> None:
    pos = randint(0,DIM-1)
    aux = list[i]
    list[i] = list[pos]
    list[pos] = aux

# function: mix the deck
def mix(list: Card) -> None:
    for i in range(DIM): swap(list,i)
    
# function: gives the three first cards to each player
def distribute(deck: Card, list: Card) -> None:
    global index
    for i in range(3): list.append(deck[i+index])
    index += 3

# function: set the briscola status
def setBriscola(list: Card) -> str:
    br = list[39].seed
    for i in range(DIM):
        if(list[i].seed == br): list[i].briscola = True
    print("Il seme di briscola e' " + br)
    system("pause")
    system("cls")
    return br

# function: defines the way to print a ground without any card
def no_card() -> None:
    print("_________")
    print("|       |")
    print("|       |")
    print("|       |")
    print("|       |")
    print("|_______|")

# function: shows the playground
def show(pl: Card, gr: Card, noc: bool, br: str) -> None:
    system("cls")
    print("Il seme di briscola e' " + br + ("            MAZZO" if br == "\33[1;33mOro\33[0m" else "          MAZZO"))
    print("___________________________" + "           Carte rimanenti: " + str(DIM-index))
    print("Queste sono le tue carte")
    for i in range(3):
        if(pl[i].launched): no_card()
        else: print_card(pl[i])
    print("___________________________")
    print("Carta a terra")
    if(noc): no_card()
    else: print_card(gr[0])

# function: executes the launch of a card on the playground
def launch(orig: Card, dest: Card, i: int):
    dest[0] = orig[i]
    orig[i].launched = True

# function: initializes the game
def initGame(deck: Card, pl: Card, op: Card) -> str:
    init(deck)
    mix(deck)
    distribute(deck,pl)
    distribute(deck,op)
    br = setBriscola(deck)
    return br

# function: draws a card from the deck
def draw(deck: Card, list: Card, n: int) -> None:
    global index
    list[n] = deck[index]
    index += 1

# function: choose who win a match
def match(list: Card, ground: Card, i: int) -> int:
    first = list[i].points if list[i].points is not None else 0
    second = ground[0].points if ground[0].points is not None else 0
    ret = first + second
    if(ground[0].briscola):
        if(list[i].briscola):
            return (ret if first > second else -ret)
        else: return -ret
    else:
        if(list[i].briscola): return ret
        else:
            if(list[i].seed == ground[0].seed):
                return (ret if first > second else -ret)   
            else: return -ret

# function: choose who win a match with "liscie" cards
def matchL(list: Card, ground: Card, i: int) -> bool:
    if(ground[0].briscola):
        if(list[i].briscola):
            return (True if list[i].value > ground[0].value else False)
    else:
        if(list[i].briscola): return True
        else: return (True if list[i].value > ground[0].value else False)

# function: it's not really a legitimate thing
def occhiata(opp: Card):
    system("cls")
    print("Minchia mbare, belle carte...")
    print("___________________________")
    print("Queste NON sono le tue carte")
    for i in range(3):
        if(opp[i].launched): no_card()
        else: print_card(opp[i])
    print('\n')
    system("pause")

# function: this is the most important function of the program
def engine(pl: Card, op: Card, gr: Card, br: str) -> bool:
    global ind1, ind2, no_ground, turn, player_points, opponent_points
    show(pl,gr,no_ground,br)
    if(turn):
        ind1 = input("\nScegli la carta da lanciare (1) (2) (3) --> ")
        while(str(ind1) == '' or not str(ind1).isdigit() or int(ind1)>3 or int(ind1)<1 or pl[int(ind1)-1].launched):
            if(str(ind1).isdigit() and int(ind1) == 1234):
                occhiata(op)
                show(pl,gr,no_ground,br)
            ind1 = input("\nScegli la carta da lanciare (1) (2) (3) --> ")
        ind1 = int(ind1)
        ind1 -= 1
        launch(pl,gr,ind1)
        no_ground = False
        show(pl,gr,no_ground,br)
        print("\nOra tocca all'avversario")
        system("pause")
        show(pl,gr,no_ground,br)
        ind2 = randint(0,2)
        while(op[ind2].launched): ind2 = randint(0,2)
        if(op[ind2].points is None):
            print("\nIl tuo avversario ci va di \33[1mliscio\33[0m con " + op[ind2].name() + (" d'" if op[ind2].seed == "\33[1;33mOro\33[0m" else " di ") + op[ind2].seed)
            if(op[ind2].briscola): print("Ma fai attenzione, ha lanciato una \33[1mbriscola\33[0m")
        else:
            print("\nIl tuo avversario sta per lanciare " + op[ind2].name() + (" d'" if op[ind2].seed == "\33[1;33mOro\33[0m" else " di ") + op[ind2].seed)
        op[ind2].launched = True
        system("pause")
        pt = match(op,gr,ind2)
        if(pt > 0):
            opponent_points += pt
            print("\nHa preso l'avversario")
            system("pause")
            no_ground = True
            turn = False
            return True
        elif(pt < 0):
            player_points -= pt
            print("\nHai preso tu")
            system("pause")
            no_ground = True
            turn = True
            return True
        else:
            if(matchL(op,gr,ind2)):
                print("\nHa preso l'avversario")
                system("pause")
                no_ground = True
                turn = False
                return True
            else:
                print("\nHai preso tu")
                system("pause")
                no_ground = True
                turn = True
                return True
    else:
        print("\nTocca all'avversario")
        ind2 = randint(0,2)
        while(op[ind2].launched): ind2 = randint(0,2)
        launch(op,gr,ind2)
        no_ground = False
        system("pause")
        show(pl,gr,no_ground,br)
        if(op[ind2].points is None): print("\nCi va di \33[1mliscio\33[0m")
        elif(op[ind2].points >= 10): print("\nIl tuo avversario ha buttato un bel \33[1mcarico\33[0m")
        print("\nOra tocca a te")
        system("pause")
        show(pl,gr,no_ground,br)
        ind1 = input("\nScegli la carta da lanciare (1) (2) (3) --> ")
        while(str(ind1) == '' or not str(ind1).isdigit() or int(ind1)>3 or int(ind1)<1 or pl[int(ind1)-1].launched):
            ind1 = input("\nScegli la carta da lanciare (1) (2) (3) --> ")
        ind1 = int(ind1)
        ind1 -= 1
        pl[ind1].launched = True
        pt = match(pl,gr,ind1)
        if(pt > 0):
            player_points += pt
            print("\nHai preso tu")
            system("pause")
            no_ground = True
            turn = True
            return True
        elif(pt < 0):
            opponent_points -= pt
            print("\nHa preso l'avversario")
            system("pause")
            no_ground = True
            turn = False
            return True
        else:
            if(matchL(pl,gr,ind1)):
                print("\nHai preso tu")
                system("pause")
                no_ground = True
                turn = True
                return True
            else:
                print("\nHa preso l'avversario")
                system("pause")
                no_ground = True
                turn = False
                return True            

#arcobalenizza le robe
def arcobaleno(str: str) -> None:
    colors = ["red","yellow","green","cyan","blue","magenta"]
    for i in range(len(str)):
        print(colored(str[i], colors[i%len(colors)], 'on_black', ['bold', 'blink']), end='')

# main function: here starts the execution
def main() -> None:
    global game,no_ground 
    colorama.init()
    br = initGame(deck,player,opponent)
    while(game):
        game = engine(player,opponent,ground,br)
        draw(deck,player,ind1)
        draw(deck,opponent,ind2)
        if(index > 39):
            show(player,ground,no_ground,br)
            print("\n\33[1;31m!!! ATTENZIONE !!!\33[0m\nIl mazzo e' appena finito, giocatela bene ora")
            system("pause")
            game = False
    for i in range(3): engine(player,opponent,ground,br)
    show(player,ground,no_ground,br)
    print("\nLa partita e' giunta alla fine, ed il vincitore e'...")
    system("pause")
    if(player_points == opponent_points): print("Wow, non me l'aspettavo, questo e' un bel pareggio")
    else:
        arcobaleno("TU!!! Grandissimo, hai vinto con un bel punteggio di: ") if player_points > opponent_points else print("Ehm, non sei tu, mi spiace ma hai perso, il tuo avversario ha totalizato un punteggio di:")
        print("--> ", end='')
        arcobaleno(str(player_points)) if player_points > opponent_points else print(str(opponent_points), end='')
        print(" <-- " + " punti")
    system("pause");

if __name__ == "__main__": main()