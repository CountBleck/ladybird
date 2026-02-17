/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/CSS/StyleValues/StyleValue.h>

namespace Web::CSS {

class OffsetRotateStyleValue : public StyleValueWithDefaultOperators<OffsetRotateStyleValue> {
public:
    enum class RotationMode : u8 {
        None,
        Auto,
        Reverse
    };

    static ValueComparingNonnullRefPtr<OffsetRotateStyleValue const> create(NonnullRefPtr<StyleValue const> angle, RotationMode);
    virtual ~OffsetRotateStyleValue() override = default;

    StyleValue const& angle() const { return m_angle; }
    RotationMode rotation_mode() const { return m_rotation_mode; }

    virtual void serialize(StringBuilder&, SerializationMode) const override;
    virtual ValueComparingNonnullRefPtr<StyleValue const> absolutized(ComputationContext const&) const override;
    bool properties_equal(OffsetRotateStyleValue const& other) const { return m_angle == other.m_angle && m_rotation_mode == other.m_rotation_mode; }

private:
    OffsetRotateStyleValue(NonnullRefPtr<StyleValue const> angle, RotationMode);

    ValueComparingNonnullRefPtr<StyleValue const> m_angle;
    RotationMode m_rotation_mode;
};

}
