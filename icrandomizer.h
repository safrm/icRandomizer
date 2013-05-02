/****************************************************************************
**
** Author: Miroslav Safr <miroslav.safr@gmail.com>
** Web: http://safrm.net/projects/icRandomizer
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
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
