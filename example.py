import app.gamewrapper as gw
import app.gamedisp as gm
from tkinter import Tk

##main code

#initiate and display the minefield
ms = gw.Minesweeper()

#set input parameters
ms.set_int(10,20,10)
ms.mine_init()

#initiate the game window
root = Tk()
GD = gm.GameDisplay(root,ms)
root.geometry("%dx%d" % (GD.WIDTH, GD.HEIGHT + 40))
root.mainloop()

  
