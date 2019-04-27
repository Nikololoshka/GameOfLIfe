#ifndef GAMEOFLIFEWINDOW_H
#define GAMEOFLIFEWINDOW_H

#include <QtWidgets>
#include "cell.h"
#include "customCell.h"
#include "classicRules.h"
#include "customRules.h"
#include "customMazeRules.h"

namespace Ui {
class GameOfLifeWindow;
}
// Основной класс игры "Жизнь"
class GameOfLIfeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOfLIfeWindow(QWidget *parent = nullptr);
    ~GameOfLIfeWindow() override;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Слоты для обработки сигналов формы
    void on_pushButtonStart_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonPlay_clicked();
    void on_pushButtonFAQ_clicked();
    void on_comboBoxRules_currentIndexChanged(int index);

private:
    // метод "игрового цикла" игры
    void gameLoop();
    // инициализация поля игры
    void initMap();
    // отчистка карты
    void clearMap();

private:
    Ui::GameOfLifeWindow *ui;

    QGraphicsScene *m_pScene;
    QVector<QVector<Cell *>> m_map;
    QVector<QVector<QVariant>> m_temporaryMap;
    bool m_loop;
    QScopedPointer<ClassicRules> m_pRules;
    QEventLoop m_eventLoop;
    QTimer m_timer;
};

#endif // GAMEOFLIFEWINDOW_H
