# AI-Tic-Tac-Toe
### Algo

1. Until end of game
   1. Take a box with current board state
   2. If box doesn't exist:
      1. find configuration
   3. Take a random bead

2. If won:
   1. replace + 3 beads to the matchbox
3. If draw:
   1. replace + 1 bead
4. If lost and matchbox is empty:
   1. replace beads

(if lost - don't touch the matchbox because the bead is already moved to "taken")

5. Save results in a file
