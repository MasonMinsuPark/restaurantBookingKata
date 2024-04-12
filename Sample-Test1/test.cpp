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

TEST_F(BookigItem, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	Schedule* schedule = new Schedule{ ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	EXPECT_THROW(bookScheduler.addSchedule(schedule), std::runtime_error);
}

TEST_F(BookigItem, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, UNDER_CAPACITY, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	EXPECT_EQ(true, bookScheduler.hasSchedule(schedule));
}

TEST_F(BookigItem, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	Schedule* schedule = new Schedule{ NOT_ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	Schedule* schedule2 = new Schedule{ NOT_ON_THE_HOUR, CAPACITY_PER_HOUR, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	EXPECT_THROW(bookScheduler.addSchedule(schedule2), std::runtime_error);
}

TEST_F(BookigItem, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {
	Schedule* schedule = new Schedule{ getTime(2023, 4, 12, 9, 0), CAPACITY_PER_HOUR, CUSTOMER };
	Schedule* schedule2 = new Schedule{ getTime(2023, 4, 12, 10, 0), CAPACITY_PER_HOUR, CUSTOMER };
	bookScheduler.addSchedule(schedule);
	bookScheduler.addSchedule(schedule2);
	EXPECT_EQ(true, bookScheduler.hasSchedule(schedule2));
}

TEST_F(BookigItem, ����Ϸ��_SMS��_������_�߼�) {

}

TEST_F(BookigItem, �̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST_F(BookigItem, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST_F(BookigItem, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST_F(BookigItem, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}