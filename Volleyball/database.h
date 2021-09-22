#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QStack>
#include <QStringList>
#include <QSqlQuery>

class Database
{

    QSqlDatabase db;

private:
    static Database* instance;
    Database(Database const&);       // Not implemented.
    void operator=(Database const&); // Not implemented.
    Database();

public:
    QStringList getPlayersData(QStack<QString> teamPlayers, QString team);
    QStringList getPlayersData(QString team);
    QString getLastGame();
    int getPlayerPerformance(QString id);
    int getPlayerResults(QString id);
    void setPlayerPerformance(QString player, QString performance);
    void setPlayerResults(QString player, QString results);
    void addGame(QString team1, QString team2, QString date);
    static Database* getInstance();
};

#endif // DATABASE_H
