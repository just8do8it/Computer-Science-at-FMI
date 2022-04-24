// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include <cstring>
// #include "doctest.h"
// #include "calendar.h"

// TEST_SUITE("Personal calendar tests") {
//     TEST_CASE("Meeting constructors and basic operations") {
//         Meeting meeting1("name1", "comment1", "28-02-1900", "19:15", "19:26");
//         Meeting meeting2("name2", "comment2", "08-12-1100", "15:59", "16:05");

//         Meeting meeting3(meeting2);
//         meeting2 = meeting1;

//         CHECK(strcmp(meeting3.getEndTime(), "16:05") == 0);
//         CHECK(strcmp(meeting2.getDate(), "28-02-1900") == 0);

//         try {
//             Meeting meeting4("name4", "comment4", "29-02-1995", "15:30", "16:00");
//         } catch (const char* e) {
//             CHECK(strcmp(e, "Invalid date!") == 0);
//         }
//     }

//     TEST_CASE("Calendar constructors and basic operations") {
//         Calendar calendar1("calendar1.txt");
//         Calendar calendar2("calendar2.txt");

//         Calendar calendar3(calendar1);
//         calendar1 = calendar2;

//         CHECK(strcmp(calendar3.getFilename(), "calendar1.txt") == 0);
//         CHECK(strcmp(calendar1.getFilename(), "calendar2.txt") == 0);
//     }

//     TEST_CASE("Adding and removing meetings") {
//         Meeting meeting1("name1", "comment1", "28-02-1900", "19:15", "19:26");
//         Meeting meeting2("name2", "comment2", "08-12-1100", "15:59", "16:05");
//         Meeting meeting3("name3", "comment3", "15-09-2002", "20:20", "23:00");
//         Meeting meeting4("name4", "comment4", "31-05-1995", "07:30", "09:45");
//         Meeting meeting5("name5", "comment5", "15-09-2002", "17:09", "19:00");

//         Calendar calendar("calendar1.txt");

//         calendar.addMeeting(meeting1);
//         calendar.addMeeting(meeting2);
//         calendar.addMeeting(meeting3);
//         calendar.addMeeting(meeting4);
//         calendar.addMeeting(meeting5);

//         CHECK(calendar.getSize() == 5);
//         CHECK(calendar.getCapacity() == 8);

//         calendar.removeMeeting(meeting5);

//         CHECK(strcmp(calendar.getMeetings()[4]->getDate(), meeting3.getDate()) == 0);
//         CHECK(*calendar.getMeetings()[3] == meeting3);

//         calendar.removeMeeting(meeting1);
//         calendar.removeMeeting(meeting2);

//         CHECK(calendar.getSize() == 2);
//         CHECK(calendar.getCapacity() == 4);
//     }

//     TEST_CASE("Changing meeting attributes") {
//         Meeting meeting1("name1", "comment1", "28-02-1900", "19:15", "19:26");
//         Meeting meeting2("name2", "comment2", "08-12-1100", "15:59", "16:05");

//         Calendar calendar("calendar1.txt");

//         Meeting meeting3("name2", "comment2", "08-12-1100", "16:00", "16:05");
//         calendar.addMeeting(meeting1);
//         calendar.addMeeting(meeting2);

//         calendar.changeStartTime(meeting2, "16:00");
//         calendar.changeEndTime(meeting3, "22:30");

//         CHECK(strcmp(calendar.getMeetings()[0]->getStartTime(), "16:00") == 0);
//         CHECK(strcmp(calendar.getMeetings()[0]->getEndTime(), "22:30") == 0);
//     }
// }