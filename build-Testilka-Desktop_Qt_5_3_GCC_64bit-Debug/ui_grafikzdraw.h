/********************************************************************************
** Form generated from reading UI file 'grafikzdraw.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAFIKZDRAW_H
#define UI_GRAFIKZDRAW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GrafikzDraw
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QListWidget *listWidget;

    void setupUi(QWidget *GrafikzDraw)
    {
        if (GrafikzDraw->objectName().isEmpty())
            GrafikzDraw->setObjectName(QStringLiteral("GrafikzDraw"));
        GrafikzDraw->resize(617, 426);
        verticalLayout = new QVBoxLayout(GrafikzDraw);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(GrafikzDraw);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(GrafikzDraw);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(GrafikzDraw);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(40, 40));
        pushButton->setMaximumSize(QSize(40, 40));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/icons/99_diagona/cross.png);"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new QGraphicsView(GrafikzDraw);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);

        listWidget = new QListWidget(GrafikzDraw);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(230, 16777214));

        horizontalLayout_2->addWidget(listWidget);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(GrafikzDraw);

        QMetaObject::connectSlotsByName(GrafikzDraw);
    } // setupUi

    void retranslateUi(QWidget *GrafikzDraw)
    {
        GrafikzDraw->setWindowTitle(QApplication::translate("GrafikzDraw", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", 0));
        label->setText(QApplication::translate("GrafikzDraw", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\276\321\202\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\260 \321\202\320\265\321\201\321\202\320\260</span></p></body></html>", 0));
        pushButton_2->setText(QApplication::translate("GrafikzDraw", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GrafikzDraw: public Ui_GrafikzDraw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAFIKZDRAW_H
