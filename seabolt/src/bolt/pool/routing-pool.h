/*
 * Copyright (c) 2002-2018 "Neo4j,"
 * Neo4j Sweden AB [http://neo4j.com]
 *
 * This file is part of Neo4j.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SEABOLT_ALL_DISCOVERY_H
#define SEABOLT_ALL_DISCOVERY_H

#include "bolt/connector.h"
#include "bolt/address.h"
#include "bolt/values.h"

struct BoltRoutingPool {
    struct BoltAddress* address;
    const struct BoltConfig* config;
    const struct BoltValue* auth_token;

    struct RoutingTable* routing_table;
    int readers_offset;
    int writers_offset;

    struct BoltAddressSet* servers;
    struct BoltDirectPool** server_pools;

    mutex_t lock;
};

#define SIZE_OF_ROUTING_POOL sizeof(struct BoltRoutingPool)
#define SIZE_OF_ROUTING_POOL_PTR sizeof(struct BoltRoutingConnectionPool*)

struct BoltRoutingPool*
BoltRoutingPool_create(struct BoltAddress* address, const struct BoltValue* auth_token, const struct BoltConfig* config);

void BoltRoutingPool_destroy(struct BoltRoutingPool* pool);

struct BoltConnectionResult
BoltRoutingPool_acquire(struct BoltRoutingPool* pool, enum BoltAccessMode mode);

int BoltRoutingPool_release(struct BoltRoutingPool* pool, struct BoltConnection* connection);

#endif //SEABOLT_ALL_DISCOVERY_H