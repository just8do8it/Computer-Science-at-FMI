#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cstring>
#include "doctest.h"
#include "calendar.h"

TEST_SUITE("Calendar tests") {
    TEST_CASE("Meeting constructors and basic operations") {
        Meeting meeting1("name1", "comment1", "28-02-1900", "19:15", "19:26");
        Meeting meeting2("name2", "comment2", "08-12-1100", "15:59", "16:05");
        // Meeting meeting3("name3", "comment3", "15-09-2002", "20:20", "23:00");
        // Meeting meeting5("name5", "comment5", "15-09-2002", "17:09", "19:00");

        Meeting meeting3(meeting2);
        meeting2 = meeting1;

        CHECK(strcmp(meeting3.getEndTime(), "16:05") == 0);
        CHECK(strcmp(meeting2.getDate(), "28-02-1900") == 0);

        try {
            Meeting meeting4("name4", "comment4", "29-02-1995", "15:30", "16:00");
        } catch (const char* e) {
            CHECK(strcmp(e, "Invalid date!") == 0);
        }
    }

    // TEST_CASE("Calendar constructors and basic operations") {

    // }
}