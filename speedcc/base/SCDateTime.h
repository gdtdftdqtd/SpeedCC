

#ifndef __SC__FSDATETIME_H__
#define __SC__FSDATETIME_H__

#include <time.h>
#include <limits>
#include "SCMacroDef.h"

namespace SpeedCC
{
    class SCString;
    class SCDateTimeSpan;
    
    class SCDateTime
    {
    public:
        enum {NullTime = -1};
        enum DSTStatus
        {
            DST_YES,
            DST_NO,
            DST_UNKNOWN,
        };
        
        struct Date
        {
            int nYear;
            int nMonth;
            int nDay;
            
            Date():
            nYear(0),
            nMonth(0),
            nDay(0)
            {}
            
            Date(const int y,const int m,const int d):
            nYear(y),
            nMonth(m),
            nDay(d)
            {}
            
            Date(const INT64 jd) { *this = SCDateTime::convertJD2Date(jd);}
            
            bool isValid() const;
            int getDayCountOfMonth() const;
            int getDayCountOfYear() const;
        };
        
        struct Time
        {
            int nHour;
            int nMinute;
            int nSeconds;
            int nMillSeconds;
            
            Time():
            nHour(0),
            nMinute(0),
            nSeconds(0),
            nMillSeconds(0)
            {}
            
            Time(const int h,const int m,const int s,const int ms):
            nHour(h),
            nMinute(m),
            nSeconds(s),
            nMillSeconds(ms)
            {}
            
            Time(const int nMillSecOfDay):
            nHour(nMillSecOfDay/(1000*60*60)),
            nMinute((nMillSecOfDay/1000)%(60*60)/60),
            nSeconds((nMillSecOfDay/1000)%60),
            nMillSeconds(nMillSecOfDay%1000)
            {}
            
            inline bool isValid() const {return (nHour<24 && nHour>=0 &&
                                                 nMinute<60 && nMinute>=0 &&
                                                 nSeconds<60 && nSeconds>=0 &&
                                                 nMillSeconds<1000 && nMillSeconds>=0);}
            
            inline int getMillSecOfDay() const
            {
                return this->isValid() ? ((nHour*(60*60) + nMinute*60 + nSeconds)*1000 + nMillSeconds) : NullTime;
            }
            
            inline int getSecOfDay() const
            {
                return this->isValid() ? (nHour*(60*60) + nMinute*60 + nSeconds) : NullTime;
            }
        };
        
    public:
        SCDateTime();
        
        // specifier refer to: https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Time-String-Parsing.html
        SCDateTime(const SCString& strDateTime,const SCString& strFormat);
        SCDateTime(const SCDateTime& dt);
        SCDateTime(const SCDateTime::Date& d,const SCDateTime::Time& t=Time(0,0,0,0));
        SCDateTime(const time_t& time);
        ~SCDateTime();
        
        SCDateTime& operator=(const SCDateTime& dt);
        
        SCDateTime addMilliSeconds(const int nMillSecond);
        SCDateTime addSeconds(const int nSeconds);
        SCDateTime addMinute(const int nMinute);
        SCDateTime addHour(const int nHour);
        SCDateTime addDay(const int nDay);
        SCDateTime addMonth(int nMonth);
        SCDateTime addYear(const int nYear);
        
        bool setMilliSeconds(const int nMillSec);
        bool setSeconds(const int nSeconds);
        bool setMinute(const int nMinute);
        bool setHour(const int nHour);
        // begin from 1
        bool setDayOfMonth(const int nDay);
        bool setMonth(const int nMonth);
        bool setYear(const int nYear);
        
        int getYear() const;
        int getMonth() const;
        
        inline int getHour() const { return Time(_nMillSecOfDay).nHour; }
        inline int getMinute() const { return Time(_nMillSecOfDay).nMinute; }
        inline int getSeconds() const { return Time(_nMillSecOfDay).nSeconds; }
        inline int getMilleSeconds() const { return _nMillSecOfDay%1000; }
        
        Date getDate() const;
        Time getTime() const;
        bool setDate(const Date& date);
        bool setTime(const Time& time);
        
        SCString getMonthName(int nMonth=0,const bool bShort = true) const;
        SCString getWeekName(int nWeek=0,const bool bShort = true) const;
        
        // base 1, sunday is the first day of week
        inline int getDayOfWeek() const { return (((_jd >= 0) ? ((_jd % 7) + 1) : (((_jd + 1) % 7) + 7)) % 7 + 1); }
        
        // base 1
        int getDayOfMonth() const;
        
        // base 1
        int getDayOfYear() const;
        
        int getWeekCountOfYear() const;
        int getDayCountOfMonth() const;
        int getDayCountOfYear() const;
        
        bool setDatetime(const time_t& time);
        
        INT64 getStamp() const;
        
        SCDateTime toUTC();
        SCDateTime toLocal();
        
        inline DSTStatus getDSTStatus() const {return _dstStatus;}
        
        void now();
        SCDateTimeSpan operator-(const SCDateTime& dt) const;
        
        // specifier refer to: https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-Time-String-Parsing.html
        SCString getFormatString(const SCString& strFormat) const;
        
        static inline bool isLeapYear(int y)
        {
            if ( y < 1) { ++y; }
            return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        }
        
    private:
        static inline INT64 getDateNull() { return (std::numeric_limits<INT64>::min)();}
        static inline int getTimeNull() {return -1;}
        
        static Date convertJD2Date(INT64 julianDay);
        static INT64 convertDate2JD(SCDateTime::Date date);
        static Date fixedDate(const int y, const int m, const int d);
        
        static inline INT64 floordiv(INT64 a, int b) {return (a - (a < 0 ? b - 1 : 0)) / b;}
        static inline int floordiv(int a, int b) { return (a - (a < 0 ? b - 1 : 0)) / b;}
        
        void fixedTime();
    private:
        int             _nMillSecOfDay; // in milliseconds
        INT64           _jd;
        int             _nOffsetSecUTC;
        DSTStatus       _dstStatus;
    };
    
    class SCDateTimeSpan
    {
    public:
        SCDateTimeSpan():_nSeconds(0){}
        SCDateTimeSpan(const int nSec):_nSeconds(nSec){}
        
        inline int getDays() const { return _nSeconds/(24*60*60); }
        inline int getHours() const { return (_nSeconds%(24*60*60))/(60*60); }
        inline int getMinutes() const { return _nSeconds%(60*60)/60; }
        inline int getSeconds() const { return _nSeconds%60; }
        
    private:
        int     _nSeconds;
    };
}



#endif // __SC__FSDATETIME_H__
