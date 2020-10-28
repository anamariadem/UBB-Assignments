import random

'''
Bulls and cows 
This is a game played by the human player against the computer as follows:
    1.The computer selects a random 4 digit number , which has no repeating digits
    2. The player tries to guess the  number
    3. Each turn, the player enters a 4 digit number
        -numbers must not have repeating digits
        - trying the same number twice loses the game
    4. The computer tells how many bulls (correct digits in the correct place) and cows(correct digit but incorrect place)
    5. Game is over when  number is guessed. The aim is to do this over the smallest number of turns
    
    4B0C -> win
'''

class Game:
    def __init__(self):
        #self._number = self._generateNumber()
        self._guesses = []
        self._done = 0
        self._bulls = 0
        self._cows = 0

    def _generateNumber(self):
        '''
        generate a valid number
        :return:
        '''
        ok = True
        while ok == True:
            num = random.randint(1023, 9876)
            x = num
            l = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            ok = False
            while num > 0:
                l[num % 10] = l[num % 10] + 1
                num = num // 10
            for i in range(0, 10):
                if l[i] > 1:
                    ok = True
                    break
        print(x)
        return x

    def newGame(self):
        self._done = 0
        self._guesses.clear()
        self._number = self._generateNumber()

    def userInput(self,no):
        num = int(no)
        try:
            no = int(no)
        except:
            raise ValueError("Input is not integer")
        len = 0
        while no != 0:
            no //= 10
            len +=1
        if len != 4:
            raise ValueError("Input does not have 4 digits")
        a = num % 10
        b = num // 10 % 10
        c = num // 100 % 10
        d = num // 1000 % 10
        if a == b or a == c or a == d or b == c or b == d or c == d:
           raise ValueError("Input has duplicate digits")

    def isRepeatedGuess(self,no):
        '''
        if yes -> lost
        :param no:
        :return:
        '''

        for i in self._guesses:
            if i == no:
                self._done = 1
                raise ValueError("Repeated guess. Game lost!")
        self._guesses.append(no)

    def guess(self, userGuess):
        '''
        compute cows and bulls
        :param userGuess:
        :return:
        '''
        self._bulls = self.calc_bulls(userGuess)
        self._cows = self.calc_cows(userGuess)
        if self._bulls == 4:
            self._done = 1
            raise ValueError("Congrats!! You won!")

    def calc_bulls(self,userGuess):
        a = int(userGuess)
        b = int(self._number)
        bulls = 0
        while a > 0:
            if a%10 == b%10:
                bulls = bulls + 1
            a = a // 10
            b = b // 10
        return bulls

    def calc_cows(self,userGuess):
        a = int(userGuess)
        b = int(self._number)
        cows = 0
        l1 = []
        l2 = []
        while a > 0:
            l1.append(a % 10)
            a = a // 10
        while b > 0:
            l2.append(b % 10)
            b = b // 10
        for i in range(0,4):
            for j in range(0,4):
                if l1[i] == l2[j] and i!=j:
                    cows = cows + 1
        return cows



'''
1. Generate 1000 numbers
2. For each generated digit
    number in [1023,9876]
    no duplicate digits
'''
def test_generate():
    pass

