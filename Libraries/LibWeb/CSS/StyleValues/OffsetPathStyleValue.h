/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/CSS/StyleValues/StyleValue.h>

namespace Web::CSS {

class OffsetPathStyleValue : public StyleValueWithDefaultOperators<OffsetPathStyleValue> {
public:
    static ValueComparingNonnullRefPtr<OffsetPathStyleValue const> create(RefPtr<StyleValue const> offset_path, CoordBox);
    virtual ~OffsetPathStyleValue() override = default;

    ValueComparingRefPtr<StyleValue const> offset_path() const { return m_offset_path; }
    CoordBox coord_box() const { return m_coord_box; }

    virtual void serialize(StringBuilder&, SerializationMode) const override;
    virtual ValueComparingNonnullRefPtr<StyleValue const> absolutized(ComputationContext const&) const override;
    bool properties_equal(OffsetPathStyleValue const& other) const { return m_offset_path == other.m_offset_path && m_coord_box == other.m_coord_box; }

private:
    OffsetPathStyleValue(RefPtr<StyleValue const> offset_path, CoordBox);

    ValueComparingRefPtr<StyleValue const> m_offset_path;
    CoordBox m_coord_box;
};

}
