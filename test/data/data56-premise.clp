(defrule printrule
	=>
	(println "test print:
		"(<http://www.w3.org/2007/rif-builtin-predicate#dateTime-equal> (gen-literal "2002-04-02T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime"))"
		"(gen-literal "2000-10-27T09:57:00" "http://www.w3.org/2001/XMLSchema#dateTime")"
		"(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-dateTime> 
			(gen-literal "2000-10-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)"
		"(gen-literal "2000-10-26" "http://www.w3.org/2001/XMLSchema#date")"
		"(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-date> 
			(gen-literal "2000-10-30" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)"
		"(gen-literal "09:57:00" "http://www.w3.org/2001/XMLSchema#time")"
		"(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-time> 
			(gen-literal "11:12:00" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)"
	")
)

(defrule rule0
	(test (eq 2000 (<http://www.w3.org/2007/rif-builtin-function#year-from-dateTime> (gen-literal "1999-12-31T24:00:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq 5 (<http://www.w3.org/2007/rif-builtin-function#month-from-dateTime> (gen-literal "1999-05-31T13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq 31 (<http://www.w3.org/2007/rif-builtin-function#day-from-dateTime> (gen-literal "1999-05-31T13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq 8 (<http://www.w3.org/2007/rif-builtin-function#hours-from-dateTime> (gen-literal "1999-05-31T08:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq 20 (<http://www.w3.org/2007/rif-builtin-function#minutes-from-dateTime> (gen-literal "1999-05-31T13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq 0 (<http://www.w3.org/2007/rif-builtin-function#seconds-from-dateTime> (gen-literal "1999-05-31T13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))

	(test (eq 1999 (<http://www.w3.org/2007/rif-builtin-function#year-from-date> (gen-literal "1999-12-31" "http://www.w3.org/2001/XMLSchema#date")) ))
	(test (eq 5 (<http://www.w3.org/2007/rif-builtin-function#month-from-date> (gen-literal "1999-05-31" "http://www.w3.org/2001/XMLSchema#date")) ))
	(test (eq 31 (<http://www.w3.org/2007/rif-builtin-function#day-from-date> (gen-literal "1999-05-31" "http://www.w3.org/2001/XMLSchema#date")) ))
	(test (eq 8 (<http://www.w3.org/2007/rif-builtin-function#hours-from-time> (gen-literal "08:20:00-05:00" "http://www.w3.org/2001/XMLSchema#time")) ))
	(test (eq 20 (<http://www.w3.org/2007/rif-builtin-function#minutes-from-time> (gen-literal "08:20:00-05:00" "http://www.w3.org/2001/XMLSchema#time")) ))
	(test (eq 0 (<http://www.w3.org/2007/rif-builtin-function#seconds-from-time> (gen-literal "08:20:00-05:00" "http://www.w3.org/2001/XMLSchema#time")) ))

	(test (eq (gen-literal "-PT5H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (<http://www.w3.org/2007/rif-builtin-function#timezone-from-dateTime> (gen-literal "1999-05-31T13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")) ))
	(test (eq (gen-literal "-PT5H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (<http://www.w3.org/2007/rif-builtin-function#timezone-from-date> (gen-literal "1999-05-31-05:00" "http://www.w3.org/2001/XMLSchema#date")) ))
	(test (eq (gen-literal "-PT5H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (<http://www.w3.org/2007/rif-builtin-function#timezone-from-time> (gen-literal "13:20:00-05:00" "http://www.w3.org/2001/XMLSchema#time")) ))
	(test (eq 21 (<http://www.w3.org/2007/rif-builtin-function#years-from-duration> (gen-literal "P20Y15M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")) ))
	(test (eq 3 (<http://www.w3.org/2007/rif-builtin-function#months-from-duration> (gen-literal "P20Y15M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")) ))
	(test (eq 3 (<http://www.w3.org/2007/rif-builtin-function#days-from-duration> (gen-literal "P3DT10H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")) ))
	(test (eq 10 (<http://www.w3.org/2007/rif-builtin-function#hours-from-duration> (gen-literal "P3DT10H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")) ))
	(test (eq -30 (<http://www.w3.org/2007/rif-builtin-function#minutes-from-duration> (gen-literal "-P5DT12H30M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")) ))
	(test (eq (gen-literal "12.5" "http://www.w3.org/2001/XMLSchema#decimal") (<http://www.w3.org/2007/rif-builtin-function#seconds-from-duration> (gen-literal "P3DT10H12.5S" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")) ))

	(test (eq
		(gen-literal "P337DT2H12M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dateTimes> 
			(gen-literal "2000-10-30T06:12:00-05:00" "http://www.w3.org/2001/XMLSchema#dateTime")
			(gen-literal "1999-11-28T09:00:00Z" "http://www.w3.org/2001/XMLSchema#dateTime")
		)
	))
	(test (eq
		(gen-literal "P337D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dates> 
			(gen-literal "2000-10-30Z" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "1999-11-28Z" "http://www.w3.org/2001/XMLSchema#date")
		)
	))
	(test (eq
		(gen-literal "PT7H12M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-times> 
			(gen-literal "11:12:00Z" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "04:00:00Z" "http://www.w3.org/2001/XMLSchema#time")
		)
	))
	(test (eq
		(gen-literal "P6Y2M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		(<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDurations> 
			(gen-literal "P2Y11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P3Y3M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "-P4M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDurations> 
			(gen-literal "P2Y11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P3Y3M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "P6Y9M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		(<http://www.w3.org/2007/rif-builtin-function#multiply-yearMonthDuration> 
			(gen-literal "P2Y11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "2.3" "http://www.w3.org/2001/XMLSchema#decimal")
		)
	))
	(test (eq
		(gen-literal "P1Y11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		(<http://www.w3.org/2007/rif-builtin-function#divide-yearMonthDuration> 
			(gen-literal "P2Y11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "1.5" "http://www.w3.org/2001/XMLSchema#decimal")
		)
	))
	(test (eq
		(gen-literal "-2.5" "http://www.w3.org/2001/XMLSchema#decimal")
		(<http://www.w3.org/2007/rif-builtin-function#divide-yearMonthDuration-by-yearMonthDuration> 
			(gen-literal "P3Y4M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "-P1Y4M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "P8DT5M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDurations> 
			(gen-literal "P2DT12H5M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "P5DT12H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "P1DT1H30M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDurations> 
			(gen-literal "P2DT12H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "P1DT10H30M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "PT4H33M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#multiply-dayTimeDuration> 
			(gen-literal "PT2H10M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "2.1" "http://www.w3.org/2001/XMLSchema#decimal")
		)
	))
	(test (eq
		(gen-literal "P2D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		(<http://www.w3.org/2007/rif-builtin-function#divide-dayTimeDuration> 
			(gen-literal "P4D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") 2
		)
	))
	(test (eq 2
		(<http://www.w3.org/2007/rif-builtin-function#divide-dayTimeDuration-by-dayTimeDuration> 
			(gen-literal "P4D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "P2D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "2001-12-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime")
		(<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDuration-to-dateTime> 
			(gen-literal "2000-10-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "P1Y2M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "2001-12-30" "http://www.w3.org/2001/XMLSchema#date")
		(<http://www.w3.org/2007/rif-builtin-function#add-yearMonthDuration-to-date> 
			(gen-literal "2000-10-30" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "P1Y2M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))

	(test (eq
		(gen-literal "2000-11-02T12:27:00" "http://www.w3.org/2001/XMLSchema#dateTime")
		(<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-dateTime> 
			(gen-literal "2000-10-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "2004-11-01Z" "http://www.w3.org/2001/XMLSchema#date")
		(<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-date> 
			(gen-literal "2004-10-30Z" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "P2DT2H30M0S" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "12:27:00" "http://www.w3.org/2001/XMLSchema#time")
		(<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-time> 
			(gen-literal "11:12:00" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "02:27:00+03:00" "http://www.w3.org/2001/XMLSchema#time")
		(<http://www.w3.org/2007/rif-builtin-function#add-dayTimeDuration-to-time> 
			(gen-literal "23:12:00+03:00" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "P1DT3H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "1999-08-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDuration-from-dateTime> 
			(gen-literal "2000-10-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "P1Y2M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "1999-08-30" "http://www.w3.org/2001/XMLSchema#date")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-yearMonthDuration-from-date> 
			(gen-literal "2000-10-30" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "P1Y2M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")
		)
	))
	(test (eq
		(gen-literal "2000-10-27T09:57:00" "http://www.w3.org/2001/XMLSchema#dateTime")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-dateTime> 
			(gen-literal "2000-10-30T11:12:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "2000-10-26" "http://www.w3.org/2001/XMLSchema#date")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-date> 
			(gen-literal "2000-10-30" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))
	(test (eq
		(gen-literal "09:57:00" "http://www.w3.org/2001/XMLSchema#time")
		(<http://www.w3.org/2007/rif-builtin-function#subtract-dayTimeDuration-from-time> 
			(gen-literal "11:12:00" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "P3DT1H15M" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")
		)
	))

	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-equal> (gen-literal "2002-04-02T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-less-than> (gen-literal "2002-04-01T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-greater-than> (gen-literal "2002-04-03T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-equal> (gen-literal "2004-12-25-12:00" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-26+12:00" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-less-than> (gen-literal "2004-12-24" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-26" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-greater-than> (gen-literal "2004-12-26" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-25" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-equal> (gen-literal "21:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-less-than> (gen-literal "20:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-greater-than> (gen-literal "22:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#duration-equal> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P12M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-less-than> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P13M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-greater-than> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-less-than> (gen-literal "P1D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "PT25H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-greater-than> (gen-literal "P1D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "PT23H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-not-equal> (gen-literal "2002-04-01T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-less-than-or-equal> (gen-literal "2002-04-01T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dateTime-greater-than-or-equal> (gen-literal "2002-04-03T12:00:00-01:00" "http://www.w3.org/2001/XMLSchema#dateTime") (gen-literal "2002-04-02T17:00:00+04:00" "http://www.w3.org/2001/XMLSchema#dateTime")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-not-equal> (gen-literal "2004-12-24" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-26" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-less-than-or-equal> (gen-literal "2004-12-24" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-26" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#date-greater-than-or-equal> (gen-literal "2004-12-26" "http://www.w3.org/2001/XMLSchema#date") (gen-literal "2004-12-25" "http://www.w3.org/2001/XMLSchema#date")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-not-equal> (gen-literal "20:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-less-than-or-equal> (gen-literal "20:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#time-greater-than-or-equal> (gen-literal "22:30:00+10:30" "http://www.w3.org/2001/XMLSchema#time") (gen-literal "06:00:00-05:00" "http://www.w3.org/2001/XMLSchema#time")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#duration-not-equal> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P1M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-less-than-or-equal> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P13M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#yearMonthDuration-greater-than-or-equal> (gen-literal "P1Y" "http://www.w3.org/2001/XMLSchema#yearMonthDuration") (gen-literal "P11M" "http://www.w3.org/2001/XMLSchema#yearMonthDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-less-than-or-equal> (gen-literal "P1D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "PT25H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")))
	(test (<http://www.w3.org/2007/rif-builtin-predicate#dayTimeDuration-greater-than-or-equal> (gen-literal "P1D" "http://www.w3.org/2001/XMLSchema#dayTimeDuration") (gen-literal "PT23H" "http://www.w3.org/2001/XMLSchema#dayTimeDuration")))
	=>
	(<http://white.gobo/ClipsInfoModelRulemachine1#import> "http://example.com/data-ok-import")
)
