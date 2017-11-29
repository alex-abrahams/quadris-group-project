#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H
class GameSingleton(){
  GameSingleton();
  Board b;
  public:
  static GameSingleton& get(){
    static GameSingleton r;
    return r;
  }

  void init();

  //control interfaces
  void down();
  void up();
  void left();
  void right();
  void clockwise();
  void counterclockwise();
  void drop();
  void levelup();
  void leveldown();
  void norandom(string file);
  void sequence(string file);
  void restart();
  void hint();
  void I();
  void L();
  void J();

}
#endif
