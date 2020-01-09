#ifndef MODEL_H
#define MODEL_H

#include <QObject>

extern int flagReceive;
extern double absAngle[10];
extern double incAngle[10];

class Model: public QObject
{
    Q_OBJECT

public:
    Model();


public:
    double Angel[10];
};

#endif // MODEL_H
