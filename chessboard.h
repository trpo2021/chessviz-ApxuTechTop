enum FigureType {
    FigureTypeKing,
    FigureTypeQueen,
    FigureTypeRook,
    FigureTypeKnight,
    FigureTypeBishop,
    FigureTypePawn,
    FigureTypeNone
};
enum FigureSide { FigureSideWhite, FigureSideBlack, FigureSideNone };

typedef struct Field {
    char letter;
    char number;
} Field;

typedef struct Move {
    Field from;
    Field to;
    char who;
    char type;
    char extra;
} Move;

typedef struct Figure {
    enum FigureType type;
    enum FigureSide side;
} Figure;

int createFigure(Figure* figure, char what);

void printFigure(Figure figure);

void createChessboard(Figure chessboard[8][8], char str[65]);

void printChessboard(Figure chessboard[8][8]);