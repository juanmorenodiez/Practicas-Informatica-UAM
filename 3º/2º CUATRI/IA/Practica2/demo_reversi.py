"""Illustration of a Reversi match.

Authors:
    Fabiano Baroni <fabiano.baroni@uam.es>,
    Alejandro Bellogin <alejandro.bellogin@uam.es>
    Alberto Suárez <alberto.suarez@uam.es>

"""

from __future__ import annotations  # For Python 3.7

from game import Player, TwoPlayerGameState, TwoPlayerMatch
from heuristic import heuristic
from reversi import (
    Reversi,
    from_array_to_dictionary_board,
    from_dictionary_to_array_board,
)
from strategy import (
    ManualStrategy,
    MinimaxAlphaBetaStrategy,
    MinimaxStrategy,
    RandomStrategy,
)

player_manual = Player(
    name='Manual',
    strategy=ManualStrategy(verbose=0),
)

player_manual2 = Player(
    name='Manual_2',
    strategy=ManualStrategy(verbose=1),
)

player_random = Player(
    name='Random',
    strategy=RandomStrategy(verbose=0),
    delay=1,
)
player_random2 = Player(
    name='Random_2',
    strategy=RandomStrategy(verbose=1),
    delay=2,
)

player_minimax3 = Player(
    name='Minimax_3',
    strategy=MinimaxStrategy(
        heuristic=heuristic,
        max_depth_minimax=3,
        verbose=1,
    ),
)

player_minimax4 = Player(
    name='Minimax_4',
    strategy=MinimaxStrategy(
        heuristic=heuristic,
        max_depth_minimax=4,
        verbose=0,
    ),
)


# Manual vs manual player
# player_a, player_b = player_manual, player_manual2

# Manual vs minimax player
# player_a, player_b = player_manual, player_minimax4


# minimax vs minimax player
player_a, player_b = player_minimax3, player_minimax4


"""
Here you can initialize the player that moves first
and the board to any valid state.
E.g., it can be an intermediate state.
"""
initial_player = player_a  # Player who moves first.

# Board at an intermediate state of the game.
initial_board = (
    ['..B.B..',
     '.WBBW..',
     'WBWBB..',
     '.W.WWW.',
     '.BBWBWB']
)

# NOTE Uncoment to use standard initial board.
# initial_board = None  # Standard initial board.

if initial_board is None:
    height, width = 8, 8
else:
    height = len(initial_board)
    width = len(initial_board[0])
    try:
        initial_board = from_array_to_dictionary_board(initial_board)
    except ValueError:
        raise ValueError('Wrong configuration of the board')
    else:
        print("Successfully initialised board from array")


# Initialize a reversi game.
game = Reversi(
    player1=player_a,
    player2=player_b,
    height=height,
    width=width,
)

# Initialize a game state.
game_state = TwoPlayerGameState(
    game=game,
    board=initial_board,
    initial_player=initial_player,
)

# Initialize a match.
match = TwoPlayerMatch(
    game_state,
    max_sec_per_move=1000,
    gui=True,
)

# Play match
scores = match.play_match()
input('Press any key to finish.')
