#ifndef _SCORE_H_
#define _SCORE_H_

class Score {
 public:
  /* members */
  int playerScore;
  int aiScore;

  /* constructor */
  Score();

  /* someone scores */
  void goal(int player);

  /* reset scores */
  void reset();
};

#endif /* _SCORE_H_ */