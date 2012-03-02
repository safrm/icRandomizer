/****************************************************************************
**
** Author: Miroslav Safr <miroslav.safr@gmail.com>
** Web: https://github.com/safrm/icRandomizer
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
#include <QtGui>
#include "icrandomizer.h"

QSize Randomizer::DefaultPictureSize(280, 280);
const QSize Randomizer::ResultSize(500,500);
const int Randomizer::UpdateTimeMs(500);
QString Randomizer::ImagesDir("images");
QString Randomizer::DefaultLogo(":/logo.png");

Randomizer::Randomizer():
  m_list(),
  m_iRandomCount(0),
  m_iPictureCounter(0),
  m_iPictureCountInDir(0)
{
    sourceButton = new QToolButton;
    sourceButton->setIconSize(DefaultPictureSize);
    connect(sourceButton, SIGNAL(clicked()), this, SLOT(chooseSourcePicture()));

    startButton = new QPushButton("Start Countdown");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startCountDown()));

    resetButton = new QPushButton("Reset");
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reload()));
    changeDirButton = new QPushButton(QDir(ImagesDir).absolutePath());
    connect(changeDirButton, SIGNAL(clicked()), this, SLOT(changeDir()));

    statusLabel = new QLabel;


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(sourceButton, 0, 0 , Qt::AlignVCenter |Qt::AlignHCenter );
    mainLayout->addWidget(startButton, 1, 0 );
    mainLayout->addWidget(resetButton, 2, 0 );
    mainLayout->addWidget(changeDirButton, 3, 0 );
    mainLayout->addWidget(statusLabel, 4, 0 , Qt::AlignHCenter);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(showNextImage()));

    setWindowTitle(tr("Image Randomizer [safrm.net]"));
    reload();
}

void Randomizer::chooseSourcePicture()
{
    if(timer->isActive()) //quick fix not to cheat :)
        return;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Source Picture"));
    if (!fileName.isEmpty())
        loadImage(fileName, &sourceImage, sourceButton);
}

void Randomizer::loadImage(const QString &fileName, QImage *image, QToolButton *button, bool bWinner)
{
    image->load(fileName);
    QImage fixedImage(DefaultPictureSize, QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(imagePos(*image), *image);
    painter.end();

    button->setIcon(QPixmap::fromImage(fixedImage));
    sourceButton->setIconSize(DefaultPictureSize);
    statusLabel->setText(QFileInfo(fileName).baseName());
    *image = fixedImage;
}

QPoint Randomizer::imagePos(const QImage &image) const
{
    return QPoint((DefaultPictureSize.width() - image.width()) / 2,
                  (DefaultPictureSize.height() - image.height()) / 2);
}

void Randomizer::startCountDown()
{
  //reload();
  m_iRandomCount = 10 + getRandomNumber(10);  //10 - 20 hits * 500ms =  5 - 10s
  m_iPictureCountInDir = m_list.size();
  m_iPictureCounter = 0;

  //no images found
  if(m_iPictureCountInDir<=0)
    return;

  timer->start(UpdateTimeMs);
  changeDirButton->setEnabled(false);
  startButton->setEnabled(false);
}

void Randomizer::showNextImage()
{
  if (m_iPictureCounter < m_iRandomCount) {
    changeImage(m_iPictureCountInDir);
    ++m_iPictureCounter;
  } else {
    timer->stop();
    changeImage(m_iPictureCountInDir, true);
    sourceButton->setIconSize(ResultSize);
    changeDirButton->setEnabled(true);
    startButton->setEnabled(true);
    centerWindow(true);
  }
}

void Randomizer::reload()
{
  timer->stop();
  changeDirButton->setEnabled(true);
  startButton->setEnabled(true);

  QDir dir(ImagesDir);
  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

  m_list = dir.entryInfoList();
  QFileInfo logoPict(ImagesDir + "/logo.png");
  if (logoPict.exists()) {
    m_list.removeOne(logoPict);
    QImage img(logoPict.absoluteFilePath());
    loadImage(logoPict.absoluteFilePath(), &sourceImage, sourceButton);
    DefaultPictureSize = img.size();
  } else {
    loadImage(DefaultLogo, &sourceImage, sourceButton);
    DefaultPictureSize = sourceImage.size();
  }
  sourceButton->setIconSize(DefaultPictureSize );

  centerWindow();
  statusLabel->setText(QString("loaded: ") + QString::number(m_list.size()) + QString(" images"));
}

int Randomizer::getRandomNumber(int iRange)
{
   if (iRange==0)
       return 0;

   static bool bSeed(false);
   if( !bSeed ) {
      qsrand(QTime::currentTime().msec());
      bSeed = true;
   }

  double dRand = rand();
  int iRandom = ((int)(dRand)  % iRange); //10-30s
  return  iRandom;
}

void Randomizer:: changeImage(int iCount, bool bWinner)
{
  int iRandomPic = getRandomNumber(iCount);
  QFileInfo fileInfo = m_list.at(iRandomPic);
  loadImage(fileInfo.absoluteFilePath(), &sourceImage, sourceButton, bWinner);
}

void Randomizer::centerWindow(bool bMax)
{
   adjustSize();
   move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

void Randomizer::changeDir()
{
    changeDirButton = new QPushButton(QDir(ImagesDir).absolutePath());
    QString newDir = QFileDialog::getExistingDirectory(this, tr("Choose Source Dir"));
    if (!newDir.isEmpty()) {
      ImagesDir = newDir;
      changeDirButton->setText(ImagesDir);
      reload();
    }
}
