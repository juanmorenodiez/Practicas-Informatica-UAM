"""Illustration of tournament.

Authors:
    Alejandro Bellogin <alejandro.bellogin@uam.es>

"""

from __future__ import annotations  # For Python 3.7

import numpy as np

from game import Player, TwoPlayerGameState, TwoPlayerMatch
from heuristic import simple_evaluation_function
from tournament import StudentHeuristic, Tournament
from reversi import (
    Reversi,
    from_array_to_dictionary_board,
    from_dictionary_to_array_board,
)

class Heuristic1(StudentHeuristic):
    def get_name(self) -> str:
        return "JM_IM_Heuristic1"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        # maximizes the coins of a player
        numberCoinsPlayer1 = 0
        numberCoinsPlayer2 = 0

        if state.is_player_max(state.player1):
            numberCoinsPlayer1 = state.game._player_coins(state.board, state.player1.label)
            return numberCoinsPlayer1

        numberCoinsPlayer2 = state.game._player_coins(state.board, state.player2.label)
        return numberCoinsPlayer2

class Heuristic2(StudentHeuristic):

    def get_name(self) -> str:
        return "JM_IM_Heuristic2"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        # returns standard deviation of scores in state
        # MOBILITY: HECHO
        # POTENTIAL-MOBILITY: POR HACER
        # CORNERS: HECHO
        # jugadores actuales
        return self.mobility(state)

    def mobility(self, state: TwoPlayerGameState):
        mobilityPlayer1 = 0
        mobilityPlayer2 = 0
        coinsPlayer1 = 0
        coinsPlayer1 = 0

        # si es el turno de player1 (jugador max)
        if state.is_player_max(state.player1):
               validMoves1 = state.game._get_valid_moves(state.board, state.player1.label)
               coinsPlayer1 = state.game._player_coins(state.board, state.player1.label)
               mobilityPlayer1 = len(validMoves1)
               return mobilityPlayer1 + self.validCorners(validMoves1) + coinsPlayer1

        # si es el turno de player2 (jugador min)
        validMoves2 = state.game._get_valid_moves(state.board, state.player2.label)
        coinsPlayer2 = state.game._player_coins(state.board, state.player2.label)
        mobilityPlayer2 = len(validMoves2) 
        return mobilityPlayer2 + self.validCorners(validMoves2) + coinsPlayer2

    def validCorners(self, validMoves):
        value = 0
        for move in validMoves:
            if move[0] == 1 and move[1] == 1:
                value += 100
            elif move[0] == 1 and move[1] == 8:
                value += 100
            elif move[0] == 8 and move[1] == 1:
                value += 100
            elif move[0] == 8 and move[1] == 8:            
                value += 100       
        return value
         
class Heuristic3(StudentHeuristic):

    def get_name(self) -> str:
        return "JM_IM_Heuristic3"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        # combina movilidad con el numero de fichas
        return self.numberCoinsAndMobility(state)

    def numberCoinsAndMobility(self, state: TwoPlayerGameState):
        numberCoinsPlayer1 = 0
        numberCoinsPlayer2 = 0
        validMovesPlayer1 = 0
        validMovesPlayer2 = 0

        if state.is_player_max(state.player1):
            numberCoinsPlayer1 = state.game._player_coins(state.board, state.player1.label)
            validMovesPlayer1 = len(state.game._get_valid_moves(state.board, state.player1.label))
            return numberCoinsPlayer1 + validMovesPlayer1

        numberCoinsPlayer2 = state.game._player_coins(state.board, state.player2.label)
        validMovesPlayer2 = len(state.game._get_valid_moves(state.board, state.player2.label))
        return numberCoinsPlayer2  + validMovesPlayer2


class Heuristic4(StudentHeuristic):

    def get_name(self) -> str:
        return "simpleEvHeuristic"

    def evaluation_function(self, state: TwoPlayerGameState) -> float:
        return simple_evaluation_function(state)


def create_match(player1: Player, player2: Player) -> TwoPlayerMatch:
    height, width = 8, 8
    initial_player = player1

    initial_board = (
        ['..B.B...',
         '.WBBW...',
         'WBWBB...',
         '.W.WWW..',
         '.BBWBWB.'
         '...BBW..'
         '.BBBW...'
         '....WW..']
    )

    if initial_board is None:
        height, width = 8, 8
    else:
        height = len(initial_board)
        width = len(initial_board[0])
        try:
            initial_board = from_array_to_dictionary_board(initial_board)
        except ValueError:
            raise ValueError('Wrong configuration of the board')

    game = Reversi(
        player1=player1,
        player2=player2,
        height=height,
        width=width,
    )

    game_state = TwoPlayerGameState(
        game=game,
        board=initial_board,
        initial_player=initial_player,
    )

    return TwoPlayerMatch(game_state, max_sec_per_move=1000, gui=False)


tour = Tournament(max_depth=3, init_match=create_match)
strats = {'opt1': [Heuristic1], 'opt2': [Heuristic2], 'opt3': [Heuristic3],
          'opt4': [Heuristic4]}
#strats = tour.load_strategies_from_folder(folder="heuristicas", max_strat=3)          

n = 5
scores, totals, names = tour.run(
    student_strategies=strats,
    increasing_depth=False,
    n_pairs=n,
    allow_selfmatch=False,
)

print(
    'Results for tournament where each game is repeated '
    + '%d=%dx2 times, alternating colors for each player' % (2 * n, n),
)

# print(totals)
# print(scores)

print('\ttotal:', end='')
for name1 in names:
    print('\t%s' % (name1), end='')
print()
for name1 in names:
    print('%s\t%d:' % (name1, totals[name1]), end='')
    for name2 in names:
        if name1 == name2:
            print('\t---', end='')
        else:
            print('\t%d' % (scores[name1][name2]), end='')
    print()
