#include "producer.h"

Producer::Producer(QWidget *parent) : QPushButton(parent)
{
   connect(this, &Producer::clicked, this, &Producer::sendData);
   m_integer =10;
   setText("Producer");
}
void Producer::sendData(){
  qDebug() << " Producer producing data, thread: " << QThread::currentThread();
  CustomData cd(10,&m_integer, "Proced data");
  emit data(cd);
}
