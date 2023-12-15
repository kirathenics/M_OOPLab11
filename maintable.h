#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QHeaderView>
#include <QTime>
#include <QTableWidgetItem>
#include <QToolTip>
#include <QString>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainTable; }
QT_END_NAMESPACE

class NumericTableWidgetItem : public QTableWidgetItem {
public:
    NumericTableWidgetItem(const QTableWidgetItem& item) : QTableWidgetItem(item.text()) {
    }

    bool operator<(const QTableWidgetItem& other) const override {
        return text().toInt() < other.text().toInt();
    }
};

class MainTable : public QWidget
{
    Q_OBJECT

public:
    MainTable(QWidget *parent = nullptr);
    ~MainTable();
    void randomizeTable();
    void sortTable(int column, Qt::SortOrder order);
    void setSortIndicator(int column, Qt::SortOrder order);

private slots:
    void onRandomizeClicked();
    void onTableHeaderClicked(int index);
    void onSortTypeChanged();

private:
    Ui::MainTable *ui;
    QTableWidget* table;
    QPushButton* randomizeButton;
    QRadioButton* asciiSortRadioButton, * numericSortRadioButton;
};
#endif // MAINTABLE_H
