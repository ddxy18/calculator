#include "mymainwindow.h"
#include "ui_mymainwindow.h"

#include<QDebug>

#include "calculate.cpp"

myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    expression="";
    clickEqualTimes=0;
    result=0;
    next=false;
    leftBracketNum=0;
    ui->setupUi(this);
}

myMainWindow::~myMainWindow()
{
    delete ui;
}

void myMainWindow::on_pushButton_0_clicked()
{
    if(next)
        clear();
    ui->textBrowser->insertPlainText("0");
}

void myMainWindow::on_pushButton_1_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("1");
}

void myMainWindow::on_pushButton_2_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("2");
}

void myMainWindow::on_pushButton_3_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("3");
}

void myMainWindow::on_pushButton_4_clicked()
{

    if(next)
        clear();
   ui->textBrowser->insertPlainText("4");
}

void myMainWindow::on_pushButton_5_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("5");
}

void myMainWindow::on_pushButton_6_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("6");
}

void myMainWindow::on_pushButton_7_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("7");
}

void myMainWindow::on_pushButton_8_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("8");
}

void myMainWindow::on_pushButton_9_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("9");
}

void myMainWindow::on_pushButton_point_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText(".");
}

void myMainWindow::on_pushButton_divide_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("/");
}

void myMainWindow::on_pushButton_multiply_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("*");
}

void myMainWindow::on_pushButton_minus_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("-");
}

void myMainWindow::on_pushButton_plus_clicked()
{

    if(next)
        clear();
    ui->textBrowser->insertPlainText("+");
}

void myMainWindow::on_pushButton_equal_clicked()
{
    if(clickEqualTimes==0&&!isInputValid())
    {
        ui->textBrowser->setText("");
        ui->textBrowser->append("输入不合法");
    }
    else if(clickEqualTimes==0)
    {
        QByteArray tmp=expression.toLatin1();
        cal.expression=tmp.data();
        cal.calculateStack();
        result=cal.sendResult();
        QString res=QString::number(result,'f',3);
        ui->textBrowser->append(res);
    }
    ++clickEqualTimes;
    next=true;
}

void myMainWindow::on_pushButton_left_clicked()
{
    if(next)
        clear();
    ui->textBrowser->insertPlainText("(");
}

void myMainWindow::on_pushButton_right_clicked()
{
    if(next)
        clear();
    ui->textBrowser->insertPlainText(")");
}

void myMainWindow::getExpression()
{
    expression=ui->textBrowser->toPlainText();
}

void myMainWindow::clear()
{
    clickEqualTimes=0;
    next=false;
    expression="";
    result=0;
    leftBracketNum=0;
    ui->textBrowser->setText("");
    cal.clear();
}

bool myMainWindow::isInputValid()
{
    getExpression();
    if(expression[0]=='+'||expression[0]=='-'||expression[0]=='*'||expression[0]=='/'||expression[0]=='.') return false;
    if(expression.length()==1) return true;
    int i=0;
    while(i<expression.length())
    {
        if(expression[i]=='(') leftBracketNum++; //判断输入括号是否成对
        if(expression[i]==')')
        {
            if(leftBracketNum==0) return false;
            leftBracketNum--;
            if(expression[i-1]=="+"||expression[i-1]=="-"||expression[i-1]=="*"||expression[i-1]=="/"||expression[i-1]==".")
                return false;
        }

        if(expression[i]=='+'||expression[i]=='-'||expression[i]=='*'||expression[i]=='/')
            if(expression[i-1]=='+'||expression[i-1]=='-'||expression[i-1]=='*'||expression[i-1]=='/'||expression[i-1]=='.'||expression[i-1]=='(')
                return false;

        if(expression[i]=='.')
        {
            int j=i-1;
            if(expression[j]>'9'||expression[j]<'0') return false;
            --j;
            while(j>=0&&expression[j]>='0'&&expression[j]<='9')
                --j;
            if(j>=0&&expression[j]==".") return false;
        }

        if(expression[i]==')')
            if(expression[i-1]=='+'||expression[i-1]=='-'||expression[i-1]=='*'||expression[i-1]=='/'||expression[i-1]=='.'||expression[i-1]=='(')
                return false;

        if(expression[i]=='0')
        {
            int j=i-1;
            while(j>=0&&expression[j]=='0')
                j--;
            if(j==-1&&expression[j+2]>="0"&&expression[j+2]<="9") return false;
            if(i+1<expression.length()&&j>=0&&expression[i+1]>="0"&&expression[i+1]<="9"&&(expression[j]=='+'||expression[j]=='-'||expression[j]=='*'||expression[j]=='/'))
                return false;
        }
        i++;
    }

    if(leftBracketNum!=0) return false;
    if(expression[i-1]=='+'||expression[i-1]=='-'||expression[i-1]=='*'||expression[i-1]=='/'||expression[i-1]=='.') return false;
    return true;
}
