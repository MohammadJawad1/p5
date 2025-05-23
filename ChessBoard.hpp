//Mohammad Jawad
//April 25 2024
//ChessBoard header for project 5 that included the queen helper, the similar groups, and the queen recursive functions.

/**
 * @class ChessBoard
 * @brief Represents an 8x8 board of Chess Pieces used to play chess
 */

#pragma once

#include <vector>
#include "pieces_module.hpp"

class ChessBoard {
    private:
        // Define board size (8x8)
        static const int BOARD_LENGTH = 8;
        
        bool playerOneTurn;
        
        std::string p1_color;
        std::string p2_color;

        std::vector<std::vector<ChessPiece*>> board;

        // Alias for readability
        typedef std::vector<std::vector<char>> CharacterBoard;

        /**
         * @brief A STATIC helper function for recursively solving the 8-queens problem.
         * 
         * This function places queens column by column, checks for valid placements,
         * and stores all valid board configurations in the provided list.
         * 
         * @param col A const reference to aninteger representing the current column being processed.
         * @param board A (non-const) reference to a 2D vector of ChessPiece*, representing the current board configuration
         * @param placedQueens A (non-const) reference to a vector storing Queen*, which represents the queens we've placed so far
         * @param allBoards A (non-const) reference to a vector of CharacterBoard objects storing all the solutions we've found thus far
        */
        static void queenHelper(const int& col, std::vector<std::vector<ChessPiece*>>& board, std::vector<Queen*>& placedQueens, std::vector<CharacterBoard>& allBoards);


    public:
        /**
         * Default constructor. 
         * @post The board is setup with the following restrictions:
         * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
         *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
         *          - Pieces on the BOTTOM half of the board are set to be "moving up" | of color "BLACK"
         *          - Pieces on the UPPER half of the board are set to be NOT "moving up"| of color "WHITE"
         *          - Their row & col members reflect their position on the board
         *          - All other parameters are default initialized.
         *   
         *      - Pawns (P), Rooks(R), Bishops(B), Kings(K), Queens(Q), and Knights(N) are placed in the following format (ie. the standard setup for chess):
         *          
         *          7 | R N B K Q B N R
         *          6 | P P P P P P P P
         *          5 | * * * * * * * *
         *          4 | * * * * * * * *
         *          3 | * * * * * * * *
         *          2 | * * * * * * * *
         *          1 | P P P P P P P P
         *          0 | R N B K Q B N R
         *              +---------------
         *              0 1 2 3 4 5 6 7
         *      
         *          (With * denoting empty cells)
         * 
         * 2) playerOneTurn is set to true.
         * 3) p1_color is set to "BLACK", and p2_color is set to "WHITE"
         */
        ChessBoard();

        /**
         * @brief Constructs a ChessBoard object with a given board configuration and player turn.
         * 
         * @param instance A 2D vector representing a board state, where each element is a pointer to a ChessPiece.
         * @param p1Turn A boolean indicating whether it's player one's turn. True for player one, false for player two.
         * 
         * @post Initializes the board layout, sets player one's color to "BLACK" and player two's color to "WHITE".
         */
        ChessBoard(const std::vector<std::vector<ChessPiece*>>& board, const bool& p1Turn);

        /**
         * @brief Gets the ChessPiece (if any) at (row, col) on the board
         * 
         * @param row The row of the cell
         * @param col The column of the cell
         * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
         */
        ChessPiece* getCell(const int& row, const int& col) const;

        /**
         * @brief Destructor. 
         * @post Deallocates all ChessPiece pointers stored on the board at time of deletion. 
         */
        ~ChessBoard();

        /**
         * @brief Finds all possible solutions to the 8-queens problem.
         * 
         * @return A vector of CharacterBoard objects, 
         *         each representing a unique solution 
         *         to the 8-queens problem.
        */
        static std::vector<CharacterBoard> findAllQueenPlacements();

        /**
         * @brief Groups similar chessboard configurations by transformations.
         * 
         * This function organizes a list of chessboard configurations into groups of similar boards, 
         * where similarity is defined as being identical under a 
         *      1) Rotation (clockwise: 0°, 90°, 180°, 270°)
         *      2) Followed by a flip across the horizontal or vertical axis
         * 
         * @param boards A const reference to a vector of CharacterBoard objects, each representing a chessboard configuration.
         * 
         * @return A 2D vector of CharacterBoard objects, 
         *         where each inner vector is a list of boards 
         *         that are transformations of each other.
         */
        static std::vector<std::vector<CharacterBoard>> groupSimilarBoards(const std::vector<CharacterBoard>& boards);



};