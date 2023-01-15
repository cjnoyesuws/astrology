#ifndef DEGMIN_H
#define DEGMIN_H
#include "astro.h"
#include "cstring"

using rapidjson, std;

class DegMin
{
    public:
        DegMin() { memset(&m_val,0,sizeof(DEG_MIN));}
        DegMin(DEG_MIN &val) { m_val = val;}
        virtual ~DegMin() {}
        DEG_MIN &getVal() {return m_val;}
        double toDouble() {
            double val = (double)m_val.degrees;
            val = val + m_val.minutes/60.0;
            if (m_val.dir=='S' || m_val.dir=='E') {
                val = val * -1;
            }
            return val;
         }
         void fromDouble(double val, const char dirs[2]) {
            m_val.degrees = (int)abs(val);
            if (val > 0.0) {
                m_val.dir=dirs[0];
            }
            else {
                m_val.dir=dirs[1];
            }
            val = abs(val);
            val -= (double)val;
            m_val.minutes = (short)(val * 60.0);
         }
    protected:

    private:
        DEG_MIN m_val;
};

#endif // DEGMIN_H
