#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QPixmap>

class ImageLabel : public QLabel {
    Q_OBJECT
public:
    explicit ImageLabel(const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPixmap m_pixmap;
};

#endif // IMAGELABEL_H
