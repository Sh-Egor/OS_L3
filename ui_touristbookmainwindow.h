/********************************************************************************
** Form generated from reading UI file 'touristbookmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOURISTBOOKMAINWINDOW_H
#define UI_TOURISTBOOKMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TouristBookMainWindowClass
{
public:
    QAction *OpenFile;
    QAction *NewDB;
    QAction *Save;
    QAction *SaveAs;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QListWidget *BrowserView;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTimeEdit *autoSaveTime;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *CreateButton;
    QPushButton *DeleteButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *RecordBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *KindOfRecreationBox;
    QLabel *label_3;
    QComboBox *CountryBox;
    QLabel *label_4;
    QLineEdit *RecreationPlaceEdit;
    QLabel *label_5;
    QSpinBox *TicketCost;
    QLabel *label_6;
    QSpinBox *Duration;
    QCheckBox *VisaCheckBox;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TouristBookMainWindowClass)
    {
        if (TouristBookMainWindowClass->objectName().isEmpty())
            TouristBookMainWindowClass->setObjectName(QStringLiteral("TouristBookMainWindowClass"));
        TouristBookMainWindowClass->resize(685, 531);
        OpenFile = new QAction(TouristBookMainWindowClass);
        OpenFile->setObjectName(QStringLiteral("OpenFile"));
        NewDB = new QAction(TouristBookMainWindowClass);
        NewDB->setObjectName(QStringLiteral("NewDB"));
        Save = new QAction(TouristBookMainWindowClass);
        Save->setObjectName(QStringLiteral("Save"));
        SaveAs = new QAction(TouristBookMainWindowClass);
        SaveAs->setObjectName(QStringLiteral("SaveAs"));
        centralWidget = new QWidget(TouristBookMainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        BrowserView = new QListWidget(centralWidget);
        BrowserView->setObjectName(QStringLiteral("BrowserView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BrowserView->sizePolicy().hasHeightForWidth());
        BrowserView->setSizePolicy(sizePolicy);
        BrowserView->setMinimumSize(QSize(400, 0));
        BrowserView->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Tahoma"));
        font.setPointSize(8);
        BrowserView->setFont(font);

        verticalLayout->addWidget(BrowserView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        autoSaveTime = new QTimeEdit(centralWidget);
        autoSaveTime->setObjectName(QStringLiteral("autoSaveTime"));
        autoSaveTime->setReadOnly(true);
        autoSaveTime->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(autoSaveTime);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        CreateButton = new QPushButton(centralWidget);
        CreateButton->setObjectName(QStringLiteral("CreateButton"));

        horizontalLayout_3->addWidget(CreateButton);

        DeleteButton = new QPushButton(centralWidget);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));

        horizontalLayout_3->addWidget(DeleteButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(13, 13, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_3->addItem(verticalSpacer_2);

        RecordBox = new QGroupBox(centralWidget);
        RecordBox->setObjectName(QStringLiteral("RecordBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(RecordBox->sizePolicy().hasHeightForWidth());
        RecordBox->setSizePolicy(sizePolicy1);
        RecordBox->setMinimumSize(QSize(251, 181));
        gridLayout = new QGridLayout(RecordBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(RecordBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        KindOfRecreationBox = new QComboBox(RecordBox);
        KindOfRecreationBox->setObjectName(QStringLiteral("KindOfRecreationBox"));

        gridLayout->addWidget(KindOfRecreationBox, 0, 1, 1, 1);

        label_3 = new QLabel(RecordBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        CountryBox = new QComboBox(RecordBox);
        CountryBox->setObjectName(QStringLiteral("CountryBox"));

        gridLayout->addWidget(CountryBox, 1, 1, 1, 1);

        label_4 = new QLabel(RecordBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        RecreationPlaceEdit = new QLineEdit(RecordBox);
        RecreationPlaceEdit->setObjectName(QStringLiteral("RecreationPlaceEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(RecreationPlaceEdit->sizePolicy().hasHeightForWidth());
        RecreationPlaceEdit->setSizePolicy(sizePolicy2);
        RecreationPlaceEdit->setMaxLength(50);
        RecreationPlaceEdit->setReadOnly(false);

        gridLayout->addWidget(RecreationPlaceEdit, 2, 1, 1, 1);

        label_5 = new QLabel(RecordBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        TicketCost = new QSpinBox(RecordBox);
        TicketCost->setObjectName(QStringLiteral("TicketCost"));
        TicketCost->setMinimum(3000);
        TicketCost->setMaximum(100000);

        gridLayout->addWidget(TicketCost, 3, 1, 1, 1);

        label_6 = new QLabel(RecordBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        Duration = new QSpinBox(RecordBox);
        Duration->setObjectName(QStringLiteral("Duration"));
        Duration->setMinimum(2);
        Duration->setMaximum(31);

        gridLayout->addWidget(Duration, 4, 1, 1, 1);

        VisaCheckBox = new QCheckBox(RecordBox);
        VisaCheckBox->setObjectName(QStringLiteral("VisaCheckBox"));
        VisaCheckBox->setEnabled(false);
        VisaCheckBox->setCheckable(true);

        gridLayout->addWidget(VisaCheckBox, 5, 1, 1, 1);

        CountryBox->raise();
        label_4->raise();
        RecreationPlaceEdit->raise();
        label_5->raise();
        TicketCost->raise();
        label_6->raise();
        Duration->raise();
        VisaCheckBox->raise();
        label_2->raise();
        KindOfRecreationBox->raise();
        label_3->raise();

        verticalLayout_3->addWidget(RecordBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_3);

        TouristBookMainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TouristBookMainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TouristBookMainWindowClass->setStatusBar(statusBar);
        QWidget::setTabOrder(CreateButton, DeleteButton);
        QWidget::setTabOrder(DeleteButton, BrowserView);
        QWidget::setTabOrder(BrowserView, KindOfRecreationBox);
        QWidget::setTabOrder(KindOfRecreationBox, CountryBox);
        QWidget::setTabOrder(CountryBox, RecreationPlaceEdit);
        QWidget::setTabOrder(RecreationPlaceEdit, TicketCost);
        QWidget::setTabOrder(TicketCost, Duration);
        QWidget::setTabOrder(Duration, VisaCheckBox);

        retranslateUi(TouristBookMainWindowClass);

        QMetaObject::connectSlotsByName(TouristBookMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *TouristBookMainWindowClass)
    {
        TouristBookMainWindowClass->setWindowTitle(QApplication::translate("TouristBookMainWindowClass", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272 \321\202\321\203\321\200\320\270\321\201\321\202\320\260", 0));
        OpenFile->setText(QApplication::translate("TouristBookMainWindowClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214...", 0));
        NewDB->setText(QApplication::translate("TouristBookMainWindowClass", "\320\235\320\276\320\262\320\260\321\217 \320\221\320\224", 0));
        Save->setText(QApplication::translate("TouristBookMainWindowClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        SaveAs->setText(QApplication::translate("TouristBookMainWindowClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", 0));
        label_7->setText(QApplication::translate("TouristBookMainWindowClass", "\320\221\321\200\320\260\321\203\320\267\320\265\321\200:", 0));
        label->setText(QApplication::translate("TouristBookMainWindowClass", "\320\222\321\200\320\265\320\274\321\217 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\263\320\276 \320\260\320\262\321\202\320\276\321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217:", 0));
        autoSaveTime->setDisplayFormat(QApplication::translate("TouristBookMainWindowClass", "hh:mm:ss", 0));
        CreateButton->setText(QApplication::translate("TouristBookMainWindowClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0));
        DeleteButton->setText(QApplication::translate("TouristBookMainWindowClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        RecordBox->setTitle(QApplication::translate("TouristBookMainWindowClass", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\267\320\260\320\277\320\270\321\201\321\214:", 0));
        label_2->setText(QApplication::translate("TouristBookMainWindowClass", "\320\222\320\270\320\264 \320\276\321\202\320\264\321\213\321\205\320\260: ", 0));
        KindOfRecreationBox->clear();
        KindOfRecreationBox->insertItems(0, QStringList()
         << QApplication::translate("TouristBookMainWindowClass", "\320\277\320\273\321\217\320\266\320\275\321\213\320\271", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\321\215\320\272\321\201\320\272\321\203\321\200\321\201\320\270\320\276\320\275\320\275\321\213\320\271", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\321\215\320\272\320\267\320\276\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\272\321\200\321\203\320\270\320\267", 0)
         << QApplication::translate("TouristBookMainWindowClass", "VIP", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\273\320\265\321\207\320\265\320\261\320\275\321\213\320\271", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\321\215\320\272\321\201\321\202\321\200\320\265\320\274\320\260\320\273\321\214\320\275\321\213\320\271", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\263\320\276\321\200\320\275\320\276\320\273\321\213\320\266\320\275\321\213\320\271", 0)
        );
        label_3->setText(QApplication::translate("TouristBookMainWindowClass", "\320\241\321\202\321\200\320\260\320\275\320\260: ", 0));
        CountryBox->clear();
        CountryBox->insertItems(0, QStringList()
         << QApplication::translate("TouristBookMainWindowClass", "\320\240\320\276\321\201\321\201\320\270\321\217", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\220\320\261\321\205\320\260\320\267\320\270\321\217", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\242\321\203\321\200\321\206\320\270\321\217", 0)
         << QApplication::translate("TouristBookMainWindowClass", "\320\225\320\263\320\270\320\277\320\265\321\202", 0)
        );
        label_4->setText(QApplication::translate("TouristBookMainWindowClass", "\320\234\320\265\321\201\321\202\320\276 \320\276\321\202\320\264\321\213\321\205\320\260: ", 0));
        RecreationPlaceEdit->setText(QString());
        label_5->setText(QApplication::translate("TouristBookMainWindowClass", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\277\321\203\321\202\320\265\320\262\320\272\320\270: ", 0));
        label_6->setText(QApplication::translate("TouristBookMainWindowClass", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214: ", 0));
        VisaCheckBox->setText(QApplication::translate("TouristBookMainWindowClass", "\320\242\321\200\320\265\320\261\321\203\320\265\321\202\321\201\321\217 \320\262\320\270\320\267\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class TouristBookMainWindowClass: public Ui_TouristBookMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOURISTBOOKMAINWINDOW_H
