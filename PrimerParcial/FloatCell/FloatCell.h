#ifndef FLOATCELL_H
#define FLOATCELL_H

class FloatCell {
public:
    explicit FloatCell(float newValue = 0);
    FloatCell(const FloatCell &rhs);
    FloatCell(FloatCell &&rhs) noexcept;
    ~FloatCell() = default;

    FloatCell &operator=(const FloatCell &rhs);
    FloatCell &operator=(FloatCell &&rhs) noexcept;

    // Overloaded assignment operator to accept primitive int
    FloatCell &operator=(float rhs);

    float getValue() const;
    void setValue(float newValue);

private:
    float storedValue;
};

#endif  // FLOATCELL_H