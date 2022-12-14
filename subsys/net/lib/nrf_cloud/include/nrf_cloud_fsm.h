/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef NRF_CLOUD_FSM_H__
#define NRF_CLOUD_FSM_H__

#include <stdbool.h>
#include <net/nrf_cloud.h>
#include <net/nrf_cloud_cell_pos.h>
#include "nrf_cloud_transport.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Internal state identifiers. */
enum nfsm_state {
	STATE_IDLE,
	STATE_INITIALIZED,
	STATE_CONNECTED,
	STATE_CC_CONNECTING,
	STATE_CC_CONNECTED,
	STATE_CLOUD_STATE_REQUESTED,
	STATE_UA_PIN_WAIT,
	STATE_UA_PIN_COMPLETE,
	STATE_DC_CONNECTING,
	STATE_DC_CONNECTED,
	STATE_TOTAL,
};

/**@brief Initialize the FSM. */
int nfsm_init(void);

/**@brief Handles incoming transport events based on the current state. */
int nfsm_handle_incoming_event(const struct nct_evt *evt,
			       enum nfsm_state current_state);

/**@brief Interface to get current state.
 *
 * To be implemented by the user application.
 */
enum nfsm_state nfsm_get_current_state(void);

/**@brief Interface to set the state.
 *
 * To be implemented by the user application.
 */
void nfsm_set_current_state_and_notify(enum nfsm_state state,
				       const struct nrf_cloud_evt *evt);

/**@brief Interface to initiate disconnection.
 *
 * To be implemented by the user application.
 */
void nfsm_disconnect(void);

/**@brief Get flag which indicates if user/app requested a disconnect.
 *
 * @retval true  User/application requested a disconnect.
 *         false Unexpected disconnect.
 */
bool nfsm_get_disconnect_requested(void);

#if defined(CONFIG_NRF_CLOUD_CELL_POS) && defined(CONFIG_NRF_CLOUD_MQTT)
/**@brief Sets a callback from the nrf_cloud_cell_pos module to
 * handle the cellular positioning response data from the cloud.
 */
void nfsm_set_cell_pos_response_cb(nrf_cloud_cell_pos_response_t cb);
#endif

#ifdef __cplusplus
}
#endif
#endif /* NRF_CLOUD_FSM_H__ */
