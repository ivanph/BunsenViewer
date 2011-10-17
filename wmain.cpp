#include "wmain.h"
#include <QFile>
#include <QDebug>
#include <QTime>

WMain::WMain(QWidget *parent) :
    QDeclarativeView(parent)
{
    m_context = rootContext();
    m_context->setContextProperty("WMain", this);

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    netAccessMan = new QNetworkAccessManager(this);
    connect(netAccessMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));

    download("http://www.heroeslocales.com/bunsen/comics/");

#if defined(Q_WS_MAEMO_5)
    setSource(QUrl("/opt/bunsenviewer/qml/bunsenviewer/main.qml"));
    setWindowState(Qt::WindowFullScreen);
#else
    setSource(QUrl("qml/bunsenviewer/main.qml"));
#endif
}

void WMain::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
	const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
	if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
	    qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
	    return;
	}
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
	attribute = static_cast<Qt::WidgetAttribute>(128);
	break;
    case ScreenOrientationLockLandscape:
	attribute = static_cast<Qt::WidgetAttribute>(129);
	break;
    default:
    case ScreenOrientationAuto:
	attribute = static_cast<Qt::WidgetAttribute>(130);
	break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
	attribute = Qt::WA_LockPortraitOrientation;
	break;
    case ScreenOrientationLockLandscape:
	attribute = Qt::WA_LockLandscapeOrientation;
	break;
    default:
    case ScreenOrientationAuto:
	attribute = Qt::WA_AutoOrientation;
	break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void WMain::quit(){
    exit(0);
}

void WMain::next(){
    if (index+1<list.count()){
	index=index+1;
	m_context->setContextProperty("CurrentImage", QString(list.at(index)));
    }

    qDebug() << list.at(index);
}

void WMain::first(){
    if (list.count()>1){
	index=0;
	m_context->setContextProperty("CurrentImage", QString(list.at(index)));
    }
}


void WMain::random(){

    QTime time = QTime::currentTime();
    srand (time.msec ());
    index=rand() % list.count();
    m_context->setContextProperty("CurrentImage", QString(list.at(index)));

    qDebug() << list.at(index);
}


void WMain::previous(){
    if (index>0){
	index=index-1;
	m_context->setContextProperty("CurrentImage", QString(list.at(index)));
    }
}

void WMain::download(QString item){
    QUrl url(item);
    QNetworkRequest request(url);
    netAccessMan->get(request);
}

void WMain::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left) {
        previous();
    }

    if (event->key() == Qt::Key_Right){
        next();
    }

}

void WMain::downloadFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
	reply->deleteLater();
	return;
    }
    QVariant redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (redir.isValid()) {
	QUrl url = redir.toUrl();
	if (url.isRelative()) {
	    url.setScheme(reply->url().scheme());
	    url.setEncodedHost(reply->url().encodedHost());
	}
	QNetworkRequest req(url);
	netAccessMan->get(req);
	reply->deleteLater();
	return;
    }

    downloadedItem = reply->readAll();
    //qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
    if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("text/html")){
	QString links=downloadedItem;
	links=links.mid(links.indexOf("Parent Directory</a> ")+21);
	links.remove(links.indexOf("<a href=\"dlf/"),links.length()-links.indexOf("<a href=\"remix/"));



	while(links.contains("<a href=")){
	    int linkStarts=links.indexOf("<a href=\"")+9;
	    int sizeOfLink=links.indexOf("\"",linkStarts)-linkStarts;
	    list.append("http://www.heroeslocales.com/bunsen/comics/"+links.mid(linkStarts,sizeOfLink));
	    links=links.mid(linkStarts);
	}

	index=list.count()-1;
	m_context->setContextProperty("CurrentImage", QString(list.at(index)));
    }
    reply->deleteLater();
}


