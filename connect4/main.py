import numpy as np
#import pygame
import sys
import random
import math
import texttable

class Game:
    def __init__(self):
        self._ROW_COUNT = 6
        self._COLUM_COUNT = 7
        self._PLAYER = 0
        self._AI = 1
        self._PLAYER_PIECE = 1
        self._AI_PIECE = 2
        self._board = np.zeros((self._ROW_COUNT, self._COLUM_COUNT))

    def get_board(self):
        return self._board

    def drop_piece(self, row, col, piece):
        self._board[row][col] = piece

    def is_valid_location(self, col):
        return self._board[self._ROW_COUNT - 1][col] == 0

    def get_next_open_row(self, col):
        for r in range(self._ROW_COUNT):
            if self._board[r][col] == 0:
                return r

    def playerMove(self, col, piece):
        if self.is_valid_location(col):
            row = self.get_next_open_row(col)
            self.drop_piece(row, col, piece)

    def isWonPlayer(self):
        if self.winning_move(1):
            return True

    def winning_move(self, piece):
        # Check horizontal locations for win
        for c in range(self._COLUM_COUNT - 3):
            for r in range(self._ROW_COUNT):
                if self._board[r][c] == piece and self._board[r][c + 1] == piece and self._board[r][c + 2] == piece and self._board[r][c + 3] == piece:
                    return True

        # Check vertical location for win
        for c in range(self._COLUM_COUNT):
            for r in range(self._ROW_COUNT - 3):
                if self._board[r][c] == piece and self._board[r + 1][c] == piece and self._board[r + 2][c] == piece and self._board[r + 3][c] == piece:
                    return True

        # Check positively sloped diagonals
        for c in range(self._COLUM_COUNT - 3):
            for r in range(self._ROW_COUNT - 3):
                if self._board[r][c] == piece and self._board[r + 1][c + 1] == piece and self._board[r + 2][c + 2] == piece and self._board[r + 3][c + 3] == piece:
                    return True

        # Check negatively sloped diagonals
        for c in range(self._COLUM_COUNT - 3):
            for r in range(3, self._ROW_COUNT):
                if self._board[r][c] == piece and self._board[r - 1][c + 1] == piece and self._board[r - 2][c + 2] == piece and self._board[r - 3][c + 3] == piece:
                    return True

    def __str__(self):
        board = np.flip(self._board, 0)
        t = texttable.Texttable()
        d = {1: 'R', 0: ' ', 2: 'Y'}
        for i in range(self._ROW_COUNT):
            row = []
            for j in range(self._COLUM_COUNT):
                row.append(d[board[i][j]])
            t.add_row(row)
        return t.draw()


class AI:
    def __init__(self):
        self._PLAYER_PIECE = 1
        self._AI_PIECE = 2
        self._EMPTY = 0
        self._ROW_COUNT = 6
        self._COLUM_COUNT = 7
        self._WINDOW_LENGHT = 4

    def drop_piece(self,board, row, col, piece):
        board[row][col] = piece

    def is_valid_location(self, board, col):
        return board[self._ROW_COUNT - 1][col] == 0

    def get_next_open_row(self, board, col):
        for r in range(self._ROW_COUNT):
            if board[r][col] == 0:
                return r

    def winning_move(self, board, piece):
        # Check horizontal locations for win
        for c in range(self._COLUM_COUNT - 3):
            for r in range(self._ROW_COUNT):
                if board[r][c] == piece and board[r][c + 1] == piece and board[r][c + 2] == piece and board[r][
                    c + 3] == piece:
                    return True

        # Check vertical location for win
        for c in range(self._COLUM_COUNT):
            for r in range(self._ROW_COUNT - 3):
                if board[r][c] == piece and board[r + 1][c] == piece and board[r + 2][c] == piece and board[r + 3][
                    c] == piece:
                    return True

        # Check positively sloped diagonals
        for c in range(self._COLUM_COUNT - 3):
            for r in range(self._ROW_COUNT - 3):
                if board[r][c] == piece and board[r + 1][c + 1] == piece and board[r + 2][c + 2] == piece and \
                        board[r + 3][c + 3] == piece:
                    return True

        # Check negatively sloped diagonals
        for c in range(self._COLUM_COUNT - 3):
            for r in range(3, self._ROW_COUNT):
                if board[r][c] == piece and board[r - 1][c + 1] == piece and board[r - 2][c + 2] == piece and \
                        board[r - 3][c + 3] == piece:
                    return True

    def evaluate_window(self, window, piece):
        score = 0
        opp_piece = self._PLAYER_PIECE
        if piece == self._PLAYER_PIECE:
            opp_piece = self._AI_PIECE

        if window.count(piece) == 4:
            score += 100
        elif window.count(piece) == 3 and window.count(self._EMPTY) == 1:
            score += 5
        elif window.count(piece) == 2 and window.count(self._EMPTY) == 2:
            score += 2
        if window.count(opp_piece) == 3 and window.count(self._EMPTY) == 1:
            score -= 4
        return score

    def score_position(self, board, piece):
        score = 0
        # Score center column
        center_array = [int(i) for i in list(board[:, self._COLUM_COUNT // 2])]
        center_count = center_array.count(piece)
        score += center_count * 3
        # Score Horizontal
        for r in range(self._ROW_COUNT):
            row_array = [int(i) for i in list(board[r, :])]
            for c in range(self._COLUM_COUNT - 3):
                window = row_array[c:c + self._WINDOW_LENGHT]
                score += self.evaluate_window(window, piece)

        # Score Vertical
        for c in range(self._COLUM_COUNT):
            col_array = [int(i) for i in list(board[:, c])]
            for r in range(self._ROW_COUNT - 3):
                window = col_array[r:r + self._WINDOW_LENGHT]
                score += self.evaluate_window(window, piece)

        # Score positive sloped diagonals
        for r in range(self._ROW_COUNT - 3):
            for c in range(self._COLUM_COUNT - 3):
                for i in range(self._WINDOW_LENGHT):
                    window = [board[r + i][c + i]]
                score += self.evaluate_window(window, piece)

        # Score negative sloped diagonals
        for r in range(self._ROW_COUNT - 3):
            for c in range(self._COLUM_COUNT - 3):
                window = [board[r + 3 - i][c + i] for i in range(self._WINDOW_LENGHT)]
                score += self.evaluate_window(window, piece)

        return score

    def is_terminal_node(self, board):
        #return self._game.winning_move(self._PLAYER_PIECE) or self._game.winning_move(self._AI_PIECE) or len(self.get_valid_location(self._game.get_board())) == 0
        return self.winning_move(board, self._PLAYER_PIECE) or self.winning_move(board, self._AI_PIECE) or len(self.get_valid_location(board)) == 0

    def minimax(self, board, depth, maximizingPlayer):
        valid_locations = self.get_valid_location(board)
        is_terminal = self.is_terminal_node(board)
        if depth == 0 or is_terminal:
            if is_terminal:
                if self.winning_move(board, self._AI_PIECE):
                    return (None, 10000000000)
                elif self.winning_move(board, self._PLAYER_PIECE):
                    return (None, -10000000000)
                else:
                    return (None, 0)
            else:
                return (None, self.score_position(board, self._AI_PIECE))
        if maximizingPlayer:  # AI
            value = -math.inf
            column = random.choice(valid_locations)
            for col in valid_locations:
                row = self.get_next_open_row(board, col)
                b_copy = board.copy()
                self.drop_piece(b_copy, row, col, self._AI_PIECE)
                new_score = self.minimax(b_copy, depth - 1, False)[1]
                if new_score > value:
                    value = new_score
                    column = col
            return (column, value)
        else:  # minimizing player
            value = math.inf
            column = random.choice(valid_locations)
            for col in valid_locations:
                row = self.get_next_open_row(board, col)
                b_copy = board.copy()
                self.drop_piece(b_copy, row, col, self._PLAYER_PIECE)
                new_score = self.minimax(b_copy, depth - 1, True)[1]
                if new_score < value:
                    value = new_score
                    column = col
            return (column, value)

    def get_valid_location(self, board):
        valid_locations = []
        for col in range(self._COLUM_COUNT):
            if self.is_valid_location(board, col):
                valid_locations.append(col)
        return valid_locations

    def pick_best_move(self, board, piece):

        best_score = -100000
        valid_locations = self.get_valid_location(board)
        best_col = random.choice(valid_locations)
        for col in valid_locations:
            row = self.get_next_open_row(board, col)
            temp_board = board.copy()
            self.drop_piece(temp_board, row, col, piece)
            score = self.score_position(temp_board, piece)
            if score > best_score:
                best_score = score
                best_col = col

        return best_col

class ComputerPlyer:
    def __init__(self, ai):
        self._ai = ai
        self._AI_PIECE = 2

    def computerMove(self, board):
        col, minimax_score = self._ai.minimax(board, 3, True)
        if self._ai.is_valid_location(board, col):
            row = self._ai.get_next_open_row(board, col)
            self._ai.drop_piece(board, row, col, self._AI_PIECE)

    def isWonAi(self, board):
        if self._ai.winning_move(board, self._AI_PIECE):
            return True

class UI:
    def __init__(self, game, computerPlayer):
        self._game = game
        self._computerPlayer = computerPlayer
        self._ROW_COUNT = 6
        self._COLUM_COUNT = 7

    def print_board(self, board):
        board = np.flip(board, 0)
        t = texttable.Texttable()
        d = {1: 'R', 0: ' ', 2: 'Y'}
        for i in range(self._ROW_COUNT):
            row = []
            for j in range(self._COLUM_COUNT):
                row.append(d[board[i][j]])
            t.add_row(row)
        return t.draw()

    def _readPlayerMove(self):
        while True:
            try:
                cmd = int(input(">"))
                if cmd < 0 or cmd > 6:
                    print("Invalid input")
                    return
                return int(cmd)
            except Exception:
                print("Invalid coordinates")

    def start(self):
        board = self._game.get_board()
        game_over = False
        turn = random.randint(self._game._PLAYER, self._game._AI)
        print(self.print_board(board))
        print("******************************")
        while not game_over:
            if turn == 0:
                choice = self._readPlayerMove()
                self._game.playerMove(choice, 1)
                if self._game.isWonPlayer():
                    print("Congrats! You won!")
                    game_over = True
                print(self.print_board(board))
                print("******************************")
                turn += 1
                turn = turn % 2
            else:
                self._computerPlayer.computerMove(board)
                if self._computerPlayer.isWonAi(board):
                    print("You were defeated!!")
                    game_over = True
                print(self.print_board(board))
                print("******************************")
                turn += 1
                turn = turn % 2