#ifndef PINSCONTROLLER_H
#define PINSCONTROLLER_H

#include <QObject>
#include <pinsmodel.h>

class PinsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PinsModel *modelDataIn READ modelDataIn  CONSTANT)
    Q_PROPERTY(PinsModel *modelDataOut READ modelDataOut  CONSTANT)
public:
    explicit PinsController(QObject *parent = 0);

    Q_INVOKABLE bool load(const QString & fname);
    Q_INVOKABLE bool save(const QString & fname) const;
    Q_INVOKABLE void initDefault(int size, int sizeOut);

    PinsModel *modelDataIn();
    PinsModel *modelDataOut();

private:
    PinsModel *_pinsDataIn;
    PinsModel *_pinsDataOut;
};

#endif // PINSCONTROLLER_H
