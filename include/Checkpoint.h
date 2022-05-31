//
// Created by auguste on 31/05/22.
//

#ifndef EDITEUR_RTB_CHECKPOINT_H
#define EDITEUR_RTB_CHECKPOINT_H


class Checkpoint {
private:
    int x, y, id;

public:
    Checkpoint(int x, int y, int id);
    ~Checkpoint();

    int getX();
    int getY();
    int getId();
};


#endif //EDITEUR_RTB_CHECKPOINT_H
