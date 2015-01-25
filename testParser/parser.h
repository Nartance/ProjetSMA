#ifndef PARSER_H
#define PARSER_H

#include <QMainWindow>

namespace Ui {
class Parser;
}

class Parser : public QMainWindow
{
    Q_OBJECT

public:
    explicit Parser(QWidget *parent = 0);
    ~Parser();

private:
    Ui::Parser *ui;
};

#endif // PARSER_H
