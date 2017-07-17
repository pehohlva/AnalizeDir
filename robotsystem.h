#ifndef ROBOTSYSTEM_H
#define ROBOTSYSTEM_H

#include <basic_helper.h>

const int limitmegaread = 1048576 / 2 ; /// 1/2 mega


namespace IndexDisk {


class Robotsystem
{
public:
    Robotsystem( const QString Followdir ,  const QString extension = "pdf"  );
    int foundTotalFile() {
      return Filefinded;
    }

private:
    QString EXTENSION;
    void followOneDir( const QString &namepathfull );
    bool RecordAppend( const QString &name , const int &typex );
    QStringList SystemDIRS;
    QString SystemNAME;
    int Dirscount;
    int Filefinded;
    int MODUS_READ;

};


}

#endif // ROBOTSYSTEM_H
