#include "ChessBoard.hpp"
#include "Transform.hpp"
/**
    * Default constructor. 
    * @post The board is setup with the following restrictions:
    * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
    *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
    *          - Pieces on the BOTTOM half of the board are set to have color "BLACK"
    *          - Pieces on the UPPER half of the board are set to have color "WHITE"
    *          - Their row & col members reflect their position on the board
    *          - All pawns on the BOTTOM half are flagged to be moving up.
    *          - All pawns on the BOTTOM half are flagged to be NOT moving up.
    *          - All other parameters are default initialized (this includes moving_up for non-Pawns!)
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
ChessBoard::ChessBoard() 
    : playerOneTurn{true}, p1_color{"BLACK"}, p2_color{"WHITE"}, board{std::vector(8, std::vector<ChessPiece*>(8)) } {
        // Allocate pieces

        auto add_mirrored = [this] (const int& i, const std::string& type) {
            if (type == "PAWN") {
                board[1][i] = new Pawn(p1_color, 1, i, true);
                board[6][i] = new Pawn(p2_color, 6, i);
            } else if (type == "ROOK") {
                board[0][i] = new Rook(p1_color, 0, i);
                board[7][i] = new Rook(p2_color, 7, i);
            } else if (type == "KNIGHT") {
                board[0][i] = new Knight(p1_color, 0, i);
                board[7][i] = new Knight(p2_color, 7, i);            
            } else if (type == "BISHOP") {
                board[0][i] = new Bishop(p1_color, 0, i);
                board[7][i] = new Bishop(p2_color, 7, i);
            } else if (type == "KING") {
                board[0][i] = new King(p1_color, 0, i);
                board[7][i] = new King(p2_color, 7, i);
            } else if (type == "QUEEN") {
                board[0][i] = new Queen(p1_color, 0, i);
                board[7][i] = new Queen(p2_color, 7, i);
            }
        };

        std::vector<std::string> inner_pieces = {"ROOK", "KNIGHT", "BISHOP", "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK"};
        for (size_t i = 0; i < BOARD_LENGTH; i++) {
            add_mirrored(i, "PAWN");
            add_mirrored(i, inner_pieces[i]);
        }
    }

/**
 * @brief Constructs a ChessBoard object with a given board configuration and player turn.
 * 
 * @param instance A 2D vector representing a board state, where each element is a pointer to a ChessPiece.
 * @param p1Turn A boolean indicating whether it's player one's turn. True for player one, false for player two.
 * 
 * @post Initializes the board layout, sets player one's color to "BLACK" and player two's color to "WHITE".
 */
ChessBoard::ChessBoard(const std::vector<std::vector<ChessPiece*>>& instance, const bool& p1Turn)
 : playerOneTurn{p1Turn}, p1_color{"BLACK"}, p2_color{"WHITE"}, board{instance}{}

/**
 * @brief Gets the ChessPiece (if any) at (row, col) on the board
 * 
 * @param row The row of the cell
 * @param col The column of the cell
 * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
 */
ChessPiece* ChessBoard::getCell(const int& row, const int& col) const {
    return board[row][col];
}

/**
 * @brief Destructor. 
 * @post Deallocates all ChessPiece pointers stored on the board at time of deletion. 
 */
ChessBoard::~ChessBoard() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (!board[i][j]) { continue; }
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
}

/**
 * @brief Finds all possible solutions to the 8-queens problem.
 * 
 * @return A vector of CharacterBoard objects, 
 *         each representing a unique solution 
 *         to the 8-queens problem.
 */
std::vector<ChessBoard::CharacterBoard> ChessBoard::findAllQueenPlacements() {
    std::vector<CharacterBoard> allSolutions;
    std::vector<std::vector<ChessPiece*>> board(8, std::vector<ChessPiece*>(8, nullptr));
    std::vector<Queen*> queens;

    queenHelper(0, board, queens, allSolutions);

    return allSolutions; 

}

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
void ChessBoard::queenHelper(const int& col, std::vector<std::vector<ChessPiece*>>& board, std::vector<Queen*>& placedQueens, std::vector<ChessBoard::CharacterBoard>& allBoards)
{
    if (col == 8) {
        ChessBoard::CharacterBoard solution(8, std::vector<char>(8, '*'));
        for (ChessPiece* q : placedQueens) {
            solution[q->getRow()][q->getColumn()] = 'Q';
        }
        allBoards.push_back(solution);
        return;
    }

    for (int row = 0; row < 8; ++row) {
        bool isSafe = true;

        for (ChessPiece* q : placedQueens) {
            if (q->canMove(row, col, board)) {
                isSafe = false;
                break;
            }
        }

        if (isSafe) {
            Queen* newQueen = new Queen("BLACK", row, col);
            board[row][col] = newQueen;
            placedQueens.push_back(newQueen);

            queenHelper(col + 1, board, placedQueens, allBoards);

            placedQueens.pop_back();
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }

}
/**
 * @brief Groups similar chessboard configurations by transformations.
 * 
 * This function organizes a list of chessboard configurations into groups of similar boards, 
 * where similarity is defined as being identical under a 
 *      1) Rotation (clockwise: 0°, 90°, 180°, 270°)
 *      2) Followed by a flip across the horizontal or vertical axis
 * 
 * @param boards A const ref. to a vector of `CharacterBoard` objects, each representing a chessboard configuration.
 * 
 * @return A 2D vector of `CharacterBoard` objects, 
 *         where each inner vector is a list of boards 
 *         that are transformations of each other.
 */
std::vector<std::vector<ChessBoard::CharacterBoard>> ChessBoard::groupSimilarBoards(const std::vector<CharacterBoard>& boards) {
    std::vector<std::vector<CharacterBoard>> result;

    for (auto board : boards) {
        bool isSimilar = false;

        for (auto& group : result) {
            CharacterBoard transformed = group[0];

            for (int i = 0; i < 4; i++) {
                if (board == transformed || board == Transform::flipAcrossVertical(transformed) || board == Transform::flipAcrossHorizontal(transformed)) {    
                    group.push_back(board);
                    isSimilar = true;
                    break;
                }

                // Rotate 90° clockwise for next comparison
                transformed = Transform::rotate(transformed);
            }

            if (isSimilar) break;
        }

        // If no similar board found, create a new group
        if (!isSimilar) {
            result.push_back({ board });
        }
    }

    return result;
}
