#include "gtest/gtest.h"
#include "AST/node.hpp"

TEST(Atom, HasAClassName) {
  NAtom *atom = new NAtom("foo");
  EXPECT_EQ("a", atom->className());
}

TEST(Atom, HasAName) {
  NAtom *atom = new NAtom("foo");
  EXPECT_EQ("foo", atom->name());
}
