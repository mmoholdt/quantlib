/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2002, 2003 Ferdinando Ametrano
 Copyright (C) 2003, 2004, 2005, 2006 StatPro Italia srl

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

/*! \file blackvolsurface.hpp
    \brief Black volatility (smile) surface
*/

#ifndef quantlib_black_vol_surface_hpp
#define quantlib_black_vol_surface_hpp

#include <ql/termstructures/blackatmvolcurve.hpp>

namespace QuantLib {

    //! Black volatility (smile) surface
    /*! This abstract class defines the interface of concrete
        Black volatility (smile) surface which will
        be derived from this one.

        Volatilities are assumed to be expressed on an annual basis.

    */
    class BlackVolSurface : public BlackAtmVolCurve {
      public:
        /*! \name Constructors
            See the TermStructure documentation for issues regarding
            constructors.
        */
        //@{
        //! default constructor
        /*! \warning term structures initialized by means of this
                     constructor must manage their own reference date
                     by overriding the referenceDate() method.
        */
        BlackVolSurface(const DayCounter& dc = Actual365Fixed());
        //! initialize with a fixed reference date
        BlackVolSurface(const Date& referenceDate,
                        const Calendar& cal = Calendar(),
                        const DayCounter& dc = Actual365Fixed());
        //! calculate the reference date based on the global evaluation date
        BlackVolSurface(Natural settlementDays,
                        const Calendar&,
                        const DayCounter& dc = Actual365Fixed());
        //@}
        virtual Real atmLevel(const Date& maturity) const = 0;
        virtual Real atmLevel(Time maturity) const = 0;
        //! \name Black spot volatility
        //@{
        //! spot volatility
        Volatility volatility(const Date& maturity,
                              Real strike,
                              bool extrapolate = false) const;
        //! spot volatility
        Volatility volatility(Time maturity,
                              Real strike,
                              bool extrapolate = false) const;
        //! spot variance
        Real variance(const Date& maturity,
                      Real strike,
                      bool extrapolate = false) const;
        //! spot variance
        Real variance(Time maturity,
                      Real strike,
                      bool extrapolate = false) const;
        //@}
        //! \name Limits
        //@{
        //! the minimum strike for which the term structure can return vols
        virtual Real minStrike() const = 0;
        //! the maximum strike for which the term structure can return vols
        virtual Real maxStrike() const = 0;
        //@}
        //! \name Visitability
        //@{
        void accept(AcyclicVisitor&);
        //@}
      protected:
        //! \name BlackArtmVolCurve interface
        //@{
        //! spot at-the-money variance calculation
        virtual Real atmVarianceImpl(Time t) const;
        //! spot at-the-money volatility calculation
        virtual Volatility atmVolImpl(Time t) const;
        //@}
        /*! \name Calculations

            These methods must be implemented in derived classes to perform
            the actual volatility calculations. When they are called,
            range check has already been performed; therefore, they must
            assume that extrapolation is required.
        */
        //@{
        //! spot at-the-money variance calculation
        virtual Real varianceImpl(Time t,
                                  Real strike) const = 0;
        //! spot at-the-money volatility calculation
        virtual Volatility volImpl(Time t,
                                   Real strike) const = 0;
        //@}
      private:
        void checkRange(const Date& d,
                        Real strike,
                        bool extrapolate) const;
        void checkRange(Time t,
                        Real strike,
                        bool extrapolate) const;
    };

}

#endif
