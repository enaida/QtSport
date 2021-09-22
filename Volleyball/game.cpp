#include "game.h"
#include "ui_game.h"
#include "mainwindow.h"
#include <QGraphicsRectItem>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    QGraphicsScene *gameScene = new QGraphicsScene(0,0,1098,498);
    db = Database::getInstance();
    this->gameDate = db->getLastGame();
    ui->gameView->setScene(gameScene);
    ui->gameView->scene()->setBackgroundBrush(QBrush(Qt::green, Qt::SolidPattern));
}

Game::~Game()
{
    delete ui;
}

void Game::startGame()
{
    drawField();
    drawPlayersTeam2();
    drawPlayersTeam1();
    drawDate();
}

void Game::addTeamsPlayers(QStack<QString> team1Players, QStack<QString> team2Players)
{
    this->team1 = db->getPlayersData(team1Players, "1");
    this->team2 = db->getPlayersData(team2Players, "2");
}

void Game::drawField()
{
    QGraphicsRectItem* innerRect = new QGraphicsRectItem(100,50,900,375);
    QGraphicsRectItem* outerRect = new QGraphicsRectItem(90,40,920,395);
    QGraphicsLineItem* fieldLine1 = new QGraphicsLineItem(400,50,400,425);
    QGraphicsLineItem* fieldLine2 = new QGraphicsLineItem(550,50,550,425);
    QGraphicsLineItem* fieldLine3 = new QGraphicsLineItem(700,50,700,425);
    innerRect->setBrush(QBrush(QColor(204,102,0)));
    outerRect->setBrush(QBrush(Qt::white));
    fieldLine1->setPen(QPen(Qt::white,4));
    fieldLine2->setPen(QPen(Qt::white,4));
    fieldLine3->setPen(QPen(Qt::white,4));
    ui->gameView->scene()->addItem(outerRect);
    ui->gameView->scene()->addItem(innerRect);
    ui->gameView->scene()->addItem(fieldLine1);
    ui->gameView->scene()->addItem(fieldLine2);
    ui->gameView->scene()->addItem(fieldLine3);
}

void Game::drawDate()
{
    QString date = "The Game Date is : ";
    date.append(db->getLastGame());
    QGraphicsTextItem* dateText = new QGraphicsTextItem;
    dateText->setPlainText(date);
    dateText->setPos(450, 10);
    dateText->setDefaultTextColor(Qt::black);
    //dateText->setTextWidth(5);
    ui->gameView->scene()->addItem(dateText);
}

void Game::drawPlayersTeam2()
{
    drawPlayerTeam2(0, 0, 0);
    drawPlayerTeam2(3, 0, 130);
    drawPlayerTeam2(6, 0, 260);
    drawPlayerTeam2(9, 190, 0);
    drawPlayerTeam2(12, 190, 130);
    drawPlayerTeam2(15, 190, 260);
}

void Game::drawPlayerTeam2(int index, int posX, int posY)
{
    QPixmap team2ShirtPixmap(":/images/tshirt2.png");
    QPixmap team2PerformancePixmap(":/images/power.jpg");
    QPixmap team2ResultsPixmap(":/images/results.jpg");
    QGraphicsTextItem* team2PlayerName = new QGraphicsTextItem;
    QGraphicsTextItem* team2PlayerNumber = new QGraphicsTextItem;
    team2PlayerNumber->setPos(TEAM_NUMBER_POS_X + posX, TEAM_NUMBER_POS_Y + posY);
    team2PlayerNumber->setPlainText(team2[index + 2]);
    team2PlayerNumber->setDefaultTextColor(Qt::black);
    team2PlayerName->setPos(TEAM_NAME_POS_X + posX, TEAM_NAME_POS_Y + posY);
    team2PlayerName->setPlainText(team2[index]);
    team2PlayerName->setDefaultTextColor(Qt::black);
    QGraphicsPixmapItem* team2ShirtGraphItem = ui->gameView->scene()->addPixmap(team2ShirtPixmap);
    team2ShirtGraphItem->setPos(TEAM_SHIRT_POS_X + posX, TEAM_SHIRT_POS_Y + posY);
    ui->gameView->scene()->addItem(team2PlayerName);
    ui->gameView->scene()->addItem(team2PlayerNumber);
    int performance = db->getPlayerPerformance(team2[index + 1]);
    for(int i = 0; i < performance; i++)
    {
        QGraphicsPixmapItem* team2PerformanceItem = ui->gameView->scene()->addPixmap(team2PerformancePixmap);
        team2PerformanceItem->setPos(TEAM_SHIRT_POS_X + posX + 120 + i*20, TEAM_SHIRT_POS_Y + posY + 20);
    }
    int results = db->getPlayerResults(team2[index + 1]);
    for(int i = 0; i < results; i++)
    {
        QGraphicsPixmapItem* team2ResultsItem = ui->gameView->scene()->addPixmap(team2ResultsPixmap);
        team2ResultsItem->setPos(TEAM_SHIRT_POS_X + posX + 120 + i*20, TEAM_SHIRT_POS_Y + posY + 50);
    }
}

void Game::drawPlayersTeam1()
{
    drawPlayerTeam1(0, 0, 0);
    drawPlayerTeam1(3, 0, 130);
    drawPlayerTeam1(6, 0, 260);
    drawPlayerTeam1(9, 190, 0);
    drawPlayerTeam1(12, 190, 130);
    drawPlayerTeam1(15, 190, 260);
}

void Game::drawPlayerTeam1(int index, int posX, int posY)
{
    QPixmap team1ShirtPixmap(":/images/tshirt1.png");
    QPixmap team1PerformancePixmap(":/images/power.jpg");
    QPixmap team1ResultsPixmap(":/images/results.jpg");
    QGraphicsTextItem* team1PlayerName = new QGraphicsTextItem;
    QGraphicsTextItem* team1PlayerNumber = new QGraphicsTextItem;
    team1PlayerNumber->setPos(982 - TEAM_NUMBER_POS_X - posX, TEAM_NUMBER_POS_Y + posY);
    team1PlayerNumber->setPlainText(team1[index + 2]);
    team1PlayerNumber->setDefaultTextColor(Qt::white);
    team1PlayerName->setPos(950 - TEAM_NAME_POS_X - posX, TEAM_NAME_POS_Y + posY);
    team1PlayerName->setPlainText(team1[index]);
    team1PlayerName->setDefaultTextColor(Qt::white);
    QGraphicsPixmapItem* team1ShirtGraphItem = ui->gameView->scene()->addPixmap(team1ShirtPixmap);
    team1ShirtGraphItem->setPos(870 - TEAM_SHIRT_POS_X - posX, TEAM_SHIRT_POS_Y + posY);
    ui->gameView->scene()->addItem(team1PlayerName);
    ui->gameView->scene()->addItem(team1PlayerNumber);
    int performance = db->getPlayerPerformance(team1[index + 1]);
    for(int i = 0; i < performance; i++)
    {
        QGraphicsPixmapItem* team1PerformanceItem = ui->gameView->scene()->addPixmap(team1PerformancePixmap);
        team1PerformanceItem->setPos(870 - TEAM_SHIRT_POS_X - posX + 120 + i*20, TEAM_SHIRT_POS_Y + posY + 20);
    }
    int results = db->getPlayerResults(team1[index + 1]);
    for(int i = 0; i < results; i++)
    {
        QGraphicsPixmapItem* team1ResultsItem = ui->gameView->scene()->addPixmap(team1ResultsPixmap);
        team1ResultsItem->setPos(870 - TEAM_SHIRT_POS_X - posX + 120 + i*20, TEAM_SHIRT_POS_Y + posY + 50);
    }
}

void Game::on_printGraphics_clicked()
{
    QPixmap pixMap = QPixmap::grabWidget(ui->gameView);
    pixMap.save("yourfile.png");
}

void Game::on_resetState_clicked()
{
    emit resetMainWindow();
    this->close();
}
