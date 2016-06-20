#pragma once

#include "labels/label.h"

#include <glm/glm.hpp>

namespace Tangram {

class TextLabels;
class TextStyle;

struct GlyphQuad {
    size_t atlas;
    struct {
        glm::i16vec2 pos;
        glm::u16vec2 uv;
    } quad[4];
};

struct TextVertex {
    glm::i16vec2 pos;
    glm::u16vec2 uv;
    struct State {
        uint32_t color;
        uint32_t stroke;
        uint8_t alpha;
        uint8_t scale;
        int16_t rotation;
    } state;

    const static float position_scale;
    const static float rotation_scale;
    const static float alpha_scale;
};

class TextLabel : public Label {

public:

    struct FontVertexAttributes {
        uint32_t fill;
        uint32_t stroke;
        uint8_t fontScale;
    };

    TextLabel(Label::Transform _transform, Type _type, Label::Options _options,
              LabelProperty::Anchor _anchor, TextLabel::FontVertexAttributes _attrib,
              glm::vec2 _dim, TextLabels& _labels, Range _vertexRange,
              size_t _anchorPoint = 0, const std::vector<glm::vec2>& _line = {});

    bool updateScreenTransform(const glm::mat4& _mvp, const glm::vec2& _screenSize,
                               bool _testVisibility, ScreenTransform& _transform) override;

    Range& quadRange() { return m_vertexRange; }


    Range obbs(const ScreenTransform& _transform, std::vector<OBB>& _obbs) override;

protected:

    void pushTransform(ScreenTransform& _transform) override;

private:
    void applyAnchor(const glm::vec2& _dimension, const glm::vec2& _origin,
                     LabelProperty::Anchor _anchor) override;

    // Back-pointer to owning container
    const TextLabels& m_textLabels;
    // first vertex and count in m_textLabels quads
    Range m_vertexRange;

    FontVertexAttributes m_fontAttrib;

    size_t m_anchorPoint;
    std::vector<glm::vec2> m_line;

    LineSampler m_sampler;
};

}
