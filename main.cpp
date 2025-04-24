#include "pieces_module.hpp"
#include "ChessBoard.hpp"
#include "Transform.hpp"

int main() {
    auto solutions = ChessBoard::findAllQueenPlacements();
    std::cout << "Total solutions: " << solutions.size() << std::endl;
    return 0;
}