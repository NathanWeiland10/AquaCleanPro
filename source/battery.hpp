class Battery{
    public:
        Battery(int pinNum, float voltage);

        float getCharge();
    private:
        int pin;
        float voltage;
};