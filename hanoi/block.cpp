// 284132 Olavi Salin olavi.salin@tuni.fi

#include "block.hh"


Block::Block(const QColor & new_color, int x_coord, int y_coord, int widht, int height) :
    x_coord_(x_coord),
    y_coord_(y_coord),
    block_widht_(widht),
    block_height_(height),
    color_(new_color)
{

}

QRectF Block::boundingRect() const
{
    return QRectF(x_coord_, y_coord_, block_widht_, block_height_);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED ( option );    // Getting rid of
    Q_UNUSED ( widget );    // the 'wunused parameter' warnings

    QRectF rec = boundingRect();    // A surface to paint
    QBrush brush(color_);           // Setting the desired color

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void Block::change_color(const QColor &new_color)
{
    color_ = new_color;
}

int Block::get_widht()
{
    return block_widht_;
}
