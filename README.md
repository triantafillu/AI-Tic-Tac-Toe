# AI Tic-Tac-Toe Using MENACE

This repository contains a Tic-Tac-Toe game implementation in C, which uses a variant of the MENACE (Machine Educable Noughts And Crosses Engine) algorithm. The game leverages a learning mechanism where it uses "matchboxes" to store and update the game strategies based on outcomes.

## Overview

In this version of Tic-Tac-Toe, the AI learns to play the game using a collection of matchboxes. Each matchbox represents a possible state of the Tic-Tac-Toe board. The matchboxes contain beads of different colors, each representing a possible move from that board state. The game progresses by the AI picking random beads from the appropriate matchbox based on the current state of the game board.

### Game Flow:

1. **Check Current Board State**: The program checks the current configuration of the board.
2. **Matchbox Selection**: It then selects a matchbox corresponding to the current state.
   - If a matchbox for the current state does not exist, it finds the configuration that fits.
3. **Move Selection**: A random bead is selected to determine the AI's move.
4. **Game Outcome Handling**:
   - **Win**: Add 3 beads of the same color to the matchbox.
   - **Draw**: Add 1 bead of the same color to the matchbox.
   - **Loss**:
     - If the matchbox becomes empty after a loss, replenish it with a baseline number of beads for each possible move.
     - If not empty, do not alter the matchbox, as the bead is already moved to "taken."
5. **Result Storage**: At the end of the game, results are saved in a file for future reference and learning enhancement.
