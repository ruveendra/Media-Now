#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QVBoxLayout>
#include <QMediaPlaylist>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_sliderVolume_sliderMoved(int position);

    void on_btn_play_clicked();

    void on_btn_stop_clicked();

    void on_btn_pause_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_actionAdd_Media_triggered();



    void on_btnMute_clicked();

    void on_comboBox_activated(int index);

    void on_btn_next_clicked();

    void on_btn_previous_clicked();

    void on_actionactionAddPlaylist_triggered();

    void on_btn_shuffle_clicked(bool checked);

    void on_pushButton_clicked(bool checked);

private:
    void SetTimeLabel();
private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* bar;
    QSlider* slider;
    QVBoxLayout* layout;
    QMediaPlaylist* playlist;
};
#endif // MAINWINDOW_H
