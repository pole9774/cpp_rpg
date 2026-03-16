#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "playercharacter.h"
#include "itemmanager.h"

TEST_CASE("PointWell clamps current to max on construction") {
    PointWell pw(10, 5);
    CHECK(pw.getMax() == 5);
    CHECK(pw.getCurrent() == 5);
}

TEST_CASE("PointWell increaseCurrent does not exceed max") {
    PointWell pw(3, 5);
    pw.increaseCurrent(10);
    CHECK(pw.getCurrent() == 5);
}

TEST_CASE("PointWell reduceCurrent does not go below zero") {
    PointWell pw(3, 5);
    pw.reduceCurrent(10);
    CHECK(pw.getCurrent() == 0);
}
