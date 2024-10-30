/*
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/ByteString.h>
#include <AK/Error.h>
#include <AK/JsonObject.h>
#include <LibJS/Heap/GCPtr.h>
#include <LibWeb/Forward.h>
#include <LibWeb/PixelUnits.h>
#include <LibWeb/WebDriver/Error.h>

namespace Web::WebDriver {

JS::GCPtr<Web::DOM::Node> get_node(HTML::BrowsingContext const&, StringView reference);
ByteString get_or_create_a_node_reference(HTML::BrowsingContext const&, Web::DOM::Node const&);
bool node_reference_is_known(HTML::BrowsingContext const&, StringView reference);

ByteString get_or_create_a_web_element_reference(HTML::BrowsingContext const&, Web::DOM::Node const& element);
JsonObject web_element_reference_object(HTML::BrowsingContext const&, Web::DOM::Node const& element);
ErrorOr<JS::NonnullGCPtr<Web::DOM::Element>, WebDriver::Error> deserialize_web_element(Web::HTML::BrowsingContext const&, JsonObject const&);
ByteString extract_web_element_reference(JsonObject const&);
bool represents_a_web_element(JsonValue const& value);
ErrorOr<JS::NonnullGCPtr<Web::DOM::Element>, Web::WebDriver::Error> get_web_element_origin(Web::HTML::BrowsingContext const&, StringView origin);
ErrorOr<JS::NonnullGCPtr<Web::DOM::Element>, Web::WebDriver::Error> get_known_element(Web::HTML::BrowsingContext const&, StringView reference);

bool is_element_stale(Web::DOM::Node const& element);
bool is_element_interactable(Web::HTML::BrowsingContext const&, Web::DOM::Element const&);
bool is_element_pointer_interactable(Web::HTML::BrowsingContext const&, Web::DOM::Element const&);
bool is_element_keyboard_interactable(Web::DOM::Element const&);

bool is_element_editable(Web::DOM::Element const&);
bool is_element_mutable(Web::DOM::Element const&);
bool is_element_mutable_form_control(Web::DOM::Element const&);
bool is_element_non_typeable_form_control(Web::DOM::Element const&);

bool is_element_in_view(ReadonlySpan<JS::NonnullGCPtr<Web::DOM::Element>> paint_tree, Web::DOM::Element&);
bool is_element_obscured(ReadonlySpan<JS::NonnullGCPtr<Web::DOM::Element>> paint_tree, Web::DOM::Element&);
JS::MarkedVector<JS::NonnullGCPtr<Web::DOM::Element>> pointer_interactable_tree(Web::HTML::BrowsingContext&, Web::DOM::Element&);

ByteString get_or_create_a_shadow_root_reference(HTML::BrowsingContext const&, Web::DOM::ShadowRoot const&);
JsonObject shadow_root_reference_object(HTML::BrowsingContext const&, Web::DOM::ShadowRoot const&);
ErrorOr<JS::NonnullGCPtr<Web::DOM::ShadowRoot>, Web::WebDriver::Error> get_known_shadow_root(HTML::BrowsingContext const&, StringView reference);
bool is_shadow_root_detached(Web::DOM::ShadowRoot const&);

CSSPixelPoint in_view_center_point(DOM::Element const& element, CSSPixelRect viewport);

}
