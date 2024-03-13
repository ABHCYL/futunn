#include <QCoreApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QString>

void test() {
    QString s1 = "fu", s2 = "tu", s3 = "nn";
    s2.append(s3); // 后面添加
    s2.prepend(s1); // 前面添加
    qDebug() << s2 << "\n"; // "futunn"
    qDebug() << s2.toUpper() << "\n"; // "FUTUNN" toLower()
    qDebug() << s2.count() << " " << s2.size() << " " << s2.length() << "\n"; // 6   6   6

    s2.prepend("    "); s2.append("    ");
    qDebug() << s2 << " " << s2.trimmed() << "\n"; // "    futunn    "   "futunn" trimmed去掉首尾空格
    s2 = " fu tu   nn   666 ";
    qDebug() << s2.simplified(); // 中间连续空格替换为1个空格 "fu tu nn 666"

    // indexOf lastIndexOf 其功能是在自身字符串内查找参数字符串 str出现的位置,参数from是开始查找的位置
    // Qt::CaseSensitivitycs参数指定是否区分大小写。
    QString str1="Qt5BookQT5.9Studyqw.cpp", str2;
    int N=str1.indexOf("5.9");
    N=str1.lastIndexOf("\\");

    // isNull isEmpty
    str1="";
    str2.isNull(); // true
    str1.isNull(); // false, str1 实际上是 "\0" 所以非NULL

    str2.isEmpty(); // true
    str1.isEmpty(); // true


    // contains
    QString strl="G:\Qt5Book\QT5.9Study\qw.cpp";
    N=strl.contains(".cpp", Qt::CaseInsensitive); // 不区分大小写, 默认是不区分
    N=strl.contains(".CPP", Qt::CaseSensitive); // 区分大小写


    // startsWith()判断是否以某个字符串开头,endsWith()判断是否容以某个字符串结束。
    strl="G:\Qt5Book\QT5.9Study\qw.cpp";
    N=strl.endsWith(".cpp", Qt::CaseInsensitive);
    N=str1. endsWith(".CPP", Qt::CaseSensitive);
    N=str1. startsWith("g: ");

    // left right 截取从左、右N个字符
    strl = "fffff,ttttt";
    qDebug() << strl.left(strl.indexOf(",")) << "\n"; // fffff
    qDebug() << strl.right(strl.size() - strl.lastIndexOf(",")) << "\n"; // ,ttttt
    qDebug() << strl.right(strl.size() - strl.lastIndexOf(",") - 1) << "\n"; // ttttt 注意细节-1

    // section 应该是这些例子里面最有用的
    // section(const QSting &sep, start, end=-1)
    // 以 sep 为分隔符，截取 s 到 e 的字符串
    strl="学生姓名,男,1984-3-4,汉族,山东";
    str2=strl.section (",",0,0); //"学生姓名" 第一段编号为0

    str2=strl.section (",",1,1); //"男"
    str2=strl.section (",",0,1); //"学生姓名,男"
    qDebug() <<  str2;
    str2=str1.section (",",4,4); //"山东"
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test();
    return a.exec();
}
