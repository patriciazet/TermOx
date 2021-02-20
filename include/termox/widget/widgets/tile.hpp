#ifndef TERMOX_WIDGET_WIDGETS_TILE_HPP
#define TERMOX_WIDGET_WIDGETS_TILE_HPP
#include <termox/painter/glyph.hpp>
#include <termox/painter/painter.hpp>
#include <termox/widget/pipe.hpp>
#include <termox/widget/widget.hpp>

namespace ox {

/// A unit width/height Widget that can display a single Glyph.
class Tile : public Widget {
   public:
    using Parameters = Glyph;

   public:
    explicit Tile(Glyph g = U' ') : display_{g}
    {
        using namespace pipe;
        *this | fixed_width(1) | fixed_height(1);
    }

   public:
    void set(Glyph g)
    {
        display_ = g;
        this->update();
    }

    [[nodiscard]] auto get() -> Glyph { return display_; }

   protected:
    auto paint_event(Painter& p) -> bool override
    {
        p.put(display_, {0, 0});
        return Widget::paint_event(p);
    }

   private:
    Glyph display_;
};

/// Helper function to create an instance.
template <typename... Args>
[[nodiscard]] auto tile(Args&&... args) -> std::unique_ptr<Tile>
{
    return std::make_unique<Tile>(std::forward<Args>(args)...);
}

}  // namespace ox
#endif  // TERMOX_WIDGET_WIDGETS_TILE_HPP
