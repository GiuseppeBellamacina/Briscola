from PIL import Image
from PIL import ImageTk
import tkinter as tk
import glob, os

window = tk.Tk()
window.geometry("1536x1024")
window.title("Asso piglia tutto")
window.configure(background="green")

photos = []
i, j = 0, 0

def func():
    print("ciao")
    
def displayImg(img):
    global i,j
    image = Image.open(img).resize((80,140),Image.ANTIALIAS)
    photo = ImageTk.PhotoImage(image)
    photos.append(photo)
    newPhoto_button = tk.Button(window,image=photo,command=func)
    newPhoto_button.grid(row=i, column=j, pady=8, padx=8)
    j+=1
    if(j==10):
        j=0
        i+=1


os.chdir("C:/Users/bella/Desktop/Carte")
for file in glob.glob("*.jpg"):
    displayImg(file) 

if __name__ == "__main__":
    window.mainloop()