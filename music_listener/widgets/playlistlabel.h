#ifndef PLAYLISTLABEL_H
#define PLAYLISTLABEL_H

#include <QLabel>


class PlaylistLabel : public QLabel
{
    Q_OBJECT

public:
    explicit PlaylistLabel(QWidget* parent = nullptr);
    ~PlaylistLabel();

    void setText(const QString text);
    void setMenu(QMenu* menu);

signals:
    void pressed();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    QMenu* menu = nullptr;
};

#endif // PLAYLISTLABEL_H
