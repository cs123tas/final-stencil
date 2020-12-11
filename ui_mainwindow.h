/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *canvas3D;
    QDockWidget *BurningTreeDock;
    QWidget *burningDockContents;
    QCheckBox *BurningButton;
    QLabel *burningTreeLabel;
    QLabel *CactusControlsLabel;
    QSlider *SizeControl;
    QLabel *SizeLabel;
    QLabel *AngleLabel;
    QSlider *AngleControl;
    QLabel *LengthALabel;
    QSlider *LengthControl;
    QLabel *BranchWidthLabel;
    QSlider *BranchWidthControl;
    QCheckBox *RandomCactus;
    QLineEdit *SizeInput;
    QLineEdit *AngleInput;
    QLineEdit *LenInput;
    QLineEdit *BranchInput;
    QDockWidget *camtransDock;
    QWidget *camtransDockContents;
    QGroupBox *cameraPosition;
    QGridLayout *gridLayout;
    QLabel *cameraPositionLabelX;
    QLabel *cameraPositionLabelY;
    QLabel *cameraPositionLabelZ;
    QDial *transX;
    QDial *transY;
    QDial *transZ;
    QLabel *cameraAspectRatio;
    QPushButton *resetSliders;
    QWidget *cameraDockEmptySpace;
    QCheckBox *cameraOrbitCheckbox;
    QWidget *cameraFrustum;
    QGridLayout *gridLayout_5;
    QLabel *cameraFovLabel;
    QLineEdit *cameraFovTextbox;
    QSlider *cameraFovSlider;
    QLabel *cameraNearLabel;
    QLineEdit *cameraNearTextbox;
    QLabel *cameraFarLabel;
    QLineEdit *cameraFarTextbox;
    QSlider *cameraNearSlider;
    QSlider *cameraFarSlider;
    QGroupBox *cameraResetAxis;
    QGridLayout *gridLayout_14;
    QPushButton *xAxisButton;
    QPushButton *yAxisButton;
    QPushButton *zAxisButton;
    QPushButton *axonometricButton;
    QGroupBox *cameraRotation;
    QVBoxLayout *verticalLayout_13;
    QWidget *cameraRotation_2;
    QGridLayout *gridLayout_15;
    QDial *rotU;
    QDial *rotV;
    QDial *rotW;
    QLabel *cameraRotationLabelYaw;
    QLabel *cameraRotationLabelPitch;
    QLabel *cameraRotationLabelRoll;
    QPushButton *resetUpVector;
    QLabel *label;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 873);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        canvas3D = new QWidget(centralWidget);
        canvas3D->setObjectName(QString::fromUtf8("canvas3D"));

        horizontalLayout->addWidget(canvas3D);

        MainWindow->setCentralWidget(centralWidget);
        BurningTreeDock = new QDockWidget(MainWindow);
        BurningTreeDock->setObjectName(QString::fromUtf8("BurningTreeDock"));
        burningDockContents = new QWidget();
        burningDockContents->setObjectName(QString::fromUtf8("burningDockContents"));
        BurningButton = new QCheckBox(burningDockContents);
        BurningButton->setObjectName(QString::fromUtf8("BurningButton"));
        BurningButton->setGeometry(QRect(10, 270, 100, 20));
        burningTreeLabel = new QLabel(burningDockContents);
        burningTreeLabel->setObjectName(QString::fromUtf8("burningTreeLabel"));
        burningTreeLabel->setGeometry(QRect(10, 240, 211, 16));
        CactusControlsLabel = new QLabel(burningDockContents);
        CactusControlsLabel->setObjectName(QString::fromUtf8("CactusControlsLabel"));
        CactusControlsLabel->setGeometry(QRect(10, 10, 101, 16));
        SizeControl = new QSlider(burningDockContents);
        SizeControl->setObjectName(QString::fromUtf8("SizeControl"));
        SizeControl->setGeometry(QRect(110, 50, 160, 22));
        SizeControl->setOrientation(Qt::Horizontal);
        SizeLabel = new QLabel(burningDockContents);
        SizeLabel->setObjectName(QString::fromUtf8("SizeLabel"));
        SizeLabel->setGeometry(QRect(10, 50, 58, 16));
        AngleLabel = new QLabel(burningDockContents);
        AngleLabel->setObjectName(QString::fromUtf8("AngleLabel"));
        AngleLabel->setGeometry(QRect(10, 90, 101, 16));
        AngleControl = new QSlider(burningDockContents);
        AngleControl->setObjectName(QString::fromUtf8("AngleControl"));
        AngleControl->setGeometry(QRect(110, 90, 160, 22));
        AngleControl->setOrientation(Qt::Horizontal);
        LengthALabel = new QLabel(burningDockContents);
        LengthALabel->setObjectName(QString::fromUtf8("LengthALabel"));
        LengthALabel->setGeometry(QRect(10, 130, 91, 16));
        LengthControl = new QSlider(burningDockContents);
        LengthControl->setObjectName(QString::fromUtf8("LengthControl"));
        LengthControl->setGeometry(QRect(110, 130, 160, 22));
        LengthControl->setOrientation(Qt::Horizontal);
        BranchWidthLabel = new QLabel(burningDockContents);
        BranchWidthLabel->setObjectName(QString::fromUtf8("BranchWidthLabel"));
        BranchWidthLabel->setGeometry(QRect(10, 170, 91, 16));
        BranchWidthControl = new QSlider(burningDockContents);
        BranchWidthControl->setObjectName(QString::fromUtf8("BranchWidthControl"));
        BranchWidthControl->setGeometry(QRect(110, 170, 160, 22));
        BranchWidthControl->setOrientation(Qt::Horizontal);
        RandomCactus = new QCheckBox(burningDockContents);
        RandomCactus->setObjectName(QString::fromUtf8("RandomCactus"));
        RandomCactus->setGeometry(QRect(10, 200, 86, 20));
        SizeInput = new QLineEdit(burningDockContents);
        SizeInput->setObjectName(QString::fromUtf8("SizeInput"));
        SizeInput->setGeometry(QRect(270, 50, 61, 21));
        AngleInput = new QLineEdit(burningDockContents);
        AngleInput->setObjectName(QString::fromUtf8("AngleInput"));
        AngleInput->setGeometry(QRect(270, 90, 61, 21));
        LenInput = new QLineEdit(burningDockContents);
        LenInput->setObjectName(QString::fromUtf8("LenInput"));
        LenInput->setGeometry(QRect(270, 130, 61, 21));
        BranchInput = new QLineEdit(burningDockContents);
        BranchInput->setObjectName(QString::fromUtf8("BranchInput"));
        BranchInput->setGeometry(QRect(270, 170, 61, 21));
        BurningTreeDock->setWidget(burningDockContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, BurningTreeDock);
        camtransDock = new QDockWidget(MainWindow);
        camtransDock->setObjectName(QString::fromUtf8("camtransDock"));
        camtransDockContents = new QWidget();
        camtransDockContents->setObjectName(QString::fromUtf8("camtransDockContents"));
        cameraPosition = new QGroupBox(camtransDockContents);
        cameraPosition->setObjectName(QString::fromUtf8("cameraPosition"));
        cameraPosition->setGeometry(QRect(6, 17, 230, 116));
        gridLayout = new QGridLayout(cameraPosition);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(-1, 5, -1, 5);
        cameraPositionLabelX = new QLabel(cameraPosition);
        cameraPositionLabelX->setObjectName(QString::fromUtf8("cameraPositionLabelX"));
        cameraPositionLabelX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelX, 1, 0, 1, 1);

        cameraPositionLabelY = new QLabel(cameraPosition);
        cameraPositionLabelY->setObjectName(QString::fromUtf8("cameraPositionLabelY"));
        cameraPositionLabelY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelY, 1, 1, 1, 1);

        cameraPositionLabelZ = new QLabel(cameraPosition);
        cameraPositionLabelZ->setObjectName(QString::fromUtf8("cameraPositionLabelZ"));
        cameraPositionLabelZ->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelZ, 1, 2, 1, 1);

        transX = new QDial(cameraPosition);
        transX->setObjectName(QString::fromUtf8("transX"));
        transX->setMinimumSize(QSize(60, 60));
        transX->setMaximumSize(QSize(60, 60));
        transX->setMinimum(-360);
        transX->setMaximum(360);
        transX->setSingleStep(10);
        transX->setPageStep(30);
        transX->setOrientation(Qt::Horizontal);
        transX->setInvertedControls(true);
        transX->setWrapping(true);

        gridLayout->addWidget(transX, 0, 0, 1, 1);

        transY = new QDial(cameraPosition);
        transY->setObjectName(QString::fromUtf8("transY"));
        transY->setMinimumSize(QSize(60, 60));
        transY->setMaximumSize(QSize(60, 60));
        transY->setMinimum(-360);
        transY->setMaximum(360);
        transY->setSingleStep(10);
        transY->setPageStep(30);
        transY->setOrientation(Qt::Horizontal);
        transY->setInvertedControls(true);
        transY->setWrapping(true);

        gridLayout->addWidget(transY, 0, 1, 1, 1);

        transZ = new QDial(cameraPosition);
        transZ->setObjectName(QString::fromUtf8("transZ"));
        transZ->setMinimumSize(QSize(60, 60));
        transZ->setMaximumSize(QSize(60, 60));
        transZ->setMinimum(-360);
        transZ->setMaximum(360);
        transZ->setSingleStep(10);
        transZ->setPageStep(30);
        transZ->setOrientation(Qt::Horizontal);
        transZ->setInvertedControls(true);
        transZ->setWrapping(true);

        gridLayout->addWidget(transZ, 0, 2, 1, 1);

        cameraAspectRatio = new QLabel(camtransDockContents);
        cameraAspectRatio->setObjectName(QString::fromUtf8("cameraAspectRatio"));
        cameraAspectRatio->setGeometry(QRect(6, 541, 230, 16));
        resetSliders = new QPushButton(camtransDockContents);
        resetSliders->setObjectName(QString::fromUtf8("resetSliders"));
        resetSliders->setGeometry(QRect(0, 503, 242, 32));
        cameraDockEmptySpace = new QWidget(camtransDockContents);
        cameraDockEmptySpace->setObjectName(QString::fromUtf8("cameraDockEmptySpace"));
        cameraDockEmptySpace->setGeometry(QRect(6, 605, 230, 175));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraDockEmptySpace->sizePolicy().hasHeightForWidth());
        cameraDockEmptySpace->setSizePolicy(sizePolicy);
        cameraOrbitCheckbox = new QCheckBox(camtransDockContents);
        cameraOrbitCheckbox->setObjectName(QString::fromUtf8("cameraOrbitCheckbox"));
        cameraOrbitCheckbox->setGeometry(QRect(4, 0, 241, 20));
        cameraFrustum = new QWidget(camtransDockContents);
        cameraFrustum->setObjectName(QString::fromUtf8("cameraFrustum"));
        cameraFrustum->setGeometry(QRect(6, 417, 230, 76));
        gridLayout_5 = new QGridLayout(cameraFrustum);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(5);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        cameraFovLabel = new QLabel(cameraFrustum);
        cameraFovLabel->setObjectName(QString::fromUtf8("cameraFovLabel"));

        gridLayout_5->addWidget(cameraFovLabel, 0, 0, 1, 1);

        cameraFovTextbox = new QLineEdit(cameraFrustum);
        cameraFovTextbox->setObjectName(QString::fromUtf8("cameraFovTextbox"));
        cameraFovTextbox->setMinimumSize(QSize(60, 0));
        cameraFovTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFovTextbox, 0, 3, 1, 1);

        cameraFovSlider = new QSlider(cameraFrustum);
        cameraFovSlider->setObjectName(QString::fromUtf8("cameraFovSlider"));
        cameraFovSlider->setMinimumSize(QSize(100, 0));
        cameraFovSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFovSlider, 0, 1, 1, 1);

        cameraNearLabel = new QLabel(cameraFrustum);
        cameraNearLabel->setObjectName(QString::fromUtf8("cameraNearLabel"));

        gridLayout_5->addWidget(cameraNearLabel, 1, 0, 1, 1);

        cameraNearTextbox = new QLineEdit(cameraFrustum);
        cameraNearTextbox->setObjectName(QString::fromUtf8("cameraNearTextbox"));
        cameraNearTextbox->setMinimumSize(QSize(60, 0));
        cameraNearTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraNearTextbox, 1, 3, 1, 1);

        cameraFarLabel = new QLabel(cameraFrustum);
        cameraFarLabel->setObjectName(QString::fromUtf8("cameraFarLabel"));

        gridLayout_5->addWidget(cameraFarLabel, 2, 0, 1, 1);

        cameraFarTextbox = new QLineEdit(cameraFrustum);
        cameraFarTextbox->setObjectName(QString::fromUtf8("cameraFarTextbox"));
        cameraFarTextbox->setMinimumSize(QSize(60, 0));
        cameraFarTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFarTextbox, 2, 3, 1, 1);

        cameraNearSlider = new QSlider(cameraFrustum);
        cameraNearSlider->setObjectName(QString::fromUtf8("cameraNearSlider"));
        cameraNearSlider->setMinimumSize(QSize(100, 0));
        cameraNearSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraNearSlider, 1, 1, 1, 1);

        cameraFarSlider = new QSlider(cameraFrustum);
        cameraFarSlider->setObjectName(QString::fromUtf8("cameraFarSlider"));
        cameraFarSlider->setMinimumSize(QSize(100, 0));
        cameraFarSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFarSlider, 2, 1, 1, 1);

        cameraResetAxis = new QGroupBox(camtransDockContents);
        cameraResetAxis->setObjectName(QString::fromUtf8("cameraResetAxis"));
        cameraResetAxis->setGeometry(QRect(6, 299, 230, 103));
        cameraResetAxis->setMinimumSize(QSize(0, 0));
        gridLayout_14 = new QGridLayout(cameraResetAxis);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        xAxisButton = new QPushButton(cameraResetAxis);
        xAxisButton->setObjectName(QString::fromUtf8("xAxisButton"));

        gridLayout_14->addWidget(xAxisButton, 0, 0, 1, 1);

        yAxisButton = new QPushButton(cameraResetAxis);
        yAxisButton->setObjectName(QString::fromUtf8("yAxisButton"));

        gridLayout_14->addWidget(yAxisButton, 1, 0, 1, 1);

        zAxisButton = new QPushButton(cameraResetAxis);
        zAxisButton->setObjectName(QString::fromUtf8("zAxisButton"));

        gridLayout_14->addWidget(zAxisButton, 0, 1, 1, 1);

        axonometricButton = new QPushButton(cameraResetAxis);
        axonometricButton->setObjectName(QString::fromUtf8("axonometricButton"));

        gridLayout_14->addWidget(axonometricButton, 1, 1, 1, 1);

        cameraRotation = new QGroupBox(camtransDockContents);
        cameraRotation->setObjectName(QString::fromUtf8("cameraRotation"));
        cameraRotation->setEnabled(true);
        cameraRotation->setGeometry(QRect(6, 133, 230, 166));
        verticalLayout_13 = new QVBoxLayout(cameraRotation);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(-1, 5, -1, 5);
        cameraRotation_2 = new QWidget(cameraRotation);
        cameraRotation_2->setObjectName(QString::fromUtf8("cameraRotation_2"));
        gridLayout_15 = new QGridLayout(cameraRotation_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setVerticalSpacing(18);
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        rotU = new QDial(cameraRotation_2);
        rotU->setObjectName(QString::fromUtf8("rotU"));
        rotU->setMinimumSize(QSize(60, 60));
        rotU->setMaximumSize(QSize(60, 60));
        rotU->setMinimum(-360);
        rotU->setMaximum(360);
        rotU->setSingleStep(10);
        rotU->setPageStep(30);
        rotU->setOrientation(Qt::Horizontal);
        rotU->setInvertedControls(true);
        rotU->setWrapping(true);

        gridLayout_15->addWidget(rotU, 0, 0, 1, 1);

        rotV = new QDial(cameraRotation_2);
        rotV->setObjectName(QString::fromUtf8("rotV"));
        rotV->setMinimumSize(QSize(60, 60));
        rotV->setMaximumSize(QSize(60, 60));
        rotV->setMinimum(-360);
        rotV->setMaximum(360);
        rotV->setSingleStep(10);
        rotV->setPageStep(30);
        rotV->setOrientation(Qt::Horizontal);
        rotV->setInvertedControls(true);
        rotV->setWrapping(true);

        gridLayout_15->addWidget(rotV, 0, 1, 1, 1);

        rotW = new QDial(cameraRotation_2);
        rotW->setObjectName(QString::fromUtf8("rotW"));
        rotW->setMinimumSize(QSize(60, 60));
        rotW->setMaximumSize(QSize(60, 60));
        rotW->setMinimum(-360);
        rotW->setMaximum(360);
        rotW->setSingleStep(10);
        rotW->setPageStep(30);
        rotW->setOrientation(Qt::Horizontal);
        rotW->setInvertedControls(true);
        rotW->setWrapping(true);

        gridLayout_15->addWidget(rotW, 0, 2, 1, 1);

        cameraRotationLabelYaw = new QLabel(cameraRotation_2);
        cameraRotationLabelYaw->setObjectName(QString::fromUtf8("cameraRotationLabelYaw"));
        cameraRotationLabelYaw->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelYaw, 1, 0, 1, 1);

        cameraRotationLabelPitch = new QLabel(cameraRotation_2);
        cameraRotationLabelPitch->setObjectName(QString::fromUtf8("cameraRotationLabelPitch"));
        cameraRotationLabelPitch->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelPitch, 1, 1, 1, 1);

        cameraRotationLabelRoll = new QLabel(cameraRotation_2);
        cameraRotationLabelRoll->setObjectName(QString::fromUtf8("cameraRotationLabelRoll"));
        cameraRotationLabelRoll->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelRoll, 1, 2, 1, 1);


        verticalLayout_13->addWidget(cameraRotation_2);

        resetUpVector = new QPushButton(cameraRotation);
        resetUpVector->setObjectName(QString::fromUtf8("resetUpVector"));

        verticalLayout_13->addWidget(resetUpVector);

        label = new QLabel(camtransDockContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(6, 565, 230, 32));
        label->setWordWrap(true);
        camtransDock->setWidget(camtransDockContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, camtransDock);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "A CS123 Final", nullptr));
        BurningButton->setText(QCoreApplication::translate("MainWindow", "Burning", nullptr));
        burningTreeLabel->setText(QCoreApplication::translate("MainWindow", "Let's make this cactus burn!", nullptr));
        CactusControlsLabel->setText(QCoreApplication::translate("MainWindow", "Cactus Controls", nullptr));
        SizeLabel->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        AngleLabel->setText(QCoreApplication::translate("MainWindow", "Branching Angle", nullptr));
        LengthALabel->setText(QCoreApplication::translate("MainWindow", "Branch Length", nullptr));
        BranchWidthLabel->setText(QCoreApplication::translate("MainWindow", "Branch Width", nullptr));
        RandomCactus->setText(QCoreApplication::translate("MainWindow", "Random", nullptr));
        cameraPosition->setTitle(QCoreApplication::translate("MainWindow", "Translation", nullptr));
        cameraPositionLabelX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        cameraPositionLabelY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        cameraPositionLabelZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        cameraAspectRatio->setText(QCoreApplication::translate("MainWindow", "Aspect ratio:", nullptr));
        resetSliders->setText(QCoreApplication::translate("MainWindow", "Reset FOV / Near / Far", nullptr));
        cameraOrbitCheckbox->setText(QCoreApplication::translate("MainWindow", "Use orbit camera instead", nullptr));
        cameraFovLabel->setText(QCoreApplication::translate("MainWindow", "FOV", nullptr));
        cameraNearLabel->setText(QCoreApplication::translate("MainWindow", "Near", nullptr));
        cameraFarLabel->setText(QCoreApplication::translate("MainWindow", "Far", nullptr));
        cameraResetAxis->setTitle(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        xAxisButton->setText(QCoreApplication::translate("MainWindow", "X axis", nullptr));
        yAxisButton->setText(QCoreApplication::translate("MainWindow", "Y axis", nullptr));
        zAxisButton->setText(QCoreApplication::translate("MainWindow", "Z axis", nullptr));
        axonometricButton->setText(QCoreApplication::translate("MainWindow", "Axonometric", nullptr));
        cameraRotation->setTitle(QCoreApplication::translate("MainWindow", "Rotation", nullptr));
        cameraRotationLabelYaw->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        cameraRotationLabelPitch->setText(QCoreApplication::translate("MainWindow", "V", nullptr));
        cameraRotationLabelRoll->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        resetUpVector->setText(QCoreApplication::translate("MainWindow", "Reset up vector", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Resize the window to change the aspect ratio.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
