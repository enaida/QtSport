#include "database.h"
#include <QSqlError>

Database* Database::instance = NULL;

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\SQLITE\\test.db");
    qDebug()<<db.open();
    qDebug()<<db.lastError().text();

}

Database* Database::getInstance()
{
    if (instance == 0)
    {
        instance = new Database();
    }

    return instance;
}

QStringList Database::getPlayersData(QStack<QString> teamPlayers, QString team)
{
    QStringList result;
    while(teamPlayers.isEmpty() == false)
    {
        QSqlQuery query;
        QString sql= "SELECT name, id, shirt_number FROM players WHERE team_id =";
        sql.append(team);
        sql.append(" and id = ");
        sql.append(teamPlayers.pop());
        query.exec(sql);
        if(query.first())
        {
            result.push_back(query.value(0).toString());
            result.push_back(query.value(1).toString());
            result.push_back(query.value(2).toString());
        }
    }
    return result;
}

QStringList Database::getPlayersData(QString team)
{
    QStringList result;
    QSqlQuery query;
    QString sql= "SELECT name, id, shirt_number FROM players WHERE team_id =";
    sql.append(team);
    query.exec(sql);
    while(query.next())
        {
            result.push_back(query.value(0).toString());
            result.push_back(query.value(1).toString());
            result.push_back(query.value(2).toString());
        }
    return result;
}

int Database::getPlayerResults(QString id)
{
    QString result;
    QSqlQuery query;
    QString sql = "SELECT results FROM players WHERE id = ";
    sql.append(id);
    query.exec(sql);
    query.first();
    result.push_back(query.value(0).toString());
    return result.toInt();
}

int Database::getPlayerPerformance(QString id)
{
    QString result;
    QSqlQuery query;
    QString sql = "SELECT performance FROM players WHERE id = ";
    sql.append(id);
    query.exec(sql);
    query.first();
    result.push_back(query.value(0).toString());
    return result.toInt();
}

QString Database::getLastGame()
{
    QString result, sql;
    QSqlQuery query;
    sql = "SELECT game_date FROM games where id = (select max(id) from games)";
    query.exec(sql);
    query.first();
    result.push_back(query.value(0).toString());
    return result;
}

void Database::setPlayerPerformance(QString player, QString performance)
{
    QSqlQuery query;
    QString sql = "UPDATE players set performance = ";
    sql.append(performance);
    sql.append(" where id = ");
    sql.append(player);
    query.exec(sql);
}

void Database::setPlayerResults(QString player, QString results)
{
    QSqlQuery query;
    QString sql = "UPDATE players set results = ";
    sql.append(results);
    sql.append(" where id = ");
    sql.append(player);
    query.exec(sql);
}

//team 1: Sebastian, Nick
  //      team2: David, Trey

void Database::addGame(QString team1, QString team2, QString date)
{
    QSqlQuery query;
    //QString sql = "INSERT INTO games VALUES(default, ";
    QString sql = "INSERT INTO games(team_id1, team_id2, game_date) VALUES(";
    sql.append(team1);
    sql.append(",");
    sql.append(team2);
    sql.append(", '");
    sql.append(date);
    sql.append("')");
    query.exec(sql);
    qDebug() << query.lastError().text();
}
