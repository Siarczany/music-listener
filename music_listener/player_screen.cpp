#include "player_screen.h"
#include "ui_player_screen.h"

#include <QSqlQuery>

PlayerScreen::PlayerScreen(QWidget *parent, QSqlDatabase* database, bool isGuest, int userId, int playlistId) :
    QWidget(parent),
    ui(new Ui::player_screen)
    , database(database)
    , isGuest(isGuest)
    , userId(userId)
    , playlistId(playlistId)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0);

    playlistInfoQuery();
    songInfoQuery();

    connect(ui->volume_s, &QSlider::valueChanged, this, &setVolume);
    connect(ui->pause_pb, &QPushButton::clicked, this, &pause);
    connect(ui->play_pb, QPushButton::clicked, this, &resume);
    connect(ui->next_pb, QPushButton::clicked, this, &nextSong);
    connect(ui->previous_pb, &QPushButton::clicked, this, &previousSong);
    connect(player, &QMediaPlayer::positionChanged, this, &updateSongSlider);
    connect(ui->songProgress_s, &QSlider::sliderPressed, this, sliderPressed);
    connect(ui->songProgress_s, &QSlider::sliderReleased, this, sliderReleased);
    connect(player, &QMediaPlayer::positionChanged, this, [this](){
        qDebug() << player->position();
    });

    connect(player, &QMediaPlayer::mediaStatusChanged, this, playerStatusChanged);
}

PlayerScreen::~PlayerScreen()
{
    delete ui;
}

void PlayerScreen::playlistInfoQuery()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "    name, "
        "    COUNT(*) AS song_count "
        "FROM playlists "
        "JOIN playlist_contents "
        "    ON playlists.id = playlist_contents.playlist "
        "WHERE playlists.id = (?) "
        "GROUP BY playlists.id"
        );
    query.bindValue(0, playlistId);

    if(!query.exec())
    {
        qDebug() << "error or osmething idk xd";
        return;
    }
    if(query.next())
    {
        ui->playlist_l->setText(query.value(0).toString());

        playlistSize = query.value(1).toInt();
    }
}

void PlayerScreen::songInfoQuery()
{
    QSqlQuery query;
    query.prepare(
        "SELECT "
        "    songs.name, "
        "    authors.name, "
        "    songs.filename, "
        "    songs.id "
        "FROM playlist_contents "
        "JOIN songs "
        "    ON playlist_contents.song = songs.id "
        "JOIN authors "
        "    ON songs.author = authors.id "
        "WHERE playlist_contents.playlist = (?) "
        "ORDER BY playlist_contents.id "
        "LIMIT 1 "
        "OFFSET (?)"
        );
    query.bindValue(0, playlistId);
    query.bindValue(1, currentSongNumber % playlistSize);

    if(!query.exec())
    {
        qDebug() << "songinfo query error";
        return;
    }

    if(query.next())
    {
        ui->title_l->setText(query.value(0).toString());

        ui->author_l->setText(query.value(1).toString());

        player->setSource(QUrl::fromLocalFile(query.value(2).toString()));
        ui->songProgress_s->setMaximum(player->duration());

        qDebug() << player->duration();
        QString minutes = QString::fromStdString(std::to_string((player->duration()/1000)/60));
        QString seconds = QString::fromStdString(std::to_string((player->duration()/1000)%60));
        songLength = minutes + ":" + seconds;
        //qDebug() << songLength;
        ui->songProgress_l->setText("00:00/" + songLength);
    }
}

float PlayerScreen::root(const int degree, const float num, const unsigned int maxIterations, const float error)
{
    float sol = 1;
    float ddeg = float(degree);
    float prev_sol = 0;
    unsigned int i = 0;
    while(std::abs(sol - prev_sol) > error && i<maxIterations)
    {
        prev_sol = sol;
        sol = sol - sol/ddeg + num/(ddeg*(powerIntFancy(sol, degree-1)));;
        //std::cout << sol << "\n";
        i++;
    }
    return sol;
}

float PlayerScreen::powerIntFancy(const float num, const int pow)
{
    float multiplicant = num;
    float result = 1;
    int pow_2 = 1; // used as a bit mask and ending condition

    for(int i = 0; i<32; i++)
    {
        if(pow_2 & pow)
        {
            result *= multiplicant;
            //std::cout << "brain damage at " << i << "\n";
        }

        pow_2 <<= 1;
        // if we are calculating x^132 then to need to keep squaring the multiplicant 32 times xd
        // 7 would be enough in this case and 2^7 is 128
        // but we did a bitshift a line ago so we are comparing against 2^8 = 256 which is larger than 132
        // so we can exit early :)
        if(pow_2 > pow)
        {
            return result;
        }

        multiplicant = multiplicant * multiplicant;
        //std::cout << "mul at " << i << "\n";
    }

    return result;
}

void PlayerScreen::setVolume()
{
    int slider = ui->volume_s->value();

    if(slider == 0)
    {
        audioOutput->setVolume(0);
        audioOutput->setMuted(true);
        return;
    }
    audioOutput->setMuted(false);

    // 0 volume basically works as a mute button
    // 100 -> 1
    // 1   -> whatever we want but close to 0
    // x   -> math :(

    const float volume_1   = 0.001;
    const float volume_100 = 1;

    const int steps = ui->volume_s->maximum() - ui->volume_s->minimum();

    const float step = root(steps, volume_100/volume_1, 1000);

    audioOutput->setVolume(volume_1 * powerIntFancy(step, slider));
}

void PlayerScreen::pause()
{
    player->pause();
    isPlaying = false;
}

void PlayerScreen::resume()
{
    player->play();
    isPlaying = true;
}


void PlayerScreen::nextSong()
{
    currentSongNumber++;
    songInfoQuery();
    if(isPlaying)
    {
        player->play();
    }
}

void PlayerScreen::previousSong()
{
    currentSongNumber--;
    //qDebug() << "wtf";
    songInfoQuery();
    if(isPlaying)
    {
        player->play();
    }
}

void PlayerScreen::updateSongSlider()
{
    if(!isUserSeeking)
    {
        ui->songProgress_s->setValue(player->position());
    }
}

void PlayerScreen::sliderPressed()
{
    isUserSeeking = true;
    player->pause();
}

void PlayerScreen::sliderReleased()
{
    isUserSeeking = false;
    player->setPosition(ui->songProgress_s->value());
    if(isPlaying)
    {
        player->play();
    }
}

void PlayerScreen::playerStatusChanged()
{
    if(player->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        nextSong();
    }
}
