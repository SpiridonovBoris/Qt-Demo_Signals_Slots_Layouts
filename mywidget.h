#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QSignalMapper>
#include <QSizePolicy>
#include <QStackedLayout>
#include <QGridLayout>
#include <QVariant>
#include <QSpacerItem>
#include <QComboBox>

#define emit

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);
    ~MyWidget();

    QSpinBox* spinBox;
    QLineEdit* lineEdit;
    QSlider* slider;
    QLabel* label;

    QComboBox* combo;
    QStackedLayout* incStackLayout;
    QVBoxLayout* outerStackLayout;
    QHBoxLayout* mainLayout;

signals:
    void mySignal(int v);

public slots:
    void mySlot(QString s);
    void ChangeLayout(QObject * pNewLayout);
};

#endif // MYWIDGET_H
