from os import system
from random import randint


DIM = 40
# class: it is the class which defines a card
class Card:
    # constructor
    def __init__(self, seed, value, points, briscola, launched):
        self.seed = seed
        self.value = value
        self.points = points
        self.briscola = briscola
        self.launched = launched
    # function: gives to each card a name
    def name(self) -> str:
        match self.value:
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

# function: defines the way to print the cards
def print_card(obj :Card) -> None:
    print("_________")
    if obj.seed == "Oro":
        print("|" + obj.seed + "    |")
    else:
        print("|" + obj.seed + "  |")
    match obj.value:
        case 1:
            print("|Asso   |")
        case 8:
            print("|Donna  |")
        case 9:
            print("|Cavallo|")
        case 10:
           print("|Re     |") 
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

# function: initializes the deck
def init(list: Card) -> None:
    a = ["Oro","Spade","Coppe","Mazze"]
    for i in range(4):
        for j in range(10):
            list.append(Card(a[i],j+1,setPoints(j+1),False,False))
    print("BRISCOLA")
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
def distribute(deck: Card, list: Card, local_index: int) -> None:
    for i in range(3): list.append(deck[i+local_index])
    local_index += 3
    global index
    index = local_index

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
def show(pl: Card, gr: Card, noc: bool, br: str, index: int) -> None:
    system("cls")
    print("Il seme di briscola e' " + br + "          MAZZO")
    print("___________________________" + "          Carte rimanenti: " + str(DIM-index))
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

#function: initializes the game
def initGame(deck: Card, pl: Card, op: Card, gr: Card) -> str:
    init(deck)
    mix(deck)
    distribute(deck,pl,index)
    distribute(deck,op,index)
    br = setBriscola(deck)
    return br

# main function: here starts the execution
# arrays
deck, player, opponent, ground = [], [], [], []
# int
index, player_points, opponent_points, ind1, ind2 = 0, 0, 0, 0, 0
# booleans
turn, no_ground, game = True, True, True
    
br = initGame(deck,player,opponent,ground)
show(player,ground,no_ground,br,index)
system("pause")