#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

#include "calculate.h"

namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = nullptr);
    ~myMainWindow();
    void getExpression(); //从显示窗口中得到表达式
    bool isInputValid(); //检查输入是否合法
    void clear(); //重新初始化显示窗口并且初始化各数据成员

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_point_clicked();

    void on_pushButton_divide_clicked();

    void on_pushButton_multiply_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

private:
    Ui::myMainWindow *ui;
    int clickEqualTimes; //记录按等于次数，不为0时不做响应
    bool next; //false表示执行当前运算，true调用clear()进行下一次运算
    int leftBracketNum;
    QString expression;
    double result;
    calculate cal;
};

#endif // MYMAINWINDOW_H
