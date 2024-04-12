#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Project18/BookingScheduler.hpp"

class BookigItem : public testing::Test {
public:
	tm getTime(int year, int mon, int day, int hour, int min)
	{
		tm result = { 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
		mktime(&result);
		return result;
	}

	tm NOT_ON_THE_HOUR = getTime(2023, 4, 12, 9, 0);
	tm ON_THE_HOUR = getTime(2023, 4, 12, 9, 1);
	Customer CUSTOMER{ "Fake Name", "010-0000-0000" };
	const int UNDER_CAPACITY = 1;
	const int CAPACITY_PER_HOUR = 3;
	BookingScheduler bookScheduler{ CAPACITY_PER_HOUR };
};

TEST_F(BookigItem, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	EXPECT_THROW(bookScheduler.addSchedule(schedule), std::runtime_error);
}

TEST_F(BookigItem, 예약은_정시에만_가능하다_정시인_경우_예약가능) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	EXPECT_EQ(true, bookScheduler.hasSchedule(schedule));
}

TEST_F(BookigItem, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	Schedule* schedule2 = new Schedule{ NOT_ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	EXPECT_THROW(bookScheduler.addSchedule(schedule2), std::runtime_error);
}

TEST_F(BookigItem, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {
	Schedule* schedule = new Schedule{ getTime(2023, 4, 12, 9, 0), CAPACITY_PER_HOUR, CUSTOMER };
	Schedule* schedule2 = new Schedule{ getTime(2023, 4, 12, 10, 0), CAPACITY_PER_HOUR, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	bookScheduler.addSchedule(schedule2);
	EXPECT_EQ(true, bookScheduler.hasSchedule(schedule2));
}

TEST_F(BookigItem, 예약완료시_SMS는_무조건_발송) {

}

TEST_F(BookigItem, 이메일이_없는_경우에는_이메일_미발송) {

}

TEST_F(BookigItem, 이메일이_있는_경우에는_이메일_발송) {

}

TEST_F(BookigItem, 현재날짜가_일요일인_경우_예약불가_예외처리) {

}

TEST_F(BookigItem, 현재날짜가_일요일이_아닌경우_예약가능) {

}