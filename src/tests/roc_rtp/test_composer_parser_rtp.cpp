/*
 * Copyright (c) 2019 Roc Streaming authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

 #include <CppUTest/TestHarness.h>

 #include "roc_core/heap_arena.h"
 #include "roc_rtp/composer.h"
 #include "roc_rtp/parser.h"
 #include "roc_packet/packet_factory.h"
 
 namespace roc {
 namespace fec {
 
 namespace {
 
 enum { BufferSize = 100 };
 
 core::HeapArena arena;
 packet::PacketFactory packet_factory(arena, BufferSize);

 }

TEST_GROUP(composer_parser_rtp) {};

TEST(composer_parser_rtp, composer_rtp_returns_non_ok) {
    enum { Alignment = 8, InvalidPayloadSize = 10 };

    core::Slice<uint8_t> invalid_buffer;
    CHECK_FALSE(invalid_buffer);

    packet::PacketPtr packet = packet_factory.new_packet();
    CHECK(packet);

    rtp::Composer composer(NULL);

    if (composer.prepare(*packet, invalid_buffer, InvalidPayloadSize)) {
        CHECK_FALSE(composer.compose(*packet));
    }
}

TEST(composer_parser_rtp, parser_rtp_returns_non_ok) {
    enum { BufferSize = 4 };

    core::HeapArena arena;
    packet::PacketFactory packet_factory(arena, BufferSize);

    const roc::rtp::EncodingMap encodingmap(arena);

    core::BufferPtr buffer = packet_factory.new_packet_buffer();
    CHECK(buffer);

    core::Slice<uint8_t> slice(*buffer, 0, BufferSize);
    CHECK(slice);

    packet::PacketPtr packet = packet_factory.new_packet();
    CHECK(packet);

    roc::rtp::Parser parser(encodingmap, NULL);

    CHECK_FALSE(parser.parse(*packet, slice));
}

 }
}