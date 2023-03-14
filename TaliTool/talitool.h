#ifndef TALITOOL_H
#define TALITOOL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TaliTool; }
QT_END_NAMESPACE

class TaliTool : public QMainWindow
{
    Q_OBJECT

public:
    TaliTool(QWidget *parent = nullptr);
    ~TaliTool();

private:
    Ui::TaliTool *ui;
};
#endif // TALITOOL_H
