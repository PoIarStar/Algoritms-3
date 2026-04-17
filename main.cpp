class Piece {
private:
    int sides[4]{};

public:
    Piece() {};
    Piece(int up, int right, int down, int left) {
        sides[0] = up;
        sides[1] = right;
        sides[2] = down;
        sides[3] = left;
    }
    void rotate() {
        int tmp = sides[3];
        for (int i = 1; i < 4; i++) {
            sides[i] = sides[i - 1];
        }
        sides[0] = tmp;
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
    Piece **puzzleBoard;
    public:
    Puzzle(int width, int height) {
        this->width = width;
        this->height = height;
        puzzleBoard = new Piece*[width];
        for (int i = 0; i < width; i++) {
            puzzleBoard[i] = new Piece[height];
        }
    };
    ~Puzzle() {
        for (int i = 0; i < width; i++) {
            delete[] puzzleBoard[i];
        }
        delete[] puzzleBoard;
    }
    void place(int x, int y, Piece piece) {}
};