#ifndef MATHTOOLS_H
#define MATHTOOLS_H


class MathTools
{
public:
    MathTools();

    template <typename T>
    static T map(T value, T minIn, T maxIn, T minOut, T maxOut)
    {
        return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
    }
};

#endif // MATHTOOLS_H
