/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Ferdinando Ametrano

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/termstructures/volatility/capfloor/constantcapfloortermvol.hpp>
#include <ql/quotes/simplequote.hpp>

namespace QuantLib {

    // floating reference date, floating market data
    ConstantCapFloorTermVolatility::ConstantCapFloorTermVolatility(
                                                    Natural settlementDays,
                                                    const Handle<Quote>& vol,
                                                    const DayCounter& dc,
                                                    const Calendar& cal,
                                                    BusinessDayConvention bdc)
    : CapFloorTermVolatilityStructure(settlementDays, cal, bdc, dc),
      volatility_(vol) {
        registerWith(volatility_);
    }

    // fixed reference date, floating market data
    ConstantCapFloorTermVolatility::ConstantCapFloorTermVolatility(
                                                    const Date& referenceDate,
                                                    const Handle<Quote>& vol,
                                                    const DayCounter& dc,
                                                    const Calendar& cal,
                                                    BusinessDayConvention bdc)
    : CapFloorTermVolatilityStructure(referenceDate, cal, bdc, dc),
      volatility_(vol) {
        registerWith(volatility_);
    }

    // floating reference date, fixed market data
    ConstantCapFloorTermVolatility::ConstantCapFloorTermVolatility(
                                                    Natural settlementDays,
                                                    Volatility vol,
                                                    const DayCounter& dc,
                                                    const Calendar& cal,
                                                    BusinessDayConvention bdc)
    : CapFloorTermVolatilityStructure(settlementDays, cal, bdc, dc),
      volatility_(boost::shared_ptr<Quote>(new SimpleQuote(vol))) {}

    // fixed reference date, fixed market data
    ConstantCapFloorTermVolatility::ConstantCapFloorTermVolatility(
                                                    const Date& referenceDate,
                                                    Volatility vol,
                                                    const DayCounter& dc,
                                                    const Calendar& cal,
                                                    BusinessDayConvention bdc)
    : CapFloorTermVolatilityStructure(referenceDate, cal, bdc, dc),
      volatility_(boost::shared_ptr<Quote>(new SimpleQuote(vol))) {}

    Volatility ConstantCapFloorTermVolatility::volatilityImpl(Time,
                                                              Rate) const {
        return volatility_->value();
    }

}