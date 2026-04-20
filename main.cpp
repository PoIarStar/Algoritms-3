#include <vector>
#include <iostream>
class Piece {
private:
  int color = 0;
  int sides[4]{};

public:
  Piece() {};
  Piece(int color, int up, int right, int down, int left) {
    this->color = color;

    sides[0] = up;
    sides[1] = right;
    sides[2] = down;
    sides[3] = left;
  }
  void rotate() {
    int tmp = sides[3];

    for (int i = 3; i > 0; i--) {
      sides[i] = sides[i - 1];
    }

    sides[0] = tmp;
  }

  int getColor() {
    return color;
  }

  int getUp() {
    return sides[0];
  }

  int getRight() {
    return sides[1];
  }

  int getDown() {
    return sides[2];
  }

  int getLeft() {
    return sides[3];
  }
};

class Puzzle {
  int width, height;
  std::vector<std::vector<Piece>> puzzleBoard;
public:
  Puzzle(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < height; i++) {
      puzzleBoard.push_back(std::vector<Piece>());
      for (int j = 0; j < width; j++)
        puzzleBoard[i].push_back(Piece());
    }
  }

  int getHeight() {
    return height;
  }

  int getWidth() {
    return width;
  }

  Piece getPiece(int i, int j) {
    return (i < 0 || i >= height || j < 0 || j >= width) ? Piece() : puzzleBoard[i][j];
  }

  bool canPlace(Piece piece, int i, int j) {
    return piece.getLeft() + getPiece(i, j - 1).getRight() == 0 &&
      piece.getUp() + getPiece(i - 1, j).getDown() == 0;
  }

  void place(Piece piece, int i, int j) {
    puzzleBoard[i][j] = piece;
  }

  void clear(int i, int j) {
    puzzleBoard[i][j] = Piece();
  }
};

bool solve(Puzzle& puzzle, std::vector<Piece> pieces, std::vector<std::vector<int>> colors, int i_start, int j_start) {
  if (i_start == puzzle.getHeight())
    return true;
  if (pieces.empty())
    return false; // не хватает деталек

  for (int i = i_start; i < puzzle.getHeight(); i++)
    for (int j = j_start; j < puzzle.getHeight(); j++)
      for (int k = 0; k < pieces.size(); k++) {

        Piece piece = pieces[k];
        for (int l = 0; l < 4; l++) {
          piece.rotate();
          if (puzzle.canPlace(piece, i, j) && piece.getColor() == colors[i][j]) {
            puzzle.place(piece, i, j);
            pieces.erase(pieces.begin() + k);

            if (solve(puzzle, pieces, colors, (j + 1 < puzzle.getWidth()) ? i : i + 1, (j + 1 < puzzle.getWidth()) ? j + 1 : 0))
              return true;

            pieces.push_back(piece);
            puzzle.clear(i, j);
          }
        }
      }
  return false;
}

void printPuzzle(Puzzle& puzzle) {
  std::cout << "Current Puzzle State:" << std::endl;
  for (int i = 0; i < puzzle.getHeight(); i++) {
    for (int j = 0; j < puzzle.getWidth(); j++) {
      Piece p = puzzle.getPiece(i, j);
      std::cout << "[" << p.getColor() << ":"
        << p.getUp() << "," << p.getRight() << ","
        << p.getDown() << "," << p.getLeft() << "] ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Example 1: Simple 1x1 puzzle
void example1() {
  std::cout << "\n=== Example 1: 1x1 Puzzle ===" << std::endl;
  Puzzle puzzle(1, 1);

  std::vector<Piece> pieces;
  pieces.push_back(Piece(1, 0, 0, 0, 0)); // color 1, all sides 0 (edges)

  std::vector<std::vector<int>> colors = { {1} };

  if (solve(puzzle, pieces, colors, 0, 0)) {
    std::cout << "Solution found!" << std::endl;
    printPuzzle(puzzle);
  }
  else {
    std::cout << "No solution exists!" << std::endl;
  }
}

// Example 2: 2x2 puzzle with matching pieces
void example2() {
  std::cout << "\n=== Example 2: 2x2 Puzzle ===" << std::endl;
  Puzzle puzzle(2, 2);

  std::vector<Piece> pieces;
  // Format: Piece(color, up, right, down, left)
  // Positive numbers = tabs, negative = blanks (sum to 0 for matching)
  pieces.push_back(Piece(1, 0, 1, -1, 0));  // Top-left
  pieces.push_back(Piece(1, 0, 0, 1, -1));  // Top-right
  pieces.push_back(Piece(2, 1, 1, 0, 0));   // Bottom-left
  pieces.push_back(Piece(2, -1, 0, 0, -1)); // Bottom-right

  std::vector<std::vector<int>> colors = {
      {1, 1},
      {2, 2}
  };

  if (solve(puzzle, pieces, colors, 0, 0)) {
    std::cout << "Solution found!" << std::endl;
    printPuzzle(puzzle);
  }
  else {
    std::cout << "No solution exists!" << std::endl;
  }
}

// Example 3: 2x2 puzzle with rotations needed
void example3() {
  std::cout << "\n=== Example 3: 2x2 Puzzle with Rotations ===" << std::endl;
  Puzzle puzzle(2, 2);

  std::vector<Piece> pieces;
  pieces.push_back(Piece(1, 0, 0, 1, 0));  // Will need rotation
  pieces.push_back(Piece(1, 1, 0, 0, 0));  // Will need rotation
  pieces.push_back(Piece(2, 0, 1, 0, 0));  // Will need rotation
  pieces.push_back(Piece(2, 0, 0, 0, 1));  // Will need rotation

  std::vector<std::vector<int>> colors = {
      {1, 1},
      {2, 2}
  };

  if (solve(puzzle, pieces, colors, 0, 0)) {
    std::cout << "Solution found!" << std::endl;
    printPuzzle(puzzle);
  }
  else {
    std::cout << "No solution exists!" << std::endl;
  }
}

// Example 4: 3x3 puzzle
void example4() {
  std::cout << "\n=== Example 4: 3x3 Puzzle ===" << std::endl;
  Puzzle puzzle(3, 3);

  std::vector<Piece> pieces;
  // Creating a simple pattern where all pieces of same color connect
  for (int color = 1; color <= 3; color++) {
    for (int i = 0; i < 3; i++) {
      pieces.push_back(Piece(color, 0, 0, 0, 0));
    }
  }

  std::vector<std::vector<int>> colors = {
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3}
  };

  if (solve(puzzle, pieces, colors, 0, 0)) {
    std::cout << "Solution found!" << std::endl;
    printPuzzle(puzzle);
  }
  else {
    std::cout << "No solution exists!" << std::endl;
  }
}

int main() {
  //example1();
  example2();
  example3();
  example4();

  return 0;
}
