/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "OffsetRotateStyleValue.h"

#include <LibWeb/CSS/StyleValues/AngleStyleValue.h>

namespace Web::CSS {

ValueComparingNonnullRefPtr<OffsetRotateStyleValue const> OffsetRotateStyleValue::create(NonnullRefPtr<StyleValue const> angle, RotationMode rotation_mode)
{
    return adopt_ref(*new (nothrow) OffsetRotateStyleValue(move(angle), rotation_mode));
}

OffsetRotateStyleValue::OffsetRotateStyleValue(NonnullRefPtr<StyleValue const> angle, RotationMode rotation_mode)
    : StyleValueWithDefaultOperators(Type::OffsetRotate)
    , m_angle(move(angle))
    , m_rotation_mode(rotation_mode)
{
}

void OffsetRotateStyleValue::serialize(StringBuilder& builder, SerializationMode mode) const
{
    if (m_rotation_mode == RotationMode::None) {
        m_angle->serialize(builder, mode);
        return;
    }

    if (m_rotation_mode == RotationMode::Auto)
        builder.append("auto"sv);
    else
        builder.append("reverse"sv);

    if (!m_angle->is_angle() || m_angle->as_angle().raw_value() != 0) {
        builder.append(' ');
        m_angle->serialize(builder, mode);
    }
}

ValueComparingNonnullRefPtr<StyleValue const> OffsetRotateStyleValue::absolutized(ComputationContext const& context) const
{
    auto absolutized_angle = m_angle->absolutized(context);

    if (absolutized_angle == m_angle && m_rotation_mode != RotationMode::Reverse)
        return *this;

    // Canonicalize all `reverse ???deg` angles to `auto ???deg` angles by adding 180 degrees
    auto rotation_mode = m_rotation_mode;
    if (rotation_mode == RotationMode::Reverse) {
        auto degrees = absolutized_angle->as_angle().angle().to_degrees();
        absolutized_angle = AngleStyleValue::create(Angle::make_degrees(degrees + 180));
        rotation_mode = RotationMode::Auto;
    }

    return create(move(absolutized_angle), rotation_mode);
}

}
