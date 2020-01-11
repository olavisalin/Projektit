// 284132 Olavi Salin olavi.salin@tuni.fi

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "block.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // We need a graphics scene in which to draw the poles and blocks
    scene_ = new QGraphicsScene(this);

    // Create a timer
    counter = 0;
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this,SLOT(update_timer()));

    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1,
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Defining the color and outline of the poles
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);

    // Draw the poles on the right places.
    pole_left_ = scene_->addRect(BORDER_RIGHT/4-POLE_WIDHT/2, POLE_MARGIN,
                                 POLE_WIDHT, POLE_LENGHT, blackPen, redBrush);
    pole_mid_ = scene_->addRect(BORDER_RIGHT/2-POLE_WIDHT/2, POLE_MARGIN,
                                POLE_WIDHT, POLE_LENGHT, blackPen, greenBrush);
    pole_right_ = scene_->addRect(BORDER_RIGHT*0.75-POLE_WIDHT/2, POLE_MARGIN,
                                  POLE_WIDHT, POLE_LENGHT, blackPen, blueBrush);
    // Before the game starts, moving buttons are disabled
    set_all_disabled();

    ui_->info_label->setText("Choose the number of \nblocks and press start.");
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::on_start_push_button_clicked()
{
    // Clears the field before starting, beacause 'start' works also as 'restart'
    clear_field();
    ui_->info_label->clear();
    ui_->info_label->setText("Get all the blocks \n"
                             "either into the green \nor the blue tower.");

    // Adds n blocks to the game.
    int n = ui_->block_number_spin_box->value();
    // Creates the blocks from bottom to top.
    for(int i=n; i>0; --i){
        int widht = BLOCK_WIDHT_MIN+i*10;
        // The center of the block always on the x-coord of the first pole.
        int x = BORDER_RIGHT/4 - widht/2;
        // Bottom block always to the level of bottom ends of the poles
        int y = POLE_LENGHT+POLE_MARGIN-(n+1-i)*BLOCK_HEIGHT;

        block_ = new Block("red", x, y, widht, BLOCK_HEIGHT);
        tower_one.push_back(block_);
        scene_->addItem(block_);

        // When blocks are added, moving buttons can be used.
        update_moving_buttons();

        // Timer starts, updsates every 1 second.
        timer_->start(1000);
    }
}


void MainWindow::update_moving_buttons()
{
    // If a tower is empty, every block can be moved into it. To make the comparison
    // and this function simplier, lets declare 'empty tower's imaginary topblocks'
    // {a,b,c} wider than the BLOCK_WIDHT_MAX.
    int a=BLOCK_WIDHT_MAX+1;
    int b=BLOCK_WIDHT_MAX+1;
    int c=BLOCK_WIDHT_MAX+1;

    // If a tower not empty, the corresponding variable {a,b,c} will get the walue
    // of the tower's topblocks' widht.
    if(!tower_one.empty()) a = tower_one.back()->get_widht();
    if(!tower_two.empty()) b = tower_two.back()->get_widht();
    if(!tower_three.empty()) c = tower_three.back()->get_widht();

    // This is a little goofy way to compare the towers, but I found it the clearest
    // and shortest to do.
    // In any case, some buttons have to be disabled and some enabled, so lets just
    //  disable all, and do the comparison only for the buttons we have to enable.
    set_all_disabled();

    if(a<b) ui_->A_to_B_push_button->setEnabled(true);
    if(a<c) ui_->A_to_C_push_button->setEnabled(true);
    if(b<a) ui_->B_to_A_push_button->setEnabled(true);
    if(b<c) ui_->B_to_C_push_button->setEnabled(true);
    if(c<a) ui_->C_to_A_push_button->setEnabled(true);
    if(c<b) ui_->C_to_B_push_button->setEnabled(true);
}


qreal MainWindow::count_deltay(int one, int another)
{
    qreal deltay;
    // The deltay is the difference between the amount of blocks below the
    // block_to_be_moved and the amount of blocks in the tower the block is
    // going to move multiplied with BLOCK_HEIGHT.
    deltay = (one-1-another) * BLOCK_HEIGHT;
    return deltay;
}


void MainWindow::has_won()
{
    // It doesnt matter is all the block in the tower two or three.
    if(tower_one.empty() and (tower_two.empty() or tower_three.empty())){
        ui_->info_label->clear();
        set_all_disabled();
        timer_->stop();
        
        int time = ui_->timer_lcd_number->value();  // Get the time from timer
        int min = time / 60;    // total minutes
        int sec = time % 60;    // and seconds

        std::string disp = "";
        disp = "You won! Your time was\n"+std::to_string(min)+" min "+
                std::to_string(sec)+" seconds.\nPress start to play again.";

        // Show the time to user.
        ui_->info_label->setText(QString::fromStdString(disp));
    }
}


void MainWindow::clear_field()
{
    // empty the vectors and release the memory
    while(!tower_one.empty()){
        std::vector<Block*>::iterator to_be_removed = tower_one.end()-1 ;
        tower_one.erase(to_be_removed);
        delete *to_be_removed;
    }
    while(!tower_two.empty()){
        std::vector<Block*>::iterator to_be_removed = tower_two.end()-1 ;
        tower_two.erase(to_be_removed);
        delete *to_be_removed;
    }
    while(!tower_three.empty()){
        std::vector<Block*>::iterator to_be_removed = tower_three.end()-1 ;
        tower_three.erase(to_be_removed);
        delete *to_be_removed;
    }
    // set the timer back to 0.
    counter = 0;
    ui_->timer_lcd_number->display(counter);
}


void MainWindow::set_all_disabled()
{
    ui_->A_to_B_push_button->setDisabled(true);
    ui_->A_to_C_push_button->setDisabled(true);
    ui_->B_to_A_push_button->setDisabled(true);
    ui_->B_to_C_push_button->setDisabled(true);
    ui_->C_to_A_push_button->setDisabled(true);
    ui_->C_to_B_push_button->setDisabled(true);
}

// Passes one second in the timer.
void MainWindow::update_timer()
{
    counter++;
    ui_->timer_lcd_number->display(counter);
}


void MainWindow::make_a_move(std::vector<Block*>& one, std::vector<Block*>& another,
                             qreal deltax, QColor new_color)
{
    Block* block_to_be_moved = one.back();

    qreal deltay = count_deltay(one.size(), another.size());
    block_to_be_moved->moveBy(deltax, deltay);
    block_to_be_moved->change_color(new_color);

    another.push_back(block_to_be_moved);   // Change the vector, the
    one.pop_back();                         // moved block is stored in.

    update_moving_buttons();    // After every move moving buttons must be
    has_won();                  // updated and has_won checked.
}


// Makes a move with a specific parameters depending on the button clicked.
void MainWindow::on_A_to_B_push_button_clicked()
{
    make_a_move(tower_one, tower_two, POLE_DISTANCE,Qt::green);
}

void MainWindow::on_A_to_C_push_button_clicked()
{
    make_a_move(tower_one, tower_three, 2*POLE_DISTANCE, Qt::blue);
}

void MainWindow::on_B_to_A_push_button_clicked()
{
    make_a_move(tower_two, tower_one, -POLE_DISTANCE, Qt::red);
}

void MainWindow::on_B_to_C_push_button_clicked()
{
    make_a_move(tower_two, tower_three, POLE_DISTANCE, Qt::blue);
}

void MainWindow::on_C_to_A_push_button_clicked()
{
    make_a_move(tower_three, tower_one, -2*POLE_DISTANCE, Qt::red);
}

void MainWindow::on_C_to_B_push_button_clicked()
{
    make_a_move(tower_three, tower_two, -POLE_DISTANCE, Qt::green);
}

