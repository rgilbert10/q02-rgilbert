/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, outofBoundsDrop) {
	Piezas b;
	Piece p = b.dropPiece(4);
	ASSERT_EQ(Invalid, p);
}

TEST(PiezasTest, outofBoundsPieceAtColumn) {
	Piezas b;
	Piece p = b.pieceAt(1,4);
	ASSERT_EQ(Invalid, p);
}

TEST(PiezasTest, outofBoundsPieceAtRow) {
	Piezas b;
	Piece p = b.pieceAt(3,2);
	ASSERT_EQ(Invalid, p);
}

TEST(PiezasTest, pieceAtReturnBlank) {
	Piezas b;
	Piece p = b.pieceAt(0,0);
	ASSERT_EQ(Blank, p);
}

TEST(PiezasTest, dropPieceSingle) {
	Piezas b;
	b.dropPiece(0);
	Piece p= b.pieceAt(0,0);
	ASSERT_EQ(X, p);
}

TEST(PiezasTest, dropPieceReturnTest) {
	Piezas b;
	b.dropPiece(0);
	Piece p= b.pieceAt(0,0);
	ASSERT_EQ(X, p);
}


TEST(PiezasTest, dropPieceOnTopOfEachOther) {
	Piezas b;
	b.dropPiece(0);
	b.dropPiece(0);
	Piece p= b.pieceAt(1,0);
	ASSERT_EQ(O, p);
}

TEST(PiezasTest, gameStateNoFullBoard) {
	Piezas b;
	b.dropPiece(0);
	b.dropPiece(0);
	Piece p = b.gameState();
	ASSERT_EQ(Invalid, p);
}

TEST(PiezasTest, gameStateHorizontalWinner) {
	Piezas b;
	b.dropPiece(0); //X
	b.dropPiece(0); //O
	b.dropPiece(1); //X
	b.dropPiece(1); //O
	b.dropPiece(2); //X
	b.dropPiece(2); //O	
	b.dropPiece(3); //X
	b.dropPiece(1); //O
	b.dropPiece(0); //X
	b.dropPiece(2); //O
	b.dropPiece(3); //X
	b.dropPiece(3); //O
	
	Piece p = b.gameState();
	ASSERT_EQ(X, p);
}

TEST(PiezasTest, gameStateVerticalWinnerX) {
	Piezas b;
	b.dropPiece(0); //X
	b.dropPiece(1); //O
	b.dropPiece(0); //X
	b.dropPiece(1); //O
	b.dropPiece(0); //X
	b.dropPiece(2); //O	
	b.dropPiece(1); //X
	b.dropPiece(2); //O
	b.dropPiece(2); //X
	b.dropPiece(3); //O
	b.dropPiece(3); //X
	b.dropPiece(3); //O
	
	Piece p = b.gameState();
	ASSERT_EQ(X, p);
}

TEST(PiezasTest, gameStateVerticalWinnerO) {
	Piezas b;
	b.dropPiece(1); //X
	b.dropPiece(0); //O
	b.dropPiece(2); //X
	b.dropPiece(0); //O
	b.dropPiece(2); //X
	b.dropPiece(0); //O	
	b.dropPiece(1); //X
	b.dropPiece(1); //O
	b.dropPiece(3); //X
	b.dropPiece(3); //O
	b.dropPiece(3); //X
	b.dropPiece(2); //O
	
	Piece p = b.gameState();
	ASSERT_EQ(O, p);
}

TEST(PiezasTest, gameStateDualWinnersStalemate) {
	Piezas b;
	b.dropPiece(0); //X
	b.dropPiece(1); //O
	b.dropPiece(0); //X
	b.dropPiece(1); //O
	b.dropPiece(0); //X
	b.dropPiece(1); //O	
	b.dropPiece(2); //X
	b.dropPiece(2); //O
	b.dropPiece(2); //X
	b.dropPiece(3); //O
	b.dropPiece(3); //X
	b.dropPiece(3); //O
	
	Piece p = b.gameState();
	ASSERT_EQ(Blank, p);
}