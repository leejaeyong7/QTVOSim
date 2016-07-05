#ifndef PATHEDITWINDOW_H
#define PATHEDITWINDOW_H

#include <QDialog>

namespace Ui {
class PathEditWindow;
}

class PathEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PathEditWindow(QWidget *parent = 0);
    ~PathEditWindow();

private:
    Ui::PathEditWindow *ui;
};

#endif // PATHEDITWINDOW_H
