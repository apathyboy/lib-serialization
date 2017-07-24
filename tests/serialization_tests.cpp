
#include "serialization.hpp"

#include <cstdint>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

SCENARIO("8 bit integral types can be serialized and deserialized", "[integrals]") {
    GIVEN("an empty binary output stream") {
        std::ostringstream os{std::stringstream::binary};

        REQUIRE(os.str().length() == 0);

        WHEN("an 8 bit signed value is written to the stream") {
            int8_t tmp = -8;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 1); }

            THEN("the serialized output contains the expected value") {
                auto str = os.str();

                REQUIRE(static_cast<unsigned char>(str[0]) == 0xF8);
            }
        }

        WHEN("an 8 bit unsigned value is written to the stream") {
            uint8_t tmp = 254;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 1); }

            THEN("the serialized output contains the expected value") {
                auto str = os.str();

                REQUIRE(static_cast<unsigned char>(str[0]) == 0xFE);
            }
        }
    }

    GIVEN("an input stream containing an 8 bit signed value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        int8_t val = -8;
        esb::write(ss, val);

        WHEN("an 8 bit value is read from the stream") {
            auto tmp = esb::read<int8_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }

    GIVEN("an input stream containing an 8 bit unsigned value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        uint8_t val = 254;
        esb::write(ss, val);

        WHEN("an 8 bit value is read from the stream") {
            auto tmp = esb::read<uint8_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }
}

SCENARIO("16 bit integral types can be serialized and deserialized", "[integrals]") {
    GIVEN("an empty binary output stream") {
        std::ostringstream os{std::stringstream::binary};

        REQUIRE(os.str().length() == 0);

        WHEN("a 16 bit signed value is written to the stream") {
            int16_t tmp = -8;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 2); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xF8);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0xFF);
            }
        }

        WHEN("a 16 bit unsigned value is written to the stream") {
            uint16_t tmp = 254;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 2); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xFE);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0x00);
            }
        }
    }

    GIVEN("an input stream containing a 16 bit signed value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        int16_t val = -8;
        esb::write(ss, val);

        WHEN("a 16 bit value is read from the stream") {
            auto tmp = esb::read<int16_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }

    GIVEN("an input stream containing a 16 bit unsigned value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        uint16_t val = 254;
        esb::write(ss, val);

        WHEN("a 16 bit value is read from the stream") {
            auto tmp = esb::read<uint16_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }
}

SCENARIO("32 bit integral types can be serialized and deserialized", "[integrals]") {
    GIVEN("an empty binary output stream") {
        std::ostringstream os{std::stringstream::binary};

        REQUIRE(os.str().length() == 0);

        WHEN("a 32 bit signed value is written to the stream") {
            int32_t tmp = -8;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 4); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xF8);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[2]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[3]) == 0xFF);
            }
        }

        WHEN("a 32 bit unsigned value is written to the stream") {
            uint32_t tmp = 254;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 4); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xFE);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[2]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[3]) == 0x00);
            }
        }
    }

    GIVEN("an input stream containing a 32 bit signed value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        int32_t val = -8;
        esb::write(ss, val);

        WHEN("a 32 bit value is read from the stream") {
            auto tmp = esb::read<int32_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }

    GIVEN("an input stream containing a 32 bit unsigned value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        uint32_t val = 254;
        esb::write(ss, val);

        WHEN("a 32 bit value is read from the stream") {
            auto tmp = esb::read<uint32_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }
}

SCENARIO("64 bit integral types can be serialized and deserialized", "[integrals]") {
    GIVEN("an empty binary output stream") {
        std::ostringstream os{std::stringstream::binary};

        REQUIRE(os.str().length() == 0);

        WHEN("a 64 bit signed value is written to the stream") {
            int64_t tmp = -8;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 8); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xF8);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[2]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[3]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[4]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[5]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[6]) == 0xFF);
                REQUIRE(static_cast<uint8_t>(str[7]) == 0xFF);
            }
        }

        WHEN("a 64 bit unsigned value is written to the stream") {
            uint64_t tmp = 254;
            esb::write(os, tmp);

            THEN("the serialized output length is increased") { REQUIRE(os.str().length() == 8); }

            THEN("the serialized output is little endian") {
                auto str = os.str();

                REQUIRE(static_cast<uint8_t>(str[0]) == 0xFE);
                REQUIRE(static_cast<uint8_t>(str[1]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[2]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[3]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[4]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[5]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[6]) == 0x00);
                REQUIRE(static_cast<uint8_t>(str[7]) == 0x00);
            }
        }
    }

    GIVEN("an input stream containing a 64 bit signed value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        int64_t val = -8;
        esb::write(ss, val);

        WHEN("a 64 bit value is read from the stream") {
            auto tmp = esb::read<int64_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }

    GIVEN("an input stream containing a 64 bit unsigned value") {
        std::stringstream ss(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        uint64_t val = 254;
        esb::write(ss, val);

        WHEN("a 64 bit value is read from the stream") {
            auto tmp = esb::read<uint32_t>(ss);

            THEN("the read value matches the written value") { REQUIRE(val == tmp); }
        }
    }
}

SCENARIO("string types can be serialized and deserialzed", "[strings]") {
    GIVEN("an initialized ascii string and a binary stream") {
        std::string       asciiStr = "Some string value";
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        WHEN("the stream has an ascii string written to it") {
            esb::write(bs, asciiStr);

            THEN(
                "the serialized output size is increased by the length of the string, plus a "
                "uint16_t string length") {
                REQUIRE(bs.str().length() == asciiStr.length() + sizeof(uint16_t));
            }

            AND_THEN("the output contains a uint16_t string length, followed by the ascii string") {
                auto length = esb::peekAt<uint16_t>(bs, 0);
                REQUIRE(length == asciiStr.length());

                auto str = bs.str();

                REQUIRE(str[2] == asciiStr[0]);
                REQUIRE(str[18] == asciiStr[16]);
            }
        }
    }

    GIVEN("a binary string containing a serialized ascii string") {
        std::string       asciiStr = "Some string value";
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        esb::write(bs, asciiStr);

        WHEN("the stream has the string read from it") {
            auto testStr = esb::read<std::string>(bs);

            THEN("the value re ad is the value expected") {
                REQUIRE(testStr.compare(asciiStr) == 0);
            }
        }

        AND_WHEN("the stream is read into an existing string variable") {
            std::string testStr;
            esb::read(bs, testStr);

            THEN("the value read is the value expected") {
                REQUIRE(testStr.compare(asciiStr) == 0);
            }
        }
    }
}

SCENARIO("enums with underlying integral types can be serialized and deserialzed", "[enums]") {
    enum class TEST_ENUM : uint32_t { TEST1 = 1, TEST2 = 2 };

    GIVEN("an initialized enum value and a binary stream") {
        TEST_ENUM         tmp = TEST_ENUM::TEST1;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        WHEN("the stream has the enum written to it") {
            esb::write(bs, tmp);

            THEN("the serialized output size is increased by 4") {
                REQUIRE(bs.str().length() == 4);
            }

            AND_THEN("the serialized output is little-endian") {
                auto str = bs.str();
                REQUIRE(str[0] == (char)0x01);
                REQUIRE(str[1] == (char)0x00);
                REQUIRE(str[2] == (char)0x00);
                REQUIRE(str[3] == (char)0x00);
            }
        }
    }

    GIVEN("a binary stream containing a serialized enum value") {
        TEST_ENUM         tmp = TEST_ENUM::TEST1;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        esb::write(bs, tmp);

        WHEN("the stream has the enum read from it") {
            auto test_enum = esb::read<TEST_ENUM>(bs);

            THEN("the value read is the value expected") { REQUIRE(test_enum == tmp); }
        }

        AND_WHEN("the stream is read into an existing enum variable") {
            TEST_ENUM tmp;
            esb::read(bs, tmp);

            THEN("the value read is the value expected") { REQUIRE(tmp == TEST_ENUM::TEST1); }
        }
    }
}

SCENARIO("booleans can be serialized and deserialzed", "[booleans]") {
    GIVEN("an initialized boolean and a binary stream") {
        bool              tmp = true;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);

        WHEN("the stream has the boolean written to it") {
            esb::write(bs, tmp);

            THEN("the serialized output size is increased by 1") {
                REQUIRE(bs.str().length() == 1);
            }

            AND_THEN("the serialized output contains 1 for true") {
                auto str = bs.str();
                REQUIRE(str[0] == (char)0x01);
            }
        }
    }

    GIVEN("a binary stream containing a boolean") {
        bool              expected = true;
        std::stringstream bs(std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        esb::write(bs, expected);

        WHEN("the stream has the integer read from it") {
            auto tmp = esb::read<bool>(bs);

            THEN("the value read is the value expected") { REQUIRE(tmp == expected); }
        }

        AND_WHEN("the stream is read into an existing integer variable") {
            bool tmp;
            esb::read(bs, tmp);

            THEN("the value read is the value expected") { REQUIRE(tmp == expected); }
        }
    }
}
