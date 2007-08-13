/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007 Ferdinando Ametrano

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

#include <ql/termstructures/blackatmvolcurve.hpp>

namespace QuantLib {

    BlackAtmVolCurve::BlackAtmVolCurve(const DayCounter& dc)
    : TermStructure(dc) {}

    BlackAtmVolCurve::BlackAtmVolCurve(const Date& refDate,
                                       const Calendar& cal,
                                       const DayCounter& dc)
    : TermStructure(refDate, cal, dc) {}

    BlackAtmVolCurve::BlackAtmVolCurve(Natural settlDays,
                                       const Calendar& cal,
                                       const DayCounter& dc)
    : TermStructure(settlDays, cal, dc) {}

    Volatility BlackAtmVolCurve::atmVol(const Date& d,
                                        bool extrapolate) const {
        Time t = timeFromReference(d);
        return atmVol(t, extrapolate);
    }

    Volatility BlackAtmVolCurve::atmVol(Time t,
                                        bool extrapolate) const {
        checkRange(t, extrapolate);
        return atmVolImpl(t);
    }

    Real BlackAtmVolCurve::atmVariance(const Date& d,
                                       bool extrapolate) const {
        Time t = timeFromReference(d);
        return atmVariance(t, extrapolate);
    }

    Real BlackAtmVolCurve::atmVariance(Time t,
                                       bool extrapolate) const {
        checkRange(t, extrapolate);
        return atmVarianceImpl(t);
    }

    void BlackAtmVolCurve::accept(AcyclicVisitor& v) {
        Visitor<BlackAtmVolCurve>* v1 =
            dynamic_cast<Visitor<BlackAtmVolCurve>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            QL_FAIL("not a BlackAtmVolCurve visitor");
    }

}
