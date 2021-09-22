#ifndef GAME_H
#define GAME_H
#define TEAM_SHIRT_POS_X 90
#define TEAM_SHIRT_POS_Y 50
#define TEAM_NAME_POS_X 130
#define TEAM_NAME_POS_Y 72
#define TEAM_NUMBER_POS_X 146
#define TEAM_NUMBER_POS_Y 100

#include <QDialog>
#include <QStack>
#include <QStringList>
#include <QString>
#include "database.h"

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

signals:
    void resetMainWindow();

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    void addTeamsPlayers(QStack<QString> team1Players, QStack<QString> team2Players);
    void startGame();

private slots:
    void on_printGraphics_clicked();

    void on_resetState_clicked();

private:
    QStringList team1, team2;
    QString gameDate;
    Database *db;
    Ui::Game *ui;
    void drawField();
    void drawDate();
    void drawPlayerTeam1(int index, int posX, int posY);
    void drawPlayersTeam1();
    void drawPlayerTeam2(int index, int posX, int posY);
    void drawPlayersTeam2();
};

#endif // GAME_H
