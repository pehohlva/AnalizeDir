



#include <QCoreApplication>
#include "robotsystem.h"


const int pointo = 76;
#define __DOCVERSION__ \
              QString("Ve.0.1.1")

#define __APPNAME__ \
              QString("Disk_Reader")

// dotslong sono i punti da fare.....

static void usagethisapp(const char *name, int size) {

    QString hdir = QDir::homePath();
    printf("Usage: %s (Options)  \n", name);
    printf(" {%d} Options:\n", size);
    printf("\t--set or -s pdf ... : Set file extension to read by disk. \n");
    printf("\t--dir or -d /Users/ ... : Set dir to begin read on by disk. Default init on %s \n",datain(hdir));
    printf("\t--version or -V: show the version of conversion used\n");
    printf("\t--help or -h: display this text.\n");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);
    QString fname;
    QTextStream cin(stdin);
    QString nameout;
    QString namedirbeginn;
    QString str("*");
    QStringList dirlistener = a.arguments();
    QTime myTimer;
    myTimer.start();
    int i;
       if (argc <= 1) {
           usagethisapp(argv[0], argc);
           return (1);
       }

       for (i = 1; i < argc; i++) {
           //// parse arguments
                   if ((!strcmp(argv[i], "-V")) ||
                           (!strcmp(argv[i], "--version")) ||
                           (!strcmp(argv[i], "-v"))) {
                       out << str.fill('*', pointo) << "\n";
                       out << __APPNAME__ << ":" << __DOCVERSION__ << "\n";
                       out << str.fill('*', pointo) << "\n";
                       out.flush();
                       return (1);
                   } else if ((!strcmp(argv[i], "--help")) || !strcmp(argv[i], "-h")) {
                       usagethisapp(argv[0], argc);
                       return (1);
                   } else if ((!strcmp(argv[i], "--set")) || !strcmp(argv[i], "-s")) {
                       int namer = i + 1;
                                   if (argc >= namer) {
                                       nameout = dirlistener.at(namer);
                                       nameout.toLower();
                                   }

                   }  else if ((!strcmp(argv[i], "--dir")) || !strcmp(argv[i], "-d")) {
                       int namer = i + 1;
                                   if (argc >= namer) {
                                       namedirbeginn = dirlistener.at(namer);
                                       namedirbeginn.prepend("/");
                                       QDir dselect(namedirbeginn);
                                       namedirbeginn.clear();
                                       if ( dselect.isReadable()) {
                                           namedirbeginn = dselect.absolutePath();
                                         }
                                   }

                   }

         }
        out << str.fill('&',dotslong) << "\n";
        out << "FreeSpace home:" << SystemSecure::freespaceonHome() << "\n";
        out << "Vediamo come procede... \n";
        out << str.fill('&',dotslong) << "\n";
        out.flush();

        if (nameout.isEmpty() ) {
            nameout = QString("pdf");
          }
        if (namedirbeginn.size() > 2 ) {
             //// ok run on dir namedirbeginn
          } else {
            namedirbeginn = QDir::homePath();
          }
        IndexDisk::Robotsystem *treedir = new IndexDisk::Robotsystem(namedirbeginn,nameout);
            out << "\n";
            out << "\n";
        const int found = treedir->foundTotalFile();
        QString founditemstream =  treedir->foundFile().join("\n");
        //// first method = 278 sec.  /// 203 la seconda ... 293odt
        int nseconds = myTimer.elapsed() / 1000;
            out << "Trovati totale: ";
            out << found << " Timesec:" << nseconds <<   "\n";
            out << "\n";
            out << "\n";
            out << "Salva in file? Save to file result? filename: " << "\n";
            out << "\n";
            fname = cin.readLine();
            out << "\n";
            out << "\n";
            ///// out << "save to: " << fname;
            if (fname.size() > 2 ) {
                if (fwriteutf16(fname,founditemstream)) {
                    out << "save to: " << fname;
                  }
              } else {
                out << "remove results..\n ";
              }
            out << "\n";
            out.flush();
            a.deleteLater();
            return 0;
        return a.exec();
}
