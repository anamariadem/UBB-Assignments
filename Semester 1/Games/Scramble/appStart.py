from domain import *
from repo import *
from gamePlay import *
from ui import *

repo =  FileRepo("sentences.txt", Sentence.readEntity)
gp = GamePlay(repo)
ui = UI(gp)
ui.start()