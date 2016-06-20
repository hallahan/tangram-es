#include "labels/spriteLabel.h"

#include "gl/dynamicQuadMesh.h"
#include "style/pointStyle.h"
#include "util/geom.h"
#include "platform.h"

namespace Tangram {

using namespace LabelProperty;

const float SpriteVertex::position_scale = 4.0f;
const float SpriteVertex::rotation_scale = 4096.0f;
const float SpriteVertex::alpha_scale = 255.f;
const float SpriteVertex::texture_scale = 65535.f;

SpriteLabel::SpriteLabel(Label::Transform _transform, glm::vec2 _size, Label::Options _options,
                         float _extrudeScale, LabelProperty::Anchor _anchor,
                         SpriteLabels& _labels, size_t _labelsPos)
    : Label(_transform, _size, Label::Type::point, _options, _anchor),
      m_labels(_labels),
      m_labelsPos(_labelsPos),
      m_extrudeScale(_extrudeScale) {

    applyAnchor(m_dim, glm::vec2(0.0), _anchor);
}

void SpriteLabel::applyAnchor(const glm::vec2& _dimension, const glm::vec2& _origin,
                              LabelProperty::Anchor _anchor) {
    // _dimension is not applied to the sprite anchor since fractionnal zoom
    // level would result in scaling the sprite size dynamically, instead we
    // store a factor between 0..1 to scale the sprite accordingly

    glm::vec2 direction = LabelProperty::anchorDirection(_anchor);

    // Transform anchor direction from anchor space (centered)
    // to local sprite space (lower-left corner for the sprite)
    m_anchor = direction * glm::vec2(-0.5, 0.5) + glm::vec2(0.5);

    m_anchor.x = -(m_dim.x * m_anchor.x);
    m_anchor.y =  (m_dim.y * m_anchor.y);
}

bool SpriteLabel::updateScreenTransform(const glm::mat4& _mvp, const glm::vec2& _screenSize,
                                        bool _testVisibility, ScreenTransform& _transform) {

    bool clipped = false;
    glm::vec2 p0 = m_transform.modelPosition1;

    glm::vec2 screenPosition = worldToScreenSpace(_mvp, glm::vec4(p0, 0.0, 1.0),
                                                  _screenSize, clipped);

    if (_testVisibility && clipped) { return false; }

    screenPosition += m_anchor;
    screenPosition.x += m_options.offset.x;
    screenPosition.y -= m_options.offset.y;

    m_transform.state.screenPos = screenPosition;

    return true;
}

Range SpriteLabel::obbs(const ScreenTransform& _transform, std::vector<OBB>& _obbs) {
    Range range {int(_obbs.size()), 1};

    glm::vec2 halfSize = m_dim * 0.5f;
    glm::vec2 sp = m_transform.state.screenPos;
    glm::vec2 dim = m_dim + glm::vec2(m_extrudeScale * 2.f); // * _zoomFract);

    if (m_occludedLastFrame) { dim += 2; }

    // FIXME: Only for testing
    if (state() == State::dead) { dim -= 4; }

    auto obb = OBB({sp.x + halfSize.x, sp.y - halfSize.y},
                   m_transform.state.rotation, dim.x, dim.y);

    _obbs.push_back(obb);

    return range;
}

void SpriteLabel::pushTransform(ScreenTransform& _transform) {

    if (!visibleState()) { return; }

    // TODO
    // if (a_extrude.x != 0.0) {
    //     float dz = u_map_position.z - abs(u_tile_origin.z);
    //     vertex_pos.xy += clamp(dz, 0.0, 1.0) * UNPACK_EXTRUDE(a_extrude.xy);
    // }

    auto& quad = m_labels.quads[m_labelsPos];

    SpriteVertex::State state {
        quad.color,
        uint8_t(m_transform.state.alpha * SpriteVertex::alpha_scale),
        0, 0
    };

    auto& style = m_labels.m_style;

    auto* quadVertices = style.getMesh()->pushQuad();

    glm::i16vec2 sp = glm::i16vec2(m_transform.state.screenPos * SpriteVertex::position_scale);

    for (int i = 0; i < 4; i++) {
        SpriteVertex& v = quadVertices[i];
        v.pos = sp + quad.quad[i].pos;
        v.uv = quad.quad[i].uv;
        //v.extrude = quad.quad[i].extrude;
        v.state = state;
    }
}

}
