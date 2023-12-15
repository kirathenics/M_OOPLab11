#include "maintable.h"
#include "ui_maintable.h"

MainTable::MainTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTable)
{
    ui->setupUi(this);

    this->resize(600, 400);
    srand(QTime::currentTime().msec());

    table = new QTableWidget(10, 3);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    randomizeButton = new QPushButton("Рандомизировать");
    connect(randomizeButton, &QPushButton::clicked, this, &MainTable::onRandomizeClicked);

    asciiSortRadioButton = new QRadioButton("ASCII Сортировка");
    numericSortRadioButton = new QRadioButton("Целочисленная Сортировка");
    connect(asciiSortRadioButton, &QRadioButton::clicked, this, &MainTable::onSortTypeChanged);
    connect(numericSortRadioButton, &QRadioButton::clicked, this, &MainTable::onSortTypeChanged);
    asciiSortRadioButton->setChecked(true);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(randomizeButton);
    buttonLayout->addWidget(asciiSortRadioButton);
    buttonLayout->addWidget(numericSortRadioButton);
    buttonLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    connect(table->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainTable::onTableHeaderClicked);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QShortcut* CtrlR = new QShortcut(Qt::CTRL | Qt::Key_R, this);

    QObject::connect(CtrlR, SIGNAL(activated()), this, SLOT(onRandomizeClicked()));

    randomizeTable();
}

MainTable::~MainTable()
{
    delete ui;
}

void MainTable::randomizeTable()
{
    for (int column = 0; column < table->columnCount(); ++column)
    {
        for (int row = 0; row < table->rowCount(); ++row)
        {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(rand() % 100));
            table->setItem(row, column, item);
            table->item(row, column)->setToolTip(table->item(row, column)->text());
        }
    }
}

void MainTable::sortTable(int column, Qt::SortOrder order)
{
    table->sortItems(column, order);
    setSortIndicator(column, order);
}

void MainTable::setSortIndicator(int column, Qt::SortOrder order)
{
    table->horizontalHeader()->setSortIndicatorShown(true);
    table->horizontalHeader()->setSortIndicator(column, order);
}

void MainTable::onRandomizeClicked()
{
    randomizeTable();
}

void MainTable::onTableHeaderClicked(int index)
{
    Qt::SortOrder sortOrder = table->horizontalHeader()->sortIndicatorOrder();
    sortTable(index, sortOrder);
}

void MainTable::onSortTypeChanged()
{
    int sortedColumn = table->horizontalHeader()->sortIndicatorSection();
    Qt::SortOrder sortOrder = table->horizontalHeader()->sortIndicatorOrder();

    if (numericSortRadioButton->isChecked())
    {
        for (int row = 0; row < table->rowCount(); ++row)
        {
            table->setItem(row, sortedColumn, new NumericTableWidgetItem(*table->item(row, sortedColumn)));
        }
    }
    else
    {
        for (int row = 0; row < table->rowCount(); ++row)
        {
            table->setItem(row, sortedColumn, new QTableWidgetItem(*table->item(row, sortedColumn)));
        }
    }

    sortTable(sortedColumn, sortOrder);
}
