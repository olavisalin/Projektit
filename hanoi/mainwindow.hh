// 284132 Olavi Salin olavi.salin@tuni.fi

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "block.hh"
#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QColor>
#include <iostream>
#include <vector>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_push_button_clicked();

    void on_A_to_B_push_button_clicked();
    void on_A_to_C_push_button_clicked();
    void on_B_to_A_push_button_clicked();
    void on_B_to_C_push_button_clicked();
    void on_C_to_A_push_button_clicked();
    void on_C_to_B_push_button_clicked();

    // Increases the digit of the timer by one.
    void update_timer();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;         // a surface for
    QGraphicsRectItem* pole_left_;  // drawing the first pole
    QGraphicsRectItem* pole_mid_;   // drawing the second pole
    QGraphicsRectItem* pole_right_; // drawing the third pole
    Block* block_;                  // drawing a block

    QTimer* timer_;                 // Counts the duration of a gameplay
    qint32 counter;                 // This is a value of the timer_

    QPainter* painter_;

    const int POLE_WIDHT = 10;
    const int POLE_LENGHT = 220;
    const int POLE_MARGIN = 20;     // Poles are shorter than the scene
    const int POLE_DISTANCE = 170;  // Distance between two poles next to each other
    const int BLOCK_WIDHT_MIN = 20; // The smallest block is always this wide.
    const int BLOCK_WIDHT_MAX = 220;// When played with 20 blocks, widest is 220.
    const int BLOCK_HEIGHT = 10;

    const int BORDER_DOWN = 260;
    const int BORDER_RIGHT = 680;

    // Containers for all blocks in a specific pole
    std::vector<Block*> tower_one = {};
    std::vector<Block*> tower_two = {};
    std::vector<Block*> tower_three = {};

    // When a move is made, buttons must be updated to prevent illegal moves.
    void update_moving_buttons();

    // Computes the change in the y-coordinate when a block is moved.
    qreal count_deltay(int one, int another);

    // Checks if player has won the game
    void has_won();

    // Resets the game by deleting all blocks and setting the timer back to 0.
    void clear_field();

    // Sets all moving buttons disabled, I found this a useful solution.
    void set_all_disabled();

    // Moves a block from one pole to another.
    void make_a_move(std::vector<Block*>& one, std::vector<Block*>& another, qreal deltax, QColor new_color);
};
#endif // MAINWINDOW_HH
