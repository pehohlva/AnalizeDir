#ifndef BASIC_HELPER_H
#define BASIC_HELPER_H

#include <QCoreApplication>
#include <QObject>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QDir>
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QDirIterator>
#include <QStorageInfo>
#include <QCryptographicHash>


#if defined(Q_OS_SYMBIAN)
#include <f32file.h>
#elif defined(Q_OS_WIN)
#include <windows.h>
#elif defined(Q_OS_MAC)
/// separate on conflict
#endif

#if defined(Q_OS_UNIX)
#if !defined(Q_OS_MAC)
#include <sys/vfs.h>
#endif

#endif

#if defined(Q_OS_MAC)
#include <sys/param.h>
#include <sys/mount.h>
#endif



const int dotslong = 76;

static bool invalidname(const QString pwd) {
    if (pwd.indexOf("/.Trash") > -1) {
        return false;
    }
    if (pwd.indexOf(".app") > -1) {
        return false;
    }
    if (pwd.indexOf("/.git") > -1) {
        return false;
    }
    if (pwd.indexOf("/.svn") > -1) {
        return false;
    }
    if (pwd.indexOf("/.DS_Store") > -1) {
        return false;
    }
    return true;
}

static QString bytesToSize(const qint64 size) {
    if (size < 0)
        return QString();
    if (size < 1024)
        return QObject::tr("%1 B").arg(QString::number(((double) size), 'f', 0));
    if ((size >= 1024) && (size < 1048576))
        return QObject::tr("%1 KB").arg(QString::number(((double) size) / 1024, 'f', 0));
    if ((size >= 1048576) && (size < 1073741824))
        return QObject::tr("%1 MB").arg(QString::number(((double) size) / 1048576, 'f', 2));
    if (size >= 1073741824)
        return QObject::tr("%1 GB").arg(QString::number(((double) size) / 1073741824, 'f', 2));
    return QString();
}


static QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result().toHex();
        }
    }
    return QByteArray();
}



namespace SystemSecure {
    /// SystemSecure::freespaceonHome()
    QString bytesToSize(const qint64 size);
    qint64 FreespaceonDir(const QString selectdir);
    static inline QString freespaceonHome() {
        return bytesToSize(FreespaceonDir(QDir::homePath()));
    }
}



class Basic_Helper : public QObject
{
  Q_OBJECT
public:
  explicit Basic_Helper(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BASIC_HELPER_H
