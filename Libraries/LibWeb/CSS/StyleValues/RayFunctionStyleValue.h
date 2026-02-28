/*
 * Copyright (c) 2026, the Ladybird developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/CSS/StyleValues/StyleValue.h>

namespace Web::CSS {

class RayFunctionStyleValue : public StyleValueWithDefaultOperators<RayFunctionStyleValue> {
public:
    static ValueComparingNonnullRefPtr<RayFunctionStyleValue const> create(NonnullRefPtr<StyleValue const> angle, RaySize, bool contain, RefPtr<StyleValue const> position);
    virtual ~RayFunctionStyleValue() override = default;

    StyleValue const& angle() const { return m_properties.angle; }
    RaySize ray_size() const { return m_properties.ray_size; }
    bool contain() const { return m_properties.contain; }
    ValueComparingRefPtr<StyleValue const> position() const { return m_properties.position; }

    virtual void serialize(StringBuilder&, SerializationMode) const override;
    virtual ValueComparingNonnullRefPtr<StyleValue const> absolutized(ComputationContext const&) const override;

    bool properties_equal(RayFunctionStyleValue const& other) const { return m_properties == other.m_properties; }

private:
    RayFunctionStyleValue(NonnullRefPtr<StyleValue const> angle, RaySize, bool contain, RefPtr<StyleValue const> position);

    struct Properties {
        ValueComparingNonnullRefPtr<StyleValue const> angle;
        RaySize ray_size;
        bool contain;
        ValueComparingRefPtr<StyleValue const> position;
        bool operator==(Properties const&) const = default;
    } m_properties;
};

}
