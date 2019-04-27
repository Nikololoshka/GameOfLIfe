#include "gameOfLifeWindow.h"
#include "ui_gameOfLifeWindow.h"

GameOfLIfeWindow::GameOfLIfeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameOfLifeWindow)
{
    // init
    ui->setupUi(this);

    m_pScene = new QGraphicsScene();
    ui->graphicsView->setScene(m_pScene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->spinBoxSpeed->setRange(50, 2000);
    ui->spinBoxSpeed->setSingleStep(50);
    ui->spinBoxSpeed->setValue(400);
    ui->spinBoxSpeed->setSuffix("ms");

    ui->spinBoxSize->setRange(8, 128);
    ui->spinBoxSize->setValue(32);

    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPause->setEnabled(false);

    m_pRules.reset(new ClassicRules());

    ui->comboBoxRules->addItem(tr("Классические"));
    ui->comboBoxRules->addItem(tr("'Лабиринт'"));
    ui->comboBoxRules->addItem(tr("Custom rules"));
    ui->comboBoxRules->setCurrentIndex(0);

    this->setWindowTitle(tr("Игра жизнь"));

    connect(&m_timer, &QTimer::timeout, &m_eventLoop, &QEventLoop::quit);
}

GameOfLIfeWindow::~GameOfLIfeWindow()
{
    for (int i = 0; i < m_map.size(); ++i)
        for (int j = 0; j < m_map[i].size(); ++j)
            delete m_map[i][j];

    delete ui;
}

void GameOfLIfeWindow::resizeEvent(QResizeEvent *event)
{
    int size =ui->spinBoxSize->value();
    m_pScene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    double minSceneSize = 0, x = 0, y = 0;

    if (m_pScene->height() < m_pScene->width()) {
        minSceneSize = m_pScene->height() * 0.9;
        x = (m_pScene->width() - minSceneSize) / 2;
        y = minSceneSize * 0.1 / 2;
    } else {
        minSceneSize = m_pScene->width() * 0.9;
        x = minSceneSize * 0.1 / 2;
        y = (m_pScene->height() - minSceneSize) / 2;
    }

    for (int i = 0; i < m_map.size(); ++i) {
        for (int j = 0; j < m_map[i].size(); ++j) {
            m_map[i][j]->setSize(minSceneSize / size, minSceneSize / size);
            m_map[i][j]->setPos(x + i * minSceneSize / size, y + j * minSceneSize / size);
        }
    }
    QMainWindow::resizeEvent(event);
}

void GameOfLIfeWindow::closeEvent(QCloseEvent *event)
{
    m_loop = false;
    if (m_eventLoop.isRunning())
        m_eventLoop.quit();

    QMainWindow::closeEvent(event);
}

void GameOfLIfeWindow::on_pushButtonStart_clicked()
{
    m_loop = true;
    m_pScene->setProperty("pause", false);
    ui->spinBoxSize->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonCancel->setEnabled(true);
    ui->pushButtonPause->setEnabled(true);
    ui->comboBoxRules->setEnabled(false);

    initMap();
    m_timer.start(ui->spinBoxSpeed->value());
    m_eventLoop.exec();
    gameLoop();
}

void GameOfLIfeWindow::on_pushButtonCancel_clicked()
{
    m_loop = false;
    if (m_eventLoop.isRunning())
        m_eventLoop.quit();

    ui->spinBoxSize->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonCancel->setEnabled(false);
    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPause->setEnabled(false);
    ui->comboBoxRules->setEnabled(true);
}

void GameOfLIfeWindow::gameLoop()
{
    while (m_loop) {
        // Создание нового поколения на основе текущих правил
        m_pRules->newGeneration(m_map, m_temporaryMap, ui->spinBoxSize->value());

        // Установка нового покаления
        bool isChange = false;
        for (int i = 0; i < m_map.size(); ++i) {
            for (int j = 0; j < m_map[i].size(); ++j) {
                if (m_map[i][j]->state() != m_temporaryMap[i][j]) {
                    isChange = true;
                    m_map[i][j]->setState(m_temporaryMap[i][j]);
                }
                m_temporaryMap[i][j] = false;
            }
        }

        // Обновление информации статистики игры
        ui->labelNumberGenerationValue->setText(QString::number(ui->labelNumberGenerationValue->text().toInt() + 1));
        ui->labelLivingCellsValue->setText(QString::number(m_pRules->numberLivingCells()));
        ui->labelDeadCellsValue->setText(QString::number(m_pRules->numberDeadCells()));

        // Проверка на окончание игры
        QString msg = m_pRules->chechWinner(isChange);
        if (!msg.isEmpty()) {
            QMessageBox::information(this, tr("Конец игры"), msg);
            on_pushButtonCancel_clicked();
            return;
        }

        // задержка между генерациями поколений
        m_timer.start(ui->spinBoxSpeed->value());
        m_eventLoop.exec();
    }
}

void GameOfLIfeWindow::initMap()
{
    clearMap();
    int size = ui->spinBoxSize->value();

    m_map.resize(size);
    m_temporaryMap.resize(size);

    for (int i = 0; i < size; ++i) {
        m_map[i].resize(size);
        m_temporaryMap[i].resize(size);
    }

    m_pScene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    double minSceneSize = 0, x = 0, y = 0;

    if (m_pScene->height() < m_pScene->width()) {
        minSceneSize = m_pScene->height() * 0.9;
        x = (m_pScene->width() - minSceneSize) / 2;
        y = minSceneSize * 0.1 / 2;
    } else {
        minSceneSize = m_pScene->width() * 0.9;
        x = minSceneSize * 0.1 / 2;
        y = (m_pScene->height() - minSceneSize) / 2;
    }

    for (int i = 0; i < m_map.size(); ++i) {
        for (int j = 0; j < m_map[i].size(); ++j) {
            m_map[i][j] = m_pRules->isCustomCell() ? new CustomCell() : new Cell();
            m_map[i][j]->setSize(minSceneSize / size, minSceneSize / size);
            m_map[i][j]->setPos(x + i * minSceneSize / size, y + j * minSceneSize / size);
            m_map[i][j]->setState(qrand() % 3 > 1 ? true : false);
            m_temporaryMap[i][j] = false;
            m_pScene->addItem(m_map[i][j]);
        }
    }

    ui->labelNumberGenerationValue->setText("0");
    ui->labelLivingCellsValue->setText("0");
    ui->labelDeadCellsValue->setText("0");
}

void GameOfLIfeWindow::clearMap()
{
    for (int i = 0; i < m_map.size(); ++i)
        for (int j = 0; j < m_map[i].size(); ++j)
            delete m_map[i][j];
}

void GameOfLIfeWindow::on_pushButtonPause_clicked()
{
    m_loop = false;
    if (m_eventLoop.isRunning())
        m_eventLoop.quit();

    m_pScene->setProperty("pause", true);

    ui->pushButtonPlay->setEnabled(true);
    ui->pushButtonPause->setEnabled(false);
}

void GameOfLIfeWindow::on_pushButtonPlay_clicked()
{
    m_loop = true;
    m_pScene->setProperty("pause", false);

    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPause->setEnabled(true);

    gameLoop();
}

void GameOfLIfeWindow::on_pushButtonFAQ_clicked()
{
    // qDebug() << m_pRules->information().toCaseFolded();
    QMessageBox::information(this, tr("Правила"), m_pRules->information());
}

void GameOfLIfeWindow::on_comboBoxRules_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        m_pRules.reset(new ClassicRules());
        break;
    case 1:
        m_pRules.reset(new CustomMazeRules());
        break;

    case 2:
        m_pRules.reset(new CustomRules());
        break;
    default:
        break;
    }
}
