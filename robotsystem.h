#ifndef ROBOTSYSTEM_H
#define ROBOTSYSTEM_H

#include <basic_helper.h>

const int limitmegaread = 1048576 / 2 ; /// 1/2 mega

/* write a file to utf-8 format */
static inline bool fwriteutf16(QString fullFileName,QString xml)
{
    if (fullFileName.contains("/", Qt::CaseInsensitive)) {
        QString ultimacartellaaperta = fullFileName.left(fullFileName.lastIndexOf("/"))+"/";
        QDir dira(ultimacartellaaperta);
        if ( dira.mkpath(ultimacartellaaperta) ) { } else {
        return false;
        }
    }
        QTextCodec *codecx;
        codecx = QTextCodec::codecForMib(106);
        QFile f( fullFileName );
        if ( f.open( QFile::WriteOnly | QFile::Text ) )
        {
        QTextStream sw( &f );
        sw.setCodec(codecx);
        sw << xml;
        f.close();
        return true;
        }
        return false;
}


namespace IndexDisk {


class Robotsystem
{
public:
    Robotsystem( const QString Followdir ,  const QString extension = "pdf"  );
    int foundTotalFile() {
      return Filefinded;
    }
    QStringList foundFile() { return FoundResults; }
private:
    QString EXTENSION;
    void followOneDir( const QString &namepathfull );
    bool RecordAppend( const QString &name , const int &typex );
    QStringList SystemDIRS;
    QStringList FoundResults;
    QString SystemNAME;
    int Dirscount;
    int Filefinded;
    int MODUS_READ;

};


}

#endif // ROBOTSYSTEM_H
