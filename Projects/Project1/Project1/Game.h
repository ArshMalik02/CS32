//
//  Game.hpp
//  Project1
//
//  Created by Arsh Malik on 1/6/22.
//

#ifndef Game_h
#define Game_h

class Mesa;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

#endif /* Game_h */
