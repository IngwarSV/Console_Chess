#include "pch.h"

#include "../Console_Chess/Game.h"
#include "../Console_Chess/Figure.h"
#include "../Console_Chess/Units.h"



class GameTest : public ::testing::Test {
protected:
    GameTest() {
        // You can do set-up work for each test here.
    }

    ~GameTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
    Game game;
};


TEST_F(GameTest, TestInitialSetup) {
    //figures in initial position
    EXPECT_EQ(game.getBoard(BR_INIT_POS1)->getFigureName(), L"BR") << L"black rook1 in initial position";
    EXPECT_EQ(game.getBoard(BN_INIT_POS1)->getFigureName(), L"BN") << L"black knight1 in initial position";
    EXPECT_EQ(game.getBoard(BB_INIT_POS1)->getFigureName(), L"BB") << L"black bishop1 in initial position";
    EXPECT_EQ(game.getBoard(BQ_INIT_POS)->getFigureName(), L"BQ") << L"black queen in initial position";
    EXPECT_EQ(game.getBoard(BK_INIT_POS)->getFigureName(), L"BK") << L"black king in initial position";
    EXPECT_EQ(game.getBoard(BB_INIT_POS2)->getFigureName(), L"BB") << L"black bishop2 in initial position";
    EXPECT_EQ(game.getBoard(BN_INIT_POS2)->getFigureName(), L"BN") << L"black knight2 in initial position";
    EXPECT_EQ(game.getBoard(BR_INIT_POS2)->getFigureName(), L"BR") << L"black rook2 in initial position";

    EXPECT_EQ(game.getBoard(WR_INIT_POS1)->getFigureName(), L"WR") << L"white rook1 in initial position";
    EXPECT_EQ(game.getBoard(WN_INIT_POS1)->getFigureName(), L"WN") << L"white knight1 in initial position";
    EXPECT_EQ(game.getBoard(WB_INIT_POS1)->getFigureName(), L"WB") << L"white bishop1 in initial position";
    EXPECT_EQ(game.getBoard(WQ_INIT_POS)->getFigureName(), L"WQ") << L"white queen in initial position";
    EXPECT_EQ(game.getBoard(WK_INIT_POS)->getFigureName(), L"WK") << L"white king in initial position";
    EXPECT_EQ(game.getBoard(WB_INIT_POS2)->getFigureName(), L"WB") << L"white bishop2 in initial position";
    EXPECT_EQ(game.getBoard(WN_INIT_POS2)->getFigureName(), L"WN") << L"white knight2 in initial position";
    EXPECT_EQ(game.getBoard(WR_INIT_POS2)->getFigureName(), L"WR") << L"white rook2 in initial position";

    //pawns in initial position
    for (int y = 0; y < BOARD_SIZE - 1; ++y) {
        EXPECT_EQ(game.getBoard(Point{ 1, y })->getFigureName(), L"BP") << L"black pawns in initial position";
        EXPECT_EQ(game.getBoard(Point{ 6, y })->getFigureName(), L"WP") << L"white pawns in initial position";
    }

    // nullptrs from x = 2 to 5
    for (int x = 2; x < BOARD_SIZE - 2; ++x) {
        for (int y = 0; y < BOARD_SIZE - 1; ++y) {
            EXPECT_EQ(game.getBoard(Point{ x, y }), nullptr) << L"nullptrs from x = 2 to 5";
        }
    }

    EXPECT_EQ(game.getWhiteArmy()->size(), 16);
    EXPECT_EQ(game.getBlackArmy()->size(), 16);

    EXPECT_EQ(game.getCurrentArmy(), game.getWhiteArmy());
    EXPECT_EQ(game.getEnemyArmy(), game.getBlackArmy());

    EXPECT_EQ(game.getBArmyBit().to_ulong(), 127UL);
    EXPECT_EQ(game.getWArmyBit().count(), BOARD_SIZE - 1);

    EXPECT_EQ(game.getEnPassantFigure(), nullptr);
    Point point{ BOARD_SIZE, BOARD_SIZE };
    EXPECT_EQ(game.getFirstEnPassantPoint(), point);

    EXPECT_EQ(game.getHalfTurn(), 0);
    EXPECT_EQ(game.getCHECKStatus(), false);
    EXPECT_EQ(game.getGameOverStatus(), false);
    EXPECT_EQ(game.getMoveCompletedStatus(), false);

    EXPECT_EQ(game.getCurrentCommand(), L"\n");
    EXPECT_EQ(game.getLogMessage(), NewGameString);
}

TEST_F(GameTest, TestIsCheck) {
    // WK is in check under attack by BQ
    game.loadGameDataString(L"1 8 8 8 8 WKA80 BQA50 BKC40");
    EXPECT_EQ(game.isCheck(), true);

    // WK is not in check
    game.loadGameDataString(L"1 8 8 8 8 WKB80 BQA50 BKC40");
    EXPECT_EQ(game.isCheck(), false);
}

TEST_F(GameTest, isCheckmate) {
    // Black king is checkmated with a rook
    game.loadGameDataString(L"0 8 8 8 8 WKF5 WRH1 BKH5");
    EXPECT_EQ(game.isCheckmate(), true);

    // Black king is not checkmated with a rook, black knight can cover black king
    game.loadGameDataString(L"0 8 8 8 8 WKF5 WRH1 BNG2 BKH5");
    EXPECT_EQ(game.isCheckmate(), false);

    // Black king is checkmated with a bishop and a knight
    game.loadGameDataString(L"0 8 8 8 8 WKG6 WBF6 WNH6 BKH8");
    EXPECT_EQ(game.isCheckmate(), true);

    // Black king is not checkmated with a bishop and a knight, black rook can attack white bishop
    game.loadGameDataString(L"0 8 8 8 8 WKG6 WBF6 WNH6 BRA6 BKH8");
    EXPECT_EQ(game.isCheckmate(), false);

    // checking if enPassant can be performed to protect the king
    //// Black pawn, which has just advanced for two squares, checkmates the white king
    game.loadGameDataString(L"1 3 1 2 1 WKA4 BNC6 BRH3 BKE8 BPB5 BQB8");
    EXPECT_EQ(game.isCheckmate(), true);

    //// Black pawn, which has just advanced for two squares, can be captured en passant by white pawn
    game.loadGameDataString(L"1 3 1 2 1 WKA4 WPC5 BNC6 BRH3 BKE8 BPB5 BQB8");
    EXPECT_EQ(game.isCheckmate(), false);
}

TEST_F(GameTest, isDraw) {
    // checking stalemate
    ////Black are in stalemate
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WQG6 WPB2 WPC3 BPB3 BKH8");
    EXPECT_EQ(game.isDraw(), true);

    ////Black are not in stalemate, because of en passant move
    game.loadGameDataString(L"0 5 2 6 2 WKF7 WQG6 WPB2 WPC3 BPB3 BKH8");
    EXPECT_EQ(game.isDraw(), false);
    

    // checking impossibility of checkmate
    //// two kings left
    game.loadGameDataString(L"0 8 8 8 8 WKF7 BKH8");
    EXPECT_EQ(game.isDraw(), true);

    //// two kings and one white pawn left
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WPB5 BKH8");
    EXPECT_EQ(game.isDraw(), false);

    //// two kings and one black pawn left
    game.loadGameDataString(L"0 8 8 8 8 WKF7 BPB5 BKH8");
    EXPECT_EQ(game.isDraw(), false);

    //// king with/without bishop versus king and bishop(bishops) on the same color
    //// king versus king and bishop
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WBB5 BKH8");
    EXPECT_EQ(game.isDraw(), true);

    //// king versus king and bishops on the same color
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WBB5 WBC6 BKH8");
    EXPECT_EQ(game.isDraw(), true);

    //// king with bishop versus king and bishops on the same color
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WBB5 WBC6 BKH8 BBD5");
    EXPECT_EQ(game.isDraw(), true);

    //// king with bishop versus king and bishops on the different colors
    game.loadGameDataString(L"0 8 8 8 8 WKF7 WBB5 WBC6 BKH8 BBD4");
    EXPECT_EQ(game.isDraw(), false);

    //// king and knight versus king
    game.loadGameDataString(L"0 8 8 8 8 WKF7 BKH8 BND5");
    EXPECT_EQ(game.isDraw(), true);

   
}












   

