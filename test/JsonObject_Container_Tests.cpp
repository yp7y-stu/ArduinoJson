// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson/JsonArray.hpp>
#include <ArduinoJson/JsonObject.hpp>
#include <ArduinoJson/JsonValue.hpp>
#include <ArduinoJson/StaticJsonBuffer.hpp>
#include "Printers.hpp"

using namespace ArduinoJson;

class JsonObject_Container_Tests : public ::testing::Test {
 protected:
  virtual void SetUp() { object = json.createObject(); }

  StaticJsonBuffer<42> json;
  JsonObject object;
};

TEST_F(JsonObject_Container_Tests, InitialSizeIsZero) {
  EXPECT_EQ(0, object.size());
}

TEST_F(JsonObject_Container_Tests, Grow_WhenValuesAreAdded) {
  object["hello"];
  EXPECT_EQ(1, object.size());

  object["world"];
  EXPECT_EQ(2, object.size());
}

TEST_F(JsonObject_Container_Tests, DoNotGrow_WhenSameValueIsAdded) {
  object["hello"];
  EXPECT_EQ(1, object.size());

  object["hello"];
  EXPECT_EQ(1, object.size());
}

TEST_F(JsonObject_Container_Tests, Shrink_WhenValuesAreRemoved) {
  object["hello"];
  object["world"];

  object.remove("hello");
  EXPECT_EQ(1, object.size());

  object.remove("world");
  EXPECT_EQ(0, object.size());
}

TEST_F(JsonObject_Container_Tests,
       DoNotShrink_WhenRemoveIsCalledWithAWrongKey) {
  object["hello"];
  object["world"];

  object.remove(":-P");

  EXPECT_EQ(2, object.size());
}

TEST_F(JsonObject_Container_Tests, CanStoreIntegers) {
  object["hello"] = 123;
  object["world"] = 456;

  EXPECT_EQ(123, object["hello"].as<int>());
  EXPECT_EQ(456, object["world"].as<int>());
}

TEST_F(JsonObject_Container_Tests, CanStoreDoubles) {
  object["hello"] = 123.45;
  object["world"] = 456.78;

  EXPECT_EQ(123.45, object["hello"].as<double>());
  EXPECT_EQ(456.78, object["world"].as<double>());
}

TEST_F(JsonObject_Container_Tests, CanStoreBooleans) {
  object["hello"] = true;
  object["world"] = false;

  EXPECT_TRUE(object["hello"].as<bool>());
  EXPECT_FALSE(object["world"].as<bool>());
}

TEST_F(JsonObject_Container_Tests, CanStoreStrings) {
  object["hello"] = "h3110";
  object["world"] = "w0r1d";

  EXPECT_STREQ("h3110", object["hello"].as<const char*>());
  EXPECT_STREQ("w0r1d", object["world"].as<const char*>());
}

TEST_F(JsonObject_Container_Tests, CanStoreInnerArrays) {
  JsonArray innerarray1 = json.createArray();
  JsonArray innerarray2 = json.createArray();

  object["hello"] = innerarray1;
  object["world"] = innerarray2;

  EXPECT_EQ(innerarray1, object["hello"].as<JsonArray>());
  EXPECT_EQ(innerarray2, object["world"].as<JsonArray>());
}

TEST_F(JsonObject_Container_Tests, CanStoreInnerObjects) {
  JsonObject innerObject1 = json.createObject();
  JsonObject innerObject2 = json.createObject();

  object["hello"] = innerObject1;
  object["world"] = innerObject2;

  EXPECT_EQ(innerObject1, object["hello"].as<JsonObject>());
  EXPECT_EQ(innerObject2, object["world"].as<JsonObject>());
}
