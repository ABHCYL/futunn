#include <QCoreApplication>
#include <QDebug>
#include <QString>

#include <QSet>
#include <QHash>
#include <QMultiHash>

#include <QMap>
#include <QMultiMap>


#include <QList>
#include <QLinkedList>
#include <QVector>

#include <QStack>
#include <QQueue>

void testQSet() {
    QSet<QString> set {"111", "333", "222"}; // 哈希 O(1) 无序

    foreach (auto & s, set)  qDebug() << s << "\n";
//    for (auto & s : set) qDebug() << s << "\n";

}

void tesQMap() {
     // QMap 提供 <
    QSet<QString> set {"111", "333", "222"};
    QSet<QString> set2 {"-1"};
    QMap<QString, QSet<QString>> map {{"b", set}, {"a", set2}};
    // 按照 key-val 添加进map的顺序而不是以key作为红黑树的比较键值（有些不实用）
    for (auto & key : map.keys()) {
        qDebug() << map[key] << "\n";
    }
    map.remove("b");
    QSet<QString> tmp = map.value("a");
}

void testQMultiMap() {
    // QMultiMap 是 QMap 子类
    QMultiMap<QString, int> m1 {{"1", 1}};
    QMultiMap<QString, int> m2 {{"2", 2}};
    QMultiMap<QString, int> m3 {{"1", 3}};

    m3 += m1 + m2;
    qDebug() << m3.size() << "\n";

    // 没有 [] 运算符
    QList<int> res = m3.values("1"); // 键"1"的所有value
    for (auto & x : res) qDebug() <<  x << " "; // 1 , 3
}

void testQHash() {
     // QHash 提供 == 和 qHash() ，和 c++ Java 一个套路
    QSet<QString> set {"111", "333", "222"};
    QSet<QString> set2 {"-1"};
    QHash<QString, QSet<QString>> hash {{"b", set}, {"a", set2}}; // 哈希 O(1) 无序 类似 QMap
    for (auto & key : hash.keys()) {
        qDebug() << hash[key] << "\n";
    }
}

void testQMultiHash() {
    // QMultiHash 是 QHash 子类
    QMultiHash<QString, int> m1 {{"1", 1}};
    QMultiHash<QString, int> m2 {{"2", 2}};
    QMultiHash<QString, int> m3 {{"1", 3}};

    m3 += m1 + m2;
    qDebug() << m3.size() << "\n";

    // 没有 [] 运算符
    QList<int> res = m3.values("1"); // 键"1"的所有value
    for (auto & x : res) qDebug() <<  x << " "; // 1 , 3
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testQSet();
    return a.exec();
}
