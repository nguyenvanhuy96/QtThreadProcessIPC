#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
      shareMemory("SharedMemoryDemoApp")
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnLoadImage_clicked()
{
    if(shareMemory.isAttached()){
        qDebug() << "Memory is attached, detaching";
        detach();
    }
    ui->lb ->setText(tr("Select an image file"));
    QString fileName = QFileDialog::getOpenFileName(nullptr, QString(), QString(), tr("Image Files (*.png *.jpg *.jpeg *.bmp * .tif)"));
    QImage image;
    if(!image.load(fileName)){
        ui->lb->setText(tr("Selected file is not am image, please select another."));
        return;
    }

    ui->lb->setPixmap(QPixmap::fromImage(image));
    // load into share memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();

    qDebug() << "Size: " << size;
    if(!shareMemory.create(size)){
        ui->lb->setText(tr("Unable to create share memory segment."));
        qDebug() << shareMemory.errorString();
        qDebug() << "Is attached: " << shareMemory.isAttached();
        return;
    }
    shareMemory.lock();

    char *to = (char*)shareMemory.data();
    const char *from = buffer.data().data();

    memcpy(to, from,qMin(shareMemory.size(),size));
    shareMemory.unlock();
}

void Widget::on_btnLoadImageFromMemory_clicked()
{
    if(!shareMemory.attach()){
        ui->lbLoadMemory->setText(tr("Unable to attach to shared memory segment.\n Load in the data first."));
        return ;
    }
    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    shareMemory.lock();
    buffer.setData((char*)shareMemory.constData(),shareMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    shareMemory.unlock();

    shareMemory.detach();
     ui->lbLoadMemory->setPixmap(QPixmap::fromImage(image));
}

void Widget::detach()
{
   if(!shareMemory.detach()){
       ui->lb->setText("Can not detach from the share memory.");
   }
}
