#!/usr/bin/env python

import pygame, sys
from pygame.locals import *
import collections

# set up window size
WINDOWWIDTH = 560
WINDOWHEIGHT =540 

# grid positions
START = 100
Grid_UpperLeft = (100,100)
Grid_UpperRight = (460, 100)
Grid_LowerLeft = (100, 460)
Grid_LowerRight = (460,460)
Grid_Size = 360

#           R     G    B
WHITE = (  255, 255, 255)
BLACK = (    0,   0,   0)

# List to hold all numbers in each cell
NUMBERS = [-1] * 81

# the button class
class Button:
    def __init__(self, pos, name_input, surface_screen):
        self.position = pos
        self.name = name_input
        self.width = 70
        self.height = 30
	self.screen = surface_screen 
	self.code = False 
        
    def drawButton(self):
        pygame.draw.line(self.screen, BLACK, self.position, (self.position[0], self.position[1]+ self.height), 1)
        pygame.draw.line(self.screen, BLACK, self.position, (self.position[0]+ self.width, self.position[1]), 1)
        pygame.draw.line(self.screen, BLACK, (self.position[0],self.position[1]+ self.height), (self.position[0]+ self.width, self.position[1]+ self.height), 1)
        pygame.draw.line(self.screen, BLACK, (self.position[0]+ self.width, self.position[1]), (self.position[0]+self.width, self.position[1]+self.height), 1)

    def writeName(self):
        font = pygame.font.Font( None, 24)
        text = font.render(self.name, 1, BLACK)
        textpos = text.get_rect()
        textpos.centerx = self.position[0] + self.width/2
        textpos.centery = self.position[1] + self.height/2
        self.screen.blit(text, textpos)

    def writeDescription(self):

        font = pygame.font.Font(None, 20)
        if self.name == "Done": text_string = "Click Done button to check your solution."
        else:
            if self.code == True:
                text_string = "Congradulations!               "
            else:  text_string = "Wrong Answer!                  "
            second_string = "Click button to start a new game."
            second_text = font.render(second_string, 1, BLACK)
            second_textpos = second_text.get_rect()
            second_textpos.centerx = 330
            second_textpos.centery = 60
            self.screen.blit(second_text, second_textpos)
        text = font.render(text_string, 1, BLACK)
        textpos = text.get_rect()
        textpos_width = text.get_width()
        textpos_height = text.get_height()
        textpos.centerx = 330
        textpos.centery = 35 
        self.screen.blit(text, textpos)

    def draw(self):
	self.drawButton()
        self.writeName()
        self.writeDescription()

    def pressed(self, code=False):
        if code == True:
            self.code = code
        if self.name == "Done": 
            self.name = "Restart"
        else: 
            self.name = "Done"
            self.code = False
            internalGame()
            
        print 74
        print code
	self.draw()
        
            
            
# set up the initial state of the game.            
def internalGame():
    global NUMBERS, RESULTS
    NUMBERS = [-1, -1, -1,7,5,6,9,-1,2,-1,4,-1,-1,3,1,-1,7,-1,-1,-1,-1,-1,4,-1,-1,1,-1,4,-1,-1,-1,-1,-1, 7,3,1,-1,-1,1,4,9,3,8,-1,-1,6,3,8,-1,-1,-1,-1,-1,9,-1,5,-1,-1,1,-1,-1,-1,-1,-1,2,-1,3,8,-1,-1,6,-1,8,-1,7,6,2,4,-1,-1,-1]

    RESULTS = [1, 8,3,7,5,6,9,4,2,2,4,9,8,3,1,6,7,5,7,6,5,2,4,9,3,1,8,4,9,2,5,6,8,7,3,1,5,7,1,4,9,3,8,2,6,6,3,8,1,7,2,4,5,9,3,5,6,9,1,7,2,8,4,9,2,4,3,8,5,1,6,7,8,1,7,6,2,4,5,9,3]


# set up the window surface 
def setupWindow():
    global    DISPLAYSURF
    # set up the window
    pygame.init()
    DISPLAYSURF = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
    DISPLAYSURF.fill(WHITE)
    BASICFONT = pygame.font.Font('freesansbold.ttf',18)
    pygame.display.set_caption('Sudoku')

   
# draw the whole game grid. 
def drawGrid():
    pygame.draw.line(DISPLAYSURF, BLACK, Grid_UpperLeft, Grid_UpperRight, 3)
    pygame.draw.line(DISPLAYSURF, BLACK, Grid_UpperLeft, Grid_LowerLeft, 3)
    pygame.draw.line(DISPLAYSURF, BLACK, Grid_UpperRight, Grid_LowerRight, 3)
    pygame.draw.line(DISPLAYSURF, BLACK, Grid_LowerLeft, Grid_LowerRight, 3)

    pygame.draw.line(DISPLAYSURF, BLACK, (220, 100), (220, 460), 2)
    pygame.draw.line(DISPLAYSURF, BLACK, (340, 100), (340, 460), 2)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 220), (460, 220), 2)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 340), (460, 340), 2)

    pygame.draw.line(DISPLAYSURF, BLACK, (140, 100), (140, 460), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (180, 100), (180, 460), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (260, 100), (260, 460), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (300, 100), (300, 460), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (380, 100), (380, 460), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (420, 100), (420, 460), 1)

    pygame.draw.line(DISPLAYSURF, BLACK, (100, 140), (460, 140), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 180), (460, 180), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 260), (460, 260), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 300), (460, 300), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 380), (460, 380), 1)
    pygame.draw.line(DISPLAYSURF, BLACK, (100, 420), (460, 420), 1)


# display all numbers in each cell.
def showNumbers():

    for i in range(81):
        showNumber(i)

# display the number of a specific cell.
def showNumber(i):
    if NUMBERS[i] < 0: return
    font = pygame.font.Font( None, 36)
    text = font.render(str(NUMBERS[i]), 1, BLACK)
    textpos = text.get_rect()
    row = i/9
    column = i%9
    textpos.centerx = START + (row + 0.5)* Grid_Size/9
    textpos.centery = START + (column + 0.5) * Grid_Size/9
    DISPLAYSURF.blit(text, textpos)

   
# from the mouse click position, get to the cell being clicked. 
def gridClicked( this_pos ):
    
    row = (this_pos[0]-START) *9 / Grid_Size
    column = (this_pos[1] - START) *9 / Grid_Size
    return ('GRID', row*9+column)
    
# exit game when triggured.
def checkExitCode():
    if EXIT_CODE == 1:
        pygame.quit()
        sys.exit()

# check if mouse clicked on any cell or the button. 
def checkMouse(this_pos):
    global first_button 

    if this_pos[0] <460 and this_pos[0] >= 100 and this_pos[1]<460  and this_pos[1] >= 100:
           return gridClicked(this_pos)       
    #print first_button.position
    #print first_button.width, first_button.height
    #print this_pos
    if this_pos[0] > first_button.position[0] and this_pos[0] < first_button.position[0] + first_button.width  and  this_pos[1] > first_button.position[1]  and this_pos[1] < first_button.position[1] + first_button.height:
       result_code = NUMBERS[:] == RESULTS[:]
       first_button.pressed(result_code)  
       print str(153) + " " + first_button.name
    return (' ', -1)


# get the user input on the number for a specific cell.
def setNumber(current_position, key):
    if   key == K_1: NUMBERS[current_position] = 1
    elif key == K_2: NUMBERS[current_position] = 2
    elif key == K_3: NUMBERS[current_position] = 3
    elif key == K_4: NUMBERS[current_position] = 4
    elif key == K_5: NUMBERS[current_position] = 5
    elif key == K_6: NUMBERS[current_position] = 6
    elif key == K_7: NUMBERS[current_position] = 7
    elif key == K_8: NUMBERS[current_position] = 8
    elif key == K_9: NUMBERS[current_position] = 9
    elif key == K_BACKSPACE: NUMBERS[current_position] = -1
    else: return 0
    return 1


# the overal setup function
def setUp():

    # Setups
    drawGrid()       # plot 9*9 grid
    showNumbers()    # show numbers

    first_button.draw()
   

# main function for the game. 
def main():
    global EXIT_CODE
    global first_button

    EXIT_CODE = 0
    
    setupWindow()    # set up initial window
    internalGame()
    # create buttons
    first_button = Button((100,20),"Done", DISPLAYSURF)

    # Event loop
    current_position = -1   
    while 1:
	DISPLAYSURF.fill(WHITE)
	setUp()
 
        for event in pygame.event.get():
            if event.type == QUIT: return
            elif event.type == MOUSEBUTTONUP:
                result = checkMouse(pygame.mouse.get_pos() )
                if result[0] == 'GRID':
                    current_position = result[1]
                flag = 1
            elif event.type == KEYDOWN:
                print "KeyDown"
                if current_position < 0: continue
                if setNumber(current_position, event.key):
                    current_position = -1
                else: continue
       
        pygame.display.update()   # show the screen
    




if __name__ == '__main__':
    main()
