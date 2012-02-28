#ifndef Randomizer_H
#define Randomizer_H

#include <QPainter>
#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QToolButton;
class QTimer;
class QString;
QT_END_NAMESPACE

class Randomizer : public QWidget
{
    Q_OBJECT

public:
    Randomizer();

private slots:
    void startCountDown();
    void showNextImage();
    void reload();
    int getRandomNumber(int iRange);
    void changeImage(int iCount, bool bWinner=false);
    void chooseSourcePicture();
    void changeDir();

private:
    void loadImage(const QString &fileName, QImage *image, QToolButton *button, bool bWinner = false);
    QPoint imagePos(const QImage &image) const;
    void centerWindow(bool bMax = false);

    static QSize DefaultPictureSize; //it is updated according 1st picture in folder
    static const QSize ResultSize;
    static const int UpdateTimeMs;
    static QString ImagesDir;
    static QString DefaultLogo;

    QToolButton *sourceButton;
    QPushButton *startButton;
    QPushButton *resetButton;
    QPushButton *changeDirButton;
    QFileInfoList m_list;
    QLabel *statusLabel;
    QImage sourceImage;
    QTimer* timer;
    int  m_iRandomCount;
    int  m_iPictureCounter;
    int  m_iPictureCountInDir;
};

#endif
