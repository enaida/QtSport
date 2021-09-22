#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QStack>
#include "database.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setBackground(QString path);
    void setPlayersCombo();
    ~MainWindow();

public slots:
     void resetToInitialState();

private slots:
    void on_team1_currentIndexChanged(int index);

    void on_team2_currentIndexChanged(int index);

    void on_player1PerfButton_clicked();

    void on_player2PerfButton_clicked();

    void on_player1ResButton_clicked();

    void on_player2ResButton_clicked();

    void on_gameStartButton_clicked();

    void on_addTeam1PlayerButton_clicked();

    void on_addTeam2PlayerButton_clicked();

private:
    Game *game;
    QStack<QString> team1Players, team2Players;
    QDate initialDate;
    QByteArray initialState, initialGeometry;
    QColor *team1Color, *team2Color;
    QStringList team1, team2;
    Database *db;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
