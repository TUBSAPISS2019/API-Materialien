#include "countdouwn.h"

#include <QTimer>
#include <QDebug>

Countdouwn::Countdouwn(QObject *parent) : QObject(parent)
{
    m_remainingTime = 10;

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeEllapsed()));
    connect(this, SIGNAL(countdownWasReset()), this, SLOT(finished()));

    timer->start(1000);
}

void Countdouwn::timeEllapsed()
{
    m_remainingTime--;
    qDebug() << m_remainingTime;

    if(m_remainingTime < 0){
        m_remainingTime = 10;
        emit countdownWasReset();
    }
}

void Countdouwn::finished()
{
    qDebug() << "Timer finished";
}
