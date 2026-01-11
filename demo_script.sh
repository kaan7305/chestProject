#!/bin/bash
# Chess Game Demonstration Script
# This script demonstrates various features of the chess game

echo "============================================"
echo "   Chess Game - Interactive Demo"
echo "============================================"
echo ""

echo "1. Displaying initial chess board..."
echo "Q" | ./chess | head -30
echo ""
echo "Press Enter to continue..."
read

echo "2. Playing some opening moves (Italian Game)..."
./chess < test_game_moves.txt | tail -20
echo ""
echo "Press Enter to continue..."
read

echo "3. Loading a CHECK position..."
./chess < test_load_check.txt | tail -15
echo ""
echo "Press Enter to continue..."
read

echo "4. Loading a CHECKMATE position..."
./chess < test_load_checkmate.txt | tail -15
echo ""

echo "============================================"
echo "   Demo Complete!"
echo "============================================"
echo ""
echo "To play interactively, run: ./chess"
echo "To load a saved game, run: ./chess then type 'L filename.txt'"
echo "To make a move, type: M <start><end> (e.g., M E2E4)"
echo ""
