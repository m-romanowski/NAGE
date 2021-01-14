#version 450 core

#define MINUTES 60
#define HALF_MINUTES MINUTES / 2
#define IS_MORNING(x) (x == 5) ? true : false
#define IS_MIDDAY(x) (x > 5 && x < 20) ? true : false
#define IS_EVENING(x) (x == 20) ? true : false
#define IS_MIDNIGHT(x) (x > 20 || x < 5) ? true : false

struct DayNightCycles
{
    vec3 morning;
    vec3 midday;
    vec3 evening;
    vec3 midnight;

    int hour;
    int minute;
    float startStep;
    float stopStep;
};

uniform DayNightCycles cycle;

in vec3 outPos;
out vec4 fragColor;

vec3 lerp(vec3 _from, vec3 _to);
void colorByHour(inout vec3 _cycleArr[2]);
float currStepwise(int _x);

void main()
{
    vec3 cycleColor[2];
    colorByHour(cycleColor);

    /**
     * Smooth Hermite interpolation (smoothstep).
     *
     * clamp(v, hi, lo) = v < lo ? lo : (hi < v) ? hi : v;
     *  - v: the value to constrain
     *  - lo: specify the lower end of the range into which to constrain v
     *  - hi: specify the upper end of the range into which to constrain v
     *
     * smoothstep(edge0, edge1, x)
     * {
     *     // undefined if edge0 ≥ edge1
     *     t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0)
     *     return t * t * (3.0 - 2.0 * t)
     * }
     *
     *  - edge0: the value of the lower edge of the Hermite function
     *  - edge1: the value of the upper edge of the Hermite function
     *  - x: the source value for interpolation
     */
    fragColor = vec4(mix(cycleColor[0], cycleColor[1], smoothstep(cycle.startStep, currStepwise(cycle.minute), outPos.y)), 1.0f);
}

vec3 lerp(vec3 _from, vec3 _to)
{
    /**
     * Linear interpolation (mix).
     *
     * mix(x, y, a) = x * (1 - a) + y * a
     *  - x: the start of the range in which to interpolate
     *  - y: the end of the range in which to interpolate
     *  - a: the value to use to interpolate between x and y
     */
    return mix(_from, _to, cos(cycle.minute * 0.1f) * 0.5f + 0.5f);
}

float currStepwise(int _x)
{
    // y = a * sin(bx)
    float amplitute = cycle.stopStep + 1.0f;
    return (amplitute * sin(((abs(cycle.startStep) / MINUTES) * 2.0f) * _x)) - 1.0f;
}

void updateIfMorning(inout vec3 _cycleArr[2])
{
    if(IS_MORNING(cycle.hour))
    {
        _cycleArr[0] = cycle.morning;
        _cycleArr[1] = cycle.midnight;

        if(cycle.minute > HALF_MINUTES)
        {
            _cycleArr[1] = lerp(cycle.midnight, cycle.midday);
        }
    }
}

void updateIfMidday(inout vec3 _cycleArr[2])
{
    if(IS_MIDDAY(cycle.hour))
    {
        _cycleArr[0] = cycle.midday;
        _cycleArr[1] = cycle.midday;
    }
}

void updateIfEvening(inout vec3 _cycleArr[2])
{
    if(IS_EVENING(cycle.hour))
    {
        _cycleArr[0] = cycle.evening;
        _cycleArr[1] = cycle.midday;

        if(cycle.minute > HALF_MINUTES)
        {
            _cycleArr[1] = lerp(cycle.midday, cycle.midnight);
        }
    }
}

void updateIfMidnight(inout vec3 _cycleArr[2])
{
    if(IS_MIDNIGHT(cycle.hour))
    {
        _cycleArr[0] = cycle.midnight;
        _cycleArr[1] = cycle.midnight;
    }
}

void colorByHour(inout vec3 _cycleArr[2])
{
    updateIfMorning(_cycleArr);
    updateIfMidday(_cycleArr);
    updateIfEvening(_cycleArr);
    updateIfMidnight(_cycleArr);
}
