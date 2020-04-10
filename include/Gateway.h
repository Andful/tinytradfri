#pragma once

#include <string.h>
#include <assert.h>

#define GATEWAY_MAX_IP_STRING_LENGTH 16
#define GATEWAY_TRADFRI_KEY_LENGTH 16
#define GATEWAY_MAX_IDENTITY_LENGTH 16

typedef struct _Gateway {
    char ip[GATEWAY_MAX_IP_STRING_LENGTH + 1];
    char key[GATEWAY_TRADFRI_KEY_LENGTH + 1];
    char identity[GATEWAY_MAX_IDENTITY_LENGTH + 1];
} Gateway;

Gateway newGateway(char* ip, char* key, char* identity) {
    Gateway gateway;
    
    memset(gateway.ip, '\0', sizeof(gateway.ip));
    memset(gateway.key, '\0', sizeof(gateway.key));
    memset(gateway.identity, '\0', sizeof(gateway.identity));

    assert(strlen(ip) <= GATEWAY_MAX_IP_STRING_LENGTH);
    assert(strlen(key) == GATEWAY_TRADFRI_KEY_LENGTH);
    assert(strlen(identity) <= GATEWAY_MAX_IDENTITY_LENGTH);

    strcpy(gateway.ip, ip);
    strcpy(gateway.key, key);
    strcpy(gateway.identity, identity);

    return gateway;
}