/*
 * Copyright (c) 2021, Sam Atkins <atkinssj@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/CSSMediaRulePrototype.h>
#include <LibWeb/Bindings/WindowObject.h>
#include <LibWeb/CSS/CSSMediaRule.h>

namespace Web::CSS {

CSSMediaRule* CSSMediaRule::create(Bindings::WindowObject& window_object, NonnullRefPtr<MediaList>&& media_queries, CSSRuleList& rules)
{
    return window_object.heap().allocate<CSSMediaRule>(window_object.realm(), window_object, move(media_queries), rules);
}

CSSMediaRule::CSSMediaRule(Bindings::WindowObject& window_object, NonnullRefPtr<MediaList>&& media, CSSRuleList& rules)
    : CSSConditionRule(window_object, rules)
    , m_media(move(media))
{
    set_prototype(&window_object.ensure_web_prototype<Bindings::CSSMediaRulePrototype>("CSSMediaRule"));
}

String CSSMediaRule::condition_text() const
{
    return m_media->media_text();
}

void CSSMediaRule::set_condition_text(String text)
{
    m_media->set_media_text(text);
}

// https://www.w3.org/TR/cssom-1/#serialize-a-css-rule
String CSSMediaRule::serialized() const
{
    // The result of concatenating the following:
    StringBuilder builder;

    // 1. The string "@media", followed by a single SPACE (U+0020).
    builder.append("@media "sv);
    // 2. The result of performing serialize a media query list on rule’s media query list.
    builder.append(condition_text());
    // 3. A single SPACE (U+0020), followed by the string "{", i.e., LEFT CURLY BRACKET (U+007B), followed by a newline.
    builder.append(" {\n"sv);
    // 4. The result of performing serialize a CSS rule on each rule in the rule’s cssRules list, separated by a newline and indented by two spaces.
    for (size_t i = 0; i < css_rules().length(); i++) {
        auto rule = css_rules().item(i);
        if (i != 0)
            builder.append("\n"sv);
        builder.append("  "sv);
        builder.append(rule->css_text());
    }
    // 5. A newline, followed by the string "}", i.e., RIGHT CURLY BRACKET (U+007D)
    builder.append("\n}"sv);

    return builder.to_string();
}

}
