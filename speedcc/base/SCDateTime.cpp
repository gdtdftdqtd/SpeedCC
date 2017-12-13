

#include <cstdlib>
#include <climits>
#include <sys/time.h>

#include "SCDateTime.h"
#include "SCString.h"
#include "SCSystem.h"

#include "../platform/SCOSSystem.h"

namespace SpeedCC
{
    enum
    {
        SECS_PER_DAY = 86400,
        MSECS_PER_DAY = 86400000,
        SECS_PER_HOUR = 3600,
        MSECS_PER_HOUR = 3600000,
        SECS_PER_MIN = 60,
        MSECS_PER_MIN = 60000,
        TIME_T_MAX = 2145916799,  // int maximum 2037-12-31T23:59:59 UTC
        JULIAN_DAY_FOR_EPOCH = 2440588 // result of julianDayFromDate(1970, 1, 1)
    };
    
    static const char s_MonthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    bool SCDateTime::Date::isValid() const
    {
        return (nYear == 0) ?  false : (nDay > 0 && nMonth > 0 && nMonth <= 12) &&
        (nDay <= s_MonthDays[nMonth] || (nDay == 29 && nMonth == 2 && SCDateTime::isLeapYear(nYear)));
    }
    
    SCDateTime::SCDateTime()
    {
        this->now();
    }
    
    SCDateTime::SCDateTime(const SCString& strDateTime,const SCString& strFormat)
    {
        struct tm tb;
        
        struct timeval tv;
        ::gettimeofday(&tv, NULL);
        
        ::memset(&tb, 0, sizeof(struct tm));
        if(::strptime(strDateTime, strFormat, &tb))
        {
            Date d = {tb.tm_year+1900,tb.tm_mon+1,tb.tm_mday};
            Time t1 = {tb.tm_hour,tb.tm_min,tb.tm_sec,(int)(tv.tv_usec/1000)};
            
            _jd = SCDateTime::convertDate2JD(d);
            _nMillSecOfDay = t1.getMillSecOfDay();
            _nOffsetSecUTC = (int)tb.tm_gmtoff;
            
            if(tb.tm_isdst>0)
            {
                _dstStatus = DST_YES;
            }
            else if(tb.tm_isdst==0)
            {
                _dstStatus = DST_NO;
            }
            else
            {
                _dstStatus = DST_UNKNOWN;
            }
        }
        else
        {
            SCLog("datetime '%s' or format '%s' incorrect",strDateTime.c_str(),strFormat.c_str());
            this->now();
        }
    }
    
    SCDateTime::SCDateTime(const SCDateTime::Date& d,const SCDateTime::Time& t)
    {
        this->now();
        
        if(d.isValid())
        {
            _jd = SCDateTime::convertDate2JD(d);
            _nMillSecOfDay = t.getMillSecOfDay();
            this->fixedTime();
        }
    }
    
    SCDateTime::SCDateTime(const SCDateTime& dt):
    _jd(dt._jd),
    _nMillSecOfDay(dt._nMillSecOfDay),
    _nOffsetSecUTC(dt._nOffsetSecUTC),
    _dstStatus(dt._dstStatus)
    {
    }
    
    SCDateTime::SCDateTime(const time_t& t)
    {
        this->setDatetime(t);
    }
    
    SCDateTime::~SCDateTime()
    {
        
    }
    
    void SCDateTime::now()
    {
        time_t t = ::time(NULL);
        
        this->setDatetime(t);
    }
    
    SCDateTime& SCDateTime::operator=(const SCDateTime& dt)
    {
        _jd = dt._jd;
        _nMillSecOfDay = dt._nMillSecOfDay;
        _nOffsetSecUTC = dt._nOffsetSecUTC;
        _dstStatus = dt._dstStatus;
        
        return *this;
    }
    
    bool SCDateTime::setDatetime(const time_t& t)
    {
        struct timeval tv;
        ::gettimeofday(&tv, NULL);
        struct tm* tb = ::localtime(&t);
        
        Date d = {tb->tm_year+1900,tb->tm_mon+1,tb->tm_mday};
        Time t1 = {tb->tm_hour,tb->tm_min,tb->tm_sec,(int)(tv.tv_usec/1000)};
        
        _jd = SCDateTime::convertDate2JD(d);
        _nMillSecOfDay = t1.getMillSecOfDay();
        _nOffsetSecUTC = (int)tb->tm_gmtoff;
        
        if(tb->tm_isdst>0)
        {
            _dstStatus = DST_YES;
        }
        else if(tb->tm_isdst==0)
        {
            _dstStatus = DST_NO;
        }
        else
        {
            _dstStatus = DST_UNKNOWN;
        }
        
        return true;
    }
    
    bool SCDateTime::setMilliSeconds(const int nMillSec)
    {
        SCASSERT(nMillSec>=0 && nMillSec<1000);
        
        bool bRet = false;
        
        if(nMillSec>=0 && nMillSec<1000)
        {
            Time t(_nMillSecOfDay);
            t.nMillSeconds = nMillSec;
            
            _nMillSecOfDay = t.getMillSecOfDay();
            
            bRet = true;
        }
        
        return bRet;
    }
    
    
    bool SCDateTime::setSeconds(const int nSeconds)
    {
        SCASSERT(nSeconds>=0 && nSeconds<60);
        
        bool bRet = false;
        
        if(nSeconds>=0 && nSeconds<60)
        {
            Time t(_nMillSecOfDay);
            t.nSeconds = nSeconds;
            
            _nMillSecOfDay = t.getMillSecOfDay();
            
            bRet = true;
        }
        
        return bRet;
    }
    
    bool SCDateTime::setMinute(const int nMinute)
    {
        SCASSERT(nMinute>=0 && nMinute<60);
        
        bool bRet = false;
        
        if(nMinute>=0 && nMinute<60)
        {
            Time t(_nMillSecOfDay);
            t.nMinute = nMinute;
            
            _nMillSecOfDay = t.getMillSecOfDay();
            
            bRet = true;
        }
        
        return bRet;
    }
    
    bool SCDateTime::setHour(const int nHour)
    {
        SCASSERT(nHour>=0 && nHour<24);
        
        bool bRet = false;
        
        if(nHour>=0 && nHour<24)
        {
            Time t(_nMillSecOfDay);
            t.nHour = nHour;
            
            _nMillSecOfDay = t.getMillSecOfDay();
            
            bRet = true;
        }
        
        return bRet;
    }
    
    bool SCDateTime::setDayOfMonth(const int nDay)
    {
        SCASSERT(nDay>0 && nDay<32);
        
        bool bRet = false;
        
        if(nDay>0 && nDay<32)
        {
            Date d(_jd);
            
            d.nDay = nDay;
            
            if(d.isValid())
            {
                _jd = SCDateTime::convertDate2JD(d);
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    bool SCDateTime::setMonth(const int nMonth)
    {
        SCASSERT(nMonth>0 && nMonth<13);
        
        bool bRet = false;
        
        if(nMonth>0 && nMonth<13)
        {
            Date d(_jd);
            
            d.nMonth = nMonth;
            
            if(d.isValid())
            {
                _jd = SCDateTime::convertDate2JD(d);
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    bool SCDateTime::setYear(const int nYear)
    {
        bool bRet = false;
        
        Date d(_jd);
        
        d.nYear = nYear;
        
        if(d.isValid())
        {
            _jd = SCDateTime::convertDate2JD(d);
            bRet = true;
        }
        
        return bRet;
    }
    
    void SCDateTime::fixedTime()
    {
        if(_nMillSecOfDay<0)
        {
            int nRemainMSec = MSECS_PER_DAY + (_nMillSecOfDay % MSECS_PER_DAY);
            int nDays = ::abs(_nMillSecOfDay / MSECS_PER_DAY);
            
            _nMillSecOfDay = nRemainMSec;
            _jd -= nDays + 1;
        }
        else if(_nMillSecOfDay>MSECS_PER_DAY)
        {
            int nRemainMSec = _nMillSecOfDay % MSECS_PER_DAY;
            int nDays = _nMillSecOfDay / MSECS_PER_DAY;
            
            _nMillSecOfDay = nRemainMSec;
            _jd += nDays;
        }
    }
    
    SCDateTime SCDateTime::addMilliSeconds(const int nMillSecond)
    {
        if(nMillSecond)
        {
            _nMillSecOfDay += nMillSecond;
            this->fixedTime();
        }
        
        return *this;
    }
    
    SCDateTime SCDateTime::addSeconds(const int nSeconds)
    {
        return this->addMilliSeconds(nSeconds*1000);
    }
    
    SCDateTime SCDateTime::addMinute(const int nMinute)
    {
        return this->addMilliSeconds(nMinute*60*1000);
    }
    
    SCDateTime SCDateTime::addHour(const int nHour)
    {
        return this->addMilliSeconds(nHour*60*60*1000);
    }
    
    SCDateTime SCDateTime::addDay(const int nDay)
    {
        return this->addMilliSeconds(nDay*24*60*60*1000);
    }
    
    SCDateTime SCDateTime::addMonth(int nMonth)
    {
        if(nMonth)
        {
            Date dt(_jd);
            int y = dt.nYear;
            int m = dt.nMonth;
            int d = dt.nDay;
            
            int old_y = y;
            
            bool increasing = nMonth > 0;
            
            while (nMonth != 0) {
                if (nMonth < 0 && nMonth + 12 <= 0)
                {
                    y--;
                    nMonth+=12;
                }
                else if (nMonth < 0)
                {
                    m+= nMonth;
                    nMonth = 0;
                    if (m <= 0)
                    {
                        --y;
                        m += 12;
                    }
                }
                else if (nMonth - 12 >= 0)
                {
                    y++;
                    nMonth -= 12;
                }
                else if (m == 12)
                {
                    y++;
                    m = 0;
                }
                else
                {
                    m += nMonth;
                    nMonth = 0;
                    if (m > 12) {
                        ++y;
                        m -= 12;
                    }
                }
            }
            
            // was there a sign change?
            if ((old_y > 0 && y <= 0) ||
                (old_y < 0 && y >= 0))
            {
                // yes, adjust the date by +1 or -1 years
                y += increasing ? +1 : -1;
            }
            
            _jd = SCDateTime::convertDate2JD(SCDateTime::fixedDate(y,m,d));
        }
        
        return *this;
    }
    
    SCDateTime SCDateTime::addYear(const int nYear)
    {
        Date pd = SCDateTime::convertJD2Date(_jd);
        
        int old_y = pd.nYear;
        pd.nYear += nYear;
        
        // was there a sign change?
        if ((old_y > 0 && pd.nYear <= 0) ||
            (old_y < 0 && pd.nYear >= 0))
        {
            // yes, adjust the date by +1 or -1 years
            pd.nYear += nYear > 0 ? +1 : -1;
        }
        
        auto d = SCDateTime::fixedDate(pd.nYear, pd.nMonth, pd.nDay);
        _jd = SCDateTime::convertDate2JD(d);
        
        return *this;
    }
    
    int SCDateTime::getYear() const
    {
        return SCDateTime::convertJD2Date(_jd).nYear;
    }
    
    int SCDateTime::getMonth() const
    {
        return SCDateTime::convertJD2Date(_jd).nMonth;
    }
    
    // Returns the week number (1 to 53)
    int SCDateTime::getWeekCountOfYear() const
    {
        int year = this->getYear();
        int yday = this->getDayOfYear();
        int wday = this->getDayOfWeek();
        
        int week = (yday - wday + 10) / 7;
        
        if (week == 0)
        {
            // last week of previous year
            --year;
            week = (yday + 365 + (SCDateTime::isLeapYear(year) ? 1 : 0) - wday + 10) / 7;
            SCASSERT(week == 52 || week == 53);
        }
        else if (week == 53)
        {
            // maybe first week of next year
            int w = (yday - 365 - (SCDateTime::isLeapYear(year) ? 1 : 0) - wday + 10) / 7;
            if (w > 0) {
                ++year;
                week = w;
            }
            SCASSERT(week == 53 || week == 1);
        }
        
        return week;
    }
    
    // Returns the number of days in the month (28 to 31)
    int SCDateTime::getDayCountOfMonth() const
    {
        const Date pd = SCDateTime::convertJD2Date(_jd);
        
        return (pd.nMonth == 2 && SCDateTime::isLeapYear(pd.nYear)) ?  29 : s_MonthDays[pd.nMonth];
    }
    
    // Returns the number of days in the year (365 or 366)
    int SCDateTime::getDayCountOfYear() const
    {
        return SCDateTime::isLeapYear(convertJD2Date(_jd).nYear) ? 366 : 365;
    }
    
    SCString SCDateTime::getMonthName(int nMonth,const bool bShort) const
    {
        if(nMonth<0 || nMonth>12)
        {
            nMonth = 0;
        }
        
        char buf[128] = {0};
        const int m = (nMonth==0 ? this->getMonth() : nMonth);
        
        ::scGetMonthName(buf,SC_ARRAY_LENGTH(buf),m,bShort);
        
        return buf;
    }
    
    SCString SCDateTime::getWeekName(int nWeek,const bool bShort) const
    {
        if(nWeek<0 || nWeek>7)
        {
            nWeek = 0;
        }
        
        char buf[128] = {0};
        const int w = nWeek==0 ? this->getDayOfWeek() : nWeek;
        
        ::scGetWeekName(buf,SC_ARRAY_LENGTH(buf),w,bShort);
        
        return buf;
    }
    
    int SCDateTime::getDayOfMonth() const
    {
        return SCDateTime::convertJD2Date(_jd).nDay;
    }
    
    int SCDateTime::getDayOfYear() const
    {
        return (int)(_jd - SCDateTime::convertDate2JD(Date(this->getYear(), 1, 1)) + 1);
    }
    
    SCDateTime SCDateTime::toUTC()
    {
        if(_nOffsetSecUTC)
        {
            this->addSeconds(_nOffsetSecUTC);
            _nOffsetSecUTC = 0;
        }
        
        return *this;
    }
    
    SCDateTime SCDateTime::toLocal()
    {
        time_t t  = ::time(NULL);
        struct tm* tb = ::localtime(&t);
        
        if(tb->tm_gmtoff!=_nOffsetSecUTC)
        {
            this->addSeconds((int)(tb->tm_gmtoff-_nOffsetSecUTC));
            _nOffsetSecUTC = (int)tb->tm_gmtoff;
        }
        
        return *this;
    }
    
    SCDateTimeSpan SCDateTime::operator-(const SCDateTime& dt) const
    {
        const int nDiffDay = (int)(_jd - dt._jd);
        int nDiffSec = (_nMillSecOfDay - dt._nMillSecOfDay)/1000;
        nDiffSec += _nOffsetSecUTC - dt._nOffsetSecUTC;
        
        return (nDiffDay*24*60*60 + nDiffSec);
    }
    
    SCDateTime::Date SCDateTime::getDate() const
    {
        return SCDateTime::convertJD2Date(_jd);
    }
    
    SCDateTime::Time SCDateTime::getTime() const
    {
        return SCDateTime::Time(_nMillSecOfDay);
    }
    
    INT64 SCDateTime::getStamp() const
    {
        if(this->getDate().isValid() && this->getTime().isValid())
        {
            return (((INT64)_jd)*24*60*60 + this->getHour()*60*60 + this->getMinute()*60 + this->getSeconds());
        }
        
        return NullTime;
    }
    
    SCString SCDateTime::getFormatString(SCString strFormat) const
    {
        if(strFormat.isEmpty())
        {
            strFormat = "%Y-%m-%d %H:%M:%S";
        }
        struct tm tb;
        
        Date date = this->getDate();
        Time time = this->getTime();
        
        tb.tm_year = date.nYear;
        tb.tm_mon = date.nMonth;
        tb.tm_mday = date.nDay;
        
        tb.tm_hour = time.nHour;
        tb.tm_min = time.nMinute;
        tb.tm_sec = time.nSeconds;
        
        tb.tm_gmtoff = _nOffsetSecUTC;
        
        char szBuf[256+1] = {0};
        
        if(::strftime(szBuf, SC_ARRAY_LENGTH(szBuf), strFormat.c_str(), &tb))
        {
            return szBuf;
        }
        
        return "";
    }
    
    ////-----
    
    SCDateTime::Date SCDateTime::fixedDate(const int y, const int m, const int d)
    {
        Date da(y, m, 1);
        Time t(0,0,0,0);
        SCDateTime dt(da,t);
        
        return Date(y,m,MIN(d,dt.getDayCountOfMonth()));
    }
    
    SCDateTime::Date SCDateTime::convertJD2Date(INT64 julianDay)
    {
        /*
         * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
         * This formula is correct for all julian days, when using mathematical integer
         * division (round to negative infinity), not c++11 integer division (round to zero)
         */
        INT64 a = julianDay + 32044;
        INT64 b = floordiv(4 * a + 3, 146097);
        INT64    c = a - floordiv(146097 * b, 4);
        
        INT64    d = floordiv(4 * c + 3, 1461);
        INT64    e = c - floordiv(1461 * d, 4);
        INT64    m = floordiv(5 * e + 2, 153);
        
        int    day = (int)(e - floordiv(153 * m + 2, 5) + 1);
        int    month = (int)(m + 3 - 12 * floordiv(m, 10));
        int    year = (int)(100 * b + d - 4800 + floordiv(m, 10));
        
        // Adjust for no year 0
        if (year <= 0)
        {
            --year ;
        }
        
        const Date result = { year, month, day };
        
        return result;
    }
    
    INT64 SCDateTime::convertDate2JD(SCDateTime::Date date)
    {
        // Adjust for no year 0
        if (date.nYear < 0)
        {
            ++date.nYear;
        }
        
        /*
         * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
         * This formula is correct for all julian days, when using mathematical integer
         * division (round to negative infinity), not c++11 integer division (round to zero)
         */
        int    a = floordiv(14 - date.nMonth, 12);
        INT64 y = (INT64)date.nYear + 4800 - a;
        int    m = date.nMonth + 12 * a - 3;
        
        return date.nDay + floordiv(153 * m + 2, 5) + 365 * y + floordiv(y, 4) - floordiv(y, 100) + floordiv(y, 400) - 32045;
    }
    
}

