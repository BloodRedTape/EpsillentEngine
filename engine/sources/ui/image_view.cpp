#include "ui/image_view.hpp"
#include "render/draw_call.hpp"
ImageView::ImageView(const sf::Vector2f &size):
    m_shape(size)
{}

void ImageView::on_render(){
    DrawCallInterface::draw(m_shape);
}

ImageView &ImageView::set_size(const sf::Vector2f &size){
    m_shape.setSize(size);
}
ImageView &ImageView::set_position(const sf::Vector2f &position){
    m_shape.setPosition(position);
}
ImageView &ImageView::set_texture(sf::Texture *texture){
    m_shape.setTexture(texture); 
}