// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * Nexthop groups are a forwarding/tunneling abstraction in EOS.
 *
 * A nexthop group is comprised of a tunneling protocol (IP/GRE or
 * MPLS, for example) and a sparse array of nexthop (aka destination)
 * IP addresses and other forwarding information (such as MPLS stack
 * operations to apply for traffic sent to that nexthop). The same
 * IP address may be specified in more than one entry within the
 * group, allowing for unequal cost load balancing. By using distinct
 * addresses for each entry, equal cost load balancing can be achieved
 *
 * The nexthop or destination IP is the tunnel (outer) destination IP
 * address for GRE and IP-in-IP. For MPLS, the nexthop address is used
 * to find (via ARP/ND) a MAC address for the MPLS next hop.
 *
 * Nexthop entries must be manually monitored and maintained by the
 * agent. If a tunnel destination (aka nexthop) becomes unreachable,
 * traffic hashed to that entry will be blackholed in the network
 * until a working entry is set in that index of the nexthop group, or
 * the entry is deleted.
 *
 * Presently, all nexthop groups encapsulate traffic directed to them,
 * either as an IP-in-IP (IP protocol 4) tunnel, a GRE (IP protocol
 * 47) tunnel encapsulating either IPv4, IPv6 or MPLS traffic, or as
 * pure MPLS frames. MPLS label switching operations are also
 * supported, see the nexthop_group_entry_t class for more
 * information.
 *
 * Presently, MPLS switching actions are only only supported when used
 * with PBR and cannot be used with IP routes.
 *
 * The following example creates a nexthop group called "nhg1" which
 * performs GRE encapsulation of traffic sent to it, sending traffic
 * to two different nexthop IP addresses unequally (at a 2/3 to 1/3
 * ratio). For a usage of a nexthop group with policy routing, see the
 * policy_map.h file.
 *
 * @code{.cpp}
 *   eos::nexthop_group_t nhg("nhg1", eos::NEXTHOP_GROUP_GRE);
 *   // Specify two destinations (nexthop group entries) for the traffic
 *   eos::nexthop_group_entry_t nhe1(eos::ip_addr_t("172.12.1.1"));
 *   eos::nexthop_group_entry_t nhe2(eos::ip_addr_t("172.12.1.2"));
 *   // Set the nexthop group entries on the group with unequal cost load balancing
 *   // Balance traffic 2/3 to 172.12.1.1, 1/3 to 172.12.1.2.
 *   nhg.nexthop_entry_set(0, nhe1);
 *   nhg.nexthop_entry_set(1, nhe1);
 *   nhg.nexthop_entry_set(2, nhe2);
 * @endcode
 */

#ifndef EOS_NEXTHOP_GROUP_H
#define EOS_NEXTHOP_GROUP_H

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

#include <eos/types/nexthop_group.h>

namespace eos {

class nexthop_group_iter_impl;

class EOS_SDK_PUBLIC nexthop_group_iter_t :
      public iter_base<nexthop_group_t, nexthop_group_iter_impl> {
 private:
   friend class nexthop_group_iter_impl;
   explicit nexthop_group_iter_t(nexthop_group_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'nexthop-group' configurations.
 *
 * Create one of these via an sdk object prior to starting the agent main loop.
 * When your eos::agent_handler::on_initialized virtual function is called, the
 * manager is valid for use.
 */
class EOS_SDK_PUBLIC nexthop_group_mgr {
 public:
   virtual ~nexthop_group_mgr();

   virtual void resync_init() = 0;
   virtual void resync_complete() = 0;

   /// Iterates over all the nexthop groups currently configured.
   virtual nexthop_group_iter_t nexthop_group_iter() const = 0;

   /// Creates or updates a nexthop group.
   virtual void nexthop_group_set(nexthop_group_t const &) = 0;
   /// Removes the named nexthop group from the configuration if it exists
   virtual void nexthop_group_del(std::string const & nexthop_group_name) = 0;
 protected:
   nexthop_group_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(nexthop_group_mgr);
};

} // end namespace eos

#endif // EOS_NEXTHOP_GROUP_H
