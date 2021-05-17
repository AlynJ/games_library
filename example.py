import app.gamewrapper as gw
import app.gamedisp as gm
from tkinter import Tk

##main code

#initiate and display the minefield
ms = gw.Minesweeper()

#initiate the game window
root = Tk()
GD = gm.GameDisplay(root,ms)
root.geometry("%dx%d" % (GD.WIDTH, GD.HEIGHT + 40))
root.mainloop()

  
