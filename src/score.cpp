#include "score.h"

/**
 * Constructor
 */
Score::Score() : playerScore(0), aiScore(0) {}

/**
 * Add player's score or AI's score by 1.
 * player = 1 if player goals, 0 if AI goals.
 */
void Score::goal(int player) {
  if (player)
    ++playerScore;
  else
    ++aiScore;
}

/**
 * Reset score
 */
void Score::reset() {
  playerScore = 0;
  aiScore = 0;
}