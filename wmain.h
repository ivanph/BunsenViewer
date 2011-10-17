#ifndef WMAIN_H
#define WMAIN_H

#include <QDeclarativeItem>
#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QNetworkReply>
#include <QKeyEvent>
#include <QEvent>

class WMain : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit WMain(QWidget *parent = 0);
    enum ScreenOrientation {
	ScreenOrientationLockPortrait,
	ScreenOrientationLockLandscape,
	ScreenOrientationAuto
    };

signals:


public slots:
    void setOrientation(ScreenOrientation orientation);
    void quit();
    void next();
    void previous();
    void first();
    void random();

protected slots:
    void keyPressEvent(QKeyEvent *event);


private slots:
    void download(QString item);
    void downloadFinished(QNetworkReply *reply);


private:
    QDeclarativeContext *m_context;
    QDeclarativeEngine *qmlEngine;
    QNetworkAccessManager *netAccessMan;
    QByteArray downloadedItem;
    QStringList list;
    int index;

};

#endif // WMAIN_H
