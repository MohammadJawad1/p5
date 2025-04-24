#include "Transform.hpp"

/**
 * @brief Rotates a square matrix 90 degrees clockwise.
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the rotated matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::rotate(const std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<T>> result = matrix;

    // Transpose
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(result[i][j], result[j][i]);
        }
    }
    // Reverse each row
    for (int i = 0; i < n; ++i) {
            std::reverse(result[i].begin(), result[i].end());
    }
    
    return result;
}
/**
 * @brief Swaps the elements of a square matrix across its vertical axis of symmetry
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the transformed matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::flipAcrossVertical(const std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<T>> result = matrix;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            std::swap(result[i][j], result[i][n - 1 - j]);
        }
    }

    return result;
}

/**
 * @brief Swaps the elements of a square matrix across its horizontal axis of symmetry
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the transformed matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::flipAcrossHorizontal(const std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<T>> result = matrix;

    for (int i = 0; i < n / 2; ++i) {
        std::swap(result[i], result[n - 1 - i]);
    }

    return result;
}