#include "basic_helper.h"

Basic_Helper::Basic_Helper(QObject *parent) : QObject(parent)
{
   /// do nothing
}


namespace SystemSecure {



QString bytesToSize(const qint64 size) {
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

 qint64 FreespaceonDir(const QString selectdir) {

#if !defined(Q_OS_WIN)
        struct statfs stats;
        statfs(selectdir.toLocal8Bit(), &stats);
        unsigned long long bavail = ((unsigned long long) stats.f_bavail);
        unsigned long long bsize = ((unsigned long long) stats.f_bsize);
        return (qint64) (bavail * bsize);
#else
        // MS recommend the use of GetDiskFreeSpaceEx, but this is not available on early versions
        // of windows 95.  GetDiskFreeSpace is unable to report free space larger than 2GB, but we're
        // only concerned with much smaller amounts of free space, so this is not a hindrance.
        DWORD bytesPerSector(0);
        DWORD sectorsPerCluster(0);
        DWORD freeClusters(0);
        DWORD totalClusters(0);
        if (::GetDiskFreeSpace(selectdir.utf16(), &bytesPerSector, &sectorsPerCluster, &freeClusters, &totalClusters) == FALSE) {
            qWarning() << "Unable to get free disk space on:" << selectdir;
        }
        return (qint64) ((bytesPerSector * sectorsPerCluster * freeClusters) > boundary);
#endif
        return 0;
  }

 }  //// end namenspace
