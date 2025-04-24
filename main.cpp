#include "pieces_module.hpp"
#include "ChessBoard.hpp"
#include "Transform.hpp"

// Helper function to print matrices
void printMatrix(const std::vector<std::vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char c : row) std::cout << c << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Test function for matrix transforms
void testMatrixTransforms() {
    std::vector<std::vector<char>> matrix = {
        {'A', 'B', 'C'},
        {'D', 'E', 'F'},
        {'G', 'H', 'I'}
    };

    std::cout << "Original:\n";
    printMatrix(matrix);

    auto rotated = Transform::rotate(matrix);
    std::cout << "Rotated 90° clockwise:\n";
    printMatrix(rotated);

    auto flippedH = Transform::flipAcrossHorizontal(matrix);
    std::cout << "Flipped across horizontal:\n";
    printMatrix(flippedH);

    auto flippedV = Transform::flipAcrossVertical(matrix);
    std::cout << "Flipped across vertical:\n";
    printMatrix(flippedV);
}

// Main function
int main() {
    testMatrixTransforms();  // Run matrix tests

    auto solutions = ChessBoard::findAllQueenPlacements();
    std::cout << "Total solutions: " << solutions.size() << std::endl;

    return 0;
}