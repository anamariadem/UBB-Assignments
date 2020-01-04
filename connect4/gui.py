from main import *
import pygame
import sys
import random
class GUI:
    def __init__(self, game, computerPlayer):
        self._game = game
        self._computerPlayer = computerPlayer
        self._BLUE = (0, 0, 255)
        self._BLACK = (0, 0, 0)
        self._RED = (255, 0, 0)
        self._YELLOW = (255, 255, 0)
        self._COLUMN_COUNT = 7
        self._ROW_COUNT = 6
        self._SQUARESIZE = 100
        self._RADIUS = int(self._SQUARESIZE / 2 - 5)
        self._PLAYER_PIECE = 1
        self._AI_PIECE = 2

    def draw_board(self, board, screen, height):
        for c in range(self._COLUMN_COUNT):
            for r in range(self._ROW_COUNT):
                pygame.draw.rect(screen, self._BLUE, (c * self._SQUARESIZE, r * self._SQUARESIZE + self._SQUARESIZE, self._SQUARESIZE, self._SQUARESIZE))
                pygame.draw.circle(screen, self._BLACK, (
                int(c * self._SQUARESIZE + self._SQUARESIZE / 2), int(r * self._SQUARESIZE + self._SQUARESIZE + self._SQUARESIZE / 2)), self._RADIUS)

        for c in range(self._COLUMN_COUNT):
            for r in range(self._ROW_COUNT):
                if board[r][c] == self._PLAYER_PIECE:
                    pygame.draw.circle(screen, self._RED, (
                        int(c * self._SQUARESIZE + self._SQUARESIZE / 2), height - int(r * self._SQUARESIZE + self._SQUARESIZE / 2)),
                                       self._RADIUS)
                elif board[r][c] == self._AI_PIECE:
                    pygame.draw.circle(screen, self._YELLOW, (
                        int(c * self._SQUARESIZE + self._SQUARESIZE / 2), height - int(r * self._SQUARESIZE + self._SQUARESIZE / 2)),
                                       self._RADIUS)
        pygame.display.update()

    def start(self):
        board = self._game.get_board()
        game_over = False
        pygame.init()
        width = self._COLUMN_COUNT * self._SQUARESIZE
        height = (self._ROW_COUNT + 1) * self._SQUARESIZE
        size = (width, height)
        screen = pygame.display.set_mode(size)
        self.draw_board(board, screen, height)
        pygame.display.update()
        myfont = pygame.font.SysFont("comicsansms", 80)
        turn = random.randint(self._game._PLAYER, self._game._AI)
        while not game_over:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                if event.type == pygame.MOUSEMOTION:
                    pygame.draw.rect(screen, self._BLACK, (0, 0, width, self._SQUARESIZE))
                    posx = event.pos[0]
                    if turn == 0:
                        pygame.draw.circle(screen, self._RED, (posx, int(self._SQUARESIZE // 2)), self._RADIUS)
                pygame.display.update()

                if event.type == pygame.MOUSEBUTTONDOWN:
                    pygame.draw.rect(screen, self._BLACK, (0, 0, width, self._SQUARESIZE))
                    if turn == 0:
                        posx = event.pos[0]
                        col = posx // self._SQUARESIZE
                        # col = int(math.floor(posx/SQUARESIZE))
                        self._game.playerMove(col, self._PLAYER_PIECE)
                        if self._game.isWonPlayer():
                            label = myfont.render("Congrats! You won!", 1, self._RED)
                            screen.blit(label, (40, 10))
                            game_over = True
                        self.draw_board(board, screen, height)
                        turn += 1
                        turn = turn % 2
                        # ask for player2
                if turn == 1 and not game_over:
                    self._computerPlayer.computerMove(board)
                    if self._computerPlayer.isWonAi(board):
                        label = myfont.render("AI won", 1, self._YELLOW)
                        screen.blit(label, (40, 10))
                        game_over = True
                    self.draw_board(board, screen, height)
                    turn += 1
                    turn = turn % 2
                if game_over:
                    pygame.time.wait(2000)