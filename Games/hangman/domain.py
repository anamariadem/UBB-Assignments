class Sentence:
    def __init__(self, sentence):
        self._sentence = sentence
        self._sentenceToDisplay = ""
        self._lenght = len(self._sentence)
    
    @property
    def FullSentence(self):
        return self._sentence

    @FullSentence.setter
    def FullSentence(self, sentence):
        self._sentence = sentence

    @property
    def Lenght(self):
        return self._lenght

    @property
    def SentenceToDisplay(self):
        return self._sentenceToDisplay

    @SentenceToDisplay.setter
    def SentenceToDisplay(self, sentence):
        self._sentenceToDisplay = sentence

    @staticmethod
    def read(line):
        sentence = line.strip()
        return Sentence(sentence)

    @staticmethod
    def write(sentence):
        return sentence.FullSentence

    def __str__(self):
        return str(self.FullSentence)