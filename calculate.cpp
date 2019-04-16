#include "calculate.h"

#include<QDebug>

calculate::calculate()
{
    result=0;
    middleLength=0;
    behindLength=0;
    expression="";
}

void calculate::getLengthMiddle()
{
    middleLength=expression.length();
}

void calculate::getLengthBehind()
{
    behindLength=behindExpression.length();
}

bool calculate::getNumbers(QString exp,int *i)
{
    QString tmp;

    if(exp[*i]=="0"&&exp[*i+1]!=".")
    {
        signal.push("0");
        return true;
    }
    while(*i<middleLength&&((exp[*i]>="0"&&exp[*i]<="9")||exp[*i]=='.'))
    {
        tmp.append(exp[*i]);
        ++*i;
    }

    if(tmp!="")
    {
        signal.push(tmp);
        return true;
    }
    return false;
}

void calculate::changeMiddleExpressionToBehindExpression()
{
    int i=0,j=0;
    QString tmp;
    getLengthMiddle();

    QStack<QString> behindExpressiontmp;
    while(i<middleLength)
    {
        if(getNumbers(expression,&i))
        {
            behindExpressiontmp.push(signal.pop());
        }
        if(i>=middleLength) break;
        if(expression[i]=="(")
        {
            tmp="";
            tmp.append(expression[i]);
            signal.push(tmp);
        }

        if(expression[i]==")")
        {
            tmp="";
            while(tmp!="(")
            {
                if(tmp!="")
                    behindExpressiontmp.push(tmp);
                tmp=signal.pop();
            }
        }

        if(expression[i]=="+"||expression[i]=="-")
        {
            tmp="";
            while(tmp!="(")
            {
                if(tmp!="")
                    behindExpressiontmp.push(tmp);
                if(!signal.isEmpty()&&signal.top()!="(")
                {
                    tmp=signal.pop();
                }
                else break;
            }
            tmp="";
            tmp.append(expression[i]);
            signal.push(tmp);
        }

        if(expression[i]=="*"||expression[i]=="/")
        {
            tmp="";
            while(tmp!="("&&tmp!="+"&&tmp!="-")
            {
                if(tmp!="")
                    behindExpressiontmp.push(tmp);
                if(!signal.isEmpty()&&(signal.top()=="*"||signal.top()=="/"))
                    tmp=signal.pop();
                else break;
            }
            tmp="";
            tmp.append(expression[i]);
            signal.push(tmp);
        }
        ++i;
    }
    while(!signal.isEmpty()) behindExpressiontmp.push(signal.pop());
    while(!behindExpressiontmp.isEmpty()) behindExpression.push(behindExpressiontmp.pop());
    getLengthBehind();
}


void calculate::calculateStack()
{
    changeMiddleExpressionToBehindExpression();
    double left=0,right=0;
    int i=1;
    QString tmp;

    while(i<=behindLength)
    {
        tmp=behindExpression.pop();
        while(tmp!="+"&&tmp!="-"&&tmp!="*"&&tmp!="/")
        {
            number.push(tmp.toDouble());
            if(!behindExpression.isEmpty())
                tmp=behindExpression.pop();
            else break;
            ++i;
        }

        if(tmp=="+")
        {
            left=number.pop();
            right=number.pop();
            number.push(left+right);
        }

        if(tmp=="-")
        {
            left=number.pop();
            right=number.pop();
            number.push(right-left);
        }

        if(tmp=="*")
        {
            left=number.pop();
            right=number.pop();
            number.push(left*right);
        }

        if(tmp=="/")
        {
            left=number.pop();
            right=number.pop();
            number.push(right/left);
        }
        ++i;
    }

    result=number.pop();
}

double calculate::sendResult()
{
    return result;
}

void calculate::clear()
{
    result=0;
    middleLength=0;
    behindLength=0;
    behindExpression.clear();
    number.clear();
    signal.clear();
    expression="";
}
