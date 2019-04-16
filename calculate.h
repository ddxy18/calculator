#ifndef CALCULATE_H
#define CALCULATE_H

#include<QObject>
#include<QString>
#include<QStack>

class calculate
{

    enum Type{PLUS,MINUS,MUTIPLY,DIVIDE,NUM};

private:
    double result; //表达式计算结果
    int behindLength; //存储后缀表达式中字符个数
    int middleLength; //存储中缀表达式中字符个数
    QStack<QString> signal; //处理表达式中的符号
    QStack<QString> behindExpression; //存储转换成的后缀表达式
    QStack<double> number; //处理数字以进行后缀表达式的运算
    //bool getNumbern(int *); //将运算数从中缀表达式提取出来
    bool getNumbers(QString,int *); //将运算数从中缀表达式提取出来
    void changeMiddleExpressionToBehindExpression(); //把中缀表达式转换为后缀表达式

public:
    void clear();
    QString expression; //字符串类型的中缀表达式
    void getLengthMiddle(); //计算中缀表达式长度
    void getLengthBehind(); //计算后缀表达式长度
    void calculateStack(); //计算子树的结果
    double sendResult(); //输出结果
    calculate();
};

#endif // CALCULATE_H
