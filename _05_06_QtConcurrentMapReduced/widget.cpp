#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

QStringList Widget::findFiles(const QString &startDir, const QStringList &filters)
{
    QStringList names;
    QDir dir(startDir);

    const auto files = dir.entryList(filters, QDir::Files);
    for (const QString &file:files) {
        names += startDir + '/'+ file;
    }
    const auto subDir = dir.entryList(QDir::AllDirs| QDir::NoDotAndDotDot);
    for(const QString &subDir: subDir){
        names+= findFiles(startDir+'/' + subDir, filters);
    }
    return  names;
}

QMap<QString, int> Widget::singleThreadedWordCount(const QStringList &files)
{
    QMap<QString,int> wordCount;
    for (const QString &file:files) {
        QFile f(file);
        f.open(QIODevice::ReadOnly);
        QTextStream textStream(&f);
        while(!textStream.atEnd()){
            const auto words = textStream.readLine().split(' ');
            for (const QString &word: words) {
                wordCount[word] +=1;
            }
        }
    }
    return  wordCount;
}

QMap<QString, int> Widget::countWords(const QString &file)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QTextStream textStream(&f);
    QMap<QString, int> wordCount;

    while(!textStream.atEnd()){
        const auto words = textStream.readLine().split(' ');
        for (const QString &word: words) {
            wordCount[word] +=1;
        }
    }
    return wordCount;
}

void Widget::reduce(QMap<QString, int> &result, const QMap<QString, int> &w)
{
    QMapIterator<QString,int> i(w);
    while(i.hasNext()){
        i.next();
        result[i.key()] += i.value();
    }
}


void Widget::on_btnChooseDir_clicked()
{
    chooseDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                  "/home", QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks );
    if(!chooseDir.isNull()){
        qDebug() << "Choose Dir: " << chooseDir;
        ui->txtChooseDir->setText(chooseDir);
    }else{
        qDebug() << "Didn't choose any file";
    }
}

void Widget::on_btnFindFiles_clicked()
{
    if(!chooseDir.isNull()){
        ui->lbFindFiles->setText("Finding file...");
        files = findFiles(chooseDir,QStringList() << "*.cpp"<< "*.h");
        int fileCount = files.count();
        ui->lbFindFiles->setText("Found " + QString::number(fileCount) + " files");
    }else{
        ui->lbFindFiles->setText("No valid dir selected");
    }
}

void Widget::on_btnSingleThread_clicked()
{
    if(!files.isEmpty()){
        QTime time;
        time.start();
        QMap<QString, int> wordCount = singleThreadedWordCount(files);
        int timeEllapsed = time.elapsed();
        QString message = "Single threaded \n Word count: " + QString::number(wordCount.keys().count()) +
                " \n Time ellapsed: " + QString::number(timeEllapsed);
        ui->lbSingleThread->setText(message);
    }
}

void Widget::on_btnMapReduced_clicked()
{
  QTime time;
  time.start();

  future= QtConcurrent::mappedReduced(files, countWords, reduce);
  future.waitForFinished();
  int timeEllapsed = time.elapsed();

  QMap<QString,int> total = future.result();

  QString message = "Map reduce \n Word count: " + QString::number(total.keys().count()) +
          " \n Time ellapsed: " + QString::number(timeEllapsed);
  ui->lbMapReduced->setText(message);
}

