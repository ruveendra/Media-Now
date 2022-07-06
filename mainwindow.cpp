#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist;
    vw = new QVideoWidget(this);
    layout = new QVBoxLayout();

    layout->addWidget(vw);
    ui->groupBox_2->setLayout(layout);
    player->setVideoOutput(vw);

// Connections made with the slider to track the progress of the playback
    connect(player, &QMediaPlayer::durationChanged,this,&MainWindow::on_durationChanged);
    connect(player, &QMediaPlayer::positionChanged,this,&MainWindow::on_positionChanged);



}

MainWindow::~MainWindow()
{
    delete ui;
}

// Open media file
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File (*.*)");
    on_actionStop_triggered();

    player -> setMedia(QUrl::fromLocalFile(filename));
    on_actionPlay_triggered();

}


void MainWindow::on_actionPlay_triggered()
{
    player->play();


    ui -> statusBar ->showMessage("Video is Playing");

}


void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui -> statusBar ->showMessage("Video is Paused");
    this->SetTimeLabel();
}


void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui -> statusBar ->showMessage("Video is Stopped");
}

// Volume Control
void MainWindow::on_sliderVolume_sliderMoved(int position)
{
    player -> setVolume(position);
    if(position == 0){
        ui->btnMute->setIcon(QIcon(":/images/Mute_48px.png"));
    }else{
        ui->btnMute->setIcon(QIcon(":/images/Voice_48px.png"));
    }
}

//Play Function
void MainWindow::on_btn_play_clicked()
{
    player->play();
    ui -> statusBar ->showMessage("Video is Playing");
}

// Stop Function
void MainWindow::on_btn_stop_clicked()
{
    player->stop();
    ui -> statusBar ->showMessage("Video is Stopped");
}
// Pause Function

void MainWindow::on_btn_pause_clicked()
{
    player->pause();
    ui -> statusBar ->showMessage("Video is Paused");
}

//Seek Bar Position
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}
//Seek Bar Position Change in GUI
void MainWindow::on_positionChanged(qint64 position)
{
    ui -> horizontalSlider->setValue(position);
}

//Duration time is taken once the file has finished loading
void MainWindow::on_durationChanged(qint64 position)
{
    ui -> horizontalSlider->setMaximum(position);
    this->SetTimeLabel();
}

// Time Label (Media Duration)
void MainWindow::SetTimeLabel()
{
    qint64 dura = player->duration();

    qint64 seconds = (dura/1000) % 60;
    qint64 minutes = (dura/60000) % 60;
    qint64 hours = (dura/3600000) % 24;

    QTime time(hours, minutes,seconds);

    ui->time_label->setText(time.toString());

}

// Add Playlist

void MainWindow::on_actionAdd_Media_triggered()
{

    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File","","Video File(*.*)");

    for(int i =0;i<filenames.size();++i){
        playlist->addMedia(QUrl::fromLocalFile(filenames[i]));
    }
    playlist->setCurrentIndex(0);
    player->setPlaylist(playlist);
    on_actionPlay_triggered();

}

//Mute button
void MainWindow::on_btnMute_clicked()
{
    player->setVolume(0);
    ui->sliderVolume->setSliderPosition(0);
    ui->btnMute->setIcon(QIcon(":/images/Mute_48px.png"));
}

// Playback Rate
void MainWindow::on_comboBox_activated(int index)
{
    {
        qreal rate = 0;
        switch (index) {
            case 0:
            {
                rate = 1;
                break;
            }
        case 1:
            {
                rate = 0.5;
                break;
            }
        case 2:
            {
                rate = 2;
                break;
            }
        }
            player->setPlaybackRate(rate);
    }
}

// Playlist Navigation Next
void MainWindow::on_btn_next_clicked()
{
    playlist->next();
}

//Playlist Navigation Previous
void MainWindow::on_btn_previous_clicked()
{
    playlist->previous();
}

//Add Playlist
void MainWindow::on_actionactionAddPlaylist_triggered()
{
    on_actionAdd_Media_triggered();
}

// Shuffle Function
void MainWindow::on_btn_shuffle_clicked(bool checked)
{
    ui->btn_shuffle->setCheckable(true);

    if(checked){

        playlist->shuffle();
    }

}
// Playback modes for the playlist (Loop & Sequenstial)
void MainWindow::on_pushButton_clicked(bool checked)
{
    ui->pushButton->setCheckable(true);
    if(checked==true){

        playlist->setPlaybackMode(QMediaPlaylist::Loop);


    }
    else {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }

}

