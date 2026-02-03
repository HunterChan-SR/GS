#ifndef CRYPTO_H
#define CRYPTO_H

#include "logger/logger.h"
#include "data_tools/data_struct/data_struct.h"
#include "data_tools/data_generater/data_generater.h"

/**
 * 支持<=64位整数的素数域运算
 * @brief Class representing a number in a prime field.
 * @tparam T The underlying integer type.
 */
template <typename T>
class PrimeFieldNumber
{
private:
    T value;
    T modulus;

    bool check_modulus(const PrimeFieldNumber &other) const
    {
        return modulus == other.modulus;
    }

public:
    PrimeFieldNumber(T val, T mod) : value(val % mod), modulus(mod)
    {
        // if (mod <= 1)
        //     throw std::invalid_argument("Modulus must be > 1");
    }
    /**
     * 构造函数 随机产生value
     * @param mod
     */
    static PrimeFieldNumber<T> random(T mod)
    {
        return PrimeFieldNumber<T>(random_uint64() % mod, mod);
    }

    /**
     * 加法运算
     */
    PrimeFieldNumber operator+(const PrimeFieldNumber &o) const
    {
        if (!check_modulus(o))
            throw std::invalid_argument("Modulus mismatch");
        return {(value + o.value) % modulus, modulus};
    }

    /**
     * 减法运算
     */
    PrimeFieldNumber operator-(const PrimeFieldNumber &o) const
    {
        if (!check_modulus(o))
            throw std::invalid_argument("Modulus mismatch");
        return {(value + modulus - o.value) % modulus, modulus};
    }

    /**
     * 负值
     */
    PrimeFieldNumber operator-() const
    {
        return {(modulus - value) % modulus, modulus};
    }

    /**
     * 乘法运算
     */
    PrimeFieldNumber operator*(const PrimeFieldNumber &o) const
    {
        if (!check_modulus(o))
            throw std::invalid_argument("Modulus mismatch");

        using Wide = __uint128_t;
        return {
            static_cast<T>((Wide)value * o.value % modulus),
            modulus};
    }

    /**
     * 指数运算
     */
    PrimeFieldNumber pow(uint64 exp) const
    {
        T result = 1;
        T base = value;

        while (exp)
        {
            if (exp & 1)
                result = (result * base) % modulus;
            base = (base * base) % modulus;
            exp >>= 1;
        }
        return {result, modulus};
    }

    /**
     * 指数运算
     */
    PrimeFieldNumber pow(const PrimeFieldNumber &exp) const
    {
        if (!check_modulus(exp))
            throw std::invalid_argument("Modulus mismatch");
        return pow(exp.value);
    }

    /**
     * 求逆元
     */
    PrimeFieldNumber mod_inverse() const
    {
        // Fermat: a^(p-2) mod p
        return pow(modulus - 2);
    }

    /**
     * <
     */
    bool operator<(const PrimeFieldNumber &o) const
    {
        if (!check_modulus(o))
            throw std::invalid_argument("Modulus mismatch");
        return value < o.value;
    }

    /**
     * ==
     */
    bool operator==(const PrimeFieldNumber &o) const
    {
        if (!check_modulus(o))
            throw std::invalid_argument("Modulus mismatch");
        return value == o.value;
    }

    /**
     * 首位符号位 msb
     */
    PrimeFieldNumber msb(){
        
    }


    /**
     * get value
     */
    T get_value() const
    {
        return value;
    }

    /**
     * get modulus
     */
    T get_modulus() const
    {
        return modulus;
    }
};

#endif // CRYPTO_H