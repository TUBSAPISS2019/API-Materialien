#ifndef COUNTDOUWN_H
#define COUNTDOUWN_H

#include <QObject>

class Countdouwn : public QObject
{
    Q_OBJECT
public:
    explicit Countdouwn(QObject *parent = nullptr);
private:
    int m_remainingTime;

signals:
    void countdownWasReset();
public slots:
    void timeEllapsed();
    void finished();
};

#endif // COUNTDOUWN_H
