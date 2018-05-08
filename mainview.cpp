#include "mainview.h"
#include "ui_mainview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFile>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    loadPhrases();

    QVBoxLayout* vlmain = new QVBoxLayout(ui->centralWidget);
    QHBoxLayout* hlmain = new QHBoxLayout();
    vlmain->addLayout(hlmain);

    QPushButton* newPhraseBtn = new QPushButton();
    newPhraseBtn->setText("New Phrase");
    connect(newPhraseBtn,
            &QPushButton::clicked,
            this,
            &MainView::onClick
            );

    hlmain->addWidget(newPhraseBtn);


    displayPhrase = new QLabel();
    vlmain->addWidget(displayPhrase);
     displayPhrase->setText(phrases[qrand() % phrases.size()]);

}

MainView::~MainView()
{
    delete ui;
}

void MainView::onClick()
{
    displayPhrase->setText(phrases[qrand() % phrases.size()]);
}

void MainView::loadPhrases()
{
    QFile iFile(":/text/phrases.txt");
    if (!iFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qWarning() << "Error opening file\n";
        exit(EXIT_FAILURE);
    }

    QTextStream in(&iFile);

    QString line = in.readLine();
    while (!in.atEnd())
    {
        phrases.push_back(line);
        line = in.readLine();
    }

    iFile.close();
}


