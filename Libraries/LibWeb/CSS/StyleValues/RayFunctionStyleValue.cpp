/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "RayFunctionStyleValue.h"

#include <LibWeb/CSS/Enums.h>

namespace Web::CSS {

ValueComparingNonnullRefPtr<RayFunctionStyleValue const> RayFunctionStyleValue::create(NonnullRefPtr<StyleValue const> angle, RaySize ray_size, bool contain, RefPtr<StyleValue const> position)
{
    return adopt_ref(*new (nothrow) RayFunctionStyleValue(move(angle), ray_size, contain, move(position)));
}

RayFunctionStyleValue::RayFunctionStyleValue(NonnullRefPtr<StyleValue const> angle, RaySize ray_size, bool contain, RefPtr<StyleValue const> position)
    : StyleValueWithDefaultOperators(Type::RayFunction)
    , m_properties({ .angle = move(angle), .ray_size = ray_size, .contain = contain, .position = move(position) })
{
}

void RayFunctionStyleValue::serialize(StringBuilder& builder, SerializationMode mode) const
{
    builder.append("ray("sv);

    m_properties.angle->serialize(builder, mode);

    if (m_properties.ray_size != RaySize::ClosestSide) {
        builder.append(' ');
        builder.append(CSS::to_string(m_properties.ray_size));
    }

    if (m_properties.contain)
        builder.append(" contain"sv);

    if (m_properties.position) {
        builder.append(" at "sv);
        m_properties.position->serialize(builder, mode);
    }

    builder.append(')');
}

ValueComparingNonnullRefPtr<StyleValue const> RayFunctionStyleValue::absolutized(ComputationContext const& context) const
{
    auto absolutized_angle = m_properties.angle->absolutized(context);

    ValueComparingRefPtr<StyleValue const> absolutized_position;
    if (m_properties.position)
        absolutized_position = m_properties.position->absolutized(context);

    if (absolutized_angle == m_properties.angle && absolutized_position == m_properties.position)
        return *this;

    return create(move(absolutized_angle), m_properties.ray_size, m_properties.contain, m_properties.position);
}

}
