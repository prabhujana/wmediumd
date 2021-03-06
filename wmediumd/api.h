/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _WMEDIUMD_API_H
#define _WMEDIUMD_API_H
#include <stdint.h>

enum wmediumd_message {
	/* invalid message */
	WMEDIUMD_MSG_INVALID,

	/* ACK, returned for each message for synchronisation */
	WMEDIUMD_MSG_ACK,

	/*
	 * Register/unregister for frames, this may be a pure control
	 * socket which doesn't want to see frames.
	 */
	WMEDIUMD_MSG_REGISTER,
	WMEDIUMD_MSG_UNREGISTER,

	/*
	 * netlink message, the data is the entire netlink message,
	 * this is used to communicate frame TX/RX in the familiar
	 * netlink format, to avoid having a special format
	 */
	WMEDIUMD_MSG_NETLINK,

	/* control message, see struct wmediumd_message_control */
	WMEDIUMD_MSG_SET_CONTROL,

	/*
	 * Indicates TX start if WMEDIUMD_RX_CTL_NOTIFY_TX_START is set,
	 * with struct wmediumd_tx_start as the payload.
	 */
	WMEDIUMD_MSG_TX_START,
};

struct wmediumd_message_header {
	/* type of message - see enum wmediumd_message */
	uint32_t type;
	/* data length */
	uint32_t data_len;

	/* variable-length data according to the message type */
	uint8_t data[];
};

enum wmediumd_control_flags {
	WMEDIUMD_CTL_NOTIFY_TX_START		= 1 << 0,
	WMEDIUMD_CTL_RX_ALL_FRAMES		= 1 << 1,
};

struct wmediumd_message_control {
	uint32_t flags;

	/*
	 * For compatibility, wmediumd is meant to understand shorter
	 * (and ignore unknown parts of longer) control messages than
	 * what's sent to it, so always take care to have defaults as
	 * zero since that's what it assumes.
	 */
};

struct wmediumd_tx_start {
	/*
	 * The cookie is set only when telling the sender, otherwise
	 * it's set to 0.
	 */
	uint64_t cookie;
	uint32_t freq;
	uint32_t reserved[3];
};

#endif /* _WMEDIUMD_API_H */
