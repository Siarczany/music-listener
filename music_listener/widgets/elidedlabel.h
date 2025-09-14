#ifndef ELIDEDLABEL_H
#define ELIDEDLABEL_H

#include <QLabel>
#include <QWidget>

class ElidedLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ElidedLabel(QWidget* parent = nullptr);
    ~ElidedLabel();

    void setFullText(const QString& text);
    void setWidthOfText();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QString fullText;
    bool optionEnabled = true;

    void updateElidedText();
};

#endif // ELIDEDLABEL_H
