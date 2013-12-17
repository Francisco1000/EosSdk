// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mpls_route.h"

namespace eos {

mpls_route_key_t::mpls_route_key_t() : top_label(0), metric(0) {
}

mpls_route_key_t::mpls_route_key_t(mpls_label_t const & _label,
                                   mpls_route_metric_t _metric)
   : top_label(_label), metric(_metric) {
}

mpls_route_t::mpls_route_t() : key(), persistent(false) {
}

mpls_route_t::mpls_route_t(mpls_route_key_t const &route_key)
   : key(route_key), persistent(false) {
}

mpls_route_via_t::mpls_route_via_t()
   : route_key(), hop(), intf(),
     pushswap_label(0),
     label_action(MPLS_ACTION_NULL),
     ttl_mode(MPLS_TTLMODE_NULL),
     payload_type(MPLS_PAYLOAD_TYPE_NULL) {
}

mpls_route_via_t::mpls_route_via_t(mpls_route_key_t const & key)
   : route_key(key), hop(), intf(),
     pushswap_label(0),
     label_action(MPLS_ACTION_NULL),
     ttl_mode(MPLS_TTLMODE_NULL),
     payload_type(MPLS_PAYLOAD_TYPE_NULL) {
}

mpls_route_mgr::mpls_route_mgr() {
}

class mpls_route_mgr_impl : public mpls_route_mgr {
 public:
   mpls_route_mgr_impl() {
   }
};

bool
mpls_route_mgr::exists(mpls_route_key_t const & route_key) const {
   return false;  // TODO: No op impl.
}

bool
mpls_route_mgr::exists(mpls_route_via_t const & route_via) const {
   return false;  // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_set(mpls_route_t const & route) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_via_set(mpls_route_via_t const & route_via) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_del(mpls_route_key_t const & route_key) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_via_del(mpls_route_via_t const & route_via) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_foreach(callback_func_route handler, void * context) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_foreach(callback_func_route handler, void * context,
                                   mpls_route_t const & bookmark) {
   // TODO: No op impl.
}

void
mpls_route_mgr::mpls_route_via_foreach(mpls_route_key_t const & key,
                                       callback_func_via handler, void * context) {
   // TODO: No op impl.
}

mpls_route_mgr *
get_mpls_route_mgr() {
   static mpls_route_mgr_impl impl;
   return &impl;
}

}  // end namespace eos