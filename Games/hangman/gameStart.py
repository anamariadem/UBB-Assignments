from domain import *
from repository import *
from service import *
from UI import *

repo = FileRepo("sentences.txt", Sentence.read, Sentence.write)
service = Service(repo)

sentence = Sentence("")
playerController = PlayerController(sentence)
gamePlay = GamePlay(repo, playerController)
gamePlay.chooseSentence()
playerController.initializeSentence()

ui = UI(service, gamePlay)

ui.startApp()