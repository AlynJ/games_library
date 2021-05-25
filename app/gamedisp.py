import numpy as np

from tkinter import Tk, Canvas, Frame, Button, BOTH, TOP, BOTTOM

## display class
class GameDisplay(Frame):
  """
    This class generates the minesweeper GUI via Tkinter.
  """
  def __init__(self, parent, game):
    """
      Initiates the class.
    """
    self.game = game
    self.parent = parent
    Frame.__init__(self, parent)
    self.lose=False
    self.flags=np.zeros([self.game.get_imx(), self.game.get_jmx()], np.int)


    self.MARGIN = 20  # Pixels around the board
    self.SIDE = 50  # Width of every board cell.
    self.HEIGHT = self.MARGIN * 2 + self.SIDE * self.game.get_imx()  # height of the whole board
    self.WIDTH = self.MARGIN * 2 + self.SIDE * self.game.get_jmx()  # width of the whole board
    self.row, self.col = -1, -1

    self._initGUI()

  def _initGUI(self):
    """
      Initiates the GUI.
    """
    self.parent.title("Minesweeper")
    self.pack(fill=BOTH, expand=1)
    self.canvas = Canvas(self,
                         bg="white",  
                         width=self.WIDTH, ##define WIDTH
                         height=self.HEIGHT) ##define HEIGHT
    self.canvas.pack(fill=BOTH, side=TOP)
    replay_button = Button(self,
                          text="Play again",
                          command=self.__replay)
    replay_button.pack(fill=BOTH, side=BOTTOM)

    self.__draw_grid()
    self.__draw_puzzle()

    self.canvas.bind("<Button-1>", self.__cell_clicked)
    self.canvas.bind("<Double-Button-1>", self.__unveil_unmarked)
    self.canvas.bind("<Button-3>", self.__marker)

  def __draw_grid(self):
    """
    Draws the grid.
    """
    color = "black"
    for i in range(0,self.game.get_imx()+1):
      x0 = self.MARGIN
      y0 = self.MARGIN + i * self.SIDE
      x1 = self.WIDTH - self.MARGIN
      y1 = self.MARGIN + i * self.SIDE
      self.canvas.create_line(x0, y0, x1, y1, fill=color)

    for j in range(0,self.game.get_jmx()+1):

      x0 = self.MARGIN + j * self.SIDE
      y0 = self.MARGIN
      x1 = self.MARGIN + j * self.SIDE
      y1 = self.HEIGHT - self.MARGIN
      self.canvas.create_line(x0, y0, x1, y1, fill=color)


  def __draw_puzzle(self):
    """
      Draws the game on the grid.
    """
    self.canvas.delete("numbers")
    for i in range(0,self.game.get_imx()):
      for j in range(0,self.game.get_jmx()):
        display = self.game.display_el(i,j)
        answer = ""  
        color = "blue" 
        if(self.flags[i,j] == 1): 
          answer = "?"
          color = "red" 
        x = self.MARGIN + j * self.SIDE + self.SIDE / 2
        y = self.MARGIN + i * self.SIDE + self.SIDE / 2
        #define the size of the grid element
        x0=x-self.SIDE / 2
        x1=x+self.SIDE / 2
        y0=y-self.SIDE / 2
        y1=y+self.SIDE / 2
        if(self.lose):
          color = "black" 
          if(self.game.minefield_el(i,j) == 9):
            answer = "*"  
            self.canvas.create_rectangle( x0, y0, x1, y1,
            tags="numbers", fill="orange red", outline="black")
          else:
            answer = self.game.minefield_el(i,j)  
        elif((self.flags[i,j] == 0) and (display != 0)):
          answer = self.game.minefield_el(i,j) 
        else:
          self.canvas.create_rectangle( x0, y0, x1, y1,
          tags="numbers", fill="light gray", outline="black")
            
        self.canvas.create_text(x 
                               ,y 
                               ,text=answer
                               ,tags="numbers" 
                               ,fill=color)

  def __draw_victory(self):
    """
      Draws a square victory sign.
    """
    imx = self.game.get_imx()
    jmx = self.game.get_jmx()
    x0 = self.MARGIN + self.SIDE * (jmx/2 - 2.5)
    y0 = self.MARGIN + self.SIDE * (imx/2 - 2.5)
    x1 = self.MARGIN + self.SIDE * (jmx/2 + 2.5)
    y1 = self.MARGIN + self.SIDE * (imx/2 + 2.5)
    self.canvas.create_rectangle(
      x0, y0, x1, y1,
      tags="victory", fill="light blue", outline=""
    )
    # create text
    x = self.MARGIN + jmx/2 * self.SIDE
    y = self.MARGIN + imx/2 * self.SIDE
    self.canvas.create_text(
      x, y,
      text="You won!", tags="victory",
      fill="white", font=("Arial", 32)
    )

  def __replay(self):
    """
      Resets the board for another game.
    """
    self.game.mine_init()
    self.lose=False
    self.canvas.delete("numbers")
    self.canvas.delete("victory")
    del self.flags
    self.flags=np.zeros([self.game.get_imx(), self.game.get_jmx()], np.int)
    self.__draw_puzzle()

  def __cell_clicked(self, event):
    """
      Interprets the left mouse click on the grid element as a command to reveal it.
    """
    x, y = event.x, event.y
    if (self.MARGIN < x < self.WIDTH - self.MARGIN and self.MARGIN < y < self.HEIGHT - self.MARGIN):
      self.canvas.focus_set()

      # get row and col numbers from x,y coordinates
      row, col = int((y - self.MARGIN) / self.SIDE), int((x - self.MARGIN) / self.SIDE)
      if (self.flags[row,col]==1):
        return
      # if cell was selected already - deselect it
      elif (self.game.display_el(row,col) == 0):
        self.row, self.col = row, col
        self.game.update(row,col)
        if(self.game.minefield_el(row,col) == 9):
          self.lose=True 
        self.__draw_puzzle()
        if (self.game.get_safe() == 0):
          self.__draw_victory()
    else:
      self.row, self.col = -1, -1

  def __unveil_unmarked(self, event):
    """
      Interprets the double left mouse click on the grid element to reveal all unflagged neighbouring 
      elements. The number of flagged neighbouring elements must be at least equal to the element clue 
      of the number of neighbouring mines.
    """
    x, y = event.x, event.y
    if (self.MARGIN < x < self.WIDTH - self.MARGIN and self.MARGIN < y < self.HEIGHT - self.MARGIN):
      self.canvas.focus_set()

      # get row and col numbers from x,y coordinates
      row, col = int((y - self.MARGIN) / self.SIDE), int((x - self.MARGIN) / self.SIDE)
      nflags=0
      for i in range(row-1,row+2):
        for j in range(col-1,col+2):
          if ((i<0) or (j<0) or (i>=self.game.get_imx()) or (j>=self.game.get_jmx())): 
            continue
          if (self.flags[i,j]==1):
            nflags+=1

      if(nflags>=self.game.minefield_el(row,col)):
        for i in range(row-1,row+2):
          for j in range(col-1,col+2):
            if ((i<0) or (j<0) or (i>=self.game.get_imx()) or (j>=self.game.get_jmx())): 
              continue
      # if cell was selected already - deselect it
            if((self.game.display_el(i,j) == 0) and (self.flags[i,j]==0)):
              self.row, self.col = i, j
              self.game.update(i,j)
              if(self.game.minefield_el(i,j) == 9):
                self.lose=True
                self.__draw_puzzle()
                return
              self.__draw_puzzle()
              if (self.game.get_safe() == 0):
                self.__draw_victory()
                return
    else:
      self.row, self.col = -1, -1
      

  def __marker(self, event):
    """
      Interprets the right mouse click on the grid element as a flag preventing this element to 
      be revealed.
    """
    x, y = event.x, event.y
    if (self.MARGIN < x < self.WIDTH - self.MARGIN and self.MARGIN < y < self.HEIGHT - self.MARGIN):
      self.canvas.focus_set()

      # get row and col numbers from x,y coordinates
      row, col = int((y - self.MARGIN) / self.SIDE), int((x - self.MARGIN) / self.SIDE)

      # if cell was selected already - deselect it
      if((self.game.display_el(row,col) == 0) and (self.flags[row,col]==0)):
        self.row, self.col = row, col
        self.flags[row,col]=1
      else:
        self.row, self.col = row, col
        self.flags[row,col]=0
      self.__draw_puzzle()
    else:
      self.row, self.col = -1, -1

  