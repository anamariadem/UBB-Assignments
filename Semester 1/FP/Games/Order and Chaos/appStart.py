from board import *
from gamePlay import *
from ui import *

b = Board()
gp = GamePlay(b)
ui = UI(gp)
ui.start()