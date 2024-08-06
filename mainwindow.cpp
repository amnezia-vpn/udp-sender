#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QClipboard>
#include <QString>

#include <QUdpSocket>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit->setPlainText(QApplication::clipboard()->text());
}


void MainWindow::on_pushButton_clicked()
{
    QString ip = ui->lineEdit->text();
    int port = ui->spinBox->value();


    QString rawData = ui->plainTextEdit->toPlainText();

    QByteArray output;

    if (rawData.contains("0x0000:")) {
        // tcpdump hex format bytes + decode
        // no ethernet first 10 bytes src dst and ipv4=0x0800

        // 23:07:11.963253 IP 128.73.68.166.50346 > 176.97.76.154.443: UDP, length 32
        // 0x0000:  4500 003c 403a 4000 3411 448c 8049 44a6  E..<@:@.4.D..ID.
        // 0x0010:  b061 4c9a c4aa 01bb 0028 ca07 e509 2117  .aL......(....!.

        //                         frag ttl  ch
        //           ip4 len  id   offs  udp sum  src ip
        // 0x0000:  4500 003c 403a 4000 3411 448c 8049 44a6  E..<@:@.4.D..ID.

        //           dst ip   srcp dstp len  sum
        // 0x0010:  b061 4c9a c4aa 01bb 0028 ca07 e509 2117  .aL......(....!.

        QStringList sl = rawData.split("\n");
        for (QString s : sl) {
            if (s.contains("UDP, length")) continue;
            s = s.trimmed();
            s.remove(0, 9);
            s = s.mid(0, 39);



            qDebug().noquote() << s;

            s.replace(" ", "");
            output.append(QByteArray::fromHex(s.toLatin1()));

        }

        // remove 28 bytes header
        output = output.mid(28);

        qDebug() << "\n";
        qDebug().noquote() << "size: " << output.size();

    }

    QUdpSocket udpSocket;
    udpSocket.writeDatagram(output, QHostAddress(ip), port);
}

