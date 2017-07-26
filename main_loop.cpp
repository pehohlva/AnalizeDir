
#include <QApplication>
#include <QMenu>
#include <QPushButton>
#include <QWidgetAction>
#include <QProgressBar>
#include <QSystemTrayIcon>
#include <QStyle>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QString>
#include <QKeySequence>
#include <QObject>
#include <QDebug>
#include <QDesktopWidget>
#include <QIcon>
#include <QPushButton>
#include <QLabel>
#include <QCursor>
#include <QEvent>
#include <QPoint>
#include <QDialog>
#include <QWidget>
#include <QTimer>
#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>


static inline QString QTR( const QString t ) {
   QString newone("translate:");
   return newone.append(t);
}



class MainWin : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWin(QWidget *parent = 0);
  void closeEvent (QCloseEvent *event);

signals:
    void request_to_close();
public slots:
};

MainWin::MainWin(QWidget *parent) : QMainWindow(parent) { }

void MainWin::closeEvent (QCloseEvent *event) {
    event->ignore();
    emit request_to_close();
}


#define mainapp \
    (static_cast<MainApp*>(QCoreApplication::instance()))


class MainApp : public QApplication
{
  Q_OBJECT
    public:
    MainApp(int &argc, char **argv);
    signals:
         void signalFileOpen( const QString &f );
         void eventLog( const QString &text );
    public slots:
         void updateCaption();
         void show_hide();
         void aboutQt();
         void closeAllWindows();
         void continue_question();
         void consolelog(QString);
    protected:
         /// static void closeAllWindows();
         /// static void aboutQt();

    bool event (QEvent *event);

    void build_Menu();
    void makemain_wide();
    private:
      QIcon basicico;
      QMenu *menu;
      QSystemTrayIcon *TraySet;
      int loopjack;
       MainWin *win;
      QPlainTextEdit *happy;
};

void MainApp::aboutQt() {
   qDebug() << "MainApp::aboutQt";
   //// QApplication::aboutQt();
}

void MainApp::continue_question() {
   QMessageBox::StandardButton resBtn = QMessageBox::question(win,QTR("Bullino"),
                                                               QTR("Are you sure to quit job?\n"),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Cancel);
    const int permission = (int)resBtn;
    //// qDebug() << "MainApp::aboutToQuit risposta:" << permission;
    if ( permission == 16384 ) {
       QApplication::quit();
       return;
    }
    this->show_hide();
    emit eventLog(QTR("Continue for action on your disk.... "));
}

void MainApp::updateCaption() {
    loopjack++;
    QString current = QString("null");
    if (loopjack%2==0) {
        current = QString("pari");
        TraySet->setIcon(basicico);
    } else {
        current = QString("dispari");
        TraySet->setIcon(QIcon(this->style()->standardIcon(QStyle::SP_DirHomeIcon)));
    }
    if (TraySet->isSystemTrayAvailable()) {
        QString messagetit = QString(QTR("App Test..")) + QString(" ") + loopjack;
        TraySet->show();
        TraySet->setVisible(true);
        //// TraySet->showMessage(messagetit,QTR("Application wait your input... "),QSystemTrayIcon::Warning,3000);
        const int sec_handle = 1000 * 1; /// 1 sec.
        QTimer::singleShot(sec_handle, this, SLOT(updateCaption()));
        emit eventLog(QTR("App updateCaption wait %1..").arg(loopjack) + current );
    }
}

void MainApp::build_Menu() {
  loopjack = 0;
  basicico = QIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
  TraySet = new QSystemTrayIcon(basicico,this);
  TraySet->setVisible(true);
  TraySet->setToolTip(QTR("System Tray Example "));
  menu = new QMenu();
  menu->setTitle(QTR("mac_spot_search"));
  menu->setToolTipsVisible(true);

  QAction *opendialogconfig = new QAction(QTR("Show/Hide Events Results"), this);
  opendialogconfig->setIcon(basicico);
  opendialogconfig->setStatusTip(QTR("Display running event.."));
  QObject::connect(opendialogconfig, SIGNAL(triggered()),this, SLOT(show_hide()));
  menu->addAction(opendialogconfig);

  QAction *aboutqt = new QAction(QTR("About QT apps"), this);
  aboutqt->setIcon(basicico);
  aboutqt->setStatusTip(QTR("About QT apps"));
  QObject::connect(aboutqt, SIGNAL(triggered(bool)),this, SLOT(aboutQt()));
  menu->addAction(aboutqt);

  QAction *apquit = new QAction(QTR("Quit"),this);
  apquit->setShortcut(QKeySequence::Open);
  apquit->setStatusTip(QTR("Quit Aplication"));
  apquit->setIcon(basicico);
  connect(apquit,SIGNAL(triggered(bool)),this,SLOT(continue_question()));
  menu->addAction(apquit);
  menu->setAsDockMenu();
  TraySet->setContextMenu(menu);
  TraySet->show();
  QTimer::singleShot(1000, this, SLOT(updateCaption()));
}

void MainApp::show_hide() {
   //// qDebug() << "MainApp::show_hide";
   if (win->isHidden()) {
      win->show();
      win->activateWindow();
      win->raise();
    } else {
       win->hide();
     }
}

void MainApp::makemain_wide() {
  win = new MainWin();
  happy = new QPlainTextEdit();
  happy->setMinimumSize(450,450);
  happy->setPlainText(QTR("Lorem ipsum ... "));
  win->setCentralWidget(happy);
  win->hide();
  connect(win,SIGNAL(request_to_close()),this,SLOT(continue_question()));
}

 void MainApp::closeAllWindows() {
    qDebug() << "MainApp::closeAllWindows";
 }
 void MainApp::consolelog( QString t ) {
    qDebug() << "MainApp::consolelog:" << t;
 }
/*
void MainApp::closeEvent (QCloseEvent *event) {
   qDebug() << "MainApp::closeEvent";
   event->ignore();
}
*/
bool MainApp::event (QEvent *event)
   {
        qDebug() << "MainApp::event:" << event->type();
        const int screenactive = this->desktop()->screenCount();
        QString text;
        text.clear();
        text.append("\nEventLog: ");
        text.append(QString("screen count %1 .").arg(screenactive)  );
        text.append(QString("type event %1 .").arg( event->type() ) );
        emit eventLog(text);

       if (event->type() == QEvent::FileOpen) {
       const QString  file_path = static_cast<QFileOpenEvent *> (event)->file();
       emit this->signalFileOpen(file_path);
       emit eventLog(QString(" \nEvent file open: ") + file_path);
       } else {
         return QApplication::event (event);  /// default
       }
       return true;
   }


/// ########################################################## ///

   MainApp::MainApp(int &argc, char **argv) : QApplication(argc,argv)
{
        //// this->setQuitLockEnabled(true);
        this->setQuitOnLastWindowClosed(false);
        this->makemain_wide();
        this->build_Menu();
     QObject::connect(this, SIGNAL(eventLog(QString)),this, SLOT(consolelog(QString)));
     QObject::connect(this, SIGNAL(eventLog(QString)),happy, SLOT(appendPlainText(QString)));
     ///// loop -> QObject::connect(this, SIGNAL(lastWindowClosed()),this, SLOT(continue_question()));

}
   /// ########################################################## ///
   /// \brief main
   /// \param argc
   /// \param argv
   /// \return
   ///
   ///


int main(int argc, char **argv)
{
    MainApp apps(argc, argv);
    return apps.exec();
}

#include "main.moc"

/*
 *
 qmake pro file for this sample to indexing file app continue to live not quit event!
 # ///// mac_spot_search.pro

QT       += core gui

# not put file on dir from Git or Subversion!!
MOC_DIR = zz_buildtoday
RCC_DIR = zz_buildtoday
OBJECTS_DIR = zz_buildtoday
# not put file on dir from Git or Subversion!!

# if main.cpp include main.moc
INCLUDEPATH += $$PWD/zz_buildtoday

QT += widgets

TARGET = xx

CONFIG   -= app_bundle
#macx:TEMPLATE = app

macx {
HiView_SIGNATURE = HiHV
CONFIG += c++11
CONFIG += QMAKE_CXXFLAGS_WARN_ON=-w QMAKE_CFLAGS_WARN_ON=-w
LIBS += -lz
DEFINES += QT_DEPRECATED_WARNINGS
}


SOURCES += main.cpp
# a_config.h
# HEADERS +=
  */
