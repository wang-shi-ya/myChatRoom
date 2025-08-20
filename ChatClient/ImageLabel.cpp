#include "ImageLabel.h"
#include <QMouseEvent>
#include <QDialog>
#include <QVBoxLayout>

ImageLabel::ImageLabel(const QPixmap &pixmap, QWidget *parent)
    : QLabel(parent), m_pixmap(pixmap)
{
    // 显示缩略图（最大宽度 200）
    setPixmap(m_pixmap.scaledToWidth(200, Qt::SmoothTransformation));
    setScaledContents(false);
    setCursor(Qt::PointingHandCursor); // 鼠标悬停变手型
}

void ImageLabel::mousePressEvent(QMouseEvent *event)
{
    if (!m_pixmap.isNull() && event->button() == Qt::LeftButton) {
        // 弹出对话框显示大图
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("查看图片");
        dialog->resize(600, 400);

        QLabel *bigLabel = new QLabel(dialog);
        bigLabel->setPixmap(m_pixmap.scaled(dialog->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        bigLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(bigLabel);
        dialog->setLayout(layout);

        dialog->exec(); // 模态显示
    }

    QLabel::mousePressEvent(event);
}
