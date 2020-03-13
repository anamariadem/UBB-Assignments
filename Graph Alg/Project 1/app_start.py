from graph_repr import *
from file_work import *
from user_interface import *

fg = FileGraphs("graph1m.txt")
fg.create_graph()
#list = fg.getAll()
#print(list)
ui = UI(fg)
ui.start()