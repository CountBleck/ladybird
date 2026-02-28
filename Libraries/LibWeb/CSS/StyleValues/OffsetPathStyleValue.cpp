/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "OffsetPathStyleValue.h"

#include <LibWeb/CSS/Enums.h>

namespace Web::CSS {

ValueComparingNonnullRefPtr<OffsetPathStyleValue const> OffsetPathStyleValue::create(RefPtr<StyleValue const> offset_path, CoordBox coord_box)
{
    return adopt_ref(*new (nothrow) OffsetPathStyleValue(move(offset_path), coord_box));
}

OffsetPathStyleValue::OffsetPathStyleValue(RefPtr<StyleValue const> offset_path, CoordBox coord_box)
    : StyleValueWithDefaultOperators(Type::OffsetPath)
    , m_offset_path(move(offset_path))
    , m_coord_box(coord_box)
{
}

void OffsetPathStyleValue::serialize(StringBuilder& builder, SerializationMode mode) const
{
    if (!m_offset_path) {
        builder.append(CSS::to_string(m_coord_box));
        return;
    }

    m_offset_path->serialize(builder, mode);

    if (m_coord_box != CoordBox::BorderBox) {
        builder.append(' ');
        builder.append(CSS::to_string(m_coord_box));
    }
}

ValueComparingNonnullRefPtr<StyleValue const> OffsetPathStyleValue::absolutized(ComputationContext const& context) const
{
    if (!m_offset_path)
        return *this;

    auto absolutized_offset_path = m_offset_path->absolutized(context);

    if (absolutized_offset_path == m_offset_path)
        return *this;

    return create(move(absolutized_offset_path), m_coord_box);
}

}
