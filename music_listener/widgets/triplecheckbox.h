#ifndef TRIPLECHECKBOX_H
#define TRIPLECHECKBOX_H

#include <QCheckBox>


class TripleCheckBox : public QCheckBox
{
    Q_OBJECT
public:

    explicit TripleCheckBox(QWidget* parent = nullptr);
    ~TripleCheckBox();

    enum class state
    {
        whatever,
        no,
        yes
    };

    state checkState();
    void setText(const QString &text);

protected:
    void nextCheckState() override;
    void paintEvent(QPaintEvent* event) override;
private:
    state internalState = state::whatever;

};

#endif // TRIPLECHECKBOX_H
