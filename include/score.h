#ifndef _SCORE_H_
#define _SCORE_H_

class Score {
 public:
  int playerScore;
  int aiScore;
  Score();
  void goal(int player);
  void reset();
};

#endif /* _SCORE_H_ */