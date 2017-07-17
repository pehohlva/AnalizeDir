#include "robotsystem.h"



namespace IndexDisk {



Robotsystem::Robotsystem(const QString Followdir , const QString extension)
{
   EXTENSION = extension.toLower();
   QTextStream out(stdout);
   SystemDIRS.clear();
   Dirscount = 0;
   Filefinded = 0;
   MODUS_READ = 2;
   //// MODUS_READ 1 only dirs
   /// MODUS_READ  2 only file
   /// MODUS_READ  3 big file
   ///
   //// out = new QTextStream(stdout);

   QStorageInfo storage = QStorageInfo::root();

       qDebug() << "QD root " <<  storage.rootPath();
       if (storage.isReadOnly()) {
           qDebug() << "QD isReadOnly:" << storage.isReadOnly();
       }


       qDebug() << "QD fileSystemType:" << storage.fileSystemType();
       qDebug() << "QD device:" << storage.device();
       qDebug() << "QD name:" << storage.name();
       qDebug() << "QD size:" << bytesToSize(storage.bytesTotal()) ;
       qDebug() << "QD availableSize:" << bytesToSize(storage.bytesAvailable());



   if (storage.name() == "osx") {
       ////  Followdir = storage.rootPath();
   }
   QDir hdir(Followdir);

               if (hdir.exists() && hdir.makeAbsolute()) {
                   out << "Dir Handle:" << hdir.absolutePath();
                   out << "\n";
                   out.flush();
                   //// if (RecordAppend(hdir.absolutePath(),0)) {
                       /// out << "END Dir Handle:" << hdir.absolutePath();
                       /// out << "\n";
                       /// out.flush();
                   ///// }
                   this->followOneDir(hdir.absolutePath());
               }
}

void Robotsystem::followOneDir( const QString &namepathfull ) {
  QTextStream out(stdout);
  QDirIterator dirIt(namepathfull,QDirIterator::Subdirectories);
  while (dirIt.hasNext()) {
            dirIt.next();
            if (!dirIt.filePath().isNull()) {
                Dirscount++;
                QString spaceholder;
                spaceholder.fill(QChar('.'),120);
                QString fdirx = dirIt.filePath();
                QStringList piecesdir = fdirx.split( "/" );
                QString DirIndex= QString("Read %1:").arg(Dirscount);
                if ( piecesdir.size() > 4 ) {
                  QString linewritteln = DirIndex + QString(" /") + piecesdir.at(3) + spaceholder;
                  linewritteln.resize(40);
                    out <<  linewritteln << "\r";
                } else if ( piecesdir.size() == 1 ) {
                    QString linewritteln = DirIndex + QString(" /") + piecesdir.at(0)  + spaceholder;
                    linewritteln.resize(40);
                    out << linewritteln  << "\r";
                } else if ( piecesdir.size() == 2 ) {
                    QString linewritteln = DirIndex + QString(" /") + piecesdir.at(1)  + spaceholder;
                    linewritteln.resize(40);
                    out << linewritteln  << "\r";
                }

              }
                if (QFileInfo(dirIt.filePath()).isFile()) {
                    if (QFileInfo(dirIt.filePath()).suffix() == EXTENSION ) {
                         Filefinded++;
                         const qint64 sizefullfromfile = dirIt.filePath().size();
                         out << Filefinded << " > " <<  dirIt.filePath()  << ".\n";
                         out.flush();
                         /// qDebug()<<dirIt.filePath();
                      }
                }
    }
}

bool Robotsystem::RecordAppend( const QString &name, const int &typex )
{
   QTextStream out(stdout);
   /// append only on SystemDIRS .. real dir
   SystemDIRS.append(name);   /// only dirs!
   int state = typex;
       state++;
       Dirscount++;

   bool result = true;
   QDir dir(name);
   QString DirIndex= QString("Read %1:").arg(Dirscount);
   QStringList piecesdir = dir.absolutePath().split( "/" );
   QDateTime timerx(QDateTime::currentDateTime());
   const QString NameTime = timerx.toString("dd.MM.yyyy-HH:mm:ss:zzz");
   if (MODUS_READ == 3) {
         //// read only dir out!
          out << "Reader " << Dirscount << "-" << state <<  " on Handle:" <<
          dir.absolutePath() << " :  " <<
          NameTime;
   out << "\n";
   out.flush();
   }
       if ( piecesdir.size() > 4 ) {
         out << DirIndex << " /" <<  piecesdir.at(3)  << ".\r";
       } else if ( piecesdir.size() == 1 ) {
         out << DirIndex << " /" <<  piecesdir.at(0)  << ".\r";
       } else if ( piecesdir.size() == 2 ) {
         out << DirIndex << " /" <<  piecesdir.at(1)  << ".\r";
       }

   Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
              if (info.isDir() && !info.isHidden()) {
                  if (invalidname(info.absoluteFilePath())) {
                    result = RecordAppend(info.absoluteFilePath(),state);
                  }
              } else if (info.isSymLink()) {

                  /// out << "Sy: " << info.fileName(); /////  << " to: " << info.symLinkTarget()  ;
                  /// out << "\n";
                  //// out.flush();

              } else if (info.isFile()) {
                  const qint64 sizefullfromfile = info.size();

                  if (sizefullfromfile > 0) {
                      //// handle
                      if (sizefullfromfile <  limitmegaread  && EXTENSION == info.completeSuffix() ) {
                          //// read only 500 kb file
                          Filefinded++;
                          const QString FilenameFullPath = dir.absolutePath() + "/" + info.fileName();
                          //// const QByteArray qsums = fileChecksum(FilenameFullPath,QCryptographicHash::Sha256);
                          out << "Parse file : " << bytesToSize(sizefullfromfile); ////  << " - " << qsums  ;
                          //// out << "\n";
                          out << " " << Filefinded << " " << info.fileName() <<  "\n";
                          out.flush();

                      }
                  }
                  //// const QString FilenameFullPath = dir.absolutePath() + "/" + info.fileName();
                  ///// result = appendFilename(info, info.absolutePath());
              }
          }

     return result;
}


} /// end namenspace IndexDisk







