from __future__ import annotations  # For Python 3.7
import time
import numpy as np

from game import (
    TwoPlayerGameState,
)
from tournament import (
    StudentHeuristic,
)

from reversi import (
    Reversi,
    from_array_to_dictionary_board,
    from_dictionary_to_array_board,
)


class Solution1(StudentHeuristic):
    
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


class Solution2(StudentHeuristic):

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
        
class Solution3(StudentHeuristic):

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
