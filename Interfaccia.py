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
