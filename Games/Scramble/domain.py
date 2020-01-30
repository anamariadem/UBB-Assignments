class Sentence:
    def __init__(self, sentence):
        self._sentence = sentence
        self._display = sentence
        self._score = 0
        self._history = ""

    def __len__(self):
        return len(self._sentence)

    @property
    def Sentence(self):
        return self._sentence

    @property
    def Display(self):
        return self._display
    @Display.setter
    def Display(self, value):
        self._display = value

    @property
    def Score(self):
        return self._score

    @Score.setter
    def Score(self, value):
        self._score = value

    @property
    def History(self):
        return self._history

    @History.setter
    def History(self, value):
        self._history = value


    def __str__(self):
        return str(self.Sentence)

    @staticmethod
    def readEntity(line):
        sentence = line.strip()
        return Sentence(sentence)
