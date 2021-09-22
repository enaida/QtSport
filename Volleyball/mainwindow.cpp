#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    team1Color = new QColor("white");
    team2Color = new QColor("black");
    db = Database::getInstance();
    QGraphicsScene *team1ShirtScene = new QGraphicsScene(0,0,120,120);
    ui->team1shirt->setScene(team1ShirtScene);
    QGraphicsScene *team2ShirtScene = new QGraphicsScene(0,0,120,120);
    ui->team2shirt->setScene(team2ShirtScene);
    initialState = saveState(1);
    initialGeometry = saveGeometry();
    initialDate = ui->gameDate->date();
}

void MainWindow::resetToInitialState()
{
    restoreState(initialState, 1);
    restoreGeometry(initialGeometry);
    ui->team1->setCurrentIndex(0);
    ui->team2->setCurrentIndex(0);
    ui->gameDate->setDate(initialDate);
    disconnect(game,SIGNAL(resetMainWindow()), this, SLOT(resetToInitialState()));
    ui->numberOfPlayersTeam1Label->setText("0");
    ui->numberOfPlayersTeam2Label->setText("0");
    team1Players.empty();
    team2Players.empty();
}

void MainWindow::setBackground(QString path)
{
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
}

void MainWindow::setPlayersCombo()
{
    team1 = db->getPlayersData("1");
    team2 = db->getPlayersData("2");
    for(int i = 0; i < team1.size(); i=i+3)
    {
        ui->team1->addItem(team1[i]);
    }
    for(int i = 0; i < team2.size(); i=i+3)
    {
        ui->team2->addItem(team2[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_team1_currentIndexChanged(int index)
{
    QPixmap team1ShirtPixmap(":/images/tshirt1.png");
    QPalette team1ShirtPalette;
    QGraphicsTextItem* team1PlayerName = new QGraphicsTextItem;
    QGraphicsTextItem* team1PlayerNumber = new QGraphicsTextItem;
    team1PlayerNumber->setPos(56,50);
    team1PlayerNumber->setPlainText(team1[index*3 + 2]);
    team1PlayerNumber->setDefaultTextColor(*team1Color);
    team1PlayerName->setPos(40,22);
    team1PlayerName->setPlainText(team1[index*3]);
    team1PlayerName->setDefaultTextColor(*team1Color);
    team1ShirtPalette.setBrush(QPalette::Background, team1ShirtPixmap);
    ui->team1shirt->setPalette(team1ShirtPalette);
    ui->team1shirt->scene()->setPalette(team1ShirtPalette);
    QGraphicsPixmapItem* team1ShirtGraphItem = ui->team1shirt->scene()->addPixmap(team1ShirtPixmap);
    team1ShirtGraphItem->setPos(0,0);
    ui->team1shirt->scene()->addItem(team1PlayerName);
    ui->team1shirt->scene()->addItem(team1PlayerNumber);
}

void MainWindow::on_team2_currentIndexChanged(int index)
{
    QPixmap team2ShirtPixmap(":/images/tshirt2.png");
    QPalette team2ShirtPalette;
    QGraphicsTextItem* team2PlayerName = new QGraphicsTextItem;
    QGraphicsTextItem* team2PlayerNumber = new QGraphicsTextItem;
    team2PlayerNumber->setPos(56,50);
    team2PlayerNumber->setPlainText(team2[index*3 + 2]);
    team2PlayerNumber->setDefaultTextColor(*team2Color);
    team2PlayerName->setPos(40,22);
    team2PlayerName->setPlainText(team2[index*3]);
    team2PlayerName->setDefaultTextColor(*team2Color);
    team2ShirtPalette.setBrush(QPalette::Background, team2ShirtPixmap);
    ui->team2shirt->setPalette(team2ShirtPalette);
    ui->team2shirt->scene()->setPalette(team2ShirtPalette);
    QGraphicsPixmapItem* team2ShirtGraphItem = ui->team2shirt->scene()->addPixmap(team2ShirtPixmap);
    team2ShirtGraphItem->setPos(0,0);
    ui->team2shirt->scene()->addItem(team2PlayerName);
    ui->team2shirt->scene()->addItem(team2PlayerNumber);
}

void MainWindow::on_player1PerfButton_clicked()
{
    int index = ui->team1->currentIndex();
    QString player = team1[index*3 + 1];
    QString performance = ui->player1Performance->toPlainText();
    db->setPlayerPerformance(player, performance);
    ui->player1Performance->setPlainText("");
}

void MainWindow::on_player2PerfButton_clicked()
{
    int index = ui->team2->currentIndex();
    QString player = team2[index*3 + 1];
    QString performance = ui->player2Performance->toPlainText();
    db->setPlayerPerformance(player, performance);
    ui->player2Performance->setPlainText("");
}

void MainWindow::on_player1ResButton_clicked()
{
    int index = ui->team1->currentIndex();
    QString player = team1[index*3 + 1];
    QString results = ui->player1Results->toPlainText();
    db->setPlayerResults(player, results);
    ui->player1Results->setPlainText("");
}

void MainWindow::on_player2ResButton_clicked()
{
    int index = ui->team2->currentIndex();
    QString player = team2[index*3 + 1];
    QString results = ui->player2Results->toPlainText();
    db->setPlayerResults(player, results);
    ui->player2Results->setPlainText("");
}

void MainWindow::on_gameStartButton_clicked()
{
    if(team1Players.size() == 6 && team2Players.size() == 6)
    {
        QString date = ui->gameDate->text();
        db->addGame("1", "2", date);
        game = new Game(this);
        connect(game,SIGNAL(resetMainWindow()), this, SLOT(resetToInitialState()));
        game->addTeamsPlayers(team1Players, team2Players);
        game->startGame();
        game->setModal(true);
        game->show();
    }
}

void MainWindow::on_addTeam1PlayerButton_clicked()
{
    if(team1Players.size() == 6)
        team1Players.pop();
    team1Players.push_back(team1[ui->team1->currentIndex() * 3 + 1]);
    ui->numberOfPlayersTeam1Label->setText(QString::number(team1Players.size()));
}

void MainWindow::on_addTeam2PlayerButton_clicked()
{
    if(team2Players.size() == 6)
        team2Players.pop();
    team2Players.push_back(team2[ui->team2->currentIndex() * 3 + 1]);
    ui->numberOfPlayersTeam2Label->setText(QString::number(team2Players.size()));
}
