#include <QCoreApplication>
#include <serializer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    core::Message m{"123", "123", "123", "123"};
    return a.exec();
}
