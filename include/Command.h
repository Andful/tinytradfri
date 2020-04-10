#pragma once

#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/time.h>

#include <libcoap.h>
#include <coap.h>

#include "Gateway.h"

#define BUFSIZE 2048

/** Rapresentation of tadfri command
*/
typedef struct _Command {
    uint8_t code;
    coap_optlist_t optlist;
    uint8_t* data;
} Command;

static void coap_handler(coap_context_t *ctx, coap_session_t *session,
                            coap_pdu_t *sent, coap_pdu_t *received,
                            const coap_tid_t id) {

}

bool sendCommand(Gateway* gateway, uint8_t method, uint8_t** paths,const int pathn, uint8_t* data) {
    coap_optlist_t optlist[pathn];

    for (int i = 0; i < pathn; i++) {
        if (i < pathn - 1) {
            optlist[i].next = &(optlist[i + 1]);
        } else {
            optlist[i].next = NULL;
        }
        optlist[i].number=COAP_OPTION_URI_PATH;
        optlist[i].length=strlen((char*)paths[i]);
        optlist[i].data=paths[i];
    }
    
    coap_context_t *ctx = coap_new_context(NULL);
    if (!ctx) {
        return false;
    }

    coap_address_t dst_addr;

    coap_address_init(&dst_addr);
    dst_addr.addr.sin.sin_family = AF_INET;
    inet_pton(AF_INET, gateway->ip, &(dst_addr.addr.sin.sin_addr));
    dst_addr.addr.sin.sin_port = htons(5683);

    coap_session_t* session = coap_new_client_session(ctx, NULL, &dst_addr, COAP_PROTO_UDP);

    if (!session) {
        return false;
    }

    coap_register_response_handler(ctx, coap_handler);

    coap_pdu_t * request = coap_new_pdu(session);
    if (!request) {
        return false;
    }

    request->type = COAP_MESSAGE_CON;
    request->tid = coap_new_message_id(session);
    request->code = COAP_REQUEST_GET;

    coap_add_optlist_pdu(request, (coap_optlist_t**)&(optlist));

    coap_send(session, request);

    return true;
}