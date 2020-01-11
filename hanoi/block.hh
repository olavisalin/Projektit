// 284132 Olavi Salin olavi.salin@tuni.fi

#ifndef BLOCK_HH
#define BLOCK_HH
#include <QPainter>
#include <QGraphicsItem>
#include <QColor>
#include <QBrush>



class Block : public QGraphicsRectItem
{
public:
    Block(const QColor & new_color, int x_coord, int y_coord, int widht, int height);

    // Returns the bounding rect of the block.
    QRectF boundingRect() const override;

    // Paints the item.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Function to change color of the block when moved.
    void change_color(const QColor & new_color);

    // Returns the widht of a block.
    int get_widht();

private:
    // Self-explanatory variables.
    int x_coord_;
    int y_coord_;  
    int block_widht_;
    int block_height_;
    QColor color_;

};

#endif // BLOCK_HH
