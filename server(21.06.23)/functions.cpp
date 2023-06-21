#include "functions.h"
#include <QObject>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <set>
#include <QVector>
#include <QPair>
#include <QSet>
#include <QInputDialog>
#include <QMap>
#include <algorithm>

QString authorization(QString login, QString password)
{
    if (Database_u::GetInstance()->CheckUser(login, password))
    {
        return "true";
    }

    return "false";
}

QString registration(QString login, QString password)
{
    if (Database_u::GetInstance()->AddUser(login, password))
        return "true";

    return "false";
}

QString gen_graph()
{
    int vertex_num = QRandomGenerator::global()->bounded(4, 8);
    int edges_num = QRandomGenerator::global()->bounded(vertex_num, vertex_num * (vertex_num - 1)/2);;
    QSet<QPair<int, int>> edges;

    while (edges.size() < edges_num)
    {
        int i,j;
        i = QRandomGenerator::global()->bounded(vertex_num);
        j = QRandomGenerator::global()->bounded(vertex_num);

        if (i > j)
            edges.insert(QPair<int, int>(j, i));
        else if (i < j)
            edges.insert(QPair<int, int>(i, j));
    }

    QString result = QString::number(vertex_num) + ":";
    for (auto &e : edges)
    {
        result += "(" + QString::number(e.first);
        result += ";" + QString::number(e.second) + "),";
    }

    result.chop(1); // удалить последний символ (в нашел случае это ",")

    return result + ":";
}

bool CheckTask1Answer(QString full_answer)
{
    QStringList parts = full_answer.split(":");
    if (parts.size() != 3)
        return false;

    QString vertex_num = parts[0];
    QStringList edges = parts[1].split(',');
    QString ans = parts[2];

    if (ans[0] != ans[ans.length() - 1])
        return false;

    while (ans.size() > 1)
    {
        if (ans[0] < ans[1])
        {
            if(edges.contains("(" + QString(ans[0]) + ";" + QString(ans[1]) + ")"))
                ans.remove(0, 1);
            else
                return false;
        }
        else if (ans[0] > ans[1])
        {
            if(edges.contains("("+ QString(ans[1]) +";"+ QString(ans[0]) +")"))
                    ans.remove(0, 1);
            else
                    return false;
        }
        else
            return false;
    }

    return true;
}

QString GetTask1(QString cLogin)
{
    Database_u::GetInstance()->AddVariant(cLogin, "Task 1", "", true);
    return gen_graph();
}

bool CheckTask2Answer(QString full_answer)
{
    QStringList parts = full_answer.split(":");
    if (parts.size() != 3)
        return false;

    QString vertex_num = parts[0];
    QStringList edges = parts[1].split(',');
    QString ans = parts[2];

    if (ans[0] != ans[ans.length() - 1])
        return false;

    while (ans.size() > 1)
    {
        QString ans_edge;

        if (ans[0] < ans[1])
        {
            ans_edge = "(" + QString(ans[0]) + ";" + QString(ans[1]) + ")";
        }
        else if (ans[0] > ans[1])
        {
            ans_edge = "(" + QString(ans[1]) + ";" + QString(ans[0]) + ")";
        }
        else
        {
            return false;
        }

        int index = edges.indexOf(ans_edge);
        if (index >= 0)
        {
            ans.remove(0, 1);
            edges.removeAt(index);
        }
        else
        {
            return false;
        }
    }

    return true;
}

QString GetTask2(QString cLogin)
{
    Database_u::GetInstance()->AddVariant(cLogin, "Task 2", "", true);
    // Генерация графа
    return gen_graph();
}

int CheckSubVertex(QString vertex, QString subvertex1, QString subvertex2, QSet<QString> &set1, QSet<QString> &set2)
{
    QString newvertex;

    if (vertex == subvertex1)
    {
        newvertex = subvertex2;
    }
    else if (vertex == subvertex2)
    {
        newvertex = subvertex1;
    }
    else
    {
        return -1;
    }

    if (set1.contains(newvertex))
    {
        return 0;
    }

    set2.insert(newvertex);

    return 1;
}

int CheckVertex(QString vertex1, QString vertex2, QSet<QString> &set1, QSet<QString> &set2)
{
    QString newvertex;

    if (set1.contains(vertex1))
    {
        if (set1.contains(vertex2))
            return 0;

        set2.insert(vertex2);
    }
    else if (set2.contains(vertex1))
    {
        if (set2.contains(vertex2))
            return 0;

        set1.insert(vertex2);
    }
    else
    {
        return -1;
    }

    return 1;
}

bool CheckTask3Answer(QString full_answer)
{
    QStringList parts = full_answer.split(":");
    if (parts.size() != 3)
        return false;

    QString vertex_num = parts[0];
    QStringList edges = parts[1].split(',');
    QString ans = parts[2];
    QSet<QString> set1;
    QSet<QString> set2;
    bool isBipartite = true;

    for (int i = 0; i < edges.size(); i++)
    {
        QStringList vertexes = edges[i].split(";");
        QString vertex1 = vertexes[0].remove(0, 1); // Удаляем открывающую скобку
        QString vertex2 = vertexes[1].remove(vertexes[1].size() - 1, 1); // Удаляем закрываюшую скобку
        int res;

        res = CheckVertex(vertex1, vertex2, set1, set2);
        if (res == 0)
        {
            isBipartite = false;
            break;
        }
        else if (res == -1)
        {
            res = CheckVertex(vertex2, vertex1, set1, set2);
            if (res == 0)
            {
                isBipartite = false;
                break;
            }
            else if (res == -1) {
                set1.insert(vertex1);
                set2.insert(vertex2);
            }
        }

        for (int j = edges.size() - 1; j > i; j--)
        {
            QStringList subvertexes = edges[j].split(";");
            QString subvertex1 = subvertexes[0].remove(0, 1); // Удаляем открывающую скобку
            QString subvertex2 = subvertexes[1].remove(subvertexes[1].size() - 1, 1); // Удаляем закрываюшую скобку

            int res = CheckSubVertex(vertex1, subvertex1, subvertex2, set1, set2);
            if (res == 0)
            {
                isBipartite = false;
                break;
            } else if (res == 1)
            {
                edges.removeAt(j);
                continue;
            }

            res = CheckSubVertex(vertex2, subvertex1, subvertex2, set2, set1);
            if (res == 0)
            {
                isBipartite = false;
                break;
            } else if (res == 1)
            {
                edges.removeAt(j);
                continue;
            }
        }

        if (isBipartite == false)
            break;
    }

    if (isBipartite == false)
    {
        return ans == "no";
    }

    if (ans.size() != set1.size() || ans.size() != set2.size())
    {
        return false;
    }

    int setindex;
    for (int i = 0; i < ans.size(); i++)
    {
        if (i == 0)
        {
            if (set1.contains(ans[i]))
            {
                setindex = 1;
            }
            else if (set2.contains(ans[i]))
            {
                setindex = 2;
            }
            else
            {
                return false;
            }
        }

        if (setindex == 1)
        {
            if (set1.contains(ans[i]))
            {
                    set1.remove(ans[i]);
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (set2.contains(ans[i]))
            {
                    set2.remove(ans[i]);
            }
            else
            {
                return false;
            }
        }
    }

    if (setindex == 1 && set1.size() > 0)
        return false;

    if (setindex == 2 && set2.size() > 0)
        return false;

    return true;
}


QString GetTask3(QString cLogin)
{
    int vertex_num = QRandomGenerator::global()->bounded(4, 8);
    int edges_num = QRandomGenerator::global()->bounded(vertex_num, vertex_num * (vertex_num - 1)/2);
    QSet<int> set1;
    QSet<int> set2;
    QSet<QPair<int, int>> edges;

    while (set1.size() < vertex_num / 2)
    {
        set1.insert(QRandomGenerator::global()->bounded(vertex_num));
    }

    for (int i = 0; i < vertex_num; i++)
    {
        if (set1.contains(i) == false)
        {
            set2.insert(i);
        }
    }

    int duplicate = 0;
    while (edges.size() < edges_num && duplicate < 10)
    {
        int i,j;
        i = set1.values()[QRandomGenerator::global()->bounded(set1.size())];
        j = set2.values()[QRandomGenerator::global()->bounded(set2.size())];

        int size = edges.size();

        if (i > j)
            edges.insert(QPair<int, int>(j, i));
        else
            edges.insert(QPair<int, int>(i, j));

        if (size == edges.size())
        {
            duplicate++;
        } else
        {
            duplicate = 0;
        }
    }

    QString result = QString::number(vertex_num) + ":";
    for (auto &e : edges)
    {
        result += "(" + QString::number(e.first);
        result += ";" + QString::number(e.second) + "),";
    }

    result.chop(1); // удалить последний символ (в нашел случае это ",")

    Database_u::GetInstance()->AddVariant(cLogin, "Task 3", "", true);
    return result + ":";
}

bool CheckTask4Answer(QString full_answer, QString login)
{
    QString q = Database_u::GetInstance()->get_answer(login);
    QStringList lines_q = q.trimmed().split("\n");
    QStringList lines_ans = full_answer.trimmed().split("\n");
    QMap<QString, QString> set_q;
    QMap<QString, QString> set_ans;

    if (lines_q.size() != lines_ans.size())
        return false;

    for (int i = 0; i < lines_q.size(); i++)
    {
        QStringList l = lines_q[i].split(" ");
        QStringList a = lines_ans[i].split(" ");

        set_q[l[0]] = l[1];

        if (a.size() != 2 || a[1].size() != 1 || set_ans.contains(a[0]))
                return false;

        set_ans[a[0]] = a[1];
    }

    for (auto &k1 : set_ans.keys())
    {
        QString p = set_ans[k1];

        if (set_q[k1].contains(p) == false)
            return false;

        for (auto i = set_ans.cbegin(), end = set_ans.cend(); i != end; ++i)
        {
            if (i.key() == k1)
                continue;

            if (i.value().contains(p))
                return false;
        }
    }

    return true;
}

QString GetTask4(QString cLogin)
{
    int set_num = QRandomGenerator::global()->bounded(2, 4);
    int N = QRandomGenerator::global()->bounded(5, 8);
    QVector<QSet<int>> set;

    set.resize(set_num);

    for (int i = 0; i < set_num; i++)
    {
        int size = QRandomGenerator::global()->bounded(2, 5);
        while (set[i].size() < size)
        {
            set[i].insert(QRandomGenerator::global()->bounded(1, N));
        }
    }

    QString result = "";
    for (int i = 0; i < set.size(); i++)
    {
        result += "A" + QString::number(i + 1) + " ";
        for (int j = 0; j < set[i].size(); j++)
        {
            result += QString::number(set[i].values()[j]);
        }
        result += "\n";
    }

    Database_u::GetInstance()->AddVariant(cLogin, "Task 4", result.trimmed(), true);
    return result;
}

// вот это отладить(?), хотя тут вроде только вычисления и надо просто подключить грамотно
QString getTask(QString name,QString cLogin)
{
    if (name == "Task 1")
    {
        return GetTask1(cLogin);
    }
    else if (name == "Task 2")
    {
        return GetTask2(cLogin);
    }
    else if (name == "Task 3")
    {
        return GetTask3(cLogin);
    }
    else if (name == "Task 4")
    {
        return GetTask4(cLogin);
    }
    return "";
}

bool CheckAnswer(QString answer, QString login)
{
    QString task = Database_u::GetInstance()->GetCurrentTask(login);
    if (task == "Task 1")
    {
        return CheckTask1Answer(answer);
    }
    else if (task == "Task 2")
    {
        return CheckTask2Answer(answer);
    }
    else if (task == "Task 3")
    {
        return CheckTask3Answer(answer);
    }
    else if (task == "Task 4")
    {
        return CheckTask4Answer(answer, login);
    }

    return false;
}

QString parse(QString data)
{
    data = data.trimmed();

    QStringList parts = data.split("&"); //разбиваем строку на список параметров, (&) - разделитель для разделения параметров
    qDebug()<<data;
    if (parts[0] == "auth" && parts.size() == 3)
        return authorization(parts[1].trimmed(), parts[2].trimmed());
    else if (parts[0] == "reg" && parts.size() == 3)
        return registration(parts[1].trimmed(), parts[2].trimmed());
    else if (parts[0] == "names" && parts.size() == 1)
        return Database_u::GetInstance()->GetTaskNames();
    else if (parts[0] == "task" && parts.size() == 3)
        return getTask(parts[1].trimmed(),parts[2].trimmed());
    else if (parts[0] == "task_template" && parts.size() == 2)
        return Database_u::GetInstance()->GetTaskTemplate(parts[1].trimmed());
    else if (parts[0] == "answer" && parts.size() == 3)
    {
        QString answer = parts[1].trimmed();
        QString login = parts[2].trimmed();
        bool isCorrect = CheckAnswer(answer,login);
        Database_u::GetInstance()->AddAnswer(login, answer, isCorrect);
        return isCorrect ? "true" : "false";
    }
    else if (parts[0] == "stat" && parts.size() == 2)
        return Database_u::GetInstance()->GetStat(parts[1]);

    return "false";
}
