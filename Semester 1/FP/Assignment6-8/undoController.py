
class UndoController:
    def __init__(self):
        self._history = []
        self._index = 0
        self._duringUndoRedo = False

    def recordOperation(self,operation):
        '''

        :param operation:
        :return:
        '''
        if self._duringUndoRedo == True:
            return

        if self._index < len(self._history):
            self._history = self._history[:self._index]

        self._history.append(operation)
        self._index += 1

    def undo(self):
        if self._index == 0:
            raise ValueError("No more undos!")
        self._duringUndoRedo = True
        self._index -= 1
        self._history[self._index].undo()
        self._duringUndoRedo = False

    def redo(self):
        if self._index == len(self._history):
            raise ValueError("No more redos!")
        self._duringUndoRedo = True
        self._history[self._index].redo()
        self._index += 1
        self._duringUndoRedo = False

class Operation:
    def __init__(self, undoFunction, redoFunction):
        self._undo = undoFunction
        self._redo = redoFunction

    def undo(self):
        self._undo.call()

    def redo(self):
        self._redo.call()

class CascadedOperation:
    def __init__(self,operation1,operation2):
        self._op1 = operation1
        self._op2 = operation2

    def undo(self):
        self._op2.undo()
        self._op1.undo()

    def redo(self):
        self._op2.redo()
        self._op1.redo()


class FunctionCall:
    def __init__(self,function,*parameters):
        self._function = function
        self._params = parameters

    def call(self):
        self._function(*self._params)