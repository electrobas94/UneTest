/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_4;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *textEdit;
    QLabel *label_3;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QComboBox *comboBox_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QSpacerItem *verticalSpacer_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(799, 560);
        verticalLayout_6 = new QVBoxLayout(Form);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_4 = new QLabel(Form);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_6->addWidget(label_4);

        frame_3 = new QFrame(Form);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(0, 45));
        frame_3->setMaximumSize(QSize(16777215, 45));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(frame_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(112, 25));

        horizontalLayout_3->addWidget(comboBox);

        pushButton_5 = new QPushButton(frame_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(frame_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(pushButton_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_9 = new QPushButton(frame_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(frame_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(pushButton_10);


        verticalLayout_6->addWidget(frame_3);

        tabWidget = new QTabWidget(Form);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame = new QFrame(tab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        listWidget_2 = new QListWidget(frame);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));

        horizontalLayout->addWidget(listWidget_2);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton_4 = new QPushButton(frame_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout->addWidget(frame_2);

        listWidget = new QListWidget(frame);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);


        verticalLayout_3->addWidget(frame);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(188, 188));
        textEdit->setMaximumSize(QSize(16777215, 188));

        horizontalLayout_4->addWidget(textEdit);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(188, 188));
        label_3->setMaximumSize(QSize(188, 188));
        label_3->setSizeIncrement(QSize(1, 1));
        label_3->setStyleSheet(QStringLiteral("margin: 0px;"));
        label_3->setScaledContents(true);

        horizontalLayout_4->addWidget(label_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frame_4 = new QFrame(tab_2);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label = new QLabel(frame_4);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 23));

        verticalLayout_2->addWidget(label);

        comboBox_2 = new QComboBox(frame_4);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 23));

        verticalLayout_2->addWidget(comboBox_2);

        pushButton_7 = new QPushButton(frame_4);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(0, 23));

        verticalLayout_2->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(frame_4);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(0, 23));

        verticalLayout_2->addWidget(pushButton_8);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addWidget(frame_4);

        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QStringLiteral(""));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 604, 415));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);

        verticalLayout_5->addLayout(verticalLayout_4);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_6->addWidget(tabWidget);


        retranslateUi(Form);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "UneTesElets v0.8: \320\234\320\276\320\264\321\203\320\273\321\214 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217 \321\202\320\265\321\201\321\202\320\276\320\262", 0));
        label_4->setText(QApplication::translate("Form", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\202\320\265\321\201\321\202: </span></p></body></html>", 0));
        label_2->setText(QApplication::translate("Form", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \320\277\321\200\320\260\320\262\320\270\320\273\320\276:", 0));
        pushButton_5->setText(QApplication::translate("Form", " \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        pushButton_6->setText(QApplication::translate("Form", " \320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        pushButton_9->setText(QApplication::translate("Form", " \320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 ", 0));
        pushButton_10->setText(QApplication::translate("Form", " \320\236\321\202\320\274\320\265\320\275\320\260 ", 0));
        pushButton_4->setText(QApplication::translate("Form", "->", 0));
        pushButton->setText(QApplication::translate("Form", "<-", 0));
        pushButton_2->setText(QApplication::translate("Form", "\320\222\321\201\320\265>>", 0));
        pushButton_3->setText(QApplication::translate("Form", "<<\320\222\321\201\320\265", 0));
        label_3->setText(QApplication::translate("Form", "<html><head/><body><p align=\"center\"><span style=\" font-size:xx-large; font-weight:600; vertical-align:sub;\">&lt;Not image&gt; </span></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Form", " \320\222\321\213\320\261\320\276\321\200\320\272\320\260 \320\262\320\276\320\277\321\200\320\276\321\201\320\276\320\262", 0));
        label->setText(QApplication::translate("Form", "\320\222\321\213\321\207\320\270\321\201\320\273\321\217\321\202\321\214 \320\277\320\276:", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Form", " \320\241\321\203\320\274\320\274\320\265", 0)
         << QApplication::translate("Form", " \320\241\321\200\320\265\320\264\320\275\320\265\320\274\321\203", 0)
        );
        pushButton_7->setText(QApplication::translate("Form", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273", 0));
        pushButton_8->setText(QApplication::translate("Form", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Form", " \320\230\320\275\321\202\320\265\321\200\320\262\320\260\320\273\321\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
