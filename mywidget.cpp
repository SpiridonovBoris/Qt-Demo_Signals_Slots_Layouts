#include "mywidget.h"

typedef QWidget * typeCB;

Q_DECLARE_METATYPE(typeCB)

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    //Buttons
    //Exit button
    QPushButton* buttonExit = new QPushButton( QObject::tr("Exit"),this );
    buttonExit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QObject::connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));

    //Controls
    spinBox = new QSpinBox() ;
    lineEdit = new QLineEdit();
    slider = new QSlider(Qt::Horizontal);
    label = new QLabel("Not set");

    QPushButton* buttonVertical = new QPushButton (QObject::tr("Vertical"), this);
    buttonVertical->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QPushButton* buttonHorizontal = new QPushButton (QObject::tr("Horizontal"), this);
    buttonHorizontal->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QPushButton* buttonGrid = new QPushButton (QObject::tr("Grid"), this);
    buttonGrid->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QPushButton* buttonStack= new QPushButton (QObject::tr("Stack"), this);
    buttonStack->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //Properties
    spinBox->setRange(0,50);
    spinBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    slider->setRange(0,50);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setTickInterval(5);
    slider->setSingleStep(1);
    slider->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    lineEdit->setValidator(new QIntValidator(0,50,this));
    lineEdit->setMaxLength(2);
    lineEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    label->setFrameStyle(QFrame::Box | QFrame::Sunken);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //Connects
    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(spinBox,SIGNAL(valueChanged(QString)),lineEdit,SLOT(setText(QString)));
    QObject::connect(spinBox,SIGNAL(valueChanged(QString)),label,SLOT(setText(QString)));

    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));

    QObject::connect(lineEdit,SIGNAL(textChanged(QString)),this, SLOT(mySlot(QString)));
    QObject::connect(this, SIGNAL(mySignal(int)),spinBox,SLOT(setValue(int)));

    QSpacerItem * spacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    //included control vertical layout
    QVBoxLayout* incControlVLayout = new QVBoxLayout();
    incControlVLayout->addWidget(buttonVertical);
    incControlVLayout->addWidget(buttonHorizontal);
    incControlVLayout->addWidget(buttonGrid);
    incControlVLayout->addWidget(buttonStack);

    //included horizontal layout
    QHBoxLayout* incHLayout = new QHBoxLayout();
    incHLayout->addWidget(spinBox);
    incHLayout->addWidget(slider);
    incHLayout->addWidget(lineEdit);
    incHLayout->addWidget(label);

    //included vertical layout
    QVBoxLayout* incVLayout = new QVBoxLayout();
    incVLayout->addWidget(spinBox,0,Qt::AlignHCenter);
    incVLayout->addWidget(slider,0,Qt::AlignHCenter);
    incVLayout->addWidget(lineEdit,0,Qt::AlignHCenter);
    incVLayout->addWidget(label,0,Qt::AlignHCenter);

    //Grid Layout
    QGridLayout* incGrLayout = new QGridLayout();
    incGrLayout->addWidget(spinBox,0,0,Qt::AlignHCenter);
    incGrLayout->addWidget(slider,0,1,Qt::AlignHCenter);
    incGrLayout->addWidget(lineEdit,1,0,Qt::AlignHCenter);
    incGrLayout->addWidget(label,1,1,Qt::AlignHCenter);

    //Stack Layout
    incStackLayout = new QStackedLayout();
    incStackLayout->setStackingMode(QStackedLayout::StackAll);
    incStackLayout->insertWidget(0,spinBox);
    incStackLayout->insertWidget(1,slider);
    incStackLayout->insertWidget(2,lineEdit);

    combo = new QComboBox();
    QVariant var;
    var.setValue<typeCB>(spinBox);
    combo->addItem("SpinBox", var);
    var.setValue<typeCB>(slider);
    combo->addItem("Slider", var);
    var.setValue<typeCB>(lineEdit);
    combo->addItem("LineEdit", var);
    combo->setEditable(true);


    outerStackLayout = new QVBoxLayout();
    outerStackLayout->addWidget(combo,0,Qt::AlignTop|Qt::AlignLeft);
    outerStackLayout->addWidget(label,0,Qt::AlignLeft);
    outerStackLayout->addLayout(incStackLayout);

    QObject::connect(combo,SIGNAL(activated(int)),incStackLayout,SLOT(setCurrentIndex(int)));

    //main Layout
    mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(incHLayout);
    mainLayout->addLayout(incControlVLayout);
    mainLayout->addWidget(buttonExit);
    mainLayout->addItem(spacer);

    QSignalMapper* mapper = new QSignalMapper (this);

    QObject::connect(buttonVertical ,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    QObject::connect(buttonHorizontal,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    QObject::connect(buttonGrid,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    QObject::connect(buttonStack,SIGNAL(clicked(bool)),mapper,SLOT(map()));

    mapper->setMapping(buttonVertical, incVLayout);
    mapper->setMapping(buttonHorizontal, incHLayout);
    mapper->setMapping(buttonGrid, incGrLayout);
    mapper->setMapping(buttonStack, outerStackLayout);

    QObject::connect(mapper,SIGNAL(mapped(QObject*)),this,SLOT(ChangeLayout(QObject*)));

}

MyWidget::~MyWidget()
{

}

void MyWidget::mySlot(QString s)
{
    int n;
    n = s.toInt();
    emit(mySignal(n));
}

void MyWidget::ChangeLayout(QObject * pNewLayout)
{
    if(pNewLayout==outerStackLayout)
    {
        combo->setVisible(true);
        if(combo->currentIndex()==0)
        {
            lineEdit->hide();
            slider->hide();
            incStackLayout->setStackingMode(QStackedLayout::StackOne);
        }
        else if(combo->currentIndex()==1)
        {
            spinBox->hide();
            lineEdit->hide();
            incStackLayout->setStackingMode(QStackedLayout::StackOne);
        }
        else if(combo->currentIndex()==2)
        {
            spinBox->hide();
            slider->hide();
            incStackLayout->setStackingMode(QStackedLayout::StackOne);
        }

    }
    else
    {
        combo->setVisible(false);
        incStackLayout->setStackingMode(QStackedLayout::StackAll);
    }

    QLayoutItem * item = mainLayout->itemAt(0);
    mainLayout->removeItem((item));
    mainLayout->insertLayout(0, (QLayout*)pNewLayout);
}
