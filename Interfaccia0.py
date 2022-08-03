from tkinter import *


#si fa la finestra
window = Tk()
#si danno le dimensioni
window.geometry("450x450")
#diamo il titolo
window.title("Titolo titolato")
#possiamo bloccare le dimensioni
window.resizable(False, False)
#facciamo lo sfondo
window.configure(background="red")

def first_print():
    text = "ciao mbare"
    text_output = Label(window, text=text, fg="blue", background="red", font=("Calibri, 24"))
    text_output.grid(row=0, column=1, sticky="W")
    
def second_print():
    text = "vediamo che fa sto coso"
    text_output = Label(window, text=text, fg="green", background="red", font=("Calibri, 24"))
    text_output.grid(row=1, column=1, sticky="W")

#creo un pulsante
first_button = Button(window, text="Pulsante1", command=first_print)
first_button.grid(row=0, column=0, sticky="W")

second_button = Button(window, text="Pulsante2", command=second_print)
second_button.grid(row=1, column=0, pady=100, sticky="W")


#per avviare la finestra si usa questo
if __name__ == "__main__":
    window.mainloop()
    
# ALTRO ESEMPIO
  
# pip install Pillow (serve per usare i jpg)
# usa questo comando sul prompt per installare la libreria (potrebbe essere gia' installata pero')
from PIL import Image
from PIL import ImageTk
import tkinter as tk

window = tk.Tk()
window.geometry("1536x1024")
window.title("Asso piglia tutto")

def func():
    print("ciao")

image_1 = ImageTk.PhotoImage(Image.open("C:/Users/bella/Desktop/Asso.jpg").resize((300,300),Image.ANTIALIAS)) # definisci l'immagine
# ti conviene inserire l'intero indirizzo dell'immagine e fai attenzione a non avere file o cartelle con gli spazi ' ' e ad usare '/' e non '\'
label_1 = tk.Button(window, image=image_1, command=func) # definisci una Label con immagine
# puoi specificare le dimensioni della Label, se non specifichi usa le dimensioni dell'immagine
label_1.pack(pady=20, side=tk.TOP, anchor='w') # serve a far comparire la Label

# padx, pady e' una spaziatura rispettivamente sull'asse x o y dalla cornice piu' vicina
# side si usa con tk.TOP, tk.LEFT, tk.RIGHT, tk.BOTTOM e serve a posizionare la Label su un lato
# anchor serve ad allineare la Label nella window e si usa con le iniziali dei punti cardinali in inglese: east, west, north, south

if __name__ == "__main__":
    window.mainloop()
# SUGGERIMENTO: le carte inseriscile come immagini di oggetti Button() (riga 13)
# label_1 = tk.Button(window, image=image_1)
