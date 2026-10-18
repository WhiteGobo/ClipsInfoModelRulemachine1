#include "udfdescription.h"
#include "literals.h"
#include <AdvancedCDatatypesTime.h>
#include "ClipsInfoModelRulemachine1_number.h"
#include "ClipsInfoModelRulemachine1_time.h"

#include "helper.h"
#include "namespace_XS.h"
#include "namespace_FUNC.h"
#include "namespace_PRED.h"

const UDFDescription builtinFunctionList_Time[];

static void year_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void month_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void day_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void hours_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void minutes_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void seconds_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void year_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void month_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void day_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void hours_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void minutes_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void seconds_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void timezone_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void timezone_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void timezone_from_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void years_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void months_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void days_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void hours_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void minutes_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void seconds_from_duration(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_dateTimes(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_dates(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_times(Environment *env, UDFContext *udfc, UDFValue *out);
static void add_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out);
static void multiply_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void divide_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void divide_yearMonthDuration_by_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void add_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out);
static void multiply_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void divide_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void divide_dayTimeDuration_by_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void add_Duration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void add_Duration_to_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void add_dayTimeDuration_to_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_Duration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_Duration_from_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract_dayTimeDuration_from_time(Environment *env, UDFContext *udfc, UDFValue *out);

static void dateTime_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void dateTime_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void dateTime_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void dateTime_not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void dateTime_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void dateTime_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);

static void date_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void date_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void date_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void date_not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void date_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static TypeHeader* TypeHeader_from_Duration(Environment*, Duration);
static void date_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);

static void time_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void time_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void time_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void time_not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void time_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void time_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);

static void duration_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void duration_not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void Duration_less_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void Duration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void Duration_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void Duration_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);


const UDFDescription builtinFunctionList_Time[] = {
	{"<"_FUNC_year_from_dateTime_">", "*", 1, 1, "*",
		year_from_dateTime, "year_from_dateTime"},
	{"<"_FUNC_month_from_dateTime_">", "*", 1, 1, "*",
		month_from_dateTime, "month_from_dateTime"},
	{"<"_FUNC_day_from_dateTime_">", "*", 1, 1, "*",
		day_from_dateTime, "day_from_dateTime"},
	{"<"_FUNC_hours_from_dateTime_">", "*", 1, 1, "*",
		hours_from_dateTime, "hours_from_dateTime"},
	{"<"_FUNC_minutes_from_dateTime_">", "*", 1, 1, "*",
		minutes_from_dateTime, "minutes_from_dateTime"},
	{"<"_FUNC_seconds_from_dateTime_">", "*", 1, 1, "*",
		seconds_from_dateTime, "seconds_from_dateTime"},
	{"<"_FUNC_year_from_date_">", "*", 1, 1, "*",
		year_from_date, "year_from_date"},
	{"<"_FUNC_month_from_date_">", "*", 1, 1, "*",
		month_from_date, "month_from_date"},
	{"<"_FUNC_day_from_date_">", "*", 1, 1, "*",
		day_from_date, "day_from_date"},
	{"<"_FUNC_hours_from_time_">", "*", 1, 1, "*",
		hours_from_time, "hours_from_time"},
	{"<"_FUNC_minutes_from_time_">", "*", 1, 1, "*",
		minutes_from_time, "minutes_from_time"},
	{"<"_FUNC_seconds_from_time_">", "*", 1, 1, "*",
		seconds_from_time, "seconds_from_time"},
	{"<"_FUNC_timezone_from_dateTime_">", "*", 1, 1, "*",
		timezone_from_dateTime, "timezone_from_dateTime"},
	{"<"_FUNC_timezone_from_date_">", "*", 1, 1, "*",
		timezone_from_date, "timezone_from_date"},
	{"<"_FUNC_timezone_from_time_">", "*", 1, 1, "*",
		timezone_from_time, "timezone_from_time"},
	{"<"_FUNC_years_from_duration_">", "*", 1, 1, "*",
		years_from_duration, "years_from_duration"},
	{"<"_FUNC_months_from_duration_">", "*", 1, 1, "*",
		months_from_duration, "months_from_duration"},
	{"<"_FUNC_days_from_duration_">", "*", 1, 1, "*",
		days_from_duration, "days_from_duration"},
	{"<"_FUNC_hours_from_duration_">", "*", 1, 1, "*",
		hours_from_duration, "hours_from_duration"},
	{"<"_FUNC_minutes_from_duration_">", "*", 1, 1, "*",
		minutes_from_duration, "minutes_from_duration"},
	{"<"_FUNC_seconds_from_duration_">", "*", 1, 1, "*",
		seconds_from_duration, "seconds_from_duration"},
	{"<"_FUNC_subtract_dateTimes_">", "*", 2, 2, "*",
		subtract_dateTimes, "subtract_dateTimes"},
	{"<"_FUNC_subtract_dates_">", "*", 2, 2, "*",
		subtract_dates, "subtract_dates"},
	{"<"_FUNC_subtract_times_">", "*", 2, 2, "*",
		subtract_times, "subtract_times"},
	{"<"_FUNC_add_yearMonthDurations_">", "*", 2, 2, "*",
		add_yearMonthDurations, "add_yearMonthDurations"},
	{"<"_FUNC_subtract_yearMonthDurations_">", "*", 2, 2, "*",
		subtract_yearMonthDurations, "subtract_yearMonthDurations"},
	{"<"_FUNC_multiply_yearMonthDuration_">", "*", 2, 2, "*",
		multiply_yearMonthDuration, "multiply_yearMonthDuration"},
	{"<"_FUNC_divide_yearMonthDuration_">", "*", 2, 2, "*",
		divide_yearMonthDuration, "divide_yearMonthDuration"},
	{"<"_FUNC_divide_yearMonthDuration_by_yearMonthDuration_">", "*", 2, 2, "*",
		divide_yearMonthDuration_by_yearMonthDuration, "divide_yearMonthDuration_by_yearMonthDuration"},

	{"<"_FUNC_add_dayTimeDurations_">", "*", 2, 2, "*",
		add_dayTimeDurations, "add_dayTimeDurations"},
	{"<"_FUNC_subtract_dayTimeDurations_">", "*", 2, 2, "*",
		subtract_dayTimeDurations, "subtract_dayTimeDurations"},
	{"<"_FUNC_multiply_dayTimeDuration_">", "*", 2, 2, "*",
		multiply_dayTimeDuration, "multiply_dayTimeDuration"},
	{"<"_FUNC_divide_dayTimeDuration_">", "*", 2, 2, "*",
		divide_dayTimeDuration, "divide_dayTimeDuration"},
	{"<"_FUNC_divide_dayTimeDuration_by_dayTimeDuration_">", "*", 2, 2, "*",
		divide_dayTimeDuration_by_dayTimeDuration, "divide_dayTimeDuration_by_dayTimeDuration"},
	{"<"_FUNC_add_yearMonthDuration_to_dateTime_">", "*", 2, 2, "*",
		add_Duration_to_dateTime, "add_Duration_to_dateTime"},
	{"<"_FUNC_add_yearMonthDuration_to_date_">", "*", 2, 2, "*",
		add_Duration_to_date, "add_Duration_to_date"},
	{"<"_FUNC_add_dayTimeDuration_to_dateTime_">", "*", 2, 2, "*",
		add_Duration_to_dateTime, "add_Duration_to_dateTime"},
	{"<"_FUNC_add_dayTimeDuration_to_date_">", "*", 2, 2, "*",
		add_Duration_to_date, "add_Duration_to_date"},
	{"<"_FUNC_add_dayTimeDuration_to_time_">", "*", 2, 2, "*",
		add_dayTimeDuration_to_time, "add_dayTimeDuration_to_time"},
	{"<"_FUNC_subtract_yearMonthDuration_from_dateTime_">", "*", 2, 2, "*",
		subtract_Duration_from_dateTime, "subtract_Duration_to_dateTime"},
	{"<"_FUNC_subtract_yearMonthDuration_from_date_">", "*", 2, 2, "*",
		subtract_Duration_from_date, "subtract_Duration_to_date"},
	{"<"_FUNC_subtract_dayTimeDuration_from_dateTime_">", "*", 2, 2, "*",
		subtract_Duration_from_dateTime, "subtract_Duration_to_dateTime"},
	{"<"_FUNC_subtract_dayTimeDuration_from_date_">", "*", 2, 2, "*",
		subtract_Duration_from_date, "subtract_Duration_to_date"},
	{"<"_FUNC_subtract_dayTimeDuration_from_time_">", "*", 2, 2, "*",
		subtract_dayTimeDuration_from_time, "subtract_dayTimeDuration_to_time"},
	{"<"_PRED_dateTime_equal_">", "*", 2, 2, "*",
		dateTime_equal, "dateTime_equal"},
	{"<"_PRED_dateTime_less_than_">", "*", 2, 2, "*",
		dateTime_less_than, "dateTime_less_than"},
	{"<"_PRED_dateTime_greater_than_">", "*", 2, 2, "*",
		dateTime_greater_than, "dateTime_greater_than"},
	{"<"_PRED_dateTime_not_equal_">", "*", 2, 2, "*",
		dateTime_not_equal, "dateTime_not_equal"},
	{"<"_PRED_dateTime_less_than_or_equal_">", "*", 2, 2, "*",
		dateTime_less_than_or_equal, "dateTime_less_than_or_equal"},
	{"<"_PRED_dateTime_greater_than_or_equal_">", "*", 2, 2, "*",
		dateTime_greater_than_or_equal, "dateTime_greater_than_or_equal"},

	{"<"_PRED_date_equal_">", "*", 2, 2, "*",
		date_equal, "date_equal"},
	{"<"_PRED_date_less_than_">", "*", 2, 2, "*",
		date_less_than, "date_less_than"},
	{"<"_PRED_date_greater_than_">", "*", 2, 2, "*",
		date_greater_than, "date_greater_than"},
	{"<"_PRED_date_not_equal_">", "*", 2, 2, "*",
		date_not_equal, "date_not_equal"},
	{"<"_PRED_date_less_than_or_equal_">", "*", 2, 2, "*",
		date_less_than_or_equal, "date_less_than_or_equal"},
	{"<"_PRED_date_greater_than_or_equal_">", "*", 2, 2, "*",
		date_greater_than_or_equal, "date_greater_than_or_equal"},
	{"<"_PRED_time_equal_">", "*", 2, 2, "*",
		time_equal, "time_equal"},
	{"<"_PRED_time_less_than_">", "*", 2, 2, "*",
		time_less_than, "time_less_than"},
	{"<"_PRED_time_greater_than_">", "*", 2, 2, "*",
		time_greater_than, "time_greater_than"},
	{"<"_PRED_time_not_equal_">", "*", 2, 2, "*",
		time_not_equal, "time_not_equal"},
	{"<"_PRED_time_less_than_or_equal_">", "*", 2, 2, "*",
		time_less_than_or_equal, "time_less_than_or_equal"},
	{"<"_PRED_time_greater_than_or_equal_">", "*", 2, 2, "*",
		time_greater_than_or_equal, "time_greater_than_or_equal"},

	{"<"_PRED_duration_equal_">", "*", 2, 2, "*",
		duration_equal, "duration_equal"},
	{"<"_PRED_duration_not_equal_">", "*", 2, 2, "*",
		duration_not_equal, "duration_not_equal"},

	{"<"_PRED_yearMonthDuration_less_than_">", "*", 2, 2, "*",
		Duration_less_than, "Duration_less_than"},
	{"<"_PRED_yearMonthDuration_greater_than_">", "*", 2, 2, "*",
		Duration_greater_than, "Duration_greater_than"},
	{"<"_PRED_yearMonthDuration_less_than_or_equal_">", "*", 2, 2, "*",
		Duration_less_than_or_equal, "Duration_less_than_or_equal"},
	{"<"_PRED_yearMonthDuration_greater_than_or_equal_">", "*", 2, 2, "*",
		Duration_greater_than_or_equal, "Duration_greater_than_or_equal"},

	{"<"_PRED_dayTimeDuration_less_than_">", "*", 2, 2, "*",
		Duration_less_than, "Duration_less_than"},
	{"<"_PRED_dayTimeDuration_greater_than_">", "*", 2, 2, "*",
		Duration_greater_than, "Duration_greater_than"},
	{"<"_PRED_dayTimeDuration_less_than_or_equal_">", "*", 2, 2, "*",
		Duration_less_than_or_equal, "Duration_less_than_or_equal"},
	{"<"_PRED_dayTimeDuration_greater_than_or_equal_">", "*", 2, 2, "*",
		Duration_greater_than_or_equal, "Duration_greater_than_or_equal"},

	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


static void year_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(ret, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, ret.year);
	}
}


static void month_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(ret, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, ret.month);
	}
}


static void day_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(ret, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, ret.day);
	}
}


static void hours_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(ret, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, ret.hour);
	}
}


static void minutes_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(ret, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, ret.minute);
	}
}


static void seconds_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime input = UDF_get_nth_as_DateTime(env, udfc, 1);
	Number ret_n;
	CLIPSValue ret_cv;
	if(DateTime_equal(input, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret_n = Number_from_decimal(input.seconds);
		ret_cv = CLIPSValue_from_Number(env, ret_n);
		out->value = ret_cv.value;
	}
}


static void year_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date input = UDF_get_nth_as_Date(env, udfc, 1);
	if(Date_equal(input, DATE_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, input.year);
	}
}


static void month_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date input = UDF_get_nth_as_Date(env, udfc, 1);
	if(Date_equal(input, DATE_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, input.month);
	}
}


static void day_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date input = UDF_get_nth_as_Date(env, udfc, 1);
	if(Date_equal(input, DATE_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, input.day);
	}
}


static void hours_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time input = UDF_get_nth_as_Time(env, udfc, 1);
	if(Time_equal(input, TIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, input.hour);
	}
}


static void minutes_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time input = UDF_get_nth_as_Time(env, udfc, 1);
	if(Time_equal(input, TIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		out->integerValue = CreateInteger(env, input.minute);
	}
}


static void seconds_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time input = UDF_get_nth_as_Time(env, udfc, 1);
	Number ret_n;
	CLIPSValue ret_cv;
	if(Time_equal(input, TIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret_n = Number_from_decimal(input.seconds);
		ret_cv = CLIPSValue_from_Number(env, ret_n);
		out->value = ret_cv.value;
	}
}

static void timezone_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	DateTime input = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(DateTime_equal(input, DATETIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = DateTime_offset_as_duration(input);
		out->header = TypeHeader_from_Duration(env, ret);
	}
}


static void timezone_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Date input = UDF_get_nth_as_Date(env, udfc, 1);
	if(Date_equal(input, DATE_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Date_offset_as_duration(input);
		out->header = TypeHeader_from_Duration(env, ret);
	}
}


static void timezone_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Time input = UDF_get_nth_as_Time(env, udfc, 1);
	if(Time_equal(input, TIME_NOTVALID)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Time_offset_as_duration(input);
		out->header = TypeHeader_from_Duration(env, ret);
	}
}


static void years_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	int64_t ret;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Duration_get_years(input);
		out->integerValue = CreateInteger(env, ret);
	}
}


static void months_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	int64_t ret;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Duration_get_months(input);
		out->integerValue = CreateInteger(env, ret);
	}
}


static void days_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	int64_t ret;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Duration_get_days(input);
		out->integerValue = CreateInteger(env, ret);
	}
}


static void hours_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	int64_t ret;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Duration_get_hours(input);
		out->integerValue = CreateInteger(env, ret);
	}
}


static void minutes_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	int64_t ret;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret = Duration_get_minutes(input);
		out->integerValue = CreateInteger(env, ret);
	}
}


static void seconds_from_duration(Environment *env, UDFContext *udfc, UDFValue *out){
	Number ret_n;
	CLIPSValue ret_cv;
	Duration input = UDF_get_nth_as_Duration(env, udfc, 1);
	if(Duration_equal(input, DURATION_NAN)){
		out->voidValue = VoidConstant(env);
		UDFThrowError(udfc);
	} else {
		ret_n = Number_from_decimal(Duration_get_seconds(input));
		ret_cv = CLIPSValue_from_Number(env, ret_n);
		out->value = ret_cv.value;
	}
}


static void subtract_dateTimes(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_sub(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void subtract_dates(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_sub(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void subtract_times(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_sub(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void add_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_add(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void subtract_yearMonthDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_sub(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void multiply_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Decimal y_decimal;
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Number y = UDF_get_nth_as_Number(env, udfc, 2);
	switch(y.type){
		case NT_DECIMAL:
			y_decimal = y.d;
			break;
		case NT_FLOAT:
		case NT_QUOTIENT:
			fprintf(stderr, "divie_yearMonthDuration not implemented\n");
		case NT_NAN:
			out->voidValue = VoidConstant(env);
			UDFThrowError(udfc);
			return;

	}
	ret = Duration_mult(x, y_decimal);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void divide_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Decimal y_decimal;
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Number y = UDF_get_nth_as_Number(env, udfc, 2);
	switch(y.type){
		case NT_DECIMAL:
			y_decimal = y.d;
			break;
		case NT_FLOAT:
		case NT_QUOTIENT:
			fprintf(stderr, "divie_yearMonthDuration not implemented\n");
		case NT_NAN:
			out->voidValue = VoidConstant(env);
			UDFThrowError(udfc);
			return;

	}
	ret = Duration_divide(x, y_decimal);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void divide_yearMonthDuration_by_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Number ret;
	CLIPSValue ret_cv;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_divide_by_Duration(x, y);
	ret_cv = CLIPSValue_from_Number(env, ret);
	out->value = ret_cv.value;
}


static void add_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_add(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void subtract_dayTimeDurations(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_sub(x, y);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void multiply_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Decimal y_decimal;
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Number y = UDF_get_nth_as_Number(env, udfc, 2);
	switch(y.type){
		case NT_DECIMAL:
			y_decimal = y.d;
			break;
		case NT_FLOAT:
		case NT_QUOTIENT:
			fprintf(stderr, "divie_yearMonthDuration not implemented\n");
		case NT_NAN:
			out->voidValue = VoidConstant(env);
			UDFThrowError(udfc);
			return;

	}
	ret = Duration_mult(x, y_decimal);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void divide_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Decimal y_decimal;
	Duration ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Number y = UDF_get_nth_as_Number(env, udfc, 2);
	switch(y.type){
		case NT_DECIMAL:
			y_decimal = y.d;
			break;
		case NT_FLOAT:
		case NT_QUOTIENT:
			fprintf(stderr, "divie_yearMonthDuration not implemented\n");
		case NT_NAN:
			out->voidValue = VoidConstant(env);
			UDFThrowError(udfc);
			return;

	}
	ret = Duration_divide(x, y_decimal);
	out->header = TypeHeader_from_Duration(env, ret);
}


static void divide_dayTimeDuration_by_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Number ret;
	CLIPSValue ret_cv;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_divide_by_Duration(x, y);
	ret_cv = CLIPSValue_from_Number(env, ret);
	out->value = ret_cv.value;
}


static void add_Duration_to_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret;
	CLIPSValue ret_cv;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = DateTime_add(x, y);
	ret_cv = CLIPSValue_from_DateTime(env, ret);
	out->value = ret_cv.value;
}


static void add_Duration_to_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date ret;
	CLIPSValue ret_cv;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Date_add(x, y);
	ret_cv = CLIPSValue_from_Date(env, ret);
	out->value = ret_cv.value;
}




static void add_dayTimeDuration_to_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time ret;
	CLIPSValue ret_cv;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Time_add(x, y);
	ret_cv = CLIPSValue_from_Time(env, ret);
	out->value = ret_cv.value;
}


static void subtract_Duration_from_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime ret;
	CLIPSValue ret_cv;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	y = Duration_neg(y);
	ret = DateTime_add(x, y);
	ret_cv = CLIPSValue_from_DateTime(env, ret);
	out->value = ret_cv.value;
}


static void subtract_Duration_from_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date ret;
	CLIPSValue ret_cv;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	y = Duration_neg(y);
	ret = Date_add(x, y);
	ret_cv = CLIPSValue_from_Date(env, ret);
	out->value = ret_cv.value;
}



static void subtract_dayTimeDuration_from_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time ret;
	CLIPSValue ret_cv;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	y = Duration_neg(y);
	ret = Time_add(x, y);
	ret_cv = CLIPSValue_from_Time(env, ret);
	out->value = ret_cv.value;
}


static void dateTime_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void dateTime_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_less(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void dateTime_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_greater(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void dateTime_not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_not_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void dateTime_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_less_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void dateTime_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	DateTime x = UDF_get_nth_as_DateTime(env, udfc, 1);
	DateTime y = UDF_get_nth_as_DateTime(env, udfc, 2);
	ret = DateTime_greater_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_less(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_greater(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_not_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_less_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void date_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Date x = UDF_get_nth_as_Date(env, udfc, 1);
	Date y = UDF_get_nth_as_Date(env, udfc, 2);
	ret = Date_greater_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_less(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_greater(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_not_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_less_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void time_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Time x = UDF_get_nth_as_Time(env, udfc, 1);
	Time y = UDF_get_nth_as_Time(env, udfc, 2);
	ret = Time_greater_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}



static void duration_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void duration_not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_not_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void Duration_less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_less(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void Duration_greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_greater(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void Duration_less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_less_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}


static void Duration_greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Duration x = UDF_get_nth_as_Duration(env, udfc, 1);
	Duration y = UDF_get_nth_as_Duration(env, udfc, 2);
	ret = Duration_greater_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}



static TypeHeader* TypeHeader_from_Duration(Environment *env, Duration dur){
	CLIPSValue out;
	out = CLIPSValue_from_Duration(env, dur);
	return out.header;
}
